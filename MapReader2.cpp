#include "MapReader2.h"

MapReader2::MapReader2()
{

}
MapReader2::~MapReader2()
{

}
void MapReader2::GetWorldOrigin(const std::string& wo)
{
	std::string worldOriginString = wo; 
	worldOriginString.erase(0, 1);
	std::istringstream iss(worldOriginString);
	iss >> worldOrigin.x >> worldOrigin.y >> worldOrigin.z;
}
void MapReader2::GetChunkLine(const std::string& ch, uint32_t& chunkIndex)
{
	std::string chunkLine = ch;
	chunkLine.erase(0, 1);
	chunkIndex = std::stoi(chunkLine);
}
void MapReader2::AddMoverEnt(const CellCoordinates& cc, const int& entNum, uint32_t& cellFlag)
{
	if (entNum >= 1022 || !(cellFlag & CellFlags::IS_BRIDGE))
		return;

	auto it = world->moverEntities.find(entNum);
	if (it == world->moverEntities.end())
	{
		MoverEntity entity(entNum);
		entity.isBridge = true;
		entity.bannedCells.insert(world->pack_cell_and_chunk(cc));
		entity.ForceUpdate();

		if (!entity.isOpening)
		{
			world->moverEntities.insert({ entNum, entity });
		}
	}
	else
	{
		world->moverEntities[entNum].bannedCells.insert(world->pack_cell_and_chunk(cc));
	}
}
Cell* MapReader2::CreateCell(const CellCoordinates& cc, const int&entNum, const uint32_t& cellFlag)
{
	Cell* cell = nullptr;
	cell = world->create_cell_empty(cc);

	world->get_chunk(cc.chunkLocation)->validCells.push_back(cc);
	cell->entNum = entNum;
	if (cell->entNum < 1022)
		cell->flags |= CellFlags::IS_MOVER;
	cell->flags |= CellFlags::IS_CREATED;
	cell->flags |= CellFlags::REFRESH;
	cell->flags |= CellFlags::WALKABLE;
	cell->flags |= cellFlag;

	AddMoverEnt(cc, entNum, cell->flags);

	cell->parentChunk->validCellsCount++;
	world->validCellsCount++;
	world->oldValidCellsCount++;

	if (cellFlag & (CellFlags::IS_ELEVATOR_BUTTON_1 | CellFlags::IS_ELEVATOR_BUTTON_2 | CellFlags::IS_ELEVATOR_BUTTON_CALL))
	{
		elevatorButtons.push_back(cc);
	}

	if (cellFlag & (CellFlags::IS_ELEVATOR_DETECTOR))
	{
		std::pair<uint32_t, Trigger> newTrig{ world->pack_cell_and_chunk(cc), (cc) };
		world->customTriggers.insert(newTrig);
	}
	else if (cellFlag & (CellFlags::IS_ELEVATOR_DETECTOR_UP))
	{
		int8_t elevOffset[3]{ 0,0, -1 };
		CellCoordinates elevatorBotLoc = world->get_offset_coordinates(cc, elevOffset);
		auto it = world->customTriggers.find(world->pack_cell_and_chunk(elevatorBotLoc));
		if (it != world->customTriggers.end())
		{
			it->second.triggerTop = cc;
		}
	}

	return cell;
}

void MapReader2::CreateMultipleCells(const uint16_t& cellLocationInChunk, const int& repeatTimes, const uint32_t& chunkIndex)
{
	uint16_t nextIndex = cellLocationInChunk - repeatTimes;
	//CreateCell({ chunkIndex, nextIndex });

	for (int i = 0; i <= repeatTimes; i++)
	{
		CreateCell({ chunkIndex, nextIndex }, 1022, 0);
		if (nextIndex == MAXUINT16)
			Utils::Error::ShowError(L"repeated cell bad parse");
		nextIndex++;
	}
}
void MapReader2::AnalyzeChunk(const std::string& chunkData, const uint32_t& chunkIndex)
{
	Chunk* ch = world->add_chunk(chunkIndex);
	if (!ch)
	{
		Utils::Error::ShowError(L"bad chunk parse");
		return;
	}
	ch->flags |= ChunkFlags::IS_CHUNK_ALREADY_EXIST;
	world->validChunks.push_back(ch->index);

	std::stringstream ss(chunkData);
	std::string temp;
	std::vector<std::string> cellData;

	while (ss >> temp) 
	{
		cellData.push_back(temp);
	}

	for (auto& cellStr : cellData)
	{
		uint16_t cellLocationInChunk = 0;

		size_t cellRepeaterPos = cellStr.find('<');
		size_t cellEntNumDelimiter = cellStr.find('|');
		size_t cellEntFlagDelimiter = cellStr.find(':');

		uint32_t cellFlag = 0;
		int cellEntNum = 1022;

		if (cellRepeaterPos != std::string::npos)
		{
			cellLocationInChunk = std::stoi(cellStr.substr(0, cellRepeaterPos));
			int repeat = std::stoi(cellStr.substr(cellRepeaterPos + 1));
			CreateMultipleCells(cellLocationInChunk, repeat, chunkIndex);
			continue;
		}

		if (cellEntNumDelimiter != std::string::npos && cellEntFlagDelimiter == std::string::npos)
		{
			cellLocationInChunk = std::stoi(cellStr.substr(0, cellEntNumDelimiter));
			cellEntNum = std::stoi(cellStr.substr(cellEntNumDelimiter + 1));
		}

		if (cellEntFlagDelimiter != std::string::npos && cellEntNumDelimiter == std::string::npos)
		{
			cellLocationInChunk = std::stoi(cellStr.substr(0, cellEntFlagDelimiter));
			cellFlag = std::stoi(cellStr.substr(cellEntFlagDelimiter + 1));
		}

		if (cellEntFlagDelimiter != std::string::npos && cellEntNumDelimiter != std::string::npos)
		{
			cellLocationInChunk = std::stoi(cellStr.substr(0, cellEntNumDelimiter));
			cellEntNum = std::stoi(cellStr.substr(cellEntNumDelimiter + 1, cellEntFlagDelimiter));
			cellFlag = std::stoi(cellStr.substr(cellEntFlagDelimiter + 1));
		}
		
		cellLocationInChunk = std::stoi(cellStr);
		CreateCell({ chunkIndex, cellLocationInChunk }, cellEntNum, cellFlag);
	}
}
void MapReader2::GenerateWorld(Utils::Tracer* _tracer, const uintptr_t& entListAddress, const int& playerOffset)
{
	world = new World(worldOrigin, _tracer, entListAddress, playerOffset);
}
World* MapReader2::ReadMap(const std::wstring& mapPath, Utils::Tracer* _tracer, const uintptr_t& entListAddress, const int& playerOffset)
{
	readTimer.Start();

	std::filesystem::path widePath(mapPath);
	std::ifstream infile(widePath, std::ios::in);
	std::string line;

	//std::unordered_map<int, std::string> mapFile;
	std::vector<std::string> mapFile;
	if (infile.is_open())
	{
		int index = 0;
		while (std::getline(infile, line))
		{
			mapFile.push_back(line);
			index++;
		}
	}
	else
		return nullptr;

	elevatorButtons.clear();
	uint32_t currentChunkIndex = 0;
	for (auto& lineInFile : mapFile)
	{
		if (lineInFile.empty())
			continue;
		switch (lineInFile[0])
		{
		case 'w':
			GetWorldOrigin(lineInFile);
			GenerateWorld(_tracer, entListAddress, playerOffset);
			break;
		case 'c':
			GetChunkLine(lineInFile, currentChunkIndex);
			break;
		default:
			AnalyzeChunk(lineInFile, currentChunkIndex);
			break;
		}
	}

	if (world)
		world->postgen_scans();
	else
		return nullptr;

	std::vector<GraphNode*> archipelago;
	for (auto& node : world->graph)
	{
		archipelago.push_back(node.second);
	}

	int breakCounter = 0;
	world->islandScanTimer.Start();
	while (!world->scan_find_all_islands(archipelago))
	{
		breakCounter++;
		if (breakCounter > 400)
			break;
	}
	world->islandScanTimer.Stop();

	for (auto& t : world->customTriggers)
	{
		world->link_trigger(t.second);
	}

	for (auto& cc : elevatorButtons)
	{
		world->connect_elevator_button_to_trigger(cc);
	}

	for (auto& t : world->customTriggers)
	{
		world->tick_triggers(0);
	}

	//for (auto& t : world->customTriggers)
	//{
	//	t.second.elevatorStateChangesCounter = 0;
	//}

	readTimer.Stop();
	world->mapReadTime = readTimer.ElapsedMcs();

	return world;
}
void MapReader2::SaveMap(const std::wstring& mapFolderPath, const std::wstring& mapName, World* _world)
{
	std::wstring directoryPath = mapFolderPath.substr(0, mapFolderPath.find_last_of(L"\\"));

	writeTimer.Start();
	if (!CreateDirectoryW(directoryPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		Utils::Error::ShowError(L"folder exists");
	}

	std::filesystem::path widePath(mapFolderPath + mapName + L".txt");
	std::ofstream file(widePath, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		Utils::Error::ShowError(L"Failed to write to map file");
		return;
	}

	world = _world;



	file << "w" + std::to_string(world->origin.x) + " " + std::to_string(world->origin.y) + " " + std::to_string(world->origin.z) << "\n";

	for (auto& chunk : world->validChunks)
	{
		Chunk* currentChunk = world->get_chunk(chunk);


		bool isGroup = false;
		int groupSize = 0;

		if (currentChunk->validCells.size() >= 1)
		{
			file << "c" + std::to_string(chunk) << "\n";
			for (int i = 0; i < currentChunk->validCells.size(); i++)
			{
				Cell* currentCell = world->get_cell(currentChunk->validCells[i]);

				Cell* nextCell = nullptr;
				if (i < currentChunk->validCells.size() - 1)
					nextCell = world->get_cell(currentChunk->validCells[i + 1]);

				if (nextCell != nullptr
					&& currentCell->loc == nextCell->loc - 1
					&& currentCell->entNum == 1022
					&& nextCell->entNum == 1022
					&& !(currentCell->flags & CellFlags::SAVED_FLAGS)
					&& !(nextCell->flags & CellFlags::SAVED_FLAGS)
					)
				{
					isGroup = true;
					groupSize++;
					continue;
				}

				if (isGroup)
				{
					file << std::to_string(currentCell->loc) + "<" + std::to_string(groupSize) + " ";
					isGroup = false;
					groupSize = 0;
					continue;
				}

				std::string resultCellString = std::to_string(currentCell->loc);

				if (currentCell->entNum != 1022)
					resultCellString += "|" + std::to_string(currentCell->entNum);
				if (currentCell->flags & CellFlags::SAVED_FLAGS)
				{
					resultCellString += ":" + std::to_string(currentCell->flags & CellFlags::SAVED_FLAGS);
				}

				resultCellString += " ";

				file << resultCellString;
			}
			file << "\n";
		}
	}
	writeTimer.Stop();
	world->mapWriteTime = writeTimer.ElapsedMcs();

	//std::wstring mapTimeWritten = L"MAP WRITTEN IN: " + std::to_wstring(world->mapWriteTime);
	//Utils::Error::ShowError(mapTimeWritten.c_str());

}