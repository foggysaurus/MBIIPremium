#include "NavMesh.h"

uintptr_t  MoverEntity::entListBaseAddress = 0;
uintptr_t  MoverEntity::entityOffset = 0;
//GRAPH

//GRAPH

//CELL--------------------------------------------------------------------------------------------------------

Cell::Cell(const Vec3_ui8& _loc, Chunk* _parentChunk) : parentChunk(_parentChunk)
{
    loc = World::pack_coordinates(_loc);
}
Cell::Cell(const uint16_t& _loc, Chunk* _parentChunk) :loc(_loc), parentChunk(_parentChunk) {}
Cell::~Cell()
{

}
//gets center (a float vector)
Vec3 Cell::GetCenter()
{
    Vec3_ui8 crd = World::unpack_coordinates(loc);
    return { parentChunk->locationFloat.x + crd.x * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2,
        parentChunk->locationFloat.y + crd.y * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2,
        parentChunk->locationFloat.z + crd.z * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2 };
}

//CELL--------------------------------------------------------------------------------------------------------


//CHUNK--------------------------------------------------------------------------------------------------------

Chunk::Chunk(World* _world, const Vec3_ui8& _locationWorld) : world(_world), chunkLocation(_locationWorld)
{
    world->get_chunk_float_location(locationFloat, chunkLocation);
    index = WorldConstants::WORLD_WIDTH_X_BREADTH * chunkLocation.z + WorldConstants::WORLD_BREADTH_X * chunkLocation.y + chunkLocation.x;
}
Chunk::Chunk(World* _world, const uint32_t& _index) : world(_world) ,    index(_index)
{
    chunkLocation = world->get_chunk_coordinates_from_index(index);
    world->get_chunk_float_location(locationFloat, chunkLocation);

}

Chunk::~Chunk()
{
    for (auto& c : cells)
    {
        delete(c);
    }
}

uint32_t Chunk::get_cell_index(const Vec3_ui8& cellLoc)
{
    return ((cellLoc.z << 10) + (cellLoc.y << 5) + cellLoc.x);
}

Cell* Chunk::add_cell_empty(const Vec3_ui8& cellLoc)
{
    uint32_t i = get_cell_index(cellLoc);

    if (cells[i] == nullptr)
    {
        cells[i] = new Cell(cellLoc, this);
        flags |= ChunkFlags::REFRESH_THIS_CHUNK;
        return cells[i];
    }
    else
        return cells[i];
}
Cell* Chunk::add_cell_empty(const uint16_t& cellLoc)
{
    if (cells[cellLoc] == nullptr)
    {
        cells[cellLoc] = new Cell(cellLoc, this);
        flags |= ChunkFlags::REFRESH_THIS_CHUNK;
        return cells[cellLoc];
    }
    else
        return cells[cellLoc];
}
void Chunk::get_all_neighbors(std::vector<Chunk*>& neighbors)
{
    int8_t offset[3]; 
    for (int i = 0; i < world->findNeighborsAllDX.size(); i++)
    {
        offset[0] = world->findNeighborsAllDX[i]; offset[1] = world->findNeighborsAllDY[i]; offset[2] = world->findNeighborsAllDZ[i];

        Vec3_ui8 nextChunkLoc = chunkLocation;
        nextChunkLoc.x += offset[0]; nextChunkLoc.y += offset[1]; nextChunkLoc.z += offset[2];

        Chunk* nextChunk = world->get_chunk(nextChunkLoc);
        if (nextChunk != nullptr)
            neighbors.push_back(nextChunk);
    }
}

//CHUNK--------------------------------------------------------------------------------------------------------


//WORLD--------------------------------------------------------------------------------------------------------

World::World(const Vec3& _origin, Utils::Tracer* _tracer, uintptr_t _moverEntsAddress, uint32_t _entityOffset) : origin(_origin), tracer(_tracer)
{
    cellMin = -1 * (float)WorldConstants::CELL_SIZE / 2; cellMin.z = 0;
    cellMax = (float)WorldConstants::CELL_SIZE / 2; cellMax.z = 0;

    moverEntsAddress = _moverEntsAddress;
    entityOffset = _entityOffset;

    MoverEntity::entListBaseAddress = _moverEntsAddress;
    MoverEntity::entityOffset = _entityOffset;

    //origin.x -= WorldConstants::CHUNK_LENGTH / 2;
    //origin.y -= WorldConstants::CHUNK_LENGTH / 2;
    //origin.z -= WorldConstants::CHUNK_LENGTH/16;

    validChunks.reserve(64);

    Offsets offset_xp, offset_yp, offset_xn, offset_yn;

    offset_xp.dx = { 1, 1, 1 };
    offset_xp.dy = { 0, 0, 0 };
    offset_xp.dz = { 0, 1, -1, };

    offset_yp.dx = { 0, 0, 0 };
    offset_yp.dy = { 1, 1, 1 };
    offset_yp.dz = { 0, 1, -1, };

    offset_xn.dx = { -1, -1, -1 };
    offset_xn.dy = { 0,   0, 0 };
    offset_xn.dz = { 0,   1, -1 };

    offset_yn.dx = { 0,   0, 0 };
    offset_yn.dy = { -1, -1, -1 };
    offset_yn.dz = { 0,   1, -1 };

    offsetsForPostGen = { offset_xp , offset_yp, offset_xn, offset_yn };

    for (int i = WorldConstants::GRAPH_MESH_MAX_SIZE; i > 0; i--)
        graphNodeSizes.push_back(i);
}

World::~World()
{
    for (auto& ch : chunks)
    {
        delete(ch);
    }
    for (auto& g : graph)
        delete(g.second);
}

uint16_t World::pack_coordinates(const Vec3_ui8& loc)
{
    return (loc.x & 0x1F) | ((loc.y & 0x1F) << 5) | ((loc.z & 0x1F) << 10);
}
Vec3_ui8 World::unpack_coordinates(const uint16_t& packedData)
{
    return { (uint8_t)(packedData & 0x1F), (uint8_t)((packedData >> 5) & 0x1F), (uint8_t)((packedData >> 10) & 0x1F) };
}
uint32_t World::pack_cell_and_chunk(const CellCoordinates& cellCoordinates)
{
    return (cellCoordinates.chunkLocation << 15) | cellCoordinates.cellLocation;
}
CellCoordinates World::unpack_cell_and_chunk(const uint32_t& chunkCell)
{
    return { static_cast<uint32_t>(chunkCell >> 15) , static_cast<uint16_t>(chunkCell & 0x7FFF) };
}

uint32_t World::get_chunk_index(const Vec3_ui8& chunkLocation)
{
    if ((chunkLocation.x < 0 || chunkLocation.x > WorldConstants::WORLD_BREADTH_X - 1)
        || (chunkLocation.y < 0 || chunkLocation.y > WorldConstants::WORLD_WIDTH_Y - 1)
        || (chunkLocation.z < 0 || chunkLocation.z > WorldConstants::WORLD_HEIGHT_Z - 1)
        )
        return -1;
    return (WorldConstants::WORLD_WIDTH_X_BREADTH * chunkLocation.z + WorldConstants::WORLD_BREADTH_X * chunkLocation.y + chunkLocation.x);
}

Vec3_ui8 World::get_chunk_coordinates_from_index(const uint32_t& index)
{
    Vec3_ui8 coords;
    coords.z = index / WorldConstants::WORLD_WIDTH_X_BREADTH;
    uint32_t remainingIndex = index % WorldConstants::WORLD_WIDTH_X_BREADTH;
    coords.y = remainingIndex / WorldConstants::WORLD_BREADTH_X;
    coords.x = remainingIndex % WorldConstants::WORLD_BREADTH_X;
    return coords;
}

void World::get_chunk_float_location(Vec3& locationFloat, const Vec3_ui8& chunkLocation)
{
    locationFloat.x = origin.x + ((float)chunkLocation.x - WorldConstants::WORLD_BREADTH_X / 2) * WorldConstants::CHUNK_LENGTH;
    locationFloat.y = origin.y + ((float)chunkLocation.y - WorldConstants::WORLD_WIDTH_Y / 2) * WorldConstants::CHUNK_LENGTH;
    locationFloat.z = origin.z + ((float)chunkLocation.z - WorldConstants::WORLD_HEIGHT_Z / 2) * WorldConstants::CHUNK_LENGTH;
}

Cell* World::get_cell(const Vec3_ui8& chunkLoc, const Vec3_ui8& cellLoc)
{
    int i = get_chunk_index(chunkLoc);
    if (i == -1)
        return nullptr;
    Chunk* ch = chunks[i];
    if (ch == nullptr)
        return nullptr;
    return ch->cells[ch->get_cell_index(cellLoc)];
}
Cell* World::get_cell(const uint32_t& chunkLoc, const uint16_t& cellLoc)
{
    if (chunkLoc > WorldConstants::WORLD_SIZE - 1)
        return nullptr;

    if (chunkLoc == -1 || cellLoc == -1)
        return nullptr;

    Chunk* ch = chunks[chunkLoc];

    if (ch == nullptr)
        return nullptr;

    if (cellLoc > WorldConstants::CHUNK_ARRAY_SIZE - 1)
        return nullptr;

    return ch->cells[cellLoc];
}
Cell* World::get_cell(const CellCoordinates& cellCoordinates)
{
    if (cellCoordinates.chunkLocation > WorldConstants::WORLD_SIZE - 1)
        return nullptr;

    if (cellCoordinates.chunkLocation == -1 || cellCoordinates.cellLocation == -1)
        return nullptr;

    Chunk* ch = chunks[cellCoordinates.chunkLocation];

    if (ch == nullptr)
        return nullptr;

    if (cellCoordinates.cellLocation > WorldConstants::CHUNK_ARRAY_SIZE - 1)
        return nullptr;

    return ch->cells[cellCoordinates.cellLocation];
}
Cell* World::get_cell(const uint32_t& cellPacked)
{
    CellCoordinates cellCoordinates = unpack_cell_and_chunk(cellPacked);
    if (cellCoordinates == 0)
        return nullptr;
    if (cellCoordinates.chunkLocation > WorldConstants::WORLD_SIZE - 1)
        return nullptr;

    if (cellCoordinates.chunkLocation == -1 || cellCoordinates.cellLocation == -1)
        return nullptr;

    Chunk* ch = chunks[cellCoordinates.chunkLocation];

    if (ch == nullptr)
        return nullptr;

    if (cellCoordinates.cellLocation > WorldConstants::CHUNK_ARRAY_SIZE - 1)
        return nullptr;

    return ch->cells[cellCoordinates.cellLocation];
}
Cell* World::get_cell(const Vec3& position, const int& depth, CellCoordinates&cellCoordinates)
{
    Vec3 relativeCellPosition;
    Vec3 chunkPosition;
    Cell* candidate = nullptr;

    for (int i = 0; i <= depth; i++)
    {
        float halfCellSize = WorldConstants::CELL_SIZE / 2;
        relativeCellPosition.x = ((position.x - origin.x - halfCellSize) / WorldConstants::CELL_SIZE);
        relativeCellPosition.y = ((position.y - origin.y - halfCellSize) / WorldConstants::CELL_SIZE);
        relativeCellPosition.z = ((position.z - origin.z - i * WorldConstants::CELL_SIZE - 0.001 - halfCellSize) / WorldConstants::CELL_SIZE);

        relativeCellPosition.x = std::round(relativeCellPosition.x);
        relativeCellPosition.y = std::round(relativeCellPosition.y);
        relativeCellPosition.z = std::round(relativeCellPosition.z);

        chunkPosition.x = int(relativeCellPosition.x / WorldConstants::CHUNK_SIZE);
        chunkPosition.y = int(relativeCellPosition.y / WorldConstants::CHUNK_SIZE);
        chunkPosition.z = int(relativeCellPosition.z / WorldConstants::CHUNK_SIZE);

        if (relativeCellPosition.x < 0)
            chunkPosition.x -= 1;
        if (relativeCellPosition.y < 0)
            chunkPosition.y -= 1;
        if (relativeCellPosition.z < 0)
            chunkPosition.z -= 1;

        relativeCellPosition.x -= chunkPosition.x * WorldConstants::CHUNK_SIZE;
        relativeCellPosition.y -= chunkPosition.y * WorldConstants::CHUNK_SIZE;
        relativeCellPosition.z -= chunkPosition.z * WorldConstants::CHUNK_SIZE;

        if (relativeCellPosition.x == 32)
        {
            relativeCellPosition.x = 0;
            chunkPosition.x += 1;
        }
        if (relativeCellPosition.y == 32)
        {
            relativeCellPosition.y = 0;
            chunkPosition.y += 1;
        }
        if (relativeCellPosition.z == 32)
        {
            relativeCellPosition.z = 0;
            chunkPosition.z += 1;
        }

        chunkPosition.x += WorldConstants::WORLD_BREADTH_X / 2;
        chunkPosition.y += WorldConstants::WORLD_WIDTH_Y / 2;
        chunkPosition.z += WorldConstants::WORLD_HEIGHT_Z / 2;

        if ((chunkPosition.x < 0 || chunkPosition.x > WorldConstants::WORLD_BREADTH_X - 1)
            || (chunkPosition.y < 0 || chunkPosition.y > WorldConstants::WORLD_WIDTH_Y - 1)
            || (chunkPosition.z < 0 || chunkPosition.z > WorldConstants::WORLD_HEIGHT_Z - 1)
            )
        {
            cellCoordinates.chunkLocation = -1;
            cellCoordinates.cellLocation = -1;
            return nullptr;
        }

        Vec3_ui8 chunkLocationTrue; 
        chunkLocationTrue.x = chunkPosition.x;
        chunkLocationTrue.y = chunkPosition.y;
        chunkLocationTrue.z = chunkPosition.z;

        Vec3_ui8 cellLocationTrue;
        cellLocationTrue.x = relativeCellPosition.x;
        cellLocationTrue.y = relativeCellPosition.y;
        cellLocationTrue.z = relativeCellPosition.z;

        if (i == 0)
        {
            cellCoordinates.chunkLocation = get_chunk_index(chunkLocationTrue);
            cellCoordinates.cellLocation = pack_coordinates(cellLocationTrue);
        }

        if (chunks[get_chunk_index(chunkLocationTrue)] != nullptr)
            candidate = chunks[get_chunk_index(chunkLocationTrue)]->cells[pack_coordinates(cellLocationTrue)];
        if (candidate && (candidate->flags & CellFlags::WALKABLE))
        {
            cellCoordinates.chunkLocation = get_chunk_index(chunkLocationTrue);
            cellCoordinates.cellLocation = pack_coordinates(cellLocationTrue);
            return candidate;
        }
    }

    return candidate;
}
CellCoordinates World::get_cell_coordinates(Cell* cell)
{
    if (cell)
    {
        return { cell->parentChunk->index, cell->loc };
    }
    else
        return {0,0};
}

Chunk* World::get_chunk(const uint32_t& index)
{
    if (index == -1)
        return nullptr;
    else
        return chunks[index];
}
Chunk* World::get_chunk(const Vec3_ui8& chunkLoc)
{
    int index = get_chunk_index(chunkLoc);
    if (index == -1)
        return nullptr;
    else
        return chunks[index];
}

Vec3 World::get_cell_float_coordinates_from_location(const CellCoordinates& cc)
{
    if (cc.chunkLocation == -1 && cc.cellLocation == -1)
        return 0;
    Vec3_ui8 crd = World::unpack_coordinates(cc.cellLocation);
    Vec3 chunkLocation; get_chunk_float_location(chunkLocation, get_chunk_coordinates_from_index(cc.chunkLocation));

    return {chunkLocation.x + crd.x * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2,
            chunkLocation.y + crd.y * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2,
            chunkLocation.z + crd.z * (float)WorldConstants::CELL_SIZE + (float)WorldConstants::CELL_SIZE / 2,};
}

Chunk* World::add_chunk(const Vec3_ui8& chunkLoc)
{
    uint32_t i = get_chunk_index(chunkLoc);
    if (i == -1 || i >= WorldConstants::WORLD_SIZE)
        return nullptr;
    if (chunks[i] == nullptr)
    {
        chunks[i] = new Chunk(this, chunkLoc);
        return chunks[i];
    }
    else
        return chunks[i];
}
Chunk* World::add_chunk(const uint32_t& chunkLoc)
{
    if (chunkLoc == -1 || chunkLoc >= WorldConstants::WORLD_SIZE)
        return nullptr;
    if (chunks[chunkLoc] == nullptr)
    {
        chunks[chunkLoc] = new Chunk(this, chunkLoc);
        return chunks[chunkLoc];
    }
    else
        return chunks[chunkLoc];
}




void World::initialize_first_cell()
{
    Vec3_ui8 stChunkLoc(WorldConstants::WORLD_BREADTH_X / 2, WorldConstants::WORLD_WIDTH_Y / 2, WorldConstants::WORLD_HEIGHT_Z / 2);
    Vec3_ui8 firstCellLoc(WorldConstants::CHUNK_SIZE/2, WorldConstants::CHUNK_SIZE / 2, WorldConstants::CHUNK_SIZE / 2);

    spawnChunk = add_chunk(stChunkLoc);
    spawnCell = spawnChunk->add_cell_empty(firstCellLoc);
}

void World::get_offset_location(Vec3_ui8& chunkLoc, Vec3_ui8& loc, const int8_t offset[3], Vec3& floatLocation)
{
    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    floatLocation.x += offset[0] * (float)WorldConstants::CELL_SIZE;
    floatLocation.y += offset[1] * (float)WorldConstants::CELL_SIZE;
    floatLocation.z += offset[2] * (float)WorldConstants::CELL_SIZE;

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }
}
Cell* World::get_offset_cell(const Vec3_ui8& _chunkLoc, const Vec3_ui8& _loc, const int8_t offset[3])
{
    Vec3_ui8 loc = _loc; Vec3_ui8 chunkLoc = _chunkLoc;

    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }

    return get_cell(chunkLoc, loc);
}
Cell* World::get_offset_cell(const CellCoordinates& cc, const int8_t offset[3])
{
    Vec3_ui8 loc = unpack_coordinates(cc.cellLocation); Vec3_ui8 chunkLoc = get_chunk_coordinates_from_index(cc.chunkLocation);

    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }

    return get_cell(chunkLoc, loc);
}
Cell* World::get_offset_cell(Cell* cell, const int8_t offset[3])
{
    if (cell == nullptr)
        return nullptr;
    Vec3_ui8 loc = unpack_coordinates(cell->loc); Vec3_ui8 chunkLoc = cell->parentChunk->chunkLocation;

    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }

    return get_cell(chunkLoc, loc);
}
CellCoordinates World::get_offset_coordinates(const CellCoordinates& cc, const int8_t offset[3])
{
    Vec3_ui8 loc = unpack_coordinates(cc.cellLocation); Vec3_ui8 chunkLoc = get_chunk_coordinates_from_index(cc.chunkLocation);

    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }
    
    return { get_chunk_index(chunkLoc),  pack_coordinates(loc) };
}
Cell* World::create_offset_cell(const Vec3_ui8& _chunkLoc, const Vec3_ui8& _loc, const int8_t offset[3])
{
    Vec3_ui8 loc = _loc; Vec3_ui8 chunkLoc = _chunkLoc;

    loc.x += offset[0]; loc.y += offset[1]; loc.z += offset[2];

    if (loc.x == UINT8_MAX)
    {
        loc.x = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.x -= 1;
    }
    if (loc.y == UINT8_MAX)
    {
        loc.y = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.y -= 1;
    }
    if (loc.z == UINT8_MAX)
    {
        loc.z = WorldConstants::CHUNK_SIZE - 1;  chunkLoc.z -= 1;
    }

    if (loc.x == WorldConstants::CHUNK_SIZE)
    {
        loc.x = 0;  chunkLoc.x += 1;
    }
    if (loc.y == WorldConstants::CHUNK_SIZE)
    {
        loc.y = 0;  chunkLoc.y += 1;
    }
    if (loc.z == WorldConstants::CHUNK_SIZE)
    {
        loc.z = 0;  chunkLoc.z += 1;
    }

    Chunk* newC = add_chunk(chunkLoc);
    if (newC)
        return newC->add_cell_empty(loc);
}
Cell* World::create_cell_empty(const Vec3_ui8& chunkLoc, const Vec3_ui8& loc)
{
    Chunk* newC = add_chunk(chunkLoc);
    if (newC)
        return newC->add_cell_empty(loc);
}
void World::connect_elevator_button_to_trigger(const CellCoordinates& cc)
{
    Cell* buttonCell = get_cell(cc);
    if (!buttonCell || !(buttonCell->flags & (CellFlags::IS_ELEVATOR_BUTTON_1 | CellFlags::IS_ELEVATOR_BUTTON_2 | CellFlags::IS_ELEVATOR_BUTTON_CALL)))
        return;

    Vec3 buttonCellLoc = buttonCell->GetCenter();

    std::map<float, Trigger*> sortedTrigs;
    for (auto&t: customTriggers)
    {
        Cell* bottom = get_cell(t.second.triggerBottom);
        if (bottom && (t.second.elevatorButton == 0 || t.second.elevatorButtonCall == 0))
        {
            Vec3 bottomCellLoc = bottom->GetCenter();
            float distance = vecs::VecDistance(bottomCellLoc, buttonCellLoc);
            if (abs(bottomCellLoc.z - buttonCellLoc.z) < 50)
            {
                std::pair<float, Trigger*> newT{ vecs::VecDistance(bottom->GetCenter(), buttonCellLoc) , &t.second };
                sortedTrigs.insert(newT);
            }
        }
    }

    if (!sortedTrigs.empty())
    {
        auto it = sortedTrigs.begin();

        if (it->first < 320)
        {
            Cell* cell = get_cell(cc);
            if (cell->flags & CellFlags::IS_ELEVATOR_BUTTON_CALL)
                it->second->elevatorButtonCall = cc;
            else
                it->second->elevatorButton = cc;


            if (cell->flags & CellFlags::IS_ELEVATOR_BUTTON_1)
                it->second->elevatorStates |= ElevatorStates::BUTTON_1;
            else if (cell->flags & CellFlags::IS_ELEVATOR_BUTTON_1)
                it->second->elevatorStates |= ElevatorStates::BUTTON_2;
        }
    }
}
void World::add_cell_manually(const CellCoordinates& cc, const uint32_t& specialFlag, const uint16_t& entityNum)
{
    Cell* newCell = get_cell(cc.chunkLocation, cc.cellLocation);
    if (newCell != nullptr)
        return;
    newCell = create_cell_empty(cc);
    newCell->parentChunk->flags &= ~ChunkFlags::REFRESH_THIS_CHUNK;
    newCell->flags |= CellFlags::IS_CREATED;
    newCell->flags |= CellFlags::WALKABLE;
    newCell->flags |= specialFlag;

    newCell->entNum = (entityNum == 0) ? 1022 : entityNum;

    if (!(newCell->parentChunk->flags & ChunkFlags::IS_CHUNK_ALREADY_EXIST))
    {
        validChunks.push_back(newCell->parentChunk->index);
        newCell->parentChunk->flags |= ChunkFlags::IS_CHUNK_ALREADY_EXIST;
    }

    newCell->parentChunk->validCells.push_back(cc);
    newCell->parentChunk->validCellsCount++;
    validCellsCount++;

    connect_elevator_button_to_trigger(cc);

    std::vector<CellCoordinates> cells; cells.push_back(cc);
    split_mesh_chunk({ cells }, 1);
    get_graph_neighbors(cells);
}
void World::delete_cell_manually(const CellCoordinates& cc)
{
    Cell* cellToDelete = get_cell(cc.chunkLocation, cc.cellLocation);
    if (cellToDelete == nullptr)
        return;
    int i = 0;
    for (auto& c : cellToDelete->parentChunk->validCells)
    {
        if (c.cellLocation == cc.cellLocation && c.chunkLocation == cc.chunkLocation)
        {
            break;
        }
        i++;
    }
    cellToDelete->parentChunk->validCells.erase(cellToDelete->parentChunk->validCells.begin() + i);

    std::vector<CellCoordinates> goodCells;
    if (cellToDelete->graphNode)
    {
        uint32_t packedCellCrd = pack_cell_and_chunk(cc);
        int badCellId = -1;
        for (int i = 0; i < cellToDelete->graphNode->cells.size(); i++)
        {
            if (cellToDelete->graphNode->cells[i] != packedCellCrd)
            {
                goodCells.push_back(unpack_cell_and_chunk(cellToDelete->graphNode->cells[i]));
            }
            else
                badCellId = i;
        }
        delete_node((uintptr_t)cellToDelete->graphNode);
    }

    if (validCellsCount > 0)
        validCellsCount--;

    //delete_trigger(cc);

    delete_cell(cellToDelete);

    if (goodCells.empty())
        return;

    for (auto& s : graphNodeSizes)
    {
        split_mesh_chunk(goodCells, s);
    }
    get_graph_neighbors(goodCells);
}
Cell* World::create_cell_empty(const CellCoordinates&cc)
{
    Vec3_ui8 chuncLocation = get_chunk_coordinates_from_index(cc.chunkLocation);
    Vec3_ui8 cellLoc = unpack_coordinates(cc.cellLocation);

    Chunk* newC = add_chunk(chuncLocation);
    if (newC)
        return newC->add_cell_empty(cellLoc);
}
void World::delete_cell(Cell*cell)
{
    if (cell == nullptr)
        return;
    int index = cell->parentChunk->get_cell_index(unpack_coordinates(cell->loc));
    cell->parentChunk->cells[index] = nullptr;
    delete(cell);
}
void World::delete_chunk(Chunk* chunk)
{
    if (chunk)
    {
        int index = get_chunk_index(chunk->chunkLocation);
        for (auto& c : chunk->cells)
            delete_cell(c);
        chunks[index] = nullptr;
        delete(chunk);
    }

}
void World::delete_node(const uintptr_t&nodeKey)
{
    //clear neighbor connections
    auto itGraph = graph.find(nodeKey);
    if (itGraph == graph.end())
        return;

    GraphNode* nodeToDelete = itGraph->second;

    for (auto& n : nodeToDelete->neighbors)
    {
        auto it = n.second->neighbors.find((uintptr_t)nodeToDelete);
        if (it != n.second->neighbors.end())
            n.second->neighbors.erase((uintptr_t)nodeToDelete);
    }

    //erase the node from chunk map
    Chunk* parentChunk = get_cell(World::unpack_cell_and_chunk(nodeToDelete->cells[0]))->parentChunk;
    auto it = parentChunk->nodes.find((uintptr_t)nodeToDelete);
    if (it != parentChunk->nodes.end())
        parentChunk->nodes.erase(it);

    //null all the cells
    for (auto& c : nodeToDelete->cells)
    {
        get_cell(World::unpack_cell_and_chunk(c))->graphNode = nullptr;
    }

    delete(nodeToDelete);
    graph.erase(nodeKey);
    return;
}
GraphNode* World::node_validity_check(const uintptr_t& node)
{
    auto it = graph.find(node);
    if (it != graph.end())
        return it->second;
    else
        return nullptr;
}

bool World::check_if_unmovable_mover(const uint16_t& entNum)
{
    if (entNum >= 1022)
        return false;
    uintptr_t moverAdd = moverEntsAddress + entityOffset * entNum;
    if (*(float*)(moverAdd + movEntOffs[MovEntOffs::LAST_TIME_UPDATED]) == 0
        && *(int*)(moverAdd + 0xD0) == 0
        && *(int*)(moverAdd + movEntOffs[MovEntOffs::HP]) == 0
        )
    {
        return true;
    }
    return false;
}
bool World::check_if_ent_is_unlocked_door(const uint16_t& entNum)
{
    if (entNum >= 1022)
        return false;
    uintptr_t moverAdd = moverEntsAddress + entityOffset * entNum;
    return *(int*)(moverAdd + movEntOffs[MovEntOffs::IS_DOOR_UNLOCKED]);
}
bool World::check_if_ent_is_opening(const uint16_t& entNum)
{
    if (entNum >= 1022 || entNum == 0)
        return false;
    uintptr_t moverAdd = moverEntsAddress + entityOffset * entNum;
    return *(int*)(moverAdd + movEntOffs[MovEntOffs::IS_OPENING]);
}

void World::analyze_above_cell(const Vec3& crd, const uint16_t& parent_entNum, uint32_t& flags)
{
    scansAboveCount++;
    scansCount++;
    Vec3 start = crd; start.z += (float)WorldConstants::HALF_CELL_SIZE + 2 * (float)WorldConstants::CELL_SIZE;
    Vec3 end = crd;  end.z += (float)WorldConstants::HALF_CELL_SIZE;

    tracer->traceLine(&trace_data, start, cellMin, cellMax, end, 0, 0x1011, 0);
    
    if ((trace_data.entityNum == 1023
        && trace_data.startsolid != 1
        )
        ) //if not solid above cell then walkable
    {
        flags |= CellFlags::WALKABLE;
        return;
    }
    if (trace_data.entityNum < 1022)
    {
        flags |= CellFlags::WALKABLE;
        if (check_if_unmovable_mover(trace_data.entityNum))
        {
            flags = CellFlags::NONE;
            return;
        }
        return;
    }

    flags = CellFlags::NONE;
    return;
}
void World::scan_location(const Vec3& crd, uint32_t& flags, uint16_t& entNum)
{
    origin;
    Vec3 start, end/*, back, forward, left, right*/;
    
    scansCount++;

    start = crd; start.z += WorldConstants::CELL_SIZE / 2;
    end = crd;   end.z -= WorldConstants::CELL_SIZE / 2;

    tracer->traceLine(&trace_data, start, cellMin, cellMax, end, 0, 0x1011, 0);

    if (trace_data.entityNum == 1023)
        tracer->traceLine(&trace_data, start, 0, 0, end, 0, 0x1011, 0);

    if (trace_data.entityNum == 1023 
        || trace_data.surfaceFlags & SURF_SLICK
        //|| (trace_data.surfaceFlags == (SURF_NODRAW | SURF_NOMARKS))
        )     //air or slippery or transparent
    {
        flags = CellFlags::NONE;
        return;
    }

    if (trace_data.entityNum == 1022)     //solid
    {
        entNum = trace_data.entityNum;

        if (trace_data.plane.normal.z == 1)
        {
            flags |= CellFlags::WALKABLE;
        }
        else if (abs(std::acos(trace_data.plane.normal.z)) < 0.792310)
        {
            flags |= CellFlags::WALKABLE;
        }
        else
        {
            flags = CellFlags::NONE;
            return;
        }
    }
    else //mover
    {
        entNum = trace_data.entityNum;
        flags |= CellFlags::IS_MOVER;

        if (check_if_unmovable_mover(entNum))
        {
            flags &= ~CellFlags::IS_MOVER;
            flags |= CellFlags::WALKABLE;
            flags |= CellFlags::IS_IMMOVABLE_OBJECT;
        }

    }

    analyze_above_cell(crd, trace_data.entityNum, flags);
}

void World::create_trigger_cell_column(const CellCoordinates& cc, int8_t dir[3], std::unordered_set<uint32_t>& columnCells)
{
    CellCoordinates nextCell = get_offset_coordinates(cc, dir);
    int maxHeight = 1024;
    int safeQuit = 0;
    while (safeQuit < maxHeight)
    {
        if (get_cell(nextCell) != nullptr)
            return;

        auto it = customTriggers.find(pack_cell_and_chunk(nextCell));
        if (it != customTriggers.end())
            return;

        add_cell_manually(nextCell, CellFlags::IS_ELEVATOR_COLUMN);
        columnCells.insert(pack_cell_and_chunk(nextCell));

        nextCell = get_offset_coordinates(nextCell, dir);
        safeQuit++;
    }
}
void World::register_trigger_cell_column(const CellCoordinates& cc, int8_t dir[3], std::unordered_set<uint32_t>& columnCells)
{
    CellCoordinates nextCell = get_offset_coordinates(cc, dir);
    int maxHeight = 1024;
    int safeQuit = 0;
    while (safeQuit < maxHeight)
    {
        if (get_cell(nextCell) == nullptr)
            return;

        auto it = customTriggers.find(pack_cell_and_chunk(nextCell));
        if (it != customTriggers.end())
            return;

        if (get_cell(nextCell)->flags & CellFlags::IS_ELEVATOR_COLUMN)
            columnCells.insert(pack_cell_and_chunk(nextCell));

        nextCell = get_offset_coordinates(nextCell, dir);
        safeQuit++;
    }
}
void World::link_trigger(Trigger& trigger)
{
    Cell* newTriggerBot = get_cell(trigger.triggerBottom);
    if (newTriggerBot == nullptr)
        return;

    if (trigger.elevatorStates & ElevatorStates::LINKED)
        return;

    int8_t dirUp[3]{ 0,0,1 };
    int8_t dirDown[3]{ 0,0,-1 };

    for (auto& t : customTriggers)
    {
        Cell* botCell = get_cell(t.second.triggerBottom);
        if (botCell == nullptr)
            continue;

        Vec3 newTrigLoc = newTriggerBot->GetCenter();  Vec3 botCellLoc = botCell->GetCenter();
        if (vecs::VecDistance2(newTrigLoc, botCellLoc) == 0 && trigger.triggerBottom != t.second.triggerBottom)
        {
            t.second.other = &trigger;
            trigger.other = &t.second;

            trigger.elevatorStates |= ElevatorStates::LINKED;
            t.second.elevatorStates |= ElevatorStates::LINKED;

            if (newTrigLoc.z > botCellLoc.z)
            {
                create_trigger_cell_column(trigger.triggerBottom, dirDown, t.second.columnCells);
                if (t.second.columnCells.empty())
                    register_trigger_cell_column(trigger.triggerBottom, dirDown, t.second.columnCells);
                t.second.elevatorStates |= ElevatorStates::BOTTOM;
                trigger.elevatorStates |= ElevatorStates::TOP;
            }
            else
            {
                create_trigger_cell_column(trigger.triggerTop, dirUp, trigger.columnCells);
                if (trigger.columnCells.empty())
                    register_trigger_cell_column(trigger.triggerTop, dirUp, trigger.columnCells);
                trigger.elevatorStates |= ElevatorStates::BOTTOM;
                t.second.elevatorStates |= ElevatorStates::TOP;
            }


            Cell* triggerBot = get_cell(t.second.triggerBottom);
            Cell* triggerTop = get_cell(t.second.triggerTop);

            Cell* triggerOtherBot = get_cell(trigger.triggerBottom);
            Cell* triggerOtherTop = get_cell(trigger.triggerTop);

            if (!triggerBot || !triggerTop || !triggerOtherBot || !triggerOtherTop)
                continue;

            if (triggerBot->entNum < 1022)
            {
                t.second.entityNum = triggerBot->entNum;
                trigger.entityNum = triggerBot->entNum;
            }
            else if (triggerTop->entNum < 1022)
            {
                t.second.entityNum = triggerTop->entNum;
                trigger.entityNum = triggerTop->entNum;
            }
            else if (triggerOtherBot->entNum < 1022)
            {
                t.second.entityNum = triggerOtherBot->entNum;
                trigger.entityNum = triggerOtherBot->entNum;

            }
            else if (triggerOtherTop->entNum < 1022)
            {
                t.second.entityNum = triggerOtherTop->entNum;
                trigger.entityNum = triggerOtherTop->entNum;
            }

            connect_elevator_bridge(triggerBot, trigger.entityNum);
            connect_elevator_bridge(triggerOtherBot, trigger.entityNum);

            break;
        }
    }
}
void World::tick_trigger(Cell*trigger, uint16_t& entNum)
{
    Vec3 origin;
    Vec3 start, end;

    origin = trigger->GetCenter();

    start = origin; start.z += WorldConstants::HALF_CELL_SIZE;
    end = origin;   end.z -= WorldConstants::HALF_CELL_SIZE;

    tracer->traceLine(&trace_data, start, 0, 0, end, 0, 0x1011, 0);

    entNum = trace_data.entityNum;

    if (check_if_unmovable_mover(trace_data.entityNum))
    {
        trigger->entNum = 1022;
        return;
    }

    if (trace_data.entityNum < 1022)
        trigger->entNum = trace_data.entityNum;
}
void World::connect_elevator_bridge(Cell* startCell, const uint16_t&entNum)
{
    int8_t offset[3];

    std::vector<Cell*> visitedCells;
    std::queue<Cell*> q;
    q.push({ startCell });

    startCell->flags |= CellFlags::IS_RESCANNED;

    visitedCells.push_back(startCell);

    Cell* nextCell = nullptr;
    while (!q.empty())
    {
        Cell* current = q.front();
        q.pop();

        for (int i = 0; i < findNeighborsAllDX.size(); i++)
        {
            offset[0] = findNeighborsAllDX[i];  offset[1] = findNeighborsAllDY[i];  offset[2] = findNeighborsAllDZ[i];

            nextCell = get_offset_cell(current, offset);

            if (nextCell && !(nextCell->flags & (CellFlags::IS_RESCANNED)) && !(nextCell->flags & (CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP | CellFlags::IS_ELEVATOR_COLUMN)) && nextCell->entNum == entNum)
            {
                nextCell->flags |= CellFlags::IS_RESCANNED;
                nextCell->flags |= CellFlags::IS_ELEVATOR_BRIDGE;
                visitedCells.push_back(nextCell);
                q.push(nextCell);
            }
        }
    }

    for (auto& c : visitedCells)
    {
        c->flags &= ~CellFlags::IS_RESCANNED;
    }
}
void World::tick_triggers(const uint16_t& playerStandingEntId)
{
    for (auto& c : customTriggers)
    {
        Cell* triggerBot = get_cell(c.second.triggerBottom);
        Cell* triggerTop = get_cell(c.second.triggerTop);

        if (triggerBot == nullptr || triggerBot->graphNode == nullptr || /*!(triggerBot->graphNode->flags & GraphFlags::IS_PATH_NODE) ||*/
            triggerTop == nullptr || triggerTop->graphNode == nullptr /*|| !(trigger->graphNode->flags & GraphFlags::IS_PATH_NODE)*/
            )
            continue;

        tick_trigger(triggerBot, c.second.entBottom);
        tick_trigger(triggerTop, c.second.entTop);

        if (check_if_ent_is_opening(c.second.entityNum))
            c.second.elevatorStates |= ElevatorStates::MOVING;
        else
            c.second.elevatorStates &= ~ElevatorStates::MOVING;

        c.second.set_primary_states();

    }
    for (auto& c : customTriggers)
    {
        c.second.set_secondary_states(playerStandingEntId);
    }

}
Trigger* World::find_trigger(const GraphNode* gn)
{
    if (!gn || !(gn->flags & GraphFlags::IS_ELEVATOR))
        return nullptr;

    CellCoordinates cc = unpack_cell_and_chunk(gn->cells[0]);

    for (auto& t : customTriggers)
    {
        if (t.second.triggerBottom == cc || t.second.triggerTop == cc)
            return &t.second;
    }
    return nullptr;
}
Trigger* World::find_trigger(const CellCoordinates&cc)
{
    for (auto& t : customTriggers)
    {
        if (t.second.triggerBottom == cc || t.second.triggerTop == cc)
            return &t.second;
    }
    return nullptr;
}
void World::create_trigger(const CellCoordinates& cc)
{
    int8_t elevOffset[3]{ 0,0, 1 };
    //add bottom half
    add_cell_manually(cc, CellFlags::IS_ELEVATOR_DETECTOR);
    //add top half
    CellCoordinates elevatorTopLoc = get_offset_coordinates(cc, elevOffset);
    add_cell_manually(elevatorTopLoc, CellFlags::IS_ELEVATOR_DETECTOR_UP);

    Trigger t{ cc, elevatorTopLoc };
    std::pair<uint32_t, Trigger> newTrig{ pack_cell_and_chunk(cc), t };
    customTriggers.insert(newTrig);

    for (auto& t : customTriggers)
    {
        tick_triggers(0);
    }
    for (auto& t : customTriggers)
    {
        link_trigger(t.second);
    }

    auto it = customTriggers.find(pack_cell_and_chunk(cc));
}
void World::delete_trigger(const CellCoordinates& cc)
{
    Cell* elevTrigC =get_cell(cc);
    if (elevTrigC && (elevTrigC->flags & (CellFlags::IS_ELEVATOR_DETECTOR)))
    {
        auto it =customTriggers.find(pack_cell_and_chunk(cc));
        if (it !=customTriggers.end())
        {
            CellCoordinates top = it->second.triggerTop;
            CellCoordinates bot = it->second.triggerBottom;

            if (!(it->second.elevatorStates & ElevatorStates::LINKED))
            {
               delete_cell_manually(top);
               delete_cell_manually(bot);
            }
            else
            {
                auto it2 =customTriggers.find(pack_cell_and_chunk(it->second.other->triggerBottom));
                if (it2 !=customTriggers.end())
                {
                    CellCoordinates top2 = it2->second.triggerTop;
                    CellCoordinates bot2 = it2->second.triggerBottom;

                   delete_cell_manually(top2);
                   delete_cell_manually(bot2);

                   if (it2->second.columnCells.size())
                   {
                       for (auto& c : it2->second.columnCells)
                       {
                           delete_cell_manually(unpack_cell_and_chunk(c));
                       }
                   }

                   customTriggers.erase(it2);
                }

               delete_cell_manually(top);
               delete_cell_manually(bot);
            }

            if (it->second.columnCells.size())
            {
                for (auto& c : it->second.columnCells)
                {
                    delete_cell_manually(unpack_cell_and_chunk(c));
                }
            }

           customTriggers.erase(it);
        }
    }
    else if (elevTrigC && (elevTrigC->flags & (CellFlags::IS_ELEVATOR_DETECTOR_UP)))
    {

        int8_t elevOffset[3]{ 0,0, -1 };
        CellCoordinates elevatorBotLoc =get_offset_coordinates(cc, elevOffset);
        Cell* elevTrigBotC =get_cell(elevatorBotLoc);


        auto it =customTriggers.find(pack_cell_and_chunk(elevatorBotLoc));
        if (it !=customTriggers.end())
        {
            CellCoordinates top = it->second.triggerTop;
            CellCoordinates bot = it->second.triggerBottom;

            if (!(it->second.elevatorStates & ElevatorStates::LINKED))
            {
               delete_cell_manually(top);
               delete_cell_manually(bot);
            }
            else
            {
                auto it2 =customTriggers.find(pack_cell_and_chunk(it->second.other->triggerBottom));
                if (it2 !=customTriggers.end())
                {
                    CellCoordinates top2 = it2->second.triggerTop;
                    CellCoordinates bot2 = it2->second.triggerBottom;

                   delete_cell_manually(top2);
                   delete_cell_manually(bot2);

                   if (it2->second.columnCells.size())
                   {
                       for (auto& c : it2->second.columnCells)
                       {
                           delete_cell_manually(unpack_cell_and_chunk(c));
                       }
                   }

                   customTriggers.erase(it2);
                }

               delete_cell_manually(top);
               delete_cell_manually(bot);
            }

            if (it->second.columnCells.size())
            {
                for (auto& c : it->second.columnCells)
                {
                    delete_cell_manually(unpack_cell_and_chunk(c));
                }
            }

           customTriggers.erase(it);
        }

    }
}
void World::create_elevator(const CellCoordinates& cc)
{
    Cell* startCell = get_cell(cc);
    if (!startCell || !(startCell->flags & CellFlags::IS_MOVER))
        return;

    int8_t offset[3];
    std::vector<Cell*> visitedCells;
    std::queue<Cell*> q;
    q.push({ startCell });

    startCell->flags |= CellFlags::IS_RESCANNED;

    visitedCells.push_back(startCell);

    Cell* nextCell = nullptr;
    while (!q.empty())
    {
        Cell* current = q.front();
        q.pop();

        for (int i = 0; i < findNeighborsAllDX.size(); i++)
        {
            offset[0] = findNeighborsAllDX[i];  offset[1] = findNeighborsAllDY[i];  offset[2] = findNeighborsAllDZ[i];

            nextCell = get_offset_cell(current, offset);

            if (nextCell && !(nextCell->flags & (CellFlags::IS_RESCANNED)) && nextCell->entNum == startCell->entNum)
            {
                nextCell->flags |= CellFlags::IS_RESCANNED;
                nextCell->flags |= CellFlags::IS_ELEVATOR_BRIDGE;
                visitedCells.push_back(nextCell);
                q.push(nextCell);
            }
        }
    }

    for (auto& c : visitedCells)
    {
        c->flags &= ~CellFlags::IS_RESCANNED;
    }

    uint16_t oldEntNum = startCell->entNum;
    delete_cell_manually(cc);
    create_trigger(cc);

    int8_t offsetUp[3]{ 0,0,1 };
    CellCoordinates offsetCellCC = cc;
    CellCoordinates topCell = {0,0};
    for (int i = 0; i < 999; i++)
    {
        offsetCellCC = get_offset_coordinates(offsetCellCC, offsetUp);
        Cell* offsetCell = get_cell(offsetCellCC);
        if (offsetCell && offsetCell->entNum == oldEntNum)
        {
            topCell = offsetCellCC;
            break;
        }
    }

    if (topCell != 0)
    {
        delete_cell_manually(topCell);
        create_trigger(topCell);
    }
}

void World::rescan_cell_bridge(const CellCoordinates& cc)
{
    Vec3 origin;
    Vec3 start, end;

    Cell* cell = get_cell(cc);
    origin = cell->GetCenter();

    if (cell->flags & CellFlags::UNBANNABLE_FLAGS)
        return;

    //for (auto& t : customTriggers)
    //{
    //    if (t.second.entityNum == cell->entNum)
    //        return;
    //}

    start = origin; start.z += WorldConstants::HALF_CELL_SIZE;
    end = origin;   end.z -= WorldConstants::HALF_CELL_SIZE;

    tracer->traceLine(&trace_data, start, cellMin, cellMax, end, 0, 0x1011, 0);



    if (trace_data.entityNum == 1023 && cell->entNum != 1022)     //if air ban the mover entity 
    {
        cell->flags |= (CellFlags::IS_BANNED | CellFlags::IS_BRIDGE);

        auto it = moverEntities.find(cell->entNum);
        if (it == moverEntities.end())
        {
            MoverEntity entity(cell->entNum);
            entity.isBridge = true;
            moverEntities.insert({ cell->entNum, entity });
            moverEntities[cell->entNum].bannedCells.insert(pack_cell_and_chunk(cc));
        }
        else
        {
            moverEntities[cell->entNum].bannedCells.insert(pack_cell_and_chunk(cc));
        }
    }
}
void World::rescan_cell(const CellCoordinates& cc)
{
    Vec3 origin;
    Vec3 start, end;

    Cell* cell = get_cell(cc);
    origin = cell->GetCenter();

    if (cell->flags & CellFlags::UNBANNABLE_FLAGS)
        return;

    start = origin; start.z += WorldConstants::HALF_CELL_SIZE;
    end = origin;   end.z -= WorldConstants::HALF_CELL_SIZE;

    tracer->traceLine(&trace_data, start, cellMin, cellMax, end, 0, 0x1011, 0);

    if (trace_data.entityNum == 1023)     //if air ban the mover entity 
    {
        cell->flags &= ~CellFlags::IS_BANNED;

        auto it = moverEntities.find(cell->entNum);
        if (it != moverEntities.end())
        {
            if (moverEntities[cell->entNum].isBridge)
            {
                cell->flags |= CellFlags::IS_BANNED;
            }
        }   
    }

    else if (trace_data.entityNum == 1022) //if solid ban the mover entity 
    {
        auto it = moverEntities.find(cell->entNum);
        if (it != moverEntities.end())
        {
            auto it2 = it->second.bannedCells.find(pack_cell_and_chunk(cc));
            if (it2 != it->second.bannedCells.end())
            {
                cell->flags &= ~CellFlags::IS_BANNED;
            }
        }

    }
    else if (trace_data.entityNum < 1022) //movers
    {
        auto it = moverEntities.find(trace_data.entityNum);
        if (it != moverEntities.end())
        {
            if (!check_if_ent_is_unlocked_door(trace_data.entityNum))
                cell->flags |= CellFlags::IS_BANNED;
            else
                cell->flags &= ~CellFlags::IS_BANNED;

            if (it->second.isBridge)
                cell->flags &= ~CellFlags::IS_BANNED;

            cell->flags |= CellFlags::IS_MOVER;
            cell->entNum = trace_data.entityNum;
            moverEntities[trace_data.entityNum].bannedCells.insert(pack_cell_and_chunk(cc));
        }
    }
}
void World::rescan_area(const CellCoordinates& myCell)
{
    rescanAreaTimer.Start();

    std::vector<Cell*> scannedCells;
    std::vector<Cell*> rebuiltCells;

    float scanRadius = 330;
    std::queue<Cell*> q;
    int8_t offset[3];
    Cell* nextcell = nullptr;
    int counterBanned = 0;

    q.push({ get_cell(myCell) });

    bool foundFirstBanned = false;
    Cell* firstBannedCell = nullptr;

    //find first banned cell
    while (!q.empty())
    {
        Cell* current = q.front();
        q.pop();
        for (int i = 0; i < rescanCellDZ.size(); i++)
        {
            offset[0] = rescanCellDX[i];  offset[1] = rescanCellDY[i];  offset[2] = rescanCellDZ[i];

            nextcell = get_offset_cell(current, offset);

            if (!nextcell)
                continue;

            int a = 3;

            if (
                 nextcell->flags & CellFlags::WALKABLE
                && !(nextcell->flags & CellFlags::IS_BANNED)
                && (vecs::VecDistance(get_cell(myCell)->GetCenter(), current->GetCenter()) < scanRadius)
                && !(nextcell->flags & CellFlags::IS_RESCANNED)
                )
            {
                rescan_cell({ nextcell->parentChunk->index, nextcell->loc });

                if (nextcell->flags & CellFlags::IS_BANNED)
                {
                    firstBannedCell = nextcell;
                    rebuiltCells.push_back(nextcell);
                    //scannedCells.push_back(nextcell);
                    foundFirstBanned = true;
                    break;

                }
                nextcell->flags |= (CellFlags::IS_RESCANNED);
                scannedCells.push_back(nextcell);
                counterBanned++;
                q.push(nextcell);


            }
            if (foundFirstBanned)
                break;
        }

    }

    //scan only banned cells
    if (foundFirstBanned)
    {
        std::queue<Cell*> qForBanned;
        qForBanned.push({ firstBannedCell });

        while (!qForBanned.empty())
        {
            Cell* current = qForBanned.front();
            qForBanned.pop();
            for (int i = 0; i < rescanCellDZ.size(); i++)
            {
                offset[0] = rescanCellDX[i];  offset[1] = rescanCellDY[i];  offset[2] = rescanCellDZ[i];

                nextcell = get_offset_cell(current, offset);


                if (nextcell
                    && nextcell->flags & CellFlags::WALKABLE
                    && !(nextcell->flags & CellFlags::IS_BANNED)
                    && !(nextcell->flags & CellFlags::IS_RESCANNED)
                    )
                {
                    counterBanned++;
                    rescan_cell({ nextcell->parentChunk->index, nextcell->loc });

                    if (nextcell->flags & CellFlags::IS_BANNED)
                    {
                        rebuiltCells.push_back(nextcell);
                        scannedCells.push_back(nextcell);
                        qForBanned.push(nextcell);

                    }
                    else
                        scannedCells.push_back(nextcell);
                  
                }
            }

        }
    }

    //delete moverent if it's empty
    for (auto it = moverEntities.begin(); it != moverEntities.end(); )
    {
        if (it->second.bannedCells.empty())
            it = moverEntities.erase(it);
        else
            ++it;
    }

    //redo graph nodes---------------------------------------------------------------------------------------------------------
    std::unordered_set<GraphNode*> affectedNodes;
    std::vector<CellCoordinates> affectedCellCoordinates;

    //get all affected nodes
    for (auto& c : rebuiltCells)
    {
        affectedNodes.insert(c->graphNode);
        c->graphNode = nullptr;
    }

    //find all affected cells
    for (auto& n : affectedNodes)
    {
        for (auto& c : n->cells)
        {
            affectedCellCoordinates.push_back(unpack_cell_and_chunk(c));
        }
    }

    //delete all affected nodes
    for (auto& n : affectedNodes)
    {
        delete_node((uintptr_t)n);
    }

    for (auto& s : graphNodeSizes)
    {
        split_mesh_chunk(affectedCellCoordinates, s);
    }

    //get neighbors
    get_graph_neighbors(affectedCellCoordinates);


    //reset flags---------------------------
    for (auto& c : scannedCells)
    {
       c->flags &= ~(CellFlags::IS_RESCANNED);
    }
    rescanAreaTimer.Stop();

    auto t = rescanAreaTimer.ElapsedMcs();
}
bool World::fill_mover_ents(const uint16_t& entAhead)
{
    static uint16_t oldEntityAhead;
    if (entAhead == oldEntityAhead/* || me.myFlags & MyFlags::IS_NOCLIP*/)
        return false;
    oldEntityAhead = entAhead;

    if (entAhead == 1022 || entAhead == 1023)
        return false;

    bool shouldRescan = false;

    for (int i = -1; i < 2; i++)
    {
        MoverEntity entity(entAhead + i);
        //entity.Scan();
        if (!entity.isOpening)
        {
            moverEntities.insert({ entAhead + i, entity });
            shouldRescan = true;
        }
    }

    return shouldRescan;
}
//unused
void World::unlock_banned_area(MoverEntity&entity)
{
    std::unordered_set<Chunk*>unbannedChunks;
    uint32_t edgeFlags = CellFlags::IS_EDGE | CellFlags::IS_EDGE2 | CellFlags::IS_EDGE3;


    for (auto& cell : entity.bannedCells)
    {
        Cell*c = get_cell(unpack_cell_and_chunk(cell));
        if (c)
        {
            c->flags &= ~CellFlags::IS_BANNED;
            unbannedChunks.insert(c->parentChunk);
        }
    }

    //set to refresh
    for (auto& chunk : unbannedChunks)
    {
        for (auto& c : chunk->validCells)
        {
            Cell* cell = get_cell(c); cell->flags &= ~edgeFlags; cell->flags |= CellFlags::REFRESH;
        }
    }
    //postgen
    for (auto&chunk: unbannedChunks)
    {
        postgen_scan_specific_chunk(chunk);
    }

    //cleanup flags
    for (auto& chunk : unbannedChunks)
    {
        for (auto& c : chunk->validCells)
        {
            Cell* cell = get_cell(c); cell->flags &= ~CellFlags::REFRESH;
        }
    }



}
void World::unlock_banned_area_all(const std::vector<uint16_t>& changedEntIds)
{
    unbanAreaTimer.Start();
    std::vector<CellCoordinates> affectedCells;
    std::unordered_set<GraphNode*> bannedNodes;
    for (auto& id : changedEntIds)
    {
        //get affected chunks
        for (auto& cell : moverEntities[id].bannedCells)
        {
            CellCoordinates cellCrd = unpack_cell_and_chunk(cell);
            Cell* c = get_cell(cellCrd);

            if (c)
            {
                rescan_cell(cellCrd);
                if (!(c->flags & CellFlags::IS_BANNED))
                {
                    affectedCells.push_back(cellCrd);
                }
                else
                {
                    affectedCells.push_back(cellCrd);
                    if (c->graphNode)
                        bannedNodes.insert(c->graphNode);
                }
            }
        }
    }
    for (auto& n : bannedNodes)
    {
        for (auto& c : n->cells)
        {      
            affectedCells.push_back(unpack_cell_and_chunk(c));
        }
        delete_node((uintptr_t)n);
    }
    for (auto& s : graphNodeSizes)
    {
        split_mesh_chunk(affectedCells, s);
    }
    get_graph_neighbors(affectedCells);

    std::unordered_set<GraphNode*> TEMP;
    int islandNum = 0;
    for (auto& c : affectedCells)
    {
        GraphNode* gn = get_cell(c)->graphNode;
        if (gn && gn->islandNum != 0)
            islandNum = gn->islandNum;
        TEMP.insert(get_cell(c)->graphNode);
    }
    for (auto& gn : TEMP)
    {
        if (gn)
            gn->islandNum = islandNum;
    }

    unbanAreaTimer.Stop();
}
bool World::is_next_node_safe(GraphNode* gn)
{
    if (graph.find((uintptr_t)gn) == graph.end())
        return false;

    if (get_cell(gn->cells[0])->flags & (CellFlags::IS_ELEVATOR_COLUMN | CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP | CellFlags::IS_ELEVATOR_BRIDGE))
    {
        return true;
    }

    bool isNodeSafe = true;
    for (auto& c : gn->cells)
    {
        Cell* cell = get_cell(unpack_cell_and_chunk(c));
        rescan_cell_bridge(unpack_cell_and_chunk(c));
        if (cell->flags & CellFlags::IS_BANNED)
        {
            isNodeSafe = false;
        }
    }

    std::vector<GraphNode*> visitedNodes;

    if (!isNodeSafe)
    {
        std::unordered_set<GraphNode*> badNodes;
        std::vector<CellCoordinates> goodCells;
        std::queue<GraphNode*> q;
        q.push({gn});

        gn->flags |= GraphFlags::IS_VISITED;
        visitedNodes.push_back(gn);

        while (!q.empty())
        {
            GraphNode* current = q.front();
            q.pop();
            for (auto&neighbor:current->neighbors)
            {

                for (auto& c : neighbor.second->cells)
                {
                    Cell* cell = get_cell(unpack_cell_and_chunk(c));
                    rescan_cell_bridge(unpack_cell_and_chunk(c));
                    if (cell->flags & CellFlags::IS_BANNED)
                    {
                        neighbor.second->flags |= GraphFlags::IS_BANNED;
                        //break;
                    }
                }

                if (neighbor.second->flags & GraphFlags::IS_BANNED)
                {
                    badNodes.insert(neighbor.second);
                }

                if (!(neighbor.second->flags & GraphFlags::IS_VISITED) && (neighbor.second->flags & GraphFlags::IS_BANNED))
                    q.push(neighbor.second);

                neighbor.second->flags |= GraphFlags::IS_VISITED;
                visitedNodes.push_back(neighbor.second);

            }
        }

        for (auto& bn : badNodes)
        {
            for (auto& c : bn->cells)
            {
                CellCoordinates cellLoc = unpack_cell_and_chunk(c);
                Cell* cell = get_cell(cellLoc);
                if (!(cell->flags & CellFlags::IS_BANNED))
                    goodCells.push_back(cellLoc);
            }
            delete_node((uintptr_t)bn);
        }
        for (auto& vn : visitedNodes)
        {
            vn->flags &= ~GraphFlags::IS_VISITED;
        }

        for (auto& s : graphNodeSizes)
        {
            split_mesh_chunk(goodCells, s);
        }
        get_graph_neighbors(goodCells);
    }

    return isNodeSafe;
}

void World::cleanup_generated_cells()
{
    cellsCleanupTimer.Start();

    uint32_t addedCells = 0;
    uint32_t addedChunks = 0;
    uint32_t checks = 0;

    for (auto& ch : chunks)
    {
        if (ch == nullptr)
            continue;
        else
        {
            if (!(ch->flags & ChunkFlags::IS_CHUNK_ALREADY_EXIST) && ch->validCellsCount != 0)
            {
                addedChunks++;
                validChunks.push_back(ch->index);
                ch->flags |= ChunkFlags::IS_CHUNK_ALREADY_EXIST;
                ch->validCells.reserve(ch->validCellsCount);
            }
            if (ch->validCellsCount == 0)
            {
                delete_chunk(ch);
                continue;
            }
            if (!(ch->flags & ChunkFlags::REFRESH_THIS_CHUNK))
                continue;
        }
        for (auto& c : ch->cells)
        {
            checks++;
            if (c && (c->flags != CellFlags::NONE))
            {
                if (!(c->flags & CellFlags::IS_CREATED))
                {
                    addedCells++;
                    ch->validCells.push_back({ ch->index, c->loc });
                    validCellsCount++;
                    c->flags |= CellFlags::IS_CREATED;
                    c->flags |= CellFlags::REFRESH;
                }
            }
            else if (c && c->flags == CellFlags::NONE)
            {
                delete_cell(c);
            }
        }
    }
    cellsCleanupTimer.Stop();
}

void World::postgen_scan_specific_chunk_edge(Chunk* chunk)
{
   
    int8_t offset[3];
    Cell* tempCell = nullptr;
    int counter = 0;

    for (auto& cellLoc : chunk->validCells)
    {
        counter++;
        Vec3_ui8 originCellLocation = unpack_coordinates(cellLoc.cellLocation);
        Cell* cell = get_cell(cellLoc.chunkLocation, cellLoc.cellLocation);

        if (!(cell->flags & CellFlags::REFRESH) || (cell->flags & CellFlags::IS_EDGE3) || (cell->flags & CellFlags::IS_EDGE2))
            continue;

        cell->flags |= CellFlags::IS_EDGE;

        bool isEdge = true;

        for (auto& o : offsetsForPostGen)
        {
            isEdge = true;
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];

                if ((tempCell = get_offset_cell(chunk->chunkLocation, originCellLocation, offset)) && (tempCell->flags & CellFlags::WALKABLE))
                {
                    if (tempCell->flags & CellFlags::IS_BANNED)
                    {
                        isEdge = true;
                        break;
                    }
                    isEdge = false;
                    break;
                }
            }
            if (isEdge)
                break;
        }

        if (!isEdge)
            cell->flags &= ~CellFlags::IS_EDGE;
    }
}
void World::postgen_scan_specific_chunk_edge2(Chunk* chunk)
{
    int8_t offset[3];
    Cell* tempCell = nullptr;
    for (auto& cellLoc : chunk->validCells)
    {
        Vec3_ui8 originCellLocation = unpack_coordinates(cellLoc.cellLocation);
        Cell* cell = get_cell(cellLoc.chunkLocation, cellLoc.cellLocation);

        if (!(cell->flags & CellFlags::IS_EDGE))
            continue;

        if (!(cell->flags & CellFlags::REFRESH))
            continue;

        for (auto& o : offsetsForPostGen)
        {
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];
                if ((tempCell = get_offset_cell(chunk->chunkLocation, originCellLocation, offset))
                    && !(tempCell->flags & CellFlags::IS_EDGE)
                    && !(tempCell->flags & CellFlags::IS_EDGE3)
                    /*&& tempCell->parentChunk->index == chunk->index*/
                    )
                {
                    tempCell->flags |= CellFlags::IS_EDGE2;
                }
            }
        }
    }
}
void World::postgen_scan_specific_chunk_edge3(Chunk* chunk)
{
    int8_t offset[3];
    Cell* tempCell = nullptr;
    for (auto& cellLoc : chunk->validCells)
    {
        Vec3_ui8 originCellLocation = unpack_coordinates(cellLoc.cellLocation);
        Cell* cell = get_cell(cellLoc.chunkLocation, cellLoc.cellLocation);

        if (!(cell->flags & CellFlags::IS_EDGE2))
            continue;

        if (!(cell->flags & CellFlags::REFRESH))
            continue;

        for (auto& o : offsetsForPostGen)
        {
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];
                if ((tempCell = get_offset_cell(chunk->chunkLocation, originCellLocation, offset))
                    && !(tempCell->flags & CellFlags::IS_EDGE)
                    && !(tempCell->flags & CellFlags::IS_EDGE2)
                    /*&& tempCell->parentChunk->index == chunk->index*/
                    )
                {
                    tempCell->flags |= CellFlags::IS_EDGE3;


                }
            }
        }
    }
}
void World::postgen_scan_specific_chunk(Chunk* chunk)
{
    int8_t offset[3];
    Cell* tempCell = nullptr;
    int counter = 0;

    postgen_scan_specific_chunk_edge(chunk);
    postgen_scan_specific_chunk_edge2(chunk);
    postgen_scan_specific_chunk_edge3(chunk);

}
void World::postgen_scan_specific_chunk_fast(Chunk* chunk)
{
    int8_t offset[3];
    Cell* tempCell = nullptr;
    int counter = 0;

    uint32_t edgeFlags = CellFlags::IS_EDGE | CellFlags::IS_EDGE3 | CellFlags::IS_EDGE2;

    std::vector<CellCoordinates> edgeCells, edgeCells2; edgeCells.reserve(1024);  edgeCells2.reserve(2048);

    for (auto& cellLoc : chunk->validCells)
    {
        counter++;
        Vec3_ui8 originCellLocation = unpack_coordinates(cellLoc.cellLocation);
        Cell* cell = get_cell(cellLoc.chunkLocation, cellLoc.cellLocation);

        if (!(cell->flags & CellFlags::REFRESH) || (cell->flags & CellFlags::IS_EDGE3) || (cell->flags & CellFlags::IS_EDGE2))
            continue;

        cell->flags |= CellFlags::IS_EDGE;

        bool isEdge = true;

        for (auto& o : offsetsForPostGen)
        {
            isEdge = true;
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];

                if ((tempCell = get_offset_cell(chunk->chunkLocation, originCellLocation, offset)) && (tempCell->flags & CellFlags::WALKABLE))
                {
                    if (tempCell->flags & CellFlags::IS_BANNED)
                    {
                        isEdge = true;
                        break;
                    }
                    isEdge = false;
                    break;
                }
            }
            if (isEdge)
                break;
        }

        if (!isEdge)
            cell->flags &= ~CellFlags::IS_EDGE;
        else
            edgeCells.push_back(cellLoc);
    }
    for (auto& cell : edgeCells)
    {
        for (auto& o : offsetsForPostGen)
        {
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];
                tempCell = get_offset_cell(cell, offset);
                if (tempCell != nullptr && !(tempCell->flags & (edgeFlags))/* && !(tempCell->flags & CellFlags::IS_EDGE2)*/)
                {
                    tempCell->flags |= CellFlags::IS_EDGE2;
                    edgeCells2.push_back(cell);
                    break;
                }
            }
        }
    }
    for (auto& cell : edgeCells2)
    {
        for (auto& o : offsetsForPostGen)
        {
            for (int i = 0; i < o.dx.size(); i++)
            {
                offset[0] = o.dx[i];  offset[1] = o.dy[i];  offset[2] = o.dz[i];
                tempCell = get_offset_cell(cell, offset);
                if (tempCell != nullptr && !(tempCell->flags & (edgeFlags))/* && !(tempCell->flags & CellFlags::IS_EDGE2)*/)
                {
                    tempCell->flags |= CellFlags::IS_EDGE3;
                    break;
                }
            }
        }
    }

}

void World::clean_up_flags()
{
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = get_chunk(chunkLoc);

        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            for (auto& cCrd : chunk->validCells)
            {
                Cell* cell = get_cell(cCrd);
                cell->flags &= ~(CellFlags::REFRESH);
            }
        }
        chunk->flags &= ~ChunkFlags::REFRESH_THIS_CHUNK;
    }
}
void World::clear_bad_nodes()
{
    nodeCullingTimer.Start();

    for (auto& graphNode : graph) 
    {
        if (!(graphNode.second->flags & GraphFlags::IS_NEW))
            continue;
        std::vector<GraphNode*> neighborsToRemove; 

        for (auto const& neighborPair : graphNode.second->neighbors)
        {
            GraphNode* neighborNode = neighborPair.second; 

            Vec3 start = neighborNode->vertex, end = graphNode.second->vertex; start.z = neighborNode->max.z + 3.0; end.z = graphNode.second->max.z + 3.0;
            tracer->traceLine(&trace_data, start, {-2,-2,-2 }, { 2,2,2 }, end, 0, 1, 0);

            if (trace_data.entityNum == 1022 && (abs(std::acos(trace_data.plane.normal.z)) > 0.792310))
            {
                neighborsToRemove.push_back(neighborNode);
            }
        }

        for (auto const& neighborToRemove : neighborsToRemove)
        {
            graphNode.second->neighbors.erase((uintptr_t)neighborToRemove);
        }

        for (auto const& neighborToRemove : neighborsToRemove)
        {
            neighborToRemove->neighbors.erase((uintptr_t)graphNode.second);
        } 
    }

    nodeCullingTimer.Stop();
}
void World::scan_find_this_island(GraphNode*startNode)
{
    if (startNode == nullptr || startNode->islandNum != 0)
        return;

    std::queue<GraphNode*> q;
    GraphNode* nextNode = nullptr;
    int islandPopulation = 1;
    islandsCount += 1;
    uint16_t newIslandNum = islandsCount;

    q.push({ startNode });
    startNode->flags |= GraphFlags::IS_VISITED;
    startNode->islandNum = newIslandNum;

    Island newIsland; newIsland.size = 1;

    newIsland.islandChunks.insert(startNode->chunksOccupied.begin(), startNode->chunksOccupied.end());

    while (!q.empty())
    {
        GraphNode* current = q.front();
        q.pop();
        for (auto&neighbor: current->neighbors)
        {
            nextNode = neighbor.second;

            if (
                !(nextNode->flags & GraphFlags::IS_VISITED)
                && !(nextNode->flags & CellFlags::IS_RESCANNED)
                && nextNode->islandNum == 0
                )
            {
                newIsland.islandChunks.insert(nextNode->chunksOccupied.begin(), nextNode->chunksOccupied.end());
                nextNode->flags |= GraphFlags::IS_VISITED;
                nextNode->islandNum = newIslandNum;
                islandPopulation++;
                q.push(nextNode);
            }
        }
    }

    newIsland.size = islandPopulation;

    islands.insert({ newIslandNum, newIsland });
}
bool World::scan_find_all_islands(std::vector<GraphNode*>& graphTemp)
{
    if (graphTemp.empty())
        return true;

    GraphNode* startNode = graphTemp[0];

    scan_find_this_island(startNode);

    std::vector<GraphNode*> graphNodesLeft;
    for (auto& gn : graph)
    {
        if (gn.second->islandNum == 0)
            graphNodesLeft.push_back(gn.second);
        gn.second->flags &= ~GraphFlags::IS_VISITED;
    }

    graphTemp = graphNodesLeft;
}
void World::redo_edge_scans()
{
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = get_chunk(chunkLoc);

        chunk->flags |= ChunkFlags::REFRESH_THIS_CHUNK;

        for (auto& cCrd : chunk->validCells)
        {
            Cell* cell = get_cell(cCrd);
            cell->flags |= (CellFlags::REFRESH);
            cell->flags &= ~(CellFlags::IS_EDGE | CellFlags::IS_EDGE2 | CellFlags::IS_EDGE3);
        }
    }

    //scan for edge
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge(chunk);
        }
    }
    //scan for edge2
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge2(chunk);
        }
    }
    //scan for edge3
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge3(chunk);
        }
    }

    clean_up_flags();

    islands.clear();
    islandsCount = 0;
    std::vector<GraphNode*> archipelago;
    for (auto& node : graph)
    {
        node.second->islandNum = 0;
        archipelago.push_back(node.second);
    }

    int breakCounter = 0;

    islandScanTimer.Start();
    while (!scan_find_all_islands(archipelago))
    {
        breakCounter++;
        if (breakCounter > 400)
            break;
    }
    islandScanTimer.Stop();
}
void World::postgen_scans()
{
    cellsPostGenTimer.Start();

    //scan for edge
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge(chunk);
        }
    }
    //scan for edge2
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge2(chunk);
        }
    }
    //scan for edge3
    for (auto& chunkLoc : validChunks)
    {
        Chunk* chunk = chunks[chunkLoc];
        if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
        {
            postgen_scan_specific_chunk_edge3(chunk);
        }
    }

    mesh_splitter();
    clean_up_flags();

    cellsPostGenTimer.Stop();
}
void World::add_new_area(CellCoordinates&cc)
{

    Vec3_ui8 chLoc = get_chunk_coordinates_from_index(cc.chunkLocation);
    Vec3_ui8 cLoc = unpack_coordinates(cc.cellLocation);

    //only scan below if our cell is invalid
    if (get_cell(chLoc, cLoc) != nullptr)
        return;

    Vec3 scanLocation = get_cell_float_coordinates_from_location(cc);


    //scan below
    float scanDepth = 3;
    int8_t offsetDown[3]{ 0,0,-1 };


    for (int i = 0; i < scanDepth; i++)
    {
        get_offset_location(chLoc, cLoc, offsetDown, scanLocation);

        uint16_t entNum = 0;
        uint32_t flag = CellFlags::NONE;

        scan_location(scanLocation, flag, entNum);

        if (flag != CellFlags::NONE && !check_if_ent_is_opening(entNum))
        {
            Cell* newCell = nullptr;
            CellCoordinates newCellCrd{ get_chunk_index(chLoc), pack_coordinates(cLoc) };
            add_cell_manually(newCellCrd, flag);
            newCell = get_cell(newCellCrd);

            flood(newCell);
            cleanup_generated_cells();
            postgen_scans();
            scan_find_this_island(newCell->graphNode);
            for (auto& gn : graph)
                gn.second->flags &= ~GraphFlags::IS_VISITED;
            return;
        }
    }

}

CellCoordinates World::cast_world_ray(const Vec3& start, const Vec3& uvec, const float& rayLength, CubeFaces& cubeFace, Vec3& intersection)
{
    return cast_world_ray_basic(start, uvec, rayLength, cubeFace, intersection);
}
CellCoordinates World::cast_world_ray(const Vec3& start, const Vec3& end, CubeFaces& cubeFace, Vec3& intersection)
{
    Vec3 distVec = end - start;
    return cast_world_ray_basic(start, vecs::NormalizeVector(distVec), vecs::VecMagnitude(distVec), cubeFace, intersection);
}
CubeFaces World::line_cube_intersection_with_faces(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& cubeMin, const Vec3& cubeMax, double rayLength, Vec3& intersection)
{
    double tNear = -std::numeric_limits<double>::infinity();
    double tFar = std::numeric_limits<double>::infinity();
    CubeFaces faceHit = CubeFaces::NONE; // Initialize faceHit to 0 (no hit)
    int dimensionIndex = -1; // Keep track of the dimension that determined tNear

    intersection = 0;

    for (int i = 0; i < 3; ++i) {
        double origin, direction, minBound, maxBound;
        if (i == 0) {
            origin = rayOrigin.x;
            direction = rayDirection.x;
            minBound = cubeMin.x;
            maxBound = cubeMax.x;
        }
        else if (i == 1) {
            origin = rayOrigin.y;
            direction = rayDirection.y;
            minBound = cubeMin.y;
            maxBound = cubeMax.y;
        }
        else { // i == 2
            origin = rayOrigin.z;
            direction = rayDirection.z;
            minBound = cubeMin.z;
            maxBound = cubeMax.z;
        }

        if (std::abs(direction) < std::numeric_limits<double>::epsilon()) {
            // Ray is parallel to the slab
            if (origin < minBound || origin > maxBound) {
                return CubeFaces::NONE; // Ray origin is outside slab, no intersection
            }
        }
        else {
            double t1 = (minBound - origin) / direction;
            double t2 = (maxBound - origin) / direction;

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            if (t1 > tNear) { // If t1 is the new tNear, update dimensionIndex
                tNear = std::max(tNear, t1);
                dimensionIndex = i; // Store the dimension index
            }
            else {
                tNear = std::max(tNear, t1); // Otherwise, just update tNear
            }
            tFar = std::min(tFar, t2);

            if (tNear > tFar) {
                return CubeFaces::NONE;
            }
            if (tFar < 0) {
                return CubeFaces::NONE;
            }
        }
    }

    if (tNear > rayLength) {
        return CubeFaces::NONE;
    }

    if (tNear <= tFar) {

        intersection.x = rayOrigin.x + tNear * rayDirection.x;
        intersection.y = rayOrigin.y + tNear * rayDirection.y;
        intersection.z = rayOrigin.z + tNear * rayDirection.z;

        // Determine face based on dimensionIndex and ray direction
        if (dimensionIndex == 1) { // Y-axis (dimension 1)
            if (rayDirection.y > 0) faceHit = CubeFaces::BACK; // Bottom face (1) - Negative Y
            else faceHit = CubeFaces::FRONT; // Top face (2) - Positive Y
        }
        else if (dimensionIndex == 0) { // X-axis (dimension 0)
            if (rayDirection.x > 0) faceHit = CubeFaces::LEFT; // Left face (3) - Negative X
            else faceHit = CubeFaces::RIGHT; // Right face (4) - Positive X
        }
        else if (dimensionIndex == 2) { // Z-axis (dimension 2)
            if (rayDirection.z > 0) faceHit = CubeFaces::BOTTOM; // Front face (5) - Negative Z
            else faceHit = CubeFaces::TOP; // Back face (6) - Positive Z
        }
    }

    return faceHit;
}
bool World::line_cube_intersection(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& cubeMin, const Vec3& cubeMax, double rayLength)
{
    double tNear = -std::numeric_limits<double>::infinity();
    double tFar = std::numeric_limits<double>::infinity();

    for (int i = 0; i < 3; ++i) {
        double origin, direction, minBound, maxBound;
        if (i == 0) {
            origin = rayOrigin.x;
            direction = rayDirection.x;
            minBound = cubeMin.x;
            maxBound = cubeMax.x;
        }
        else if (i == 1) {
            origin = rayOrigin.y;
            direction = rayDirection.y;
            minBound = cubeMin.y;
            maxBound = cubeMax.y;
        }
        else { // i == 2
            origin = rayOrigin.z;
            direction = rayDirection.z;
            minBound = cubeMin.z;
            maxBound = cubeMax.z;
        }

        if (std::abs(direction) < std::numeric_limits<double>::epsilon()) 
            {
            // Ray is parallel to the slab
            if (origin < minBound || origin > maxBound) {
                return false; // Ray origin is outside slab, no intersection
            }
        }
        else {
            double t1 = (minBound - origin) / direction;
            double t2 = (maxBound - origin) / direction;

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            if (t1 > tNear) { // If t1 is the new tNear, update dimensionIndex
                tNear = std::max(tNear, t1);
            }
            else {
                tNear = std::max(tNear, t1); // Otherwise, just update tNear
            }
            tFar = std::min(tFar, t2);

            if (tNear > tFar) {
                return false;
            }
            if (tFar < 0) {
                return false;
            }
        }
    }

    if (tNear > rayLength) {
        return false;
    }

    return true;
}
CellCoordinates World::cast_world_ray_basic(const Vec3& start, const Vec3& uvec, const float& rayLength, CubeFaces&cubeFace, Vec3& intersection)
{
    int opCount = 0;
    float halfCell = WorldConstants::CELL_SIZE / 2;
    Vec3 min{ -halfCell ,-halfCell ,-halfCell }, max{ halfCell,halfCell,halfCell };
    std::map<float, CellCoordinates> hitCells;
    std::map<float, int> hitChunks;

    for (auto& ch : validChunks)
    {
        Chunk* chunk = get_chunk(ch);

        Vec3 chunkMin = chunk->locationFloat; Vec3 chunkMax = chunk->locationFloat; chunkMax += WorldConstants::CHUNK_LENGTH;
        Vec3 chunkCenter = chunk->locationFloat; chunkCenter += WorldConstants::CHUNK_LENGTH / 2;



        if (!line_cube_intersection(start, uvec, chunkMin, chunkMax, rayLength))
            continue;
        else
        {
            std::pair<float, int> pChunk{ vecs::VecDistance(start, chunkCenter), ch };
            hitChunks.insert(pChunk);
        }
    }

    for (auto& hitCh : hitChunks)
    {
        Chunk* chunk = get_chunk(hitCh.second);

        bool isExit = false;
        for (auto& c : chunk->validCells)
        {
            Cell* cell = get_cell(c);
            Vec3 cellCenter = cell->GetCenter();
            Vec3 cubeMin = cellCenter, cubeMax = cellCenter;
            cubeMin -= halfCell;
            cubeMax += halfCell;
            if (line_cube_intersection(start, uvec, cubeMin, cubeMax, rayLength))
            {
                std::pair<float, CellCoordinates> p{ vecs::VecDistance(start, cellCenter), c };
                hitCells.insert(p);
                isExit = true;
            }
            opCount++;
        }
        if (isExit)
            break;
    }

    auto it = hitCells.begin();

    if (it != hitCells.end())
    {
        Cell* c = get_cell(it->second);
        if (c)
        {
            Vec3 cellCenter = c->GetCenter();
            Vec3 cubeMin = cellCenter, cubeMax = cellCenter;
            cubeMin -= halfCell;
            cubeMax += halfCell;
            cubeFace = line_cube_intersection_with_faces(start, uvec, cubeMin, cubeMax, rayLength, intersection);

            return it->second;
        }
    }
    return {0,0};
}

void World::flood(Cell* start)
{
    cellsGenTimer.Start();

    int8_t offset[3]{ 0,0,0 };
    int8_t offsetBelow[3]{ 0,0,-1 }; int8_t offsetAbove[3]{ 0,0,1 };
    int exitCounter = 0;
    int repetitionsCounter = 0;

    std::queue<Cell*> q;
    uint16_t entNum = 0;


    scan_location(start->GetCenter(), start->flags, start->entNum);
    q.push(start);

    
    Cell* current = nullptr;
    Vec3_ui8 nextCellLoc;
    Vec3_ui8 nextChunkLoc;
    Vec3 nextFloatLoc;
    Chunk* nextChunk = start->parentChunk;

    while (!q.empty() && exitCounter < 200000)
    {

        current = q.front();
        q.pop();

        //get current cell data//
        Vec3_ui8 currentCellLoc = unpack_coordinates(current->loc);
        Vec3_ui8 currentChunkLoc = current->parentChunk->chunkLocation;
        Vec3 currentFloatLoc = current->GetCenter();
        Chunk* currentChunk = current->parentChunk;
        //get current cell data//

        for (int i = 0; i < dx.size(); i++)
        {
            offset[0] = dx[i];  offset[1] = dy[i];  offset[2] = dz[i];

            nextCellLoc = currentCellLoc;
            nextChunkLoc = currentChunkLoc;
            nextFloatLoc = currentFloatLoc;

            get_offset_location(nextChunkLoc, nextCellLoc, offset, nextFloatLoc);

            repetitionsCounter++;

            Chunk* ch = get_chunk(nextChunkLoc);

            //if cell exists we skip it
          
            if (ch && ch->cells[ch->get_cell_index(nextCellLoc)] != nullptr)
                continue;

            if (currentChunk != ch)
            {
                nextChunk = add_chunk(nextChunkLoc);
            }
            else nextChunk = currentChunk;

            if (nextChunk == nullptr)
                continue;

            uint16_t entNum = 0;
            uint32_t flag = 0;

            scan_location(nextFloatLoc, flag, entNum);

            if (flag != CellFlags::NONE)
            {
                Cell* nextCell = nextChunk->add_cell_empty(nextCellLoc);

                if (flag & CellFlags::IS_MOVER)
                {
                    CellCoordinates cellToTest = { nextChunk->index, pack_coordinates(nextCellLoc) };
                    int8_t moverOffset[3]{ 0,0,0 };
                    bool isMoverNeighborDetected = false;
                    for (int i = 0; i < findMoverNeighborsDX.size(); i++)
                    {
                        moverOffset[0] = findMoverNeighborsDX[i];  moverOffset[1] = findMoverNeighborsDY[i];  moverOffset[2] = findMoverNeighborsDZ[i];

                        CellCoordinates lowerCellToTest = cellToTest;
                        lowerCellToTest = get_offset_coordinates(lowerCellToTest, moverOffset);
                        Cell* cellMoverOrNot = get_cell(lowerCellToTest);
                        if (cellMoverOrNot && (cellMoverOrNot->flags & CellFlags::IS_MOVER))
                        {
                            isMoverNeighborDetected = true;
                            break;
                        }
                    }
                    if (isMoverNeighborDetected)
                        continue;
                }


                create_offset_cell(nextChunkLoc, nextCellLoc, offsetBelow);
                create_offset_cell(nextChunkLoc, nextCellLoc, offsetAbove);

                nextCell->flags = flag;
                nextCell->entNum = entNum;
                nextChunk->validCellsCount++;

                q.push(nextCell);
            }
        }
        exitCounter++;
    }
    cellsGenTimer.Stop();
}

//WORLD--------------------------------------------------------------------------------------------------------

//PATHFINDER------------------
void World::get_graph_neighbors(std::vector<CellCoordinates>& cells)
{
    int8_t offset[3];
    for (auto& c : cells)
    {
        Cell* cell = get_cell(c);
        GraphNode* node = cell->graphNode;
        if (!node || (node->flags & GraphFlags::IS_BANNED))
            continue;

        int counter = 0;
        for (int i = 0; i < findNeighborsAllDX.size(); i++)
        {
            offset[0] = findNeighborsAllDX[i];  offset[1] = findNeighborsAllDY[i];  offset[2] = findNeighborsAllDZ[i];
            Cell* neighbor = get_offset_cell(cell, offset);

            if (neighbor && neighbor->graphNode && neighbor->graphNode != node && !(neighbor->flags & CellFlags::IS_BANNED))
            {
                counter++;


                if ((cell->flags & CellFlags::IS_ELEVATOR_DETECTOR) && (neighbor->flags & CellFlags::IS_ELEVATOR_BRIDGE))
                {
                        node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                        neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                else if ((cell->flags & CellFlags::IS_ELEVATOR_DETECTOR) && (neighbor->flags & CellFlags::IS_ELEVATOR_DETECTOR_UP))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                else if ((cell->flags & (CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP)) && (neighbor->flags & CellFlags::IS_ELEVATOR_COLUMN))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                else if ((cell->flags & CellFlags::IS_ELEVATOR_COLUMN) && (neighbor->flags & CellFlags::IS_ELEVATOR_COLUMN))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                else if ((cell->flags & CellFlags::IS_ELEVATOR_BRIDGE) 
                    && !(neighbor->flags & (CellFlags::ISOLATED_FLAGS)))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                if ((cell->flags & CellFlags::IS_ELEVATOR_BRIDGE) && (neighbor->flags & CellFlags::IS_ELEVATOR_BRIDGE))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                else if ((cell->flags & CellFlags::IS_JUMP) && !(neighbor->flags & CellFlags::ISOLATED_FLAGS))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }
                        
                if (!(cell->flags & CellFlags::ISOLATED_FLAGS) && !(neighbor->flags & CellFlags::ISOLATED_FLAGS))
                {
                    node->neighbors[(uintptr_t)neighbor->graphNode] = neighbor->graphNode;
                    neighbor->graphNode->neighbors[(uintptr_t)node] = node;
                }             


                if (neighbor->graphNode->islandNum != 0)
                    node->islandNum = neighbor->graphNode->islandNum;
                if (node->islandNum != 0 && neighbor->graphNode->islandNum == 0)
                    neighbor->graphNode->islandNum = node->islandNum;
            }
        }
    }
}
//unused
void World::split_mesh_chunk_simple(std::vector<CellCoordinates>& cells, const int& meshSize)
{
    Cell* offsetCellX = nullptr;
    Cell* offsetCellY = nullptr;
    Cell* offsetCellZP = nullptr;
    Cell* offsetCellZN = nullptr;

    int8_t offsetXP[3]{ 1,0,0 };
    int8_t offsetYP[3]{ 0,1,0 };
    int8_t offsetZP[3]{ 0,0,1 };
    int8_t offsetZN[3]{ 0,0,-1 };

    //bool isSplitIntoChunks = false;

    Cell* testCellsArray[WorldConstants::GRAPH_MESH_MAX_SIZE][WorldConstants::GRAPH_MESH_MAX_SIZE];

    Cell* startCell = nullptr;

    for (auto&cc: cells)
    {
        Cell* cell = get_cell(cc);
        startCell = cell;

        if (cell->graphNode)
            continue;

        offsetCellX = cell;
        offsetCellY = cell;

        memset(testCellsArray, 0, sizeof(testCellsArray));

        bool edgeDetected = false;

        uint32_t startChunkIndex = cell->parentChunk->index;


        for (int i = 0; i < meshSize; i++)
        {
            for (int j = 0; j < meshSize - 1; j++)
            {

                offsetCellY = get_offset_cell(offsetCellY, offsetYP);

                if (!offsetCellY)
                {
                    edgeDetected = true;
                    break;
                }

                if (offsetCellY && ((offsetCellY->flags & (CellFlags::IS_BANNED)) || offsetCellY->graphNode))
                {
                    edgeDetected = true;
                    break;
                }

                //disabled
                if (offsetCellY && (offsetCellY->parentChunk->index != startChunkIndex))
                {
                    edgeDetected = true;
                    break;
                }

                testCellsArray[i][j] = offsetCellY;

            }
            if (edgeDetected || i == meshSize - 1)
                break;
            offsetCellX = get_offset_cell(offsetCellX, offsetXP);

            if (!offsetCellX || (offsetCellX->flags & CellFlags::IS_BANNED) || offsetCellX->graphNode)
            {
                edgeDetected = true;
                break;
            }

            if (offsetCellX && (offsetCellX->parentChunk->index != startChunkIndex))
            {
                edgeDetected = true;
                break;
            }
            testCellsArray[i][meshSize - 1] = offsetCellX;
            offsetCellY = offsetCellX;
        }

        if (!edgeDetected)
        {
            GraphNode* newNode = nullptr;
            newNode = startCell->graphNode = new GraphNode();
            newNode->startCellLocation = pack_cell_and_chunk({ startCell->parentChunk->index, startCell->loc });
            newNode->flags |= GraphFlags::IS_NEW;

            for (int i = 0; i < meshSize; i++)
            {
                for (int j = 0; j < meshSize; j++)
                {
                    if (testCellsArray[i][j])
                        testCellsArray[i][j]->graphNode = newNode;
                }
            }

            if (meshSize == 1 && startCell->flags & CellFlags::IS_BANNED)
                newNode->flags |= GraphFlags::IS_BANNED;

            newNode->vertex = startCell->GetCenter();
            newNode->size = meshSize;
            newNode->vertex.x += WorldConstants::CELL_SIZE * meshSize / 2 - WorldConstants::CELL_SIZE / 2;
            newNode->vertex.y += WorldConstants::CELL_SIZE * meshSize / 2 - WorldConstants::CELL_SIZE / 2;

            graph[(uintptr_t)newNode] = newNode;

            float weight = 0;

            newNode->weight = weight;
        }
    }

}
void World::split_mesh_chunk(std::vector<CellCoordinates>& cells, const int& meshSize)
{
    CellCoordinates offsetCellX;
    CellCoordinates offsetCellY;
    CellCoordinates offsetCellZP;
    CellCoordinates offsetCellZN;
    CellCoordinates offsetCellZP_X;
    CellCoordinates offsetCellZN_X;

    int8_t offsetXP[3]{ 1,0,0 };
    int8_t offsetYP[3]{ 0,1,0 };
    int8_t offsetZP[3]{ 0,0,1 };
    int8_t offsetZN[3]{ 0,0,-1 };

    //bool isSplitIntoChunks = false;

    Cell* testCellsArray[WorldConstants::GRAPH_MESH_MAX_SIZE][WorldConstants::GRAPH_MESH_MAX_SIZE];
    Vec3_ui8 testCellsArray_locations[WorldConstants::GRAPH_MESH_MAX_SIZE][WorldConstants::GRAPH_MESH_MAX_SIZE];

    Cell* startCell = nullptr;

    int counter = 0;

    for (auto& cc : cells)
    {
        Cell* cell = get_cell(cc);
        startCell = cell;

        if (cell->graphNode || (cell->flags & CellFlags::IS_BANNED))
            continue;
        if ((cell->flags & CellFlags::ONE_CELL_ONE_NODE_FLAGS) && meshSize > 1)
        {
            continue;
        }

        memset(testCellsArray, 0, sizeof(testCellsArray));

        testCellsArray[0][0] = cell;
        testCellsArray_locations[0][0] = unpack_coordinates(cell->loc);

        Vec3_ui8 startCrd = unpack_coordinates(cell->loc);

        offsetCellX = cc;
        offsetCellY = cc;



        bool edgeDetected = false;

        uint32_t startChunkIndex = cell->parentChunk->index;

        Vec3 graph_min = cell->GetCenter(), graph_max = graph_min;

        for (int i = 0; i < meshSize; i++)
        {
            for (int j = 1; j < meshSize; j++)
            {

                offsetCellY = get_offset_coordinates(offsetCellY, offsetYP);
                Cell* tempCellY = get_cell(offsetCellY);

                offsetCellZP = get_offset_coordinates(offsetCellY, offsetZP);
                Cell* tempCellZP = get_cell(offsetCellZP);

                offsetCellZN = get_offset_coordinates(offsetCellY, offsetZN);
                Cell* tempCellZN = get_cell(offsetCellZN);

                if (!tempCellY && !tempCellZP && !tempCellZN)
                {
                    edgeDetected = true;
                    break;
                }

                //check if normal
                if (tempCellY && ((tempCellY->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellY->graphNode))
                {
                    edgeDetected = true;
                    break;
                }
                else if (tempCellZP && ((tempCellZP->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellZP->graphNode))
                {
                    edgeDetected = true;
                    break;
                }
                else if (tempCellZN && ((tempCellZN->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellZN->graphNode))
                {
                    edgeDetected = true;
                    break;
                }
                //check if normal

                //check chunk border
                if (offsetCellY.chunkLocation != startChunkIndex)
                {
                    edgeDetected = true;
                    break;
                }


                if (tempCellY)
                    testCellsArray[i][j] = tempCellY;
                else if (tempCellZP)
                    testCellsArray[i][j] = tempCellZP;
                else if (tempCellZN)
                    testCellsArray[i][j] = tempCellZN;
            }
            if (edgeDetected || i == meshSize - 1)
                break;

            counter++;

            offsetCellX = get_offset_coordinates(offsetCellX, offsetXP);
            Cell* tempCellX = get_cell(offsetCellX);

            offsetCellZP_X = get_offset_coordinates(offsetCellX, offsetZP);
            Cell* tempCellXZP = get_cell(offsetCellZP_X);

            offsetCellZN_X = get_offset_coordinates(offsetCellX, offsetZN);
            Cell* tempCellXZN = get_cell(offsetCellZN_X);

            if (!tempCellX && !tempCellXZP && !tempCellXZN)
            {
                edgeDetected = true;
                break;
            }

            //check if normal
            if (tempCellX && ((tempCellX->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellX->graphNode))
            {
                edgeDetected = true;
                break;
            }
            else if (tempCellXZP && ((tempCellXZP->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellXZP->graphNode))
            {
                edgeDetected = true;
                break;
            }
            else if (tempCellXZN && ((tempCellXZN->flags & (CellFlags::ONE_CELL_ONE_NODE_FLAGS)) || tempCellXZN->graphNode))
            {
                edgeDetected = true;
                break;
            }

            if (offsetCellX.chunkLocation != startChunkIndex)
            {
                edgeDetected = true;
                break;
            }

            if (tempCellX)
                testCellsArray[i + 1][0] = tempCellX;
            else if (tempCellXZP)
                testCellsArray[i + 1][0] = tempCellXZP;
            else if (tempCellXZN)
                testCellsArray[i + 1][0] = tempCellXZN;

            offsetCellY = offsetCellX;
        }

        if (!edgeDetected)
        {
            GraphNode* newNode = nullptr;
            newNode = startCell->graphNode = new GraphNode();
            newNode->flags |= GraphFlags::IS_NEW;

            float totalWeight = 0;
            float weightEdge = 0;
            float weightEdge2 = 0;
            float weightEdge3 = 0;

            //set special flags
            if (startCell->flags & CellFlags::IS_WALKABLE_DOWN)
            {
                newNode->flags |= GraphFlags::IS_WALKABLE_DOWN;
            }
            else if (startCell->flags & CellFlags::IS_WALKABLE_UP)
            {
                newNode->flags |= GraphFlags::IS_WALKABLE_UP;
            }
            else if (startCell->flags & CellFlags::IS_ELEVATOR_COLUMN)
            {
                newNode->flags |= GraphFlags::IS_ELEVATOR_COLUMN_NODE;
            }
            else if (startCell->flags & CellFlags::IS_ELEVATOR_BRIDGE)
            {
                newNode->flags |= GraphFlags::IS_BRIDGE_NODE;
            }
            else if (startCell->flags & (CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP))
            {
                newNode->flags |= GraphFlags::IS_ELEVATOR;
            }


            //weights
            for (int i = 0; i < meshSize; i++)
            {
                for (int j = 0; j < meshSize; j++)
                {
                    Cell* tempCell = testCellsArray[i][j];
                    tempCell->graphNode = newNode;    
                    newNode->cells.push_back(pack_cell_and_chunk({ tempCell->parentChunk->index, tempCell->loc}));
                    newNode->chunksOccupied.insert(tempCell->parentChunk->index);
                    //get weights

                    if (tempCell->flags & CellFlags::IS_EDGE)
                    {
                        totalWeight += 3.5 * WorldConstants::CELL_SIZE;
                    }
                    else if (tempCell->flags & CellFlags::IS_EDGE2)
                    {
                        totalWeight += 1.6 * WorldConstants::CELL_SIZE;
                    }
                    else if (tempCell->flags & CellFlags::IS_EDGE3)
                    {
                        totalWeight += 1 * WorldConstants::CELL_SIZE;
                    }

                    if ((tempCell->flags & CellFlags::IS_MOVER) && !(tempCell->flags & CellFlags::IS_ELEVATOR_BRIDGE))
                    {
                        totalWeight += 100;
                    }

                    //get bounding box
                    Vec3 cellCenter = tempCell->GetCenter();
                    if (graph_min.z > cellCenter.z)
                        graph_min.z = cellCenter.z;
                    if (graph_max.x < cellCenter.x)
                        graph_max.x = cellCenter.x;
                    if (graph_max.y < cellCenter.y)
                        graph_max.y = cellCenter.y;
                    if (graph_max.z < cellCenter.z)
                        graph_max.z = cellCenter.z;
                }
            }

            //insert in chunk
            get_cell(unpack_cell_and_chunk(newNode->cells[0]))->parentChunk->nodes.insert({(uintptr_t)newNode, newNode });

            if (meshSize > 2)
                totalWeight /= (meshSize * 1.5f);
            else
                totalWeight /= meshSize;

            graph_max = graph_max + WorldConstants::CELL_SIZE/2;
            graph_min = graph_min - WorldConstants::CELL_SIZE / 2;

            newNode->min = graph_min;
            newNode->max = graph_max;

            if (meshSize == 1 && startCell->flags & CellFlags::IS_BANNED)
                newNode->flags |= GraphFlags::IS_BANNED;

            newNode->vertex = startCell->GetCenter();
            newNode->size = meshSize;
            newNode->vertex.x += WorldConstants::CELL_SIZE * meshSize / 2 - WorldConstants::CELL_SIZE / 2;
            newNode->vertex.y += WorldConstants::CELL_SIZE * meshSize / 2 - WorldConstants::CELL_SIZE / 2;

            newNode->weight = (int)totalWeight;

            if (newNode->flags & GraphFlags::IS_BRIDGE_NODE)
                newNode->weight = 36;
            else if (startCell->flags & CellFlags::IS_HIGHCOST)
                newNode->weight = 9999;
            else if (startCell->flags & CellFlags::IS_WALKABLE_DOWN)
                newNode->weight = 0;

            graph[(uintptr_t)newNode] = newNode;
        }
    }

}
void World::mesh_splitter()
{
    splitMeshTimer.Start();
    const size_t arSize = graphNodeSizes[0];

    for (auto& s : graphNodeSizes)
    {
        for (auto& chunkLoc : validChunks)
        {
            Chunk* chunk = get_chunk(chunkLoc);
            if (chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK)
            {
                split_mesh_chunk(chunk->validCells, s);
            }
        }
    }

    int8_t offset[3];
    
    for (auto& ch : validChunks)
    {
        Chunk* chunk = get_chunk(ch);
        if (!(chunk->flags & ChunkFlags::REFRESH_THIS_CHUNK))
            continue;

        get_graph_neighbors(chunk->validCells);
    }


    clear_bad_nodes();

    //no longer new
    for (auto& n : graph)
    {
        n.second->flags &= ~GraphFlags::IS_NEW;
    }


    splitMeshTimer.Stop();
}
PathfindingErrors World::generate_path(GraphNode* start, GraphNode* end, std::vector<uintptr_t>& path)
{

    if ((start == nullptr || (start->flags & (GraphFlags::IS_BANNED | GraphFlags::IS_BRIDGE_NODE | GraphFlags::IS_ELEVATOR_COLUMN_NODE))) || (end == nullptr || (end->flags & GraphFlags::IS_BANNED)))
    {
        return PathfindingErrors::START_OR_FINISH_WAS_INVALID;
    }

    pathGenTimer.Start();

    if (start == end)
    {
        pathGenTimer.Stop();
        path.push_back((uintptr_t)end);
        return  PathfindingErrors::START_AND_FINISH_SAME_NODE;
    }

    bool isIgnoreExplosionNodes = false;
    if (end->flags & GraphFlags::IS_AFFECTED_BY_EXPLOSION)
        isIgnoreExplosionNodes = true;

    std::vector<GraphNode*> ResetFlagsVector;
    std::priority_queue<GraphNode*, std::vector<GraphNode*>, GraphNodeComparator> openSet;

    Vec3 st = start->vertex;
    Vec3 en = end->vertex;

    start->g = 0; start->h = vecs::VecDistance(st, en); start->f = start->h; start->parent = nullptr; start->flags |= GraphFlags::IS_VISITED;
    ResetFlagsVector.push_back(start);

    openSet.push(start);

    int counter = 0;
    while (!openSet.empty())
    {
        counter++;
        if (counter > 80000)
        {
            for (auto& n : ResetFlagsVector)
            {
                n->flags &= ~GraphFlags::IS_VISITED;
                n->parent = nullptr;
                n->f = 0;
                n->g = 0;
                n->h = 0;
            }
            pathGenTimer.Stop();
            return PathfindingErrors::TOO_FAR_AWAY;

        }

        GraphNode* current = openSet.top();
        openSet.pop();

        //end trigg
        if ((current == end))
        {
            GraphNode* currentNode = current;
            int cnt = 0;
            while (currentNode != nullptr)
            {
                cnt++;
                currentNode->flags |= GraphFlags::IS_PATH_NODE;
                path.push_back((uintptr_t)currentNode);
                currentNode = currentNode->parent;
            }

            for (auto& n : ResetFlagsVector)
            {
                n->flags &= ~GraphFlags::IS_VISITED;
                n->parent = nullptr;
                n->f = 0;
                n->g = 0;
                n->h = 0;
            }

            pathGenTimer.Stop();
            return PathfindingErrors::SUCCESS;
        }

        for (auto& neigh : current->neighbors)
        {
            if (neigh.second->flags & GraphFlags::IS_BANNED)
                continue;

            if (!isIgnoreExplosionNodes && (neigh.second->flags & GraphFlags::IS_AFFECTED_BY_EXPLOSION))
                continue;

            if (neigh.second->flags & GraphFlags::IS_WALKABLE_DOWN)
            {
                if (neigh.second->vertex.z < current->vertex.z)
                    continue;
            }


            int newH = vecs::VecDistance(neigh.second->vertex, en);
            int newG = current->g + vecs::VecDistance(neigh.second->vertex, current->vertex) + neigh.second->weight;

            if (!(neigh.second->flags & GraphFlags::IS_VISITED))
            {
                neigh.second->flags |= GraphFlags::IS_VISITED;
                neigh.second->parent = current;
                neigh.second->g = newG;
                neigh.second->h = newH;
                neigh.second->f = newG + newH;

                openSet.push(neigh.second);
                ResetFlagsVector.push_back(neigh.second);
            }
            else
            {
                if (newG < neigh.second->g)
                {
                    neigh.second->g = newG;
                    neigh.second->f = newH + newG;
                    neigh.second->parent = current;
                }
            }
        }



    }

    for (auto& n : ResetFlagsVector)
    {
        n->flags &= ~GraphFlags::IS_VISITED;
        n->parent = nullptr;
        n->f = 0;
        n->g = 0;
        n->h = 0;
    }

    pathGenTimer.Stop();
    return PathfindingErrors::UNREACHABLE;
}

//MOVER ENT--------------------------------------------------------------------------------------------------------
MoverEntity::MoverEntity(const uint16_t& _entNum) : entNum(_entNum)
{
    Scan();
    IsUpdated();
}
void MoverEntity::Scan()
{
    if (entNum == 0)
        return;
    address = entListBaseAddress + entNum * entityOffset;
    isOpening = *(int*)(address + movEntOffs[MovEntOffs::IS_OPENING]);
}
void MoverEntity::ForceUpdate()
{
    forceUpdate = true;
}
bool MoverEntity::IsUpdated()
{
    int lastTimeUpdated = *(int*)(address + movEntOffs[MovEntOffs::LAST_TIME_UPDATED]);
    int lastTimeRendered = *(int*)(address + movEntOffs[MovEntOffs::LAST_TIME_RENDERED]);
    int ticker = *(int*)(address + movEntOffs[MovEntOffs::TICKER]);
    int hp = *(int*)(address + movEntOffs[MovEntOffs::HP]);
    int maxHp = *(int*)(address + movEntOffs[MovEntOffs::MAX_HP]);
    bool isRendered = *(int*)(address + movEntOffs[MovEntOffs::IS_RENDERED]);

    isOpening = *(int*)(address + movEntOffs[MovEntOffs::IS_OPENING]);

    if (lastTimeUpdatedPrev != lastTimeUpdated && !isOpening && lastTimeRendered)
    {
        lastTimeUpdatedPrev = lastTimeUpdated;
        return true;
    }

    if (isBridge && lastTimeRendered && lastTimeRendered != lastTimeRenderedPrev)
    {
        lastTimeRenderedPrev = lastTimeRendered;
        return true;
    }

    if (maxHp && hp == 0 && !isRendered && !prevHpState)
    {
        prevHpState = true;
        return true;
    }
    if (!maxHp)
        prevHpState = false;

    bool isDoorUnlocked = *(int*)(address + movEntOffs[MovEntOffs::IS_DOOR_UNLOCKED]);

    if (isDoorUnlocked && !prevLockedState)
    {
        prevLockedState = true;
        return true;
    }
    if (isDoorUnlocked == 0)
        prevLockedState = false;

    if (forceUpdate)
    {
        forceUpdate = false;
        return true;
    }


    return false;
}
//MOVER ENT--------------------------------------------------------------------------------------------------------

//TRIGGER----------------------------

Trigger::Trigger(const CellCoordinates& _cellBot, const CellCoordinates& _cellTop)
{
    triggerBottom = _cellBot;
    triggerTop = _cellTop;
}
void Trigger::set_primary_states()
{
    if (entBottom < 1022 && entBottom == entityNum && entTop > 1022 && !(elevatorStates & ElevatorStates::MOVING))
    {
        elevatorStates |= ElevatorStates::ACTIVE;
    }
    else
    {
        elevatorStates &= ~ElevatorStates::ACTIVE;
    }

    if (entBottom == 1022 || entTop == 1022)
    {
        elevatorStates |= ElevatorStates::OUTOFRENDER;
        elevatorStates &= ~ElevatorStates::MOVING;
    }

    if (entBottom >= 1022 && entTop >= 1022 && !(elevatorStates & ElevatorStates::MOVING))
    {
        elevatorStates |= ElevatorStates::OUTOFRENDER;
        elevatorStates &= ~ElevatorStates::MOVING;
    }
    else
        elevatorStates &= ~ElevatorStates::OUTOFRENDER;

    
}
void Trigger::set_secondary_states(const uint16_t& playerStandingEntId)
{
    if (!(elevatorStates & ElevatorStates::LINKED))
        return;

    if ((elevatorStates & ElevatorStates::OUTOFRENDER) && (other->elevatorStates & ElevatorStates::OUTOFRENDER))
    {
        elevatorStates |= ElevatorStates::OUTOFRENDER;
        other->elevatorStates |= ElevatorStates::OUTOFRENDER;

    }
    else
    {
        elevatorStates &= ~ElevatorStates::OUTOFRENDER;
        other->elevatorStates &= ~ElevatorStates::OUTOFRENDER;
    }

    if ((elevatorStates & (ElevatorStates::ACTIVE)) && (elevatorStates & (ElevatorStates::BOTTOM)))
    {
        elevatorStates |= ElevatorStates::BOTTOM_ACTIVE;
        other->elevatorStates |= ElevatorStates::BOTTOM_ACTIVE;
    }

    else if ((elevatorStates & (ElevatorStates::ACTIVE)) && (elevatorStates & (ElevatorStates::TOP)))
    {
        elevatorStates |= ElevatorStates::TOP_ACTIVE;
        other->elevatorStates |= ElevatorStates::TOP_ACTIVE;
    }

    if (elevatorStates & (ElevatorStates::MOVING | ElevatorStates::OUTOFRENDER))
    {
        elevatorStates &= ~ElevatorStates::TOP_ACTIVE;
        other->elevatorStates &= ~ElevatorStates::TOP_ACTIVE;
        elevatorStates &= ~ElevatorStates::BOTTOM_ACTIVE;
        other->elevatorStates &= ~ElevatorStates::BOTTOM_ACTIVE;
    }

    isPlayerOnMe = playerStandingEntId == entityNum;

    if (elevatorStates & (ElevatorStates::MOVING))
    {
        delayTime = 0;
        elevatorResetDelayTimer.Stop();
        redoPathLock = false;
        other->redoPathLock = false;
    }
    else
        delayTime = elevatorResetDelayTimer.ElapsedContinuous();

    bool isUp = elevatorStates & ElevatorStates::TOP_ACTIVE;
    bool isDown = elevatorStates & ElevatorStates::BOTTOM_ACTIVE;

    elevatorStates &= ~ElevatorStates::REDO_PATH;
    other->elevatorStates &= ~ElevatorStates::REDO_PATH;

    if (isUp || isDown)
    {
        //ON UP once
        if (oldElevatorState != isUp)
        {
            elevatorStateChangesCounter++;
            oldElevatorState = isUp;
        }

        if (!(elevatorStates & ElevatorStates::ACTIVATED_BY_PLAYER))
            deactivate();

        if (delayTime > readyForReactivationTimeLimit
            && elevatorStateChangesCounter == 1
            && !activationLock
            )
        {
            activationLock = true;
            elevatorStates |= ElevatorStates::READY_FOR_REACTIVATION;
        }

        if (elevatorStateChangesCounter >= 2 && delayTime > readyForReactivationTimeLimit)
            deactivate();
    }

    if (elevatorStates & (ElevatorStates::MOVING))
    {
        elevatorStates &= ~ElevatorStates::READY_FOR_REACTIVATION;
    }

    if (delayTime > deactivationResetTimeLimit)
    {
        deactivate();

    }
}

void Trigger::activate()
{
    if (!other)
        return;

   elevatorStates |= ElevatorStates::ACTIVATED_BY_PLAYER;
   other->elevatorStates |= ElevatorStates::ACTIVATED_BY_PLAYER;
   elevatorStates &= ~ElevatorStates::READY_FOR_REACTIVATION;
   other->elevatorStates &= ~ElevatorStates::READY_FOR_REACTIVATION;
}


void Trigger::deactivate()
{
    if (!other)
        return;

    elevatorStates &= ~ElevatorStates::READY_FOR_REACTIVATION;
    elevatorStates &= ~ElevatorStates::ACTIVATED_BY_PLAYER;
    elevatorStateChangesCounter = 0;
    delayTime = 0;
    elevatorResetDelayTimer.Stop();
    activationLock = false;

    other->elevatorStates &= ~ElevatorStates::READY_FOR_REACTIVATION;
    other->elevatorStates &= ~ElevatorStates::ACTIVATED_BY_PLAYER;
    other->elevatorStateChangesCounter = 0;
    other->delayTime = 0;
    other->elevatorResetDelayTimer.Stop();
    other->activationLock = false;
}

//--------