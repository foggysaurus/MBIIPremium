#pragma once
#include <string>
#include "Vectors.h"
#include <vector>
#include <unordered_map>
#include "GLFW/glfw3.h"
#include "Enums.h"

namespace menu
{
	enum MENU_BLOCKS
	{
		PLAYERS_BLOCK,
		TIMERS_BLOCK,
		MESH_TIMERS_BLOCK,
		MY_CELL_LOCATION_BLOCK,
		GENERATED_PATH_INFO_BLOCK,
		MISSILES_BLOCK,
		DEBUG_INFO_BLOCK,
		PROBERAY_BLOCK,
		BUILD_BLOCK,
	};

	enum Timers
	{
		GET_KEYS_TIMER,
		INIT_PLAYERS_TIMER,
		INIT_ENTS_TIMER,
		PREDICT_MISSILE_PATH_TIMER,
		SET_WEAPONS_TIMER,
		VISIBILITY_TIMER,
		DRAW_PLAYER_INFO,
		READ_SHARED_MEMORY_TIMER,
		LAST_NAME_INSERTION_TIMER,

		TOTAL_MAINEVENT_TIMER,

	};

	enum WorldGenTimers
	{
		GET_WORLD_GEN_TIMER,
		GET_WORLD_CLEANUP_TIMER,
		GET_WORLD_POSTGEN_TIMER,
		GET_NODE_CULLING_TIMER,
		ISLAND_SCAN_TIMER,
		GET_MESH_SPLIT_TIMER,
		GET_MAP_WRITTEN_TIMER,
		GET_MAP_READ_TIMER,
		GET_DOOR_SCAN_TIMER,
		GET_UNBAN_AREA_TIMER,
		GET_GENERATED_PATH_TIMER,

	};

	enum MyCellLocation
	{
		MESH_TOTAL_SCANS,
		MESH_TOTAL_CELLS,
		MESH_TOTAL_GRAPHNODES,
		MY_CHUNK_LOCATION,
		MY_CELL_LOCATION,
		MY_CELL_FLAG_LOCATION,
		MY_CELL_GRAPH_NODE,
		MY_MASKED_CELL_FLAG_LOCATION,
		ENUMERATE_CELL_FLAGS,
		ENT_NUM_LOCATION,
	};

	enum Generatedpath
	{
		GENERATED_PATH_SIZE, 
		GENERATED_PATH_LENGTH,
		GENERATED_PATH_CURRENT_STEP,
		GENERATED_PATH_ETA,
		GENERATED_PATH_TIME, 
		GENERATED_PATH_ERRORS,
	};

	enum Debug
	{
		MY_CLASS_DBG,
		MY_WEAPON_DBG,
		MY_WEAPON_VEL,
		MY_WEAPON_FIRERATE,
		MY_WEAPON_VEL_FACT,
		MY_STANCE1_DBG,
		MY_STANCE2_DBG,
		MY_SABER_ANIM_DBG,
	};

	enum ProBeRayEnums
	{
		RAY_CONTENTS,
		RAY_SURFACE_FLAGS,
		RAY_SURFACE,
		RAY_ENTNUM,
		RAY_ANGLE_TO_XY,
		RAY_ENTADDRESS,
	};
}


class MenuBlock;
class MenuItem
{
public:
	MenuItem()
	{
		loc.x = 0;
		loc.y = 0;
	};
	MenuItem(const int& _id, const std::string& _item) : id(_id)
	{
		item = _item;
		loc.x = 0; loc.y = 0;
	};
	std::string GetTotalString()
	{
		if (item.empty())
			return totalString = value;
		return totalString = item + ": " + value;
	};
	size_t GetSize() { return totalString.size(); };

	Vertex2 loc;
	std::string item;
	std::string value;
	int id;
	MenuBlock* daddyBlock = nullptr;
	GLfloat color[4];

private:
	std::string totalString;
};

class MenuBlock
{
public:
	MenuBlock() {};
	MenuBlock(const Vertex2& _loc, const std::string& _title) : loc(_loc), title(_title) 
	{ 
		titlePos = loc; titlePos.x += CHARSIZES::CALIBRI28; titlePos.y += menuPadding * 1.5; 
		color[0] = 0; color[1] = 0; color[2] = 0; color[3] = 0.4;

	}
	void AddMenuItem(const int& id, const std::string& menuItem);
	void SetBlockSize(const bool& _displayValidItems);
	bool IsHovered(const Vec2& mouseCrd);


	Vertex2 loc;
	Vertex2 titlePos;
	float width = 0, height = 0;
	std::string title;
	std::unordered_map<int, MenuItem> items;
	GLfloat color[4];

	bool isDraw = true;
private:
	void GetMenuItemLocation();

	int menuPadding = 18;
	//int charWidth = 9;
	bool displayValidItems = false;
	Vertex2 firstItemLoc;
};

class UI
{
public:
	UI() {};
	~UI() {};

	void SaveMenuBlock(const int& id, MenuBlock& mb)
	{
			menuBlocks.insert({id, mb});
	}
	std::unordered_map<int, MenuBlock> menuBlocks;
private:

};



