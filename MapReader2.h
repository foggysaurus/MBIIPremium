#pragma once
#include <fstream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <iostream>

#include "NavMesh.h"
#include "Utils.h"
#include "Vectors.h"

class MapReader2
{
public:
	MapReader2();
	~MapReader2();
	void GetWorldOrigin(const std::string& wo);
	void AddMoverEnt(const CellCoordinates& cc, const int& entNum, uint32_t& cellFlag);
	void GetChunkLine(const std::string& ch, uint32_t& chunkIndex);
	void GenerateWorld(Utils::Tracer* _tracer, const uintptr_t& entListAddress, const int& playerOffset);
	Cell* CreateCell(const CellCoordinates& cc, const int& entNum, const uint32_t& cellFlag);
	void CreateMultipleCells(const uint16_t& cellLocationInChunk, const int& repeatTimes, const uint32_t& chunkIndex);
	void AnalyzeChunk(const std::string& chunkData, const uint32_t& chunkIndex);
	World* ReadMap(const std::wstring& mapPath, Utils::Tracer* _tracer, const uintptr_t& entListAddress, const int& playerOffset);
	std::string TurnCellIntoString(Cell* c);
	void SaveMap(const std::wstring& mapFolderPath, const std::wstring& mapName, World* _world);
private:
	World* world = nullptr;
	Vec3 worldOrigin;
	Utils::MrTimer readTimer;
	Utils::MrTimer writeTimer;
	std::vector<CellCoordinates> elevatorButtons;
};

