#pragma once

#define NOMINMAX
#include <vector>
#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <map>

#include "Utils.h"
#include "Vectors.h"
#include "Enums.h"

namespace WorldConstants
{
	//do NOT change chunksize
	constexpr uint32_t WORLD_HEIGHT_Z = 16, WORLD_WIDTH_Y = 32, WORLD_BREADTH_X = 32; //z y x
	constexpr uint32_t CHUNK_SIZE = 32, CELL_SIZE = 24, CHUNK_LENGTH = CELL_SIZE * CHUNK_SIZE;
	constexpr uint32_t HALF_CELL_SIZE = CELL_SIZE / 2;
	constexpr uint32_t WORLD_HEIGHT_X_WIDTH = WORLD_HEIGHT_Z * WORLD_WIDTH_Y;
	constexpr uint32_t WORLD_WIDTH_X_BREADTH = WORLD_BREADTH_X * WORLD_WIDTH_Y;
	constexpr uint32_t CHUNK_PLANE_SIZE = CHUNK_SIZE * CHUNK_SIZE;
	constexpr uint32_t CHUNK_ARRAY_SIZE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
	constexpr uint32_t WORLD_SIZE = WORLD_HEIGHT_Z * WORLD_WIDTH_Y * WORLD_BREADTH_X;
	constexpr uint32_t GRAPH_MESH_MAX_SIZE = 4;
}

class Cell;
class Chunk;
class World;


namespace CellFlags
{
	enum CellFlags
	{
		NONE                      = 0,
		WALKABLE	              = 1 << 0,
		IS_MOVER	              = 1 << 1,
		IS_CREATED	              = 1 << 2,
		IS_EDGE		              = 1 << 3,
		IS_EDGE2	              = 1 << 4,
		IS_EDGE3	              = 1 << 5,
		IS_BANNED	              = 1 << 6,
		REFRESH                   = 1 << 7,
		IS_RESCANNED              = 1 << 8,
		IS_IMMOVABLE_OBJECT       = 1 << 9,
		IS_BRIDGE                 = 1 << 10,
						          
						          
		IS_JUMP                   = 1 << 11,
		IS_WALKABLE_UP            = 1 << 12,
		IS_WALKABLE_DOWN          = 1 << 13,
		IS_ELEVATOR_DETECTOR      = 1 << 14,
		IS_ELEVATOR_DETECTOR_UP   = 1 << 15,
		IS_ELEVATOR_COLUMN        = 1 << 16,
		IS_ELEVATOR_BRIDGE        = 1 << 17,
		IS_ELEVATOR_BUTTON_1      = 1 << 18, //button for elevators that return automatically
		IS_HIGHCOST               = 1 << 19,
		IS_ELEVATOR_BUTTON_2      = 1 << 20, //button for elevators that need to be pressed twice
		IS_ELEVATOR_BUTTON_CALL   = 1 << 21, //for elevators that require an extra button to call them
		IS_USE                    = 1 << 22,

		//flags that are saved
		SAVED_FLAGS = IS_JUMP | IS_USE | IS_WALKABLE_UP | IS_WALKABLE_DOWN | IS_BRIDGE | IS_IMMOVABLE_OBJECT | IS_ELEVATOR_DETECTOR | IS_ELEVATOR_DETECTOR_UP | IS_ELEVATOR_COLUMN | IS_ELEVATOR_BRIDGE | IS_ELEVATOR_BUTTON_1 | IS_ELEVATOR_BUTTON_2 | IS_HIGHCOST | IS_ELEVATOR_BUTTON_CALL,
		ONE_CELL_ONE_NODE_FLAGS = IS_JUMP | IS_USE | IS_BANNED | IS_WALKABLE_UP | IS_WALKABLE_DOWN | IS_IMMOVABLE_OBJECT | IS_ELEVATOR_DETECTOR | IS_ELEVATOR_DETECTOR_UP | IS_ELEVATOR_COLUMN | IS_ELEVATOR_BRIDGE | IS_ELEVATOR_BUTTON_1 | IS_ELEVATOR_BUTTON_2 | IS_HIGHCOST | IS_ELEVATOR_BUTTON_CALL,
		UNBANNABLE_FLAGS = IS_JUMP | IS_USE | IS_WALKABLE_UP | IS_WALKABLE_DOWN | IS_IMMOVABLE_OBJECT | IS_ELEVATOR_DETECTOR | IS_ELEVATOR_DETECTOR_UP | IS_ELEVATOR_COLUMN | IS_ELEVATOR_BRIDGE | IS_ELEVATOR_BUTTON_1 | IS_ELEVATOR_BUTTON_2 | IS_HIGHCOST | IS_ELEVATOR_BUTTON_CALL,
		ISOLATED_FLAGS = IS_ELEVATOR_DETECTOR | IS_ELEVATOR_DETECTOR_UP | IS_ELEVATOR_COLUMN | IS_ELEVATOR_BRIDGE,
	
	};
}

//cells that i can add in editor
static std::vector<std::pair<CellFlags::CellFlags, std::string>> specialCellFlagList
{
	{CellFlags::WALKABLE, "IS_NORMAL"},
	{CellFlags::IS_HIGHCOST, "IS_HIGHCOST"},
	{CellFlags::IS_JUMP, "IS_JUMP"},
	{CellFlags::IS_USE, "IS_USE"},
	{CellFlags::IS_WALKABLE_UP, "IS_WALKABLE_UP"},
	{CellFlags::IS_WALKABLE_DOWN, "IS_WALKABLE_DOWN"},
	{CellFlags::IS_ELEVATOR_DETECTOR, "IS_ELEVATOR_DETECTOR"},
	{CellFlags::IS_ELEVATOR_BUTTON_1, "IS_ELEVATOR_BUTTON_1"},
	{CellFlags::IS_ELEVATOR_BUTTON_2, "IS_ELEVATOR_BUTTON_2"},
	{CellFlags::IS_ELEVATOR_BUTTON_CALL, "IS_ELEVATOR_BUTTON_CALL"},
};

//display all flags
static std::map<CellFlags::CellFlags, std::string> cellFlagsList
{
	{CellFlags::NONE, "NONE"},
	{CellFlags::WALKABLE, "WALKABLE"},
	{CellFlags::IS_MOVER, "IS_MOVER"},
	{CellFlags::IS_CREATED, "IS_CREATED"},
	{CellFlags::IS_EDGE, "IS_EDGE"},
	{CellFlags::IS_EDGE2, "IS_EDGE2"},
	{CellFlags::IS_EDGE3, "IS_EDGE3"},
	{CellFlags::IS_BANNED, "IS_BANNED"},
	{CellFlags::IS_BRIDGE, "IS_BRIDGE"},
	{CellFlags::REFRESH, "REFRESH"},
	{CellFlags::IS_RESCANNED, "IS_RESCANNED"},
	{CellFlags::IS_IMMOVABLE_OBJECT, "IS_IMMOVABLE_OBJECT"},
	{CellFlags::IS_JUMP, "IS_JUMP"},
	{CellFlags::IS_WALKABLE_UP, "IS_WALKABLE_UP"},
	{CellFlags::IS_WALKABLE_DOWN, "IS_WALKABLE_DOWN"},
	{CellFlags::IS_ELEVATOR_DETECTOR, "IS_ELEVATOR_DETECTOR"},
	{CellFlags::IS_ELEVATOR_DETECTOR_UP, "IS_ELEVATOR_DETECTOR_UP"},
	{CellFlags::IS_ELEVATOR_COLUMN, "IS_ELEVATOR_COLUMN"},
	{CellFlags::IS_ELEVATOR_BRIDGE, "IS_ELEVATOR_BRIDGE"},
	{CellFlags::IS_ELEVATOR_BUTTON_1, "IS_ELEVATOR_BUTTON_1"},
	{CellFlags::IS_ELEVATOR_BUTTON_2, "IS_ELEVATOR_BUTTON_2"},
	{CellFlags::IS_ELEVATOR_BUTTON_CALL, "IS_ELEVATOR_BUTTON_CALL"},
	{CellFlags::IS_HIGHCOST, "IS_HIGHCOST"},
	{CellFlags::IS_USE, "IS_USE"},
};

enum class MovEntOffs : int
{
	IS_OPENING,
	LAST_TIME_UPDATED,
	IS_RENDERED,
	LAST_TIME_RENDERED,
	TICKER,
	HP,
	MAX_HP,
	IS_DOOR_UNLOCKED,
};

static std::map<MovEntOffs, uintptr_t> movEntOffs
{
	{MovEntOffs::IS_OPENING, 0x10},
	{MovEntOffs::LAST_TIME_UPDATED, 0x14},
	{MovEntOffs::IS_RENDERED, 0x218},
	{MovEntOffs::LAST_TIME_RENDERED, 0x228},
	{MovEntOffs::TICKER, 0x248},
	{MovEntOffs::HP, 0x170},
	{MovEntOffs::MAX_HP, 0x174},
	{MovEntOffs::IS_DOOR_UNLOCKED, 0xEC},
};

namespace ChunkFlags
{
	enum ChunkFlags
	{
		NONE,
		IS_CHUNK_ALREADY_EXIST = 1 << 0,
		REFRESH_THIS_CHUNK     = 1 << 1,
		IS_VISITED_BY_BOT      = 1 << 2,
	};
}

namespace WorldFlags
{
	enum WorldFlags
	{
		NONE,
		IS_GENERATED    = 1 << 0,
		IS_MAP_READ     = 1 << 1,
		IS_MAP_CHANGE   = 1 << 2,
		IS_SAVE_REQURED = 1 << 3,
	};
}

namespace PathfindingFlags
{
	enum PathfindingFlags
	{
		IS_GENERATED = 1 << 0,
		IS_SUCCESS   = 1 << 1,
		IS_UPDATED   = 1 << 2,
	};
}

namespace GraphFlags
{
	enum GraphFlags
	{
		NONE,
		IS_NEW                   = 1 << 0,
		IS_BANNED                = 1 << 1,
		IS_VISITED               = 1 << 2,
		IS_TARGET                = 1 << 3,
		IS_AFFECTED_BY_EXPLOSION = 1 << 4,
		IS_NEAR_SABER            = 1 << 5,
		IS_WALKABLE_DOWN         = 1 << 6,
		IS_WALKABLE_UP           = 1 << 7,
		IS_PATH_NODE             = 1 << 8,
		IS_ELEVATOR_COLUMN_NODE  = 1 << 9,
		IS_BRIDGE_NODE           = 1 << 10,
		IS_ELEVATOR              = 1 << 11,

		SPECIAL_GRAPH_FLAGS = IS_ELEVATOR | IS_BRIDGE_NODE | IS_ELEVATOR_COLUMN_NODE,
	};
}

//for display purposes
static std::map<GraphFlags::GraphFlags, std::string> graphNodeFlagsList
{
	{GraphFlags::IS_NEW, "IS_NEW"},
	{GraphFlags::IS_BANNED, "IS_BANNED"},
	{GraphFlags::IS_VISITED, "IS_VISITED"},
	{GraphFlags::IS_TARGET, "IS_TARGET"},
	{GraphFlags::IS_AFFECTED_BY_EXPLOSION, "IS_AFFECTED_BY_EXPLOSION"},
	{GraphFlags::IS_NEAR_SABER, "IS_NEAR_SABER"},
	{GraphFlags::IS_WALKABLE_DOWN, "IS_WALKABLE_DOWN"},
	{GraphFlags::IS_WALKABLE_UP, "IS_WALKABLE_UP"},
	{GraphFlags::IS_PATH_NODE, "IS_PATH_NODE"},
	{GraphFlags::IS_ELEVATOR_COLUMN_NODE, "IS_ELEVATOR_COLUMN_NODE"},
	{GraphFlags::IS_BRIDGE_NODE, "IS_BRIDGE_NODE"},
	{GraphFlags::IS_ELEVATOR, "IS_ELEVATOR"},
};


enum class CubeFaces : int
{
	NONE,
	BOTTOM,
	TOP,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

enum class PathfindingErrors : int
{
	NONE,
	SUCCESS,
	START_OR_FINISH_WAS_INVALID,
	TOO_FAR_AWAY,
	UNREACHABLE,
	START_AND_FINISH_SAME_NODE,
	START_AND_FINISH_DIFFERENT_ISLANDS,
};


struct Island
{
	size_t size = 0;
	std::unordered_set<uint32_t> islandChunks;
};

struct CellCoordinates
{
	uint32_t chunkLocation;
	uint16_t cellLocation;

	bool operator==(const CellCoordinates& other) const
	{
		return chunkLocation == other.chunkLocation && cellLocation == other.cellLocation;
	}
	bool operator==(const int& other) const
	{
		return chunkLocation == other && cellLocation == other;
	}
	CellCoordinates& operator=(const CellCoordinates& other)
	{
		if (this != &other)
		{
			chunkLocation = other.chunkLocation;
			cellLocation = other.cellLocation;
		}

		return *this;
	}
	CellCoordinates& operator=(const int& other)
	{
		chunkLocation = static_cast<uint32_t>(other);
		cellLocation = static_cast<uint16_t>(other);

		return *this;
	}
};

struct GraphNode
{
public:
	int g;
	int h;
	int f;

	uint32_t flags = 0;
	int weight = 0;
	GraphNode* parent = nullptr;

	float size = 0;

	Vec3 vertex, min, max;
	std::unordered_map<uintptr_t, GraphNode*> neighbors;
	std::vector<uint32_t> cells;
	uint32_t startCellLocation;
	uint16_t islandNum = 0;
	std::unordered_set<uint32_t> chunksOccupied;
};


class Cell
{
public:
	Cell(const Vec3_ui8& _loc, Chunk* _dadChunk);
	Cell(const uint16_t& _loc, Chunk* _parentChunk);
	~Cell();

	Vec3 GetCenter();

	uint16_t loc;
	uint32_t flags = 0;
	uint16_t entNum = 1022;

	Chunk* parentChunk = nullptr;
	GraphNode* graphNode = nullptr;

private:
};

struct MoverEntity
{
public:
	static uintptr_t entListBaseAddress;
	static uintptr_t entityOffset;

	MoverEntity() {}
	MoverEntity(const uint16_t& _entNum);
	void Scan();
	bool IsUpdated();
	void ForceUpdate();
	//uintptr_t address = 0;
	uint32_t flag = 0;
	uintptr_t address = 0;
	bool isOpening = false;
	bool isUpdated = false;
	bool isBridge = false;

	std::unordered_set<uint32_t> bannedCells;
private:
	uint16_t entNum = 0;
	int lastTimeUpdatedPrev = 0;
	int lastTimeRenderedPrev = 0;
	bool prevLockedState = false;
	bool prevHpState = false;
	bool forceUpdate = false;
};


namespace ElevatorStates
{
	enum ElevatorStates : uint32_t
	{
		NONE                   = 0,
		TOP                    = 1 << 0,
		BOTTOM                 = 1 << 1,
		MOVING                 = 1 << 2,
		LINKED                 = 1 << 3,
		OUTOFRENDER            = 1 << 4,
		ACTIVE                 = 1 << 5,
		BOTTOM_ACTIVE          = 1 << 6,
		TOP_ACTIVE             = 1 << 7,
		ACTIVATED_BY_PLAYER    = 1 << 8,
		READY_FOR_REACTIVATION = 1 << 9,
		BUTTON_1               = 1 << 10,
		BUTTON_2               = 1 << 11,
		REDO_PATH              = 1 << 13,
	};
};

static std::map<ElevatorStates::ElevatorStates, std::string> elevatorStatesList
{
	{ElevatorStates::NONE, "NONE"},
	{ElevatorStates::OUTOFRENDER, "OUTOFRENDER"},
	{ElevatorStates::LINKED, "LINKED"},
	{ElevatorStates::TOP, "TOP"},
	{ElevatorStates::BOTTOM, "BOTTOM"},
	{ElevatorStates::MOVING, "MOVING"},
	{ElevatorStates::ACTIVE, "ACTIVE"},
	{ElevatorStates::BOTTOM_ACTIVE, "BOTTOM_ACTIVE"},
	{ElevatorStates::TOP_ACTIVE, "TOP_ACTIVE"},
	{ElevatorStates::ACTIVATED_BY_PLAYER, "ACTIVATED_BY_PLAYER"},
	{ElevatorStates::READY_FOR_REACTIVATION, "READY_FOR_REACTIVATION"},
};

struct Trigger
{
public:
	Trigger(const CellCoordinates& _cellBot, const CellCoordinates& _cellTop = {0,0});
	void set_primary_states();
	void set_secondary_states(const uint16_t& playerStandingEntId);
	void activate();
	void deactivate();

	CellCoordinates triggerBottom = { 0,0 };
	CellCoordinates triggerTop = { 0, 0 };
	CellCoordinates elevatorButton = { 0, 0 };
	CellCoordinates elevatorButtonCall = { 0, 0 };

	Trigger* other = nullptr;

	uint32_t elevatorStates = ElevatorStates::NONE;

	uint16_t entityNum = 0;
	uint16_t entBottom = 0;
	uint16_t entTop = 0;

	std::unordered_set<uint32_t> columnCells;

	int elevatorStateChangesCounter = 0;
private:
	Utils::MrTimer elevatorResetDelayTimer;
	float deactivationResetTimeLimit = 6000;
	float readyForReactivationTimeLimit = 2200;
	float delayTime = 0;
	bool oldElevatorState = false;
	bool isPlayerOnMe = false;
	bool activationLock = false;
	bool redoPathLock = false;
};

class Chunk
{
public:
	Chunk(World* _world, const Vec3_ui8& _locationWorld);
	Chunk(World* _world, const uint32_t& _index);
	~Chunk();
	Cell* add_cell_empty(const Vec3_ui8& cellLoc);
	Cell* add_cell_empty(const uint16_t& cellLoc);
	uint32_t get_cell_index(const Vec3_ui8& cellLoc);
	void get_all_neighbors(std::vector<Chunk*>& neighbors);

	std::array<Cell*, WorldConstants::CHUNK_ARRAY_SIZE> cells;
	std::vector<CellCoordinates> validCells;
	std::unordered_map<uintptr_t, GraphNode*> nodes;

	uint32_t index = 0;
	Vec3_ui8 chunkLocation;
	Vec3 locationFloat;
	uint32_t flags = 0;

	World* world = nullptr;
	uint16_t validCellsCount = 0;
private:

};

class World
{
public:
	World(const Vec3& _origin, Utils::Tracer* _tracer = nullptr, uintptr_t _moverEntsAddress = 0, uint32_t _entityOffset = 0);
	~World();

	uint32_t get_chunk_index(const Vec3_ui8& chunkLoc);
	Vec3_ui8 get_chunk_coordinates_from_index(const uint32_t& index);
	void get_chunk_float_location(Vec3& locationFloat, const Vec3_ui8& chunkLocation);

	Vec3 get_cell_float_coordinates_from_location(const CellCoordinates& cc);

	static uint16_t pack_coordinates(const Vec3_ui8& loc);
	static Vec3_ui8 unpack_coordinates(const uint16_t& packedData);
	static uint32_t pack_cell_and_chunk(const CellCoordinates& cellCoordinates);
	static CellCoordinates unpack_cell_and_chunk(const uint32_t& chunkCell);

	Cell* get_cell(const Vec3_ui8& chunkLoc, const Vec3_ui8& cellLoc);
	Cell* get_cell(const uint32_t& chunkLoc, const uint16_t& cellLoc);
	Cell* get_cell(const CellCoordinates& cellCoordinates);
	Cell* get_cell(const uint32_t& cellPacked);
	Cell* get_cell(const Vec3& position, const int& depth, CellCoordinates& cellCoordinates);
	CellCoordinates get_cell_coordinates(Cell* cell);

	Chunk* get_chunk(const uint32_t& index);
	Chunk* get_chunk(const Vec3_ui8& chunkLoc);

	Chunk* add_chunk(const Vec3_ui8& chunkLoc);
	Chunk* add_chunk(const uint32_t& chunkLoc);
	void initialize_first_cell();

	void get_offset_location(Vec3_ui8& chunkLoc, Vec3_ui8& loc, const int8_t offset[3], Vec3& floatLocation);

	Cell* get_offset_cell(const Vec3_ui8& _chunkLoc, const Vec3_ui8& _loc, const int8_t offset[3]);
	Cell* get_offset_cell(const CellCoordinates&cc, const int8_t offset[3]);
	Cell* get_offset_cell(Cell* cell, const int8_t offset[3]);
	CellCoordinates get_offset_coordinates(const CellCoordinates& cc, const int8_t offset[3]);

	Cell* create_offset_cell(const Vec3_ui8& _chunkLoc, const Vec3_ui8& _loc, const int8_t offset[3]);
	Cell* create_cell_empty(const Vec3_ui8& chunkLoc, const Vec3_ui8& loc);
	Cell* create_cell_empty(const CellCoordinates& cc);

	void add_cell_manually(const CellCoordinates& cc, const uint32_t& specialFlag, const uint16_t& entityNum = 0);
	void connect_elevator_button_to_trigger(const CellCoordinates& cc);
	void delete_cell_manually(const CellCoordinates& cc);

	void delete_cell(Cell* cell);
	void delete_chunk(Chunk* chunk);

	void delete_node(const uintptr_t& nodeKey);
	GraphNode* node_validity_check(const uintptr_t& node);

	bool check_if_unmovable_mover(const uint16_t& entNum);
	bool check_if_ent_is_unlocked_door(const uint16_t& entNum);
	bool check_if_ent_is_opening(const uint16_t& entNum);
	void analyze_above_cell(const Vec3& crd, const uint16_t& parent_entNum, uint32_t& flags);
	void scan_location(const Vec3& crd, uint32_t& flags, uint16_t& entNum);

	void register_trigger_cell_column(const CellCoordinates& cc, int8_t dir[3], std::unordered_set<uint32_t>& columnCells);
	void link_trigger(Trigger& trigger);
	void tick_triggers(const uint16_t& playerStandingEntId);
	void connect_elevator_bridge(Cell* startCell, const uint16_t& entNum);
	Trigger* find_trigger(const GraphNode* gn);
	Trigger* find_trigger(const CellCoordinates& cc);
	void create_trigger(const CellCoordinates& cc);
	void delete_trigger(const CellCoordinates& cc);
	void create_elevator(const CellCoordinates& cc);

	void rescan_cell_bridge(const CellCoordinates& cc);
	void rescan_cell(const CellCoordinates& cc);
	void rescan_area(const CellCoordinates& myCell);
	bool fill_mover_ents(const uint16_t& entAhead);
	void unlock_banned_area(MoverEntity& entity);
	void unlock_banned_area_all(const std::vector<uint16_t>& changedEntIds);
	bool is_next_node_safe(GraphNode* gn);
	PathfindingErrors generate_path(GraphNode* start, GraphNode* end, std::vector<uintptr_t>& path);

	void flood(Cell* start);
	void cleanup_generated_cells();
	void redo_edge_scans();
	void postgen_scans();
	void add_new_area(CellCoordinates& cc);

	CellCoordinates cast_world_ray(const Vec3& start, const Vec3& uvec, const float& rayLength, CubeFaces& cubeFace, Vec3& intersection);
	CellCoordinates cast_world_ray(const Vec3& start, const Vec3& end, CubeFaces& cubeFace, Vec3& intersection);

	void postgen_scan_specific_chunk_edge(Chunk* chunk);
	void postgen_scan_specific_chunk_edge2(Chunk* chunk);
	void postgen_scan_specific_chunk_edge3(Chunk* chunk);
	void postgen_scan_specific_chunk(Chunk* chunk);
	void postgen_scan_specific_chunk_fast(Chunk* chunk);
	bool scan_find_all_islands(std::vector<GraphNode*>& graphTemp);
	void clear_bad_nodes();
	void clean_up_flags();


	std::array<Chunk*, WorldConstants::WORLD_SIZE> chunks;
	std::vector<uint32_t> validChunks;
	std::vector<std::pair<uint32_t, float>> sortedChunkPairs;
	std::unordered_map<uint32_t, Trigger> customTriggers; //bottom cell is key

	Chunk* spawnChunk = nullptr;
	Cell* spawnCell = nullptr;

	Vec3 origin;
	Vec3 cellMin, cellMax;

	Utils::MrTimer cellsGenTimer;
	Utils::MrTimer cellsCleanupTimer;
	Utils::MrTimer cellsPostGenTimer;
	Utils::MrTimer rescanAreaTimer;
	Utils::MrTimer unbanAreaTimer;
	Utils::MrTimer splitMeshTimer;
	Utils::MrTimer pathGenTimer;
	Utils::MrTimer nodeCullingTimer;
	Utils::MrTimer islandScanTimer;

	double mapReadTime = 0;
	double mapWriteTime = 0;

	size_t validCellsCount = 0;
	size_t oldValidCellsCount = 0;
	size_t scansCount = 0;
	size_t scansAboveCount = 0;

	Utils::Tracer* tracer = nullptr;
	uintptr_t moverEntsAddress = 0;
	uint32_t entityOffset= 0;

//graph builder
public:
	void split_mesh_chunk(std::vector<CellCoordinates>& cells, const int& meshSize);
	void get_graph_neighbors(std::vector<CellCoordinates>& cells);
	void split_mesh_chunk_simple(std::vector<CellCoordinates>& cells, const int& meshSize);
	void mesh_splitter();

	std::unordered_map<uintptr_t, GraphNode*> graph;
	std::unordered_map<uint16_t, Island> islands;
	std::vector<int> graphNodeSizes;
	std::unordered_map<uint16_t, MoverEntity> moverEntities;

	std::array<int8_t, 26> findNeighborsAllDX = { -1, 1,  0, 0,  -1, 1,  1, -1,       -1, 1,  0, 0,  -1, 1,  1, -1, 0,       -1, 1,   0,  0, -1,  1,  1, -1,  0 };
	std::array<int8_t, 26> findNeighborsAllDY = { 0,  0, -1, 1,  -1, 1, -1,  1,       0,  0, -1, 1,  -1, 1, -1,  1, 0,        0, 0,  -1,  1, -1,  1, -1,  1,  0 };
	std::array<int8_t, 26> findNeighborsAllDZ = { 0,  0,  0, 0,   0, 0,  0,  0,       1,  1,  1, 1,   1, 1,  1,  1, 1,       -1, -1, -1, -1, -1, -1, -1, -1, -1 };

private:

	CellCoordinates cast_world_ray_basic(const Vec3& start, const Vec3& uvec, const float& rayLength, CubeFaces& cubeFace, Vec3& intersection);
	void scan_find_this_island(GraphNode* startNode);
	CubeFaces line_cube_intersection_with_faces(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& cubeMin, const Vec3& cubeMax, double rayLength, Vec3& intersection);
	bool line_cube_intersection(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& cubeMin, const Vec3& cubeMax, double rayLength);


	void create_trigger_cell_column(const CellCoordinates& cc, int8_t dir[3], std::unordered_set<uint32_t>& columnCells);
	void tick_trigger(Cell* trigger, uint16_t& entNum);

	//int  line_cube_intersection_with_face(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& cubeMin, const Vec3& cubeMax, double rayLength);

	uint16_t islandsCount = 0;

	std::array<int8_t, 16> dx = { -1, 1,  0, 0,     -1,  1, 0,  0,   -1,  1,  0, 0, }; //-1, -1,  1, 1,
	std::array<int8_t, 16> dy = { 0, 0, -1, 1,      0,  0, -1, 1,    0,  0, -1, 1, }; //1, -1, -1, 1,
	std::array<int8_t, 16> dz = { 0, 0,  0, 0,     -1, -1, -1,-1,    1,  1,  1, 1, }; //0,  0,  0, 0,

	std::array<int8_t, 12> rescanCellDX = { -1, 1,  0, 0,     -1,  1, 0,  0,   -1,  1,  0, 0, }; //-1, -1,  1, 1,
	std::array<int8_t, 12> rescanCellDY = { 0, 0, -1, 1,      0,  0, -1, 1,    0,  0, -1, 1, }; //1, -1, -1, 1,
	std::array<int8_t, 12> rescanCellDZ = { 0, 0,  0, 0,     -1, -1, -1,-1,    1,  1,  1, 1, }; //0,  0,  0, 0,



	std::array<int8_t, 18> findMoverNeighborsDX = {-1, 1,  0, 0,  -1, 1,  1, -1, 0,       -1, 1,   0,  0, -1,  1,  1, -1,  0 };
	std::array<int8_t, 18> findMoverNeighborsDY = {0,  0, -1, 1,  -1, 1, -1,  1, 0,        0, 0,  -1,  1, -1,  1, -1,  1,  0 };
	std::array<int8_t, 18> findMoverNeighborsDZ = {1,  1,  1, 1,   1, 1,  1,  1, 1,       -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	struct Offsets
	{
		std::vector<int8_t> dx;
		std::vector<int8_t> dy;
		std::vector<int8_t> dz;
	};

	std::vector<Offsets> offsetsForPostGen;

	Utils::Tracer::trace_t trace_data;

	Chunk* previuousScannedChunk = nullptr;

	struct GraphNodeComparator {
		bool operator()(const GraphNode* a, const GraphNode* b) const {
			return a->f > b->f; 
		}
	};
};