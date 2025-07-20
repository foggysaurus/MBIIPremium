#include "MainEvents.h"

MainEvents::MainEvents(Draw* _draw, Input* _input) : draw(_draw), input(_input)
{
	//players
	Vertex2 blockStart;

	blockStart.x = 100; blockStart.y = 120;
	MenuBlock pls(blockStart, "Players"); //title
	ui.SaveMenuBlock(menu::PLAYERS_BLOCK, pls);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		Player player;
		players[i] = player;

 // SHOW_PLAYERS

	ui.menuBlocks[menu::PLAYERS_BLOCK].AddMenuItem(i, "");

	}
	ui.menuBlocks[menu::PLAYERS_BLOCK].isDraw = false;
	//timers
#ifdef ENABLE_TIMERS
	blockStart.x = 800; blockStart.y = 120;
	MenuBlock tmrs(blockStart, "Timers"); //title
	ui.SaveMenuBlock(menu::TIMERS_BLOCK, tmrs);

	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::GET_KEYS_TIMER, "Get keys");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::INIT_PLAYERS_TIMER, "Init players");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::INIT_ENTS_TIMER, "Init ents");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::PREDICT_MISSILE_PATH_TIMER, "Predict mis");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::SET_WEAPONS_TIMER, "Set Weapons");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::VISIBILITY_TIMER, "Visibility check");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::DRAW_PLAYER_INFO, "DrawPlayerInfo");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::READ_SHARED_MEMORY_TIMER, "SharedMemoryRead"); //lastNameInsertionTimer
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::LAST_NAME_INSERTION_TIMER, "LastNameInsertionTime");
	ui.menuBlocks[menu::TIMERS_BLOCK].AddMenuItem(menu::TOTAL_MAINEVENT_TIMER, "Total"); memcpy(ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::TOTAL_MAINEVENT_TIMER].color, RGB::pink, sizeof(RGB::pink));
	ui.menuBlocks[menu::TIMERS_BLOCK].isDraw = false;
#endif // ENABLE_TIMERS


	//grid timers


	blockStart.x = 100; blockStart.y = 360;
	MenuBlock meshTimers(blockStart, "Mesh timers"); //title
	ui.SaveMenuBlock(menu::MESH_TIMERS_BLOCK, meshTimers);

	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_WORLD_GEN_TIMER, "WorldGen");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_WORLD_CLEANUP_TIMER, "WorldCleanup");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_WORLD_POSTGEN_TIMER, "PostGen");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_NODE_CULLING_TIMER, "NodeCulling");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::ISLAND_SCAN_TIMER, "IslandScanned");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_MESH_SPLIT_TIMER, "MeshSplit");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_MAP_WRITTEN_TIMER, "Map Write");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_MAP_READ_TIMER, "Map Read");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_DOOR_SCAN_TIMER, "Door scan");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].AddMenuItem(menu::GET_UNBAN_AREA_TIMER, "UbanArea");
	ui.menuBlocks[menu::MESH_TIMERS_BLOCK].isDraw = false;

	blockStart.x = 100; blockStart.y = 180;
	MenuBlock myCellLocation(blockStart, "Mesh Info"); //title
	ui.SaveMenuBlock(menu::MY_CELL_LOCATION_BLOCK, myCellLocation);

	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MESH_TOTAL_SCANS, "TotalScans");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MESH_TOTAL_CELLS, "TotalCells");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MESH_TOTAL_GRAPHNODES, "TotalGraphNodes");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MY_CHUNK_LOCATION, "ChunkLoc");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MY_CELL_LOCATION, "CellLoc");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MY_CELL_FLAG_LOCATION, "Flag");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MY_CELL_GRAPH_NODE, "GraphNode");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::MY_MASKED_CELL_FLAG_LOCATION, "Masked Flag");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::ENUMERATE_CELL_FLAGS, "Flags");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].AddMenuItem(menu::ENT_NUM_LOCATION, "Ent Num");
	ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].isDraw = false;

	blockStart.x = 100; blockStart.y = 500;
	MenuBlock generatedpathInfo(blockStart, "Path Info"); //title
	ui.SaveMenuBlock(menu::GENERATED_PATH_INFO_BLOCK, generatedpathInfo);
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_SIZE, "PathSize");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_LENGTH, "PathLength");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_CURRENT_STEP, "Current Step");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_ETA, "PathETA");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_TIME, "PathTime");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].AddMenuItem(menu::GENERATED_PATH_ERRORS, "Error");
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].isDraw = false;

	//grid timers

	blockStart.x = 800; blockStart.y = 620;
	MenuBlock dbgInfo(blockStart, "Debug Info"); //title
	ui.SaveMenuBlock(menu::MENU_BLOCKS::DEBUG_INFO_BLOCK, dbgInfo);

	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_CLASS_DBG, "Class"); 
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_WEAPON_DBG, "Weapon");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_WEAPON_VEL, "Velocity");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_WEAPON_FIRERATE, "Fire rate");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_WEAPON_VEL_FACT, "ProjVel");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_STANCE1_DBG, "Stance1");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_STANCE2_DBG, "Stance2");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].AddMenuItem(menu::MY_SABER_ANIM_DBG, "SaberAnim");
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].isDraw = false;
	ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_WEAPON_VEL_FACT].value = "NA";

	blockStart.x = 800; blockStart.y = 360;
	MenuBlock probeRay(blockStart, "ProbeRay"); //title
	ui.SaveMenuBlock(menu::MENU_BLOCKS::PROBERAY_BLOCK, probeRay);

	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_CONTENTS, "Contents");
	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_SURFACE_FLAGS, "Surface Flags");
	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_SURFACE, "Surface");
	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_ENTNUM, "EntNum");
	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_ANGLE_TO_XY, "AngletoXY");
	ui.menuBlocks[menu::PROBERAY_BLOCK].AddMenuItem(menu::RAY_ENTADDRESS, "EntAddress");
	ui.menuBlocks[menu::PROBERAY_BLOCK].isDraw = false;

	blockStart.x = 800; blockStart.y = 180;
	MenuBlock buildBlock(blockStart, "MyBuild"); //title
	ui.SaveMenuBlock(menu::MENU_BLOCKS::BUILD_BLOCK, buildBlock);
	ui.menuBlocks[menu::BUILD_BLOCK].isDraw = false;

	for (int i = 0; i < MAX_BUILD_ITEMS; i++)
	{
		ui.menuBlocks[menu::MENU_BLOCKS::BUILD_BLOCK].AddMenuItem(i, "");
	}
	



}
MainEvents::~MainEvents()
{
	if (sendConsoleCommand)
	{
		sendConsoleCommand("cg_thirdpersonalpha 1\n");
		sendConsoleCommand("cg_thirdpersonrange 80\n");
	}
	act.DeInit();

	PlayersToSend pts;
	int nuller = 0;
	int index = 0;

	for (auto& p : players)
	{
		memset(&pts.playersData[index], 0, sizeof(PlayerData));
		index++;
		continue;
	}

	otherClientData.WriteMemory(pts);

	delete(world);
	delete(mapReader);
}
void MainEvents::Init(Addresses* _addresses, Draw* _draw, ReadWrite* _rw, const bool& _isRobot, 
	const bool& _isConfigRefreshed, const bool& _isGameUnminimised)
{
	static bool initOnce = false;
	static bool delayedInitOnce = false;

	if (!initOnce)
	{
		add = _addresses;
		draw = _draw;
		rw = _rw;

		mapReader = new MapReader2();

		initOnce = true;
		act.Init(add);
		playerOffset = *(int*)add->playerOffset;
		classOffset = *(int*)add->classOffset;
		me.bot.myPid = GetCurrentProcessId();

		otherClientData.CreateSharedMemory();
		//otherClientData.CreateMultipleSharedMemoryReaders();
		rw->ReadNameList();
		sharedMemoryReaderDelayTimer.Start();
	}

	if (sharedMemoryReaderDelayTimer.ElapsedCurrentMs() > 2000 && !delayedInitOnce)
	{
		otherClientData.CreateMultipleSharedMemoryReaders();
		delayedInitOnce = true;
	}


	isRobot = _isRobot;
	isConfigRefreshed = _isConfigRefreshed;
	isGameUnminimised = _isGameUnminimised;
	configFlags = rw->configFlags;
	wallhackFlags = rw->wallHackFlags;
	botConfigFlags = rw->botConfigFlags;
	tracer.traceLine = (Utils::Tracer::_TraceLine)add->traceLine;
	tracer.fastTrace = (Utils::Tracer::_FastTraceLine)(add->fastTraceLine);
	sendConsoleCommand = (Utils::_SendConsoleCommand)add->sendConsoleCommand;
	gameTime = *(int*)add->gameTime;
	isConsoleOpen = *(int*)add->consoleOpen;
}

//console
void MainEvents::AddFriend(Player* p)
{
	if (!p)
		return;
	if (!(p->permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND))
	{
		p->permanentPlayerFlags |= PermanentPlayerFlags::IS_FRIEND;
	}
	else
		p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_FRIEND;

	p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_TARGET;
}
void MainEvents::ClearLeaders()
{
	for (auto& p : players)
	{
		p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_LEADER;
		p.permanentPlayerFlags |= PermanentPlayerFlags::IS_NOT_LEADER;
	}
}
void MainEvents::DeleteLeader(const int& id)
{
	if (id < 0 || id > 31)
		return;

	Player* p = &players[id];

	p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_LEADER;
	p->permanentPlayerFlags |= PermanentPlayerFlags::IS_NOT_LEADER;
}
void MainEvents::MakeLeader(const int& id)
{
	if (id < 0 || id > 31)
		return;

	Player* p = &players[id];

	if (!(p->permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER))
	{
		p->permanentPlayerFlags |= PermanentPlayerFlags::IS_LEADER;
		p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_NOT_LEADER;

		for (auto& pl : players)
		{
			if (pl.id == id)
				continue;
			pl.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_LEADER;
			pl.permanentPlayerFlags |= PermanentPlayerFlags::IS_NOT_LEADER;
		}
	}
}
void MainEvents::AddFriend(const int& id)
{
	if (id < 0 || id > 31)
		return;
	for (Player& p : players)
	{
		if (id == p.id)
		{
			if (!(p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND))
				p.permanentPlayerFlags |= PermanentPlayerFlags::IS_FRIEND;
			else
				p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_FRIEND;

			p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_TARGET;
			break;
		}
	}

}
void MainEvents::AddTarget(Player* p)
{
	if (!p)
		return;
	if (!(p->permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET))
		p->permanentPlayerFlags |= PermanentPlayerFlags::IS_TARGET;
	else
		p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_TARGET;

	p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_FRIEND;
}
void MainEvents::AddTarget(const int& id)
{
	if (id < 0 || id > 31)
		return;
	for (Player& p : players)
	{
		if (id == p.id)
		{
			if (!(p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET))
				p.permanentPlayerFlags |= PermanentPlayerFlags::IS_TARGET;
			else
				p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_TARGET;

			p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_FRIEND;
			break;
		}
	}

}
void MainEvents::MakeFriendsAndEnemies()
{
	if (input->IsKeyToggled(MyKeysEnum::MAKE_FRIEND_KEYS))
	{
		AddFriend(me.closestPlayer.player);
	}
	if (input->IsKeyToggled(MyKeysEnum::MAKE_TARGET_KEYS))
	{
		AddTarget(me.closestPlayer.player);
	}
}
std::string MainEvents::ToLowerCase(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}
void MainEvents::DeathMessage()
{
	if (!(configFlags & ConfigFlags::SET_ON_KILL_TAUNTS))
		return;

	size_t killerNameLocation = lastLineOfconsole.find(" by^7");

	if (killerNameLocation == std::string::npos)
		return;

	std::string killerName = lastLineOfconsole.substr(killerNameLocation + 6);
	std::string victimName;

	size_t newLineLoc = killerName.find_first_of("\n");
	if (newLineLoc != std::string::npos)
	{
		killerName = killerName.substr(0, newLineLoc);
	}

	size_t victimNameEnd = lastLineOfconsole.find(" ^7was");
	if (victimNameEnd != std::string::npos && victimNameEnd >= 2)
	{
		victimName = lastLineOfconsole.substr(0, victimNameEnd - 2);
	}

	//deal with assists
	if (killerName.find(me.name) != std::string::npos)
	{
		size_t assistLoc = killerName.find("assisted by");
		if (assistLoc != std::string::npos)
		{
			std::string assister = killerName.substr(assistLoc + 14);
			if (assister.find(me.name) != std::string::npos)
				return;
		}
	}
	else
		return;

 	int victimId = -1;
	bool isVictimFriend = false;
	for (auto& p : players)
	{
		if (p.name == victimName)
		{
			if (p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
				isVictimFriend = true;
			victimId = p.id;
			break;
		}
	}

	if (victimId == -1)
		return;

	if (!rw->onKillMessages.empty() )
	{
		if (!isVictimFriend)
		{
			int phraseId = Utils::GenerateRandomInt(0, rw->onKillMessages.size() - 1);
			std::string killMessage = rw->onKillMessages[phraseId];

			//search if player mentioned
			size_t pNameLoc = killMessage.find("%");
			if (pNameLoc != std::string::npos)
			{
				killMessage.replace(pNameLoc, 1, " ^7"  + players[victimId].name + "^2");
			}

			std::string strToSend;
			if ((configFlags & ConfigFlags::ON_KILL_TAUNTS_GENERAL_CHAT))
				strToSend = "say " + killMessage + "\n";
			else
				strToSend = "tell " + std::to_string(victimId) + " " + killMessage + "\n";

			sendConsoleCommand(strToSend.c_str());
		}
		else
		{
			std::string strToSend = "tell " + std::to_string(victimId) + " " + "Sorry, my friend" + "\n";
			sendConsoleCommand(strToSend.c_str());
		}
	}
}
void MainEvents::FunnyReplies()
{
	int frameDelay = 125;

	if (isRobot)
	{
		//reply thanks-------------------------------
		static int thanksFrameTracker = 0;
		if (thanksFrameTracker == frameDelay - 1)
		{
			sendConsoleCommand("voice_cmd reply_thanks\n");
		}
		if (isReplyThanks && thanksFrameTracker < frameDelay)
		{
			thanksFrameTracker++;
		}
		else 
		{
			thanksFrameTracker = 0;
			isReplyThanks = false;
		}
		//------------------------------------------
		
		//reply sorry-------------------------------
		static int sorryFrameTracker = 0;
		if (sorryFrameTracker == frameDelay - 1)
		{
			sendConsoleCommand("voice_cmd reply_sorry\n");
		}
		if (isReplySorry && sorryFrameTracker < frameDelay)
		{
			sorryFrameTracker++;
		}
		else
		{
			sorryFrameTracker = 0;
			isReplySorry = false;
		}
		//------------------------------------------
		//reply yes-------------------------------
		static int yesFrameTracker = 0;
		if (yesFrameTracker == frameDelay - 1)
		{
			sendConsoleCommand("voice_cmd reply_yes\n");
		}
		if (isReplyYes && yesFrameTracker < frameDelay)
		{
			yesFrameTracker++;
		}
		else
		{
			yesFrameTracker = 0;
			isReplyYes = false;
		}
		//------------------------------------------

		//reply roger-------------------------------
		static int rogerFrameTracker = 0;
		if (rogerFrameTracker == frameDelay - 1)
		{
			sendConsoleCommand("voice_cmd reply_yes2\n");
		}
		if (isReplyRoger && rogerFrameTracker < frameDelay)
		{
			rogerFrameTracker++;
		}
		else
		{
			rogerFrameTracker = 0;
			isReplyRoger = false;
		}
		//------------------------------------------

		//reply help-------------------------------
		static int helpFrameTracker = 0;
		if (helpFrameTracker == frameDelay - 1)
		{
			sendConsoleCommand("voice_cmd reply_coming3\n");
		}
		if (isReplyHelp && helpFrameTracker < frameDelay)
		{
			helpFrameTracker++;
		}
		else
		{
			helpFrameTracker = 0;
			isReplyHelp = false;
		}
		//------------------------------------------
	}
}
void MainEvents::MakeFollowleader()
{
	int leaderId = -1;
	for (auto& p : sortedPlayers)
	{
		if (p->permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)
		{
			leaderId = p->id;
			break;
		}
	}
	if (leaderId == -1 && !isRobot)
		leaderId = me.trueId;

	if (leaderId == -1)
		return;

	size_t nameLoc = lastLineOfconsole.find(players[leaderId].name);
	if (nameLoc == std::string::npos)
		return;

	size_t followLoc = lastLineOfconsole.find("Follow");
	size_t stayLoc = lastLineOfconsole.find("Stay");
	size_t defendLoc = lastLineOfconsole.find("Defend Position");
    size_t complimentLoc = lastLineOfconsole.find("Compliment");
	size_t frustrationLoc = lastLineOfconsole.find("Frustration");
	size_t helpLoc = lastLineOfconsole.find("Request Assistance");

	if (followLoc != std::string::npos)
	{
		MakeLeader(leaderId);
		players[leaderId].botInfo.cellLookingAtSave = 0;
		if (isRobot)
			isReplyYes = true;
	}
	else if (stayLoc != std::string::npos)
	{
		//players[leaderId].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_LEADER;
		//players[leaderId].permanentPlayerFlags |= PermanentPlayerFlags::IS_NOT_LEADER;
	}
	else if (defendLoc != std::string::npos)
	{
		players[leaderId].botInfo.cellLookingAtSave = players[leaderId].botInfo.cellLookingAt;
		if (isRobot)
		{
			me.bot.tgtCells[TargetCells::ORDER_TARGET_CELL] = players[leaderId].botInfo.cellLookingAtSave;
			isReplyRoger = true;
		}

	}
	else if (complimentLoc != std::string::npos && isRobot)
	{
		isReplyThanks = true;
	}
	else if (frustrationLoc != std::string::npos && isRobot)
	{
		isReplySorry = true;
	}
	else if (helpLoc != std::string::npos && isRobot)
	{
		isReplyHelp = true;
	}
}
void MainEvents::ReadConsoleCommands()
{

	//if this is a console command
	static int lineConsoleSizeOld = 0;
	if (lastLineOfconsole.size()  && lineConsoleSizeOld != *(int*)add->consoleSize)
	{
		size_t nameLocation = lastLineOfconsole.find(" connected\n");
		size_t killerNameLocation = lastLineOfconsole.find(" by^7");

		if (lastLineOfconsole[0] == ']')
		{
			size_t idPos = -1;
			size_t finishLinePos = -1;

			if ((idPos = lastLineOfconsole.find("]fr") != std::string::npos) || (idPos = lastLineOfconsole.find("]tgt") != std::string::npos))
			{
				bool isFriend = true;
				finishLinePos = lastLineOfconsole.find("\n");
				idPos = lastLineOfconsole.find(' ') + 1;
				std::string buf = lastLineOfconsole.substr(idPos, finishLinePos - idPos);

				if (lastLineOfconsole.find("]tgt") != std::string::npos)
					isFriend = false;

				try
				{
					int id = std::stoi(buf);
					if (id >= 0 && id < 32)
					{
						if (isFriend)
							AddFriend(id);
						else
							AddTarget(id);
					}
				}
				catch (const std::exception&)
				{

					for (auto& pl : players)
					{
						std::string lowerCaseName = ToLowerCase(pl.shortName);
						if (pl.shortName.find(buf) != std::string::npos || lowerCaseName.find(buf) != std::string::npos)
						{
							if (isFriend)
								AddFriend(pl.id);
							else
								AddTarget(pl.id);
						}
					}
				}
			}
			else if (lastLineOfconsole.find("]unfr") != std::string::npos)
			{
				for (auto& pl : players)
				{
					if (pl.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
						pl.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_FRIEND;
				}
			}
			else if (lastLineOfconsole.find("]untgt") != std::string::npos)
			{
				for (auto& pl : players)
				{
					if (pl.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
						pl.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_TARGET;
				}
			}
			else if (lastLineOfconsole.find("]leader") != std::string::npos)
			{
				finishLinePos = lastLineOfconsole.find("\n");
				idPos = lastLineOfconsole.find(' ') + 1;
				std::string buf = lastLineOfconsole.substr(idPos, finishLinePos - idPos);
				try
				{
					int id = std::stoi(buf);
					MakeLeader(id);
				}
				catch (const std::exception&)
				{
					for (auto& pl : players)
					{
						std::string lowerCaseName = ToLowerCase(pl.shortName);
						if (pl.shortName.find(buf) != std::string::npos || lowerCaseName.find(buf) != std::string::npos)
						{
							MakeLeader(pl.id);
						}
					}
				}
			}
			else if (lastLineOfconsole.find("]unleader") != std::string::npos)
			{
				ClearLeaders();
			}

		}
		if (nameLocation != std::string::npos)
		{
			lastNameInsertionTimer.Start();
			std::string name = lastLineOfconsole.substr(0, nameLocation - 2);
			if (name.size() < 40)	
			{
				std::regex regex("[\\^][0-9]");
				std::string shortName = std::regex_replace(name, regex, "");
				rw->nameList[shortName] = name;
				lastNameInsertionTimer.Stop();
			}
		}
		DeathMessage();
		MakeFollowleader();
		//leader commands
		
		//leader commands

		lineConsoleSizeOld = *(int*)add->consoleSize;
	}
}
void MainEvents::ReadLastLineConsole()
{
	int consoleSize = *(int*)add->consoleSize;
	static int oldConsoleSize = consoleSize;
	int msgSize = 0;
	if (consoleSize != oldConsoleSize)
	{
		msgSize = consoleSize - oldConsoleSize;
		if (msgSize > 8192 || msgSize < 0)
		{
			msgSize = 0;
			oldConsoleSize = consoleSize;
			return;
		}
		lastLineOfconsole = std::string((char*)(add->consoleStart + oldConsoleSize), 0, msgSize);
		oldConsoleSize = consoleSize;
	}

	ReadConsoleCommands();
}
//console

//helper
void MainEvents::SenseWH()
{
	if (!(rw->wallHackFlags & WALLHACK_FLAGS::DRAW_OLDWH))
		return;

	int value = 0;
	if ((rw->wallHackFlags & WALLHACK_FLAGS::DRAW_OLDWH1))
		value = 1;
	else if ((rw->wallHackFlags & WALLHACK_FLAGS::DRAW_OLDWH2))
		value = 2;
	else if ((rw->wallHackFlags & WALLHACK_FLAGS::DRAW_OLDWH3))
		value = 3;


	*(int*)(add->mbiiBase + 0x63DF50) = 16384;
	*(int*)(add->mbiiBase + 0x644E14) = 16384;
	*(int*)(add->mbiiBase + 0x645A7C) = 16384;
	*(int*)(add->mbiiBase + 0x6466E4) = 16384;
	*(int*)(add->mbiiBase + 0x64734C) = 16384;
	*(int*)(add->mbiiBase + 0x647FB4) = 16384;
	*(int*)(add->mbiiBase + 0x648C1C) = 16384;
	*(int*)(add->mbiiBase + 0x649884) = 16384;
	*(int*)(add->mbiiBase + 0x64A4EC) = 16384;
	*(int*)(add->mbiiBase + 0x64B154) = 16384;
	*(int*)(add->mbiiBase + 0x64BDBC) = 16384;
	*(int*)(add->mbiiBase + 0x64CA24) = 16384;
	*(int*)(add->mbiiBase + 0x64D68C) = 16384;
	*(int*)(add->mbiiBase + 0x64E2F4) = 16384;
	*(int*)(add->mbiiBase + 0x64EF5C) = 16384;
	*(int*)(add->mbiiBase + 0x64FBC4) = 16384;
	*(int*)(add->mbiiBase + 0x64082C) = 16384;
	*(int*)(add->mbiiBase + 0x641494) = 16384;
	*(int*)(add->mbiiBase + 0x6420FC) = 16384;

	*(int*)(add->mbiiBase + 0x64DFE8) = value;
	*(int*)(add->mbiiBase + 0x644EAC) = value;
	*(int*)(add->mbiiBase + 0x645B14) = value;
	*(int*)(add->mbiiBase + 0x64677C) = value;
	*(int*)(add->mbiiBase + 0x6473E4) = value;
	*(int*)(add->mbiiBase + 0x64804C) = value;
	*(int*)(add->mbiiBase + 0x648CB4) = value;
	*(int*)(add->mbiiBase + 0x64991C) = value;
	*(int*)(add->mbiiBase + 0x64A584) = value;
}
uintptr_t MainEvents::GetEntAddressFromId(const uint16_t& id)
{
	return add->entList + id * playerOffset + 4;
}
void MainEvents::DrawProbeRay()
{
	if (!ui.menuBlocks[menu::PROBERAY_BLOCK].isDraw)
		return;

	Utils::Tracer::trace_t trace;
	Vec3 end = me.uvec * 1500 + me.position.posGun;
	UINT flag = CONTENTS_ALL;
	tracer.traceLine(&trace, me.position.posGun, 0,0, end, me.trueId, 1, 0);

	std::stringstream ssContents;
	std::stringstream ssSurface;
	std::stringstream ssHexEntNum;
	int cont = trace.contents;
	int surf = trace.surfaceFlags;
	int hexEntNum = trace.entityNum;
	ssContents << std::hex << cont;
	ssSurface << std::hex << surf;
	ssHexEntNum << std::hex << hexEntNum;

	std::string surface = std::to_string(trace.endpos.x) + " " + std::to_string(trace.endpos.y) + " " + std::to_string(trace.endpos.z);
	std::string surfaceFlags = ssSurface.str();
	std::string contents = ssContents.str();
	std::string entNum = std::to_string(trace.entityNum);
	std::string hexEntNums = ssHexEntNum.str();

	//get address of entity we are pointing at
	if (trace.entityNum > 31 && trace.entityNum < 1022)
	{
		static uintptr_t oldEntAdd;
		
		uintptr_t entAddress = GetEntAddressFromId(trace.entityNum) - 4;

		std::stringstream ssEntAddress;
		ssEntAddress << std::hex << entAddress;

		if (entAddress != oldEntAdd)
		{
			Utils::CopyToClipboard(ssEntAddress.str());
			oldEntAdd = entAddress;
		}
		ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_ENTADDRESS].value = ssEntAddress.str();
	}
	else
		ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_ENTADDRESS].value = "-";

	ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_CONTENTS].value = contents;
	ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_SURFACE_FLAGS].value = surfaceFlags;
	ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_SURFACE].value = surface;
	ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_ENTNUM].value = entNum + " " + hexEntNums;
	ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_ANGLE_TO_XY].value = std::to_string(acos(trace.plane.normal.z)* RADIAN) + " " + std::to_string(acos(trace.plane.normal.z));



	Vec3 endLine = trace.endpos;

	GLfloat col[4];

	if (trace.entityNum == 1023)
		memcpy(col, RGB::white, sizeof(col));
	if (trace.entityNum == 1022)
		memcpy(col, RGB::cyan, sizeof(col));
	if (trace.entityNum < 1022 && trace.entityNum > 31)
		memcpy(col, RGB::green, sizeof(col));
	if (trace.entityNum < 31)
		memcpy(col, RGB::lightYellow, sizeof(col));

	memcpy(ui.menuBlocks[menu::PROBERAY_BLOCK].items[menu::RAY_ENTNUM].color, col, sizeof(col));

	draw->DrawLine(me.position.posGun, endLine, 2, col);
}
void MainEvents::MakeMyModelTransparent()
{
	static bool isTransparent = false;
	static bool isOpaque = false;

	if (!isTransparent && -me.pitch > 12)
	{
		sendConsoleCommand("cg_thirdpersonalpha 0.05\n");
		isTransparent = true;
		isOpaque = false;
	}
	else if (isTransparent && -me.pitch < 12 && !isOpaque)
	{
		sendConsoleCommand("cg_thirdpersonalpha 1\n");
		isTransparent = false;
		isOpaque = true;
	}
}
void MainEvents::GetFps()
{
	currentFrame++;
	if (fpsTimer.IsElapsedPeriod(1000.0f))
	{
		fps = currentFrame;
		fpsTimer.Stop();
		currentFrame = 0;
	}
}
void MainEvents::GetPlayerNames()
{
	if (!isRoundBegin)
		return;
	for (auto& p : players)
	{
		if (!p.shortName.empty())
		{
			if (p.name.find("Padawan") == std::string::npos)
				rw->nameList[p.shortName] = p.name;
		}
	}
}
void MainEvents::GetMapNamePath()
{
	static std::string oldMapname;
	static bool firstLoad = true;

	worldFlags &= ~WorldFlags::IS_MAP_CHANGE;

	if (isRoundBegin || firstLoad)
	{
		currentMap = (char*)(add->mapName);
		if (oldMapname != currentMap && !currentMap.empty())
		{
			worldFlags |= WorldFlags::IS_MAP_CHANGE;
			oldMapname = currentMap;
			currentMapPath = rw->mapFolderPath;
			currentMapW = rw->StringToWString(currentMap);
			currentMapPath += currentMapW + L".txt";
		}
		firstLoad = false;
	}
}
void  MainEvents::IsServerTick()
{
	static int oldRefresh = *(int*)add->gameRefreshRate;
	int serverTime = *(int*)add->gameRefreshRate;
	if (serverTime != oldRefresh)
	{
		oldRefresh = serverTime;
		isServerTicked = true;
		return;
	}
	isServerTicked = false;
}
//helper

bool CompareByAngle(const Player* ent1, const Player* ent2)
{
	return ent1->angles.me_to_this_target3D < ent2->angles.me_to_this_target3D;
}
bool CompareByDistance(const Player* ent1, const Player* ent2)
{
	return ent1->distances.distance3 < ent2->distances.distance3;
}
void MainEvents::SortPLayersAngle()
{
	me.closestPlayer.player = nullptr;
	me.closestPlayer.teammate = nullptr;
	me.closestPlayer.enemy = nullptr;

	sortedPlayers.clear();
	sortedPlayers.reserve(maxPlayerId);

	for (int i =0; i <= maxPlayerId; i++)
	{
		if ((players[i].playerFlags & PlayerFlags::IS_VALID))
		{
			sortedPlayers.push_back(&players[i]);
		}
	}
	if (!isRobot)
		std::sort(sortedPlayers.begin(), sortedPlayers.end(), CompareByAngle);
	else
		std::sort(sortedPlayers.begin(), sortedPlayers.end(), CompareByDistance);

	if (sortedPlayers.size())
		me.closestPlayer.player = sortedPlayers[0];

	for (auto& en : sortedPlayers)
	{
		if (me.team != en->team)
		{
			me.closestPlayer.enemy = en;
			break;
		}
	}

	for (auto& t : sortedPlayers)
	{
		if (me.team == t->team)
		{
			me.closestPlayer.teammate = t;
			break;
		}
	}
}
//aim
void MainEvents::GetPlayerTrajectory(Player* p)
{
	if (p->surface != 1023 || p->speed.z > 320 
		|| (p->entClass == EntClass::CL_DEKA)
		|| (p->playerFlags & PlayerFlags::IS_JETPACK)
		|| me.wpInfo.speed == WeaponVelocities::MAX_FLOAT)
	{
		return;
	}

	std::vector<Vec3> traj;
	Vec3 norm;
	Vec3 lastPoint;
	uint32_t flags = 0; flags |= (TrajectoryFlags::TRAJECTORY_RECORD | TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION);
	GetTrajectory(p->position.posCrotch, p->speed, p->projTravelTimeToThisTarget, traj, TRAJECTORY_TYPE::TR_GRAVITY, flags, norm, lastPoint);
	draw->DrawTrajectory(traj, 2.0, RGB::yellow);

	GetAimAngles(me.position.posGun, lastPoint, me.yaw, me.pitch, p->angles.me_to_this_target.x, p->angles.me_to_this_target.y);
}
Player* MainEvents::SmartChooseTarget()
{
	int lowestHp = 1000;
	int maxClass = 14;

	Player* dangerWook = nullptr;
	Player* lowestHPtarget = nullptr;
	Player* shootingAtMeTarget = nullptr;
	Player* saberist = nullptr;
	Player* attackingSaberist = nullptr;
	Player* lookingAwaySaberist = nullptr;
	Player* deflectingSaberist = nullptr;
	Player* closestToCrosshair = nullptr;

	//find lowestHP
	for (auto& pl : sortedPlayers)
	{
		if (
			!(pl->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE)
			|| me.team == pl->team
			)
		{
			continue;
		}

		if (pl->hp < lowestHp)
			lowestHp = pl->hp;
	}

	//set all target flags
	for (auto& ent : sortedPlayers)
	{
		if (
			(ent->playerFlags & PlayerFlags::IS_IN_TK_RANGE)
			|| !(ent->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE)
			|| me.team == ent->team
			)
			continue;

		//find saberist who is looking away
		if (
			(ent->wpInfo.num == Weapons::WP_LS && ent->swordOn == 2) //turned off
			|| (ent->wpInfo.num == Weapons::WP_LS && ent->swordOn != 2 && abs(ent->angles.this_target_to_me.x) > 90) //when turned ON but looking away
			|| (ent->wpInfo.num == Weapons::WP_LS && (ent->stance2 == Stances2::PUSH || ent->stance2 == Stances2::PULL)) //when pushing or pullung
			|| (ent->wpInfo.num == Weapons::WP_LS && ent->swordOn != 2) && ent->stance == Stances::IDLE //when idle
			)
		{
			ent->targetFlags |= TargetFlags::IS_VIABLE_SABERIST_TGT;
		}

		//find saberists
		else if (
			ent->wpInfo.num == Weapons::WP_LS
			&& ent->swordOn != 2
			&& abs(ent->angles.this_target_to_me.x) < 90
			&& ent->stance != Stances::IDLE
			&& ent->stance2 != Stances2::PUSH
			&& ent->stance2 != Stances2::PULL
			&& ent->stance2 != Stances2::LIGHTNING
			&& ent->stance2 != Stances2::LIGHTNING_SABER_OUT
			)
		{
			ent->targetFlags |= TargetFlags::IS_SABERIST_TGT;
		}

		if (ent->hp == lowestHp && !(ent->targetFlags & TargetFlags::IS_SABERIST_TGT))
			ent->targetFlags |= TargetFlags::IS_LOWEST_HP_TGT;

		//melee wook
		if (ent->entClass == EntClass::CL_WOOK
			&& ent->wpInfo.num == Weapons::WP_MELEE
			&& ent->distances.distance3 < 300)
		{
			ent->targetFlags |= TargetFlags::IS_DANGER_WOOK_TGT;
		}

		//attacking saberist
		if (me.wpInfo.num != Weapons::WP_MELEE
			&& ent->distances.distance3 < 150
			&& ent->saberAnim > 1
			&& ent->saberAnim < 135)
		{
			ent->targetFlags |= TargetFlags::IS_DANGER_JEDI_TGT;
		}

		//target shooting at me
		if (
			ent->wpInfo.num != Weapons::WP_LS
			&& ent->wpInfo.num != Weapons::WP_MELEE
			&& (ent->playerFlags & PlayerFlags::IS_SHOOTING)
			&& ent->playerFlags & PlayerFlags::IS_LOOKING_AT_ME
			)
		{
			ent->targetFlags |= TargetFlags::IS_SHOOTING_AT_ME_TGT;
		}

	}
	for (auto& ent : sortedPlayers)
	{
		if (
			(ent->playerFlags & PlayerFlags::IS_IN_TK_RANGE)
			|| !(ent->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE)
			|| me.team == ent->team
			)
			continue;

		//a deflecting saberist
		if (
			(ent->targetFlags & TargetFlags::IS_SABERIST_TGT)
			&& (ent->playerFlags & PlayerFlags::IS_LOOKING_AT_ME)
			&& ent->wpInfo.num == Weapons::WP_LS
			&& !(ent->playerFlags & PlayerFlags::IS_RUNNING)
			&& ent->swordOn != 2
			&& (ent->distances.distance3 > 250)
			)
		{
			ent->targetFlags |= TargetFlags::IS_DEFLECTING_AT_ME_TGT;
		}
	}

	for (int i = sortedPlayers.size() - 1; i >= 0; i--)
	{
		if (
			(sortedPlayers[i]->playerFlags & PlayerFlags::IS_IN_TK_RANGE)
			|| !(sortedPlayers[i]->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE)
			|| me.team == sortedPlayers[i]->team
			)
			continue;


		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_DANGER_JEDI_TGT)
		{
			attackingSaberist = sortedPlayers[i];
			break;
		}

		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_DANGER_WOOK_TGT)
		{
			dangerWook = sortedPlayers[i];
			break;
		}

		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_SHOOTING_AT_ME_TGT)
		{
			shootingAtMeTarget = sortedPlayers[i];
			break;
		}

		if ((sortedPlayers[i]->targetFlags & TargetFlags::IS_SABERIST_TGT) && !(sortedPlayers[i]->targetFlags & TargetFlags::IS_DEFLECTING_AT_ME_TGT))
		{
			saberist = sortedPlayers[i];
			continue;
		}

		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_DEFLECTING_AT_ME_TGT)
		{
			deflectingSaberist = sortedPlayers[i];
			continue;
		}

		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_VIABLE_SABERIST_TGT)
			lookingAwaySaberist = sortedPlayers[i];

		if (sortedPlayers[i]->targetFlags & TargetFlags::IS_LOWEST_HP_TGT)
			lowestHPtarget = sortedPlayers[i];

		if (!(sortedPlayers[i]->targetFlags & TargetFlags::IS_DEFLECTING_AT_ME_TGT))
			closestToCrosshair = sortedPlayers[i];
	}

	if (attackingSaberist)
		return attackingSaberist;
	if (dangerWook)
		return dangerWook;
	if (shootingAtMeTarget)
		return shootingAtMeTarget;
	if (lowestHPtarget)
		return lowestHPtarget;
	if (closestToCrosshair)
		return closestToCrosshair;
	if (lookingAwaySaberist)
		return lookingAwaySaberist;
	if (saberist)
		return saberist;
	return nullptr;
}
void MainEvents::AimLockThisTarget(const float& angleHor, const float& angleVert)
{
	*(float*)add->myRawYaw = me.editYaw + angleHor;
	*(float*)add->myRawPitch = me.editPitch + angleVert;
}
Player* MainEvents::ChooseClosestVisibleTarget()
{
	for (auto& p : sortedPlayers)
	{
		if (p->team != me.team /*&& p->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE*/)
			return p;
	}
	return nullptr;
}
void MainEvents::SelectNewTarget(Player*& target, Player* oldTarget)
{
	if (!(configFlags & ConfigFlags::SET_AIM_SELECTOR))
		return;

	target = SmartChooseTarget();

	if (oldTarget && (oldTarget->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
	{
		if (target && !(target->targetFlags & TargetFlags::IS_DANGER_JEDI_TGT)
			&& !(target->targetFlags & TargetFlags::IS_DANGER_WOOK_TGT))
			target = oldTarget;
	}

}
void MainEvents::Aim()
{
	static Player* target = nullptr;
	static Player* oldTarget = nullptr;
	static bool isAimToggle = false;

	if (sortedPlayers.empty())
		return;

	//hold to aim
	if (!(configFlags & ConfigFlags::SET_TOGGLE_AIM))
	{
		if (input->IsKeyPressed(MyKeysEnum::AIM_KEYS))
		{


			if (!isAimToggle)
			{
				target = ChooseClosestVisibleTarget();
				oldTarget = target;
				isAimToggle = true;
			}
			//select new target if old is obstructed
			SelectNewTarget(target, oldTarget);

			if (target != nullptr && (target->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
			{
				GetPlayerTrajectory(target);
				AimLockThisTarget(target->angles.me_to_this_target.x, target->angles.me_to_this_target.y);
			}
		}
		else
		{
			target = nullptr;
			isAimToggle = false;
		}
	}
	if (configFlags & ConfigFlags::SET_TOGGLE_AIM)
	{
		if (input->IsKeyToggled(MyKeysEnum::AIM_KEYS))
		{
			target = ChooseClosestVisibleTarget();
			oldTarget = target;
			isAimToggle = !isAimToggle;
		}

		if (isAimToggle)
		{
			SelectNewTarget(target, oldTarget);

			if (target != nullptr && (target->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
			{
				GetPlayerTrajectory(target);
				AimLockThisTarget(target->angles.me_to_this_target.x, target->angles.me_to_this_target.y);
			}
		}
	}
}
//aim

//init weapons

float MainEvents::ExtremeAngleAdjustment(const float& angleSetY)
{
	//entClasses Classes;

	float adjustedAngle = angleSetY;
	if (me.entClass == EntClass::CL_DEKA)
	{
		if (angleSetY > 45 && angleSetY < 90)
			adjustedAngle = 45;
		else if (angleSetY < 330 && angleSetY > 270)
			adjustedAngle = 330;
	}
	else
	{
		if (angleSetY > 87 && angleSetY < 90)
			adjustedAngle = 87;
		else if (angleSetY < 280 && angleSetY > 270)
			adjustedAngle = 280;
	}
	return adjustedAngle;
}
double MainEvents::AngleBetween(const float& X, const float& Y)
{
	double angle;

	if (((X < 0) && (Y > 0)) || ((X < 0) && (Y < 0)))
	{
		angle = atan(Y / X);
		angle += PI;
	}
	else if ((X > 0) && (Y < 0))
		angle = (float)(2 * PI + atan(Y / X));
	else
		angle = atan(Y / X);

	return (180 / PI) * angle;
}
void MainEvents::GetAimAngles(const Vec3& from, const Vec3& to, const float& yaw, const float& pitch, float& yawSet, float& pitchSet)
{
	float enYawZero = 0;
	float enPitchZero = 0;
	float angleSet = 0;
	float angleSetY = 0;
	float distXY = 0;
	Vec3 deltas;

	deltas = from;
	deltas = deltas - to;

	enYawZero -= yaw + 90;
	enPitchZero = -pitch;

	distXY = vecs::VecDistance2(from, to);

	angleSetY = AngleBetween(distXY, -deltas.z);
	angleSet = AngleBetween(deltas.y, deltas.x);

	angleSetY = enPitchZero - angleSetY;
	angleSet = enYawZero - angleSet;


	if (angleSet < -360)
		angleSet += 360;
	if (angleSet > 360)
		angleSet -= 360;

	if (angleSet < -180)
		angleSet += 360;

	if (angleSetY < -360)
		angleSetY += 360;
	if (angleSetY > 360)
		angleSetY -= 360;

	if (angleSetY < -180)
		angleSetY += 360;

	if (isnan(angleSet) || isnan(angleSetY))
	{
		yawSet = 0; pitchSet = 0;
		return;
	}

	yawSet = angleSet;
	pitchSet = ExtremeAngleAdjustment(angleSetY);
}
void MainEvents::TestLookingAtMe(Player&p)
{
	float angleHor = atan((me.playerModel.defaultModelWidth / 2) / p.distances.distance3) * RADIAN;
	float angleVert = atan((me.playerModel.defaultModelHeight / 2) / p.distances.distance3) * RADIAN;

	if (angleHor > abs(p.angles.this_target_to_me.x) && angleVert > abs(p.angles.this_target_to_me.y))
		p.playerFlags |= PlayerFlags::IS_LOOKING_AT_ME;
}
void MainEvents::AntiTk(Player& p, const float& travelTime)
{
	if (p.team != me.team)
		return;

	float angleHor = atan((p.playerModel.defaultModelWidth / 2 + p.maxSpeed * travelTime) / p.distances.distance3) * RADIAN;
	float angleVert = atan((p.playerModel.defaultModelHeight) / p.distances.distance3) * RADIAN;

	float allyAngleX = AngleBetween((p.position.posCrotch.y - me.position.posCrotch.y), (p.position.posCrotch.x - me.position.posCrotch.x));
	float temp = sqrt((me.position.posCrotch.x - p.position.posCrotch.x) * (me.position.posCrotch.x - p.position.posCrotch.x) + (me.position.posCrotch.y - p.position.posCrotch.y) * (me.position.posCrotch.y - p.position.posCrotch.y));
	float allyAngleY = atan((me.position.posCrotch.z - p.position.posCrotch.z) / temp) * RADIAN;

	for (auto& enemyP : players)
	{
		if (!(enemyP.playerFlags & PlayerFlags::IS_VALID) || enemyP.team == me.team)
			continue;

		float enemyAngleX = AngleBetween((enemyP.position.posCrotch.y - me.position.posCrotch.y), (enemyP.position.posCrotch.x - me.position.posCrotch.x));
		temp = sqrt((me.position.posCrotch.x - enemyP.position.posCrotch.x) * (me.position.posCrotch.x - enemyP.position.posCrotch.x) + (me.position.posCrotch.y - enemyP.position.posCrotch.y) * (me.position.posCrotch.y - enemyP.position.posCrotch.y));
		float enemyAngleY = atan((me.position.posCrotch.z - enemyP.position.posCrotch.z) / temp) * RADIAN;

		if (angleHor > abs(enemyAngleX - allyAngleX) && angleVert > abs(enemyAngleY - allyAngleY))
		{
			enemyP.playerFlags |= PlayerFlags::IS_IN_TK_RANGE;
		}
	}
}
void MainEvents::GetAimVals()
{
	for (auto& p : players)
	{
		//set aim pos
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
		{
			continue;
		}
		if (p.permanentPlayerFlags & PermanentPlayerFlags::IS_AIM_HEAD)
			p.position.posAim = p.position.posHead;
		else
			p.position.posAim = p.position.posChest;
		//set aim pos

		p.distances.distance3 = vecs::VecDistance(me.position.posGun, p.position.posAim);
		p.distances.distance2 = vecs::VecDistance2(me.position.posGun, p.position.posAim);
		GetAimAngles(p.position.posCrotch, me.position.posFeet, p.yaw, p.pitch, p.angles.this_target_to_me.x, p.angles.this_target_to_me.y);

	//3dAngles
		p.angles.me_to_this_target3D = vecs::AngleBetweenVec(me.uvec, p.position.posAim - me.position.posGun);
		p.angles.this_target_to_me3D = vecs::AngleBetweenVec(p.uvec, me.position.posFeet - p.position.posCrotch);
		//3dAngles

		float projVel = me.wpInfo.speed;
		//if (p.distances.distance3 < 200)
		//	projVel = MAXINT;
		p.projTravelTimeToThisTarget = (p.distances.distance3 / projVel) + me.ping / 1000.0f;

		p.predictedPosition.posAim = p.speed * p.projTravelTimeToThisTarget + p.position.posAim;
		p.predictedDistances.distance3 = vecs::VecDistance(me.position.posGun, p.predictedPosition.posAim);
		p.predictedDistances.distance2 = vecs::VecDistance2(me.position.posGun, p.predictedPosition.posAim);


		GetAimAngles(me.position.posGun, p.predictedPosition.posAim, me.yaw, me.pitch, p.angles.me_to_this_target.x, p.angles.me_to_this_target.y);



		TestLookingAtMe(p);
		AntiTk(p, p.projTravelTimeToThisTarget);
	}

	SortPLayersAngle();
}
void MainEvents::CalculateMuzzleOffset()
{
	Vec3 uvec2D;


	float offset = WeaponOffsets[me.wpInfo.num];

	uvec2D.x = -sin(me.yaw * DEGREE_TO_RAD) * offset;
	uvec2D.y = -cos(me.yaw * DEGREE_TO_RAD) * offset;
	uvec2D.z = me.position.posGun.z;

	me.position.posGun.x -= uvec2D.x;
	me.position.posGun.y += uvec2D.y;
}
void MainEvents::InitializeWeapons()
{
	setWeaponsTimer.Start();

	me.wpInfo.speed = WeaponVelocitiesMap[me.wpInfo.num];
	me.wpInfo.fireRate = 0;

	switch (me.wpInfo.num)
	{
	case Weapons::WP_E11:
		if ((me.myFlags & MyFlags::IS_ALTATTACK) || me.bot.isAltAttaking)
		{
			me.wpInfo.speed = WeaponVelocities::WP_E11_ALT_VELOCITY;
			me.wpInfo.fireRate = WeaponFireRates::WP_E11_S;
		}
		else
			me.wpInfo.fireRate = WeaponFireRates::WP_E11_P;
		break;
	case Weapons::WP_PISTOL:
		if (me.entClass == EntClass::CL_DEKA)
			me.wpInfo.speed = WeaponVelocities::DEKA_VELOCITY;
		break;
	case Weapons::WP_T21:
		if ((me.myFlags & MyFlags::IS_ALTATTACK) || me.bot.isAltAttaking)
		{
			me.wpInfo.speed = WeaponVelocities::WP_T21_ALT_VELOCITY;
			me.wpInfo.fireRate = WeaponFireRates::WP_T21_S;
		}
		else
			me.wpInfo.fireRate = WeaponFireRates::WP_E11_P;
		break;
	case Weapons::WP_DEMP2:
		if ((me.myFlags & MyFlags::IS_ALTATTACK) || me.bot.isAltAttaking)
			me.wpInfo.speed = WeaponVelocities::WP_DEMP2_ALT_VELOCITY;
		break;
	case Weapons::WP_MERR_SONN:
		if ((me.myFlags & MyFlags::IS_ALTATTACK) || me.bot.isAltAttaking)
			me.wpInfo.speed = WeaponVelocities::WP_MERR_SONN_ALT_VELOCITY;
		break;
	case Weapons::WP_CONCUSSION_RIFLE:
		if ((me.myFlags & MyFlags::IS_ALTATTACK) || me.bot.isAltAttaking)
			me.wpInfo.speed = WeaponVelocities::WP_CONCUSSION_RIFLE_ALT_VELOCITY;
		break;
	case Weapons::WP_A280:
		if (me.myFlags & MyFlags::IS_ALTFIRE)
			me.wpInfo.speed = WeaponVelocities::WP_A280_ALT_VELOCITY;
		else
			me.wpInfo.fireRate = WeaponFireRates::WP_A280_P;
		break;
	case Weapons::WP_DLT:
		if (me.myFlags & MyFlags::IS_ALTFIRE)
			me.wpInfo.speed = WeaponVelocities::WP_DLT_ALT_VELOCITY;
		else
			me.wpInfo.fireRate = WeaponFireRates::WP_A280_P;
		break;
	case Weapons::WP_M5:
		if (me.myFlags & MyFlags::IS_SCOPE)
			me.wpInfo.speed = WeaponVelocities::WP_M5_ALT_VELOCITY;
		break;
	case Weapons::WP_EE3_CARABINE:
		if (me.myFlags & MyFlags::IS_SCOPE)
			me.wpInfo.speed = WeaponVelocities::WP_EE3_CARABINE_ALT_VELOCITY;
		break;
	case Weapons::WP_ARM_BLASTER:
		if (me.myConfig[ConfigVals::FIREPOWER] == 0)
			me.wpInfo.fireRate = WeaponFireRates::WP_ARM_BLASTER_0;
		else if (me.myConfig[ConfigVals::FIREPOWER] == 1)
			me.wpInfo.fireRate = WeaponFireRates::WP_ARM_BLASTER_1;
		else if (me.myConfig[ConfigVals::FIREPOWER] == 2)
			me.wpInfo.fireRate = WeaponFireRates::WP_ARM_BLASTER_2;
		else if (me.myConfig[ConfigVals::FIREPOWER] == 3)
			me.wpInfo.fireRate = WeaponFireRates::WP_ARM_BLASTER_3;
		break;
	case Weapons::WP_BOW:
		if (me.myFlags & MyFlags::IS_ALTFIRE)
			break;
		if (me.myConfig[ConfigVals::BOWCASTER] == 1)
			me.wpInfo.fireRate = WeaponFireRates::WP_BOW_1;
		else if (me.myConfig[ConfigVals::BOWCASTER] == 2)
			me.wpInfo.fireRate = WeaponFireRates::WP_BOW_2;
		else if (me.myConfig[ConfigVals::BOWCASTER] == 3)
			me.wpInfo.fireRate = WeaponFireRates::WP_BOW_3;
		break;
	case Weapons::WP_CR:
		if (me.myConfig[ConfigVals::CLONE_RIFLE] == 1)
			me.wpInfo.fireRate = WeaponFireRates::WP_CR_1;
		else if (me.myConfig[ConfigVals::CLONE_RIFLE] == 2)
			me.wpInfo.fireRate = WeaponFireRates::WP_CR_2;
		else if (me.myConfig[ConfigVals::CLONE_RIFLE] == 3)
			me.wpInfo.fireRate = WeaponFireRates::WP_CR_3;
		break;
	default:
		break;
	}
	CalculateMuzzleOffset();
	GetAimVals();
	setWeaponsTimer.Stop();
}
//init weapons

//write/read memory
void MainEvents::WriteSDCommon(PlayerData& playerData, const Player& p)
{
	for (int i = 0; i <= maxPlayerId; i++)
	{
		if (
			(!(p.playerFlags & PlayerFlags::IS_RENDERED) && me.trueId != p.id)
			|| !(p.playerFlags & PlayerFlags::IS_ALIVE)
			|| (p.playerFlags & (PlayerFlags::IS_TELECOMMUNICATED)))
		{
			return;
		}

		playerData.commonData.id = p.id;
		playerData.commonData.entClass = p.entClass;
		playerData.commonData.stance = p.stance;
		playerData.commonData.weapon = p.wpInfo.num;
		playerData.commonData.team = p.team;
		playerData.commonData.position = p.position;
		playerData.commonData.playerModel = p.playerModel;
		playerData.commonData.playerFlags = p.playerFlags;
		playerData.commonData.yaw = p.yaw;
		playerData.commonData.pitch = p.pitch;
		playerData.commonData.uvec = p.uvec;
	}
}
void MainEvents::WriteSDLeaderToBot(PlayersToSend& playersData)
{
	if (isRobot)
		return;

	playersData.leaderToBot.bossId = me.trueId;
	if (reloadBotMaps)
		playersData.leaderToBot.iRefreshedMap = true;

	if (players[me.trueId].permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)
		playersData.leaderToBot.leaderId = me.trueId;
	else if (players[me.trueId].permanentPlayerFlags & PermanentPlayerFlags::IS_NOT_LEADER)
		playersData.leaderToBot.leaderId = -1;
}
void MainEvents::WriteSDBotToLeader(PlayersToSend& playersData)
{
	if (!isRobot)
		return;

	playersData.botToLeader.botId = me.trueId;

	if (reloadThisBotMap)
	{
		reloadThisBotMap = false;
		playersData.botToLeader.iRefreshedMap = true;
	}
}
void MainEvents::WriteSharedData()
{
	PlayersToSend playersToSend;

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		memset(&playersToSend.playersData[i], 0, sizeof(PlayerData));
	}


	for (int i = 0; i <= maxPlayerId; i++)
	{
		WriteSDCommon(playersToSend.playersData[i], players[i]);
	}

	WriteSDLeaderToBot(playersToSend);
	WriteSDBotToLeader(playersToSend);

	playersToSend.maxId = maxPlayerId;

	otherClientData.WriteMemory(playersToSend);
}
void MainEvents::ReadSDCommon(PlayerData& playerData, const int& playerIndex)
{
	if ((playerData.commonData.id == me.trueId)
		|| (players[playerIndex].playerFlags & (PlayerFlags::IS_RENDERED))
		|| !(players[playerIndex].playerFlags & (PlayerFlags::IS_ALIVE))
		)
		return;

	players[playerIndex].id	= playerData.commonData.id;
	players[playerIndex].entClass = playerData.commonData.entClass;
	players[playerIndex].stance = playerData.commonData.stance;
	players[playerIndex].wpInfo.num = playerData.commonData.weapon;
	players[playerIndex].team = playerData.commonData.team;
	players[playerIndex].position = playerData.commonData.position;
	players[playerIndex].playerModel = playerData.commonData.playerModel;
	players[playerIndex].playerFlags = playerData.commonData.playerFlags;
	players[playerIndex].yaw = playerData.commonData.yaw;
	players[playerIndex].pitch = playerData.commonData.pitch;
	players[playerIndex].uvec = playerData.commonData.uvec;

	players[playerIndex].playerFlags |= (PlayerFlags::IS_RENDERED | PlayerFlags::IS_ALIVE | PlayerFlags::IS_VALID | PlayerFlags::IS_TELECOMMUNICATED);

}
void MainEvents::ReadSDLeaderFromBot(PlayersToSend& playersData)
{
	if (isRobot)
		return;
	if (playersData.botToLeader.iRefreshedMap)
	{
		reloadBotMaps = false;
	}
}
void MainEvents::ReadSDBotFromLeader(PlayersToSend& playersData)
{
	if (!isRobot)
		return;
	if (playersData.leaderToBot.iRefreshedMap)
	{
		reloadThisBotMap = true;
	}
	if (playersData.leaderToBot.bossId == playersData.leaderToBot.leaderId)
	{
		players[playersData.leaderToBot.bossId].permanentPlayerFlags |= PermanentPlayerFlags::IS_LEADER;
	}
	else
	{
		players[playersData.leaderToBot.bossId].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_LEADER;
	}
}
void MainEvents::ReadSharedData()
{
	std::vector<PlayersToSend> allClientsData;
	allClientsData = otherClientData.ReadMultipleMemories();

	for (auto& allPlayers : allClientsData)
	{
		for (int i = 0; i <= allPlayers.maxId; i++)
		{

			ReadSDCommon(allPlayers.playersData[i], i);

		}
		ReadSDLeaderFromBot(allPlayers);
		ReadSDBotFromLeader(allPlayers);
	}
}

//init players and basic events
void MainEvents::OnRoundBegin()
{
	static bool roundLock = false;
	isRoundBegin = false;
	if (*(int*)add->isRound)
	{
		if (!roundLock)
		{
			isRoundBegin = true;
			roundLock = true;
		}
	}

	if (!*(int*)add->isRound || !*(int*)add->mbiiBaseEnt)
		roundLock = false;
}
void MainEvents::VisibilityChecker()
{
	CheckVisibilityTimer.Start();
	Utils::Tracer::trace_t trace;

	float val = 0;
	Vec3 min{ -val, -val, -val };
	Vec3 max{ val, val, val };
	Vec3 end;

	if (isServerTicked)
		for (int i = 0; i <= maxPlayerId; i++)
		{
			if (!(players[i].playerFlags & PlayerFlags::IS_VALID))
			{
				players[i].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_VISIBLE;
				continue;
			}

			tracer.traceLine(&trace, me.position.posGun, min, max, players[i].position.posChest, 0, 0x1, 0);

			if (trace.entityNum == 1023)
			{
				players[i].permanentPlayerFlags |= PermanentPlayerFlags::IS_VISIBLE;
				players[i].permanentPlayerFlags |= PermanentPlayerFlags::IS_AIM_CHEST;
				players[i].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_AIM_HEAD;
				continue;
			}
			else
			{
				players[i].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_VISIBLE;
			}

			if (trace.entityNum == 1022 && players[i].entClass != EntClass::CL_DEKA)
			{
				tracer.traceLine(&trace, me.position.posGun, min, max, players[i].position.posHead, 0, 0x1, 0);

				if (trace.entityNum == 1023)
				{
					players[i].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_AIM_CHEST;
					players[i].permanentPlayerFlags |= PermanentPlayerFlags::IS_AIM_HEAD;
					players[i].permanentPlayerFlags |= PermanentPlayerFlags::IS_VISIBLE;
					continue;
				}
				else
				{
					players[i].permanentPlayerFlags &= ~PermanentPlayerFlags::IS_VISIBLE;
				}
			}
		}
	CheckVisibilityTimer.Stop();
}
void MainEvents::TestCrouch(Player& ent)
{
	if ((
		ent.stance == Stances::KICK_W
		|| ent.stance == Stances::KICK_A
		|| ent.stance == Stances::KICK_D
		|| ent.stance == Stances::KICK_S
		|| ent.stance == Stances::SLAP
		|| ent.stance == Stances::JUMPKICK
		|| ent.stance == Stances::ROUNDHOUSE_SLAP_LEFT
		|| ent.stance == Stances::ROUNDHOUSE_SLAP_RIGHT
		|| ent.stance == Stances::FLYKICK_W
		|| ent.stance == Stances::FLYKICK_A
		|| ent.stance == Stances::FLYKICK_D
		|| ent.stance == Stances::FLYKICK_S
		|| ent.stance == Stances::UPPERCUT
		|| ent.stance2 == Stances2::SBD_SLAP
		|| ent.stance2 == Stances2::WOOK_SLAP
		|| ent.stance2 == Stances2::WOOK_BARGE)
		)
	{
		ent.playerFlags |= PlayerFlags::IS_GONNA_KNOCK_ME_DOWN;
	}
}
void MainEvents::CrouchWhenAttacked()
{
	if (!(configFlags & ConfigFlags::SET_ANTICROUCH))
		return;

	float innerRad = 160;
	float kickRad = 60;

	bool shouldCrouch = false;
	bool shouldJump = false;

	static bool crouchToggler = false;
	static bool jumpToggler = false;

	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID) || me.entClass == EntClass::CL_DEKA)
			continue;

		if (p.distances.distance3 < innerRad)
		{
			TestCrouch(p);

			//normal players
			if (p.playerFlags & PlayerFlags::IS_GONNA_KNOCK_ME_DOWN
				&& me.entClass != EntClass::CL_WOOK 
				&& me.entClass != EntClass::CL_SBD
				)
			{
				//forward kicks
				if (abs(p.angles.this_target_to_me.x) < 60
					&& (
						 p.distances.distance3 < kickRad
						&& p.stance != Stances::KICK_A
						&& p.stance != Stances::KICK_D
						&& p.stance != Stances::FLYKICK_A
						&& p.stance != Stances::FLYKICK_D
						&& p.stance != Stances::KICK_S
						&& p.stance != Stances::FLYKICK_S
						)
					)
				{
					shouldCrouch = true; crouchToggler = true;
					draw->bold28->Print(400, 400, RGB::yellow, "CROUCH");
					break;
				}
				//side kicks
				else if (abs(p.angles.this_target_to_me.x) > 60
					&& p.distances.distance3 < kickRad
					&& (
						   p.stance == Stances::KICK_A
						|| p.stance == Stances::KICK_D
						|| p.stance == Stances::FLYKICK_A
						|| p.stance == Stances::FLYKICK_D
						)
					)
				{
					draw->bold28->Print(400, 400, RGB::yellow, "CROUCH SIDE");
					shouldCrouch = true; crouchToggler = true;
					break;
				}
				//back kicks
				else if (abs(p.angles.this_target_to_me.x) > 120 &&
					p.distances.distance3 < kickRad 
					&& (p.stance == Stances::KICK_S
						|| p.stance == Stances::FLYKICK_S))
				{
					draw->bold28->Print(400, 400, RGB::yellow, "CROUCH BACK");
					shouldCrouch = true; crouchToggler = true;
					break;
				}


			}
			//wook sbd
			else if (p.playerFlags & PlayerFlags::IS_GONNA_KNOCK_ME_DOWN)
			{
				if (abs(p.angles.this_target_to_me.x) < 90)
				{
					draw->bold28->Print(400, 400, RGB::yellow, "WOOK");
					shouldCrouch = true; crouchToggler = true;
					break;
				}
			}
			else if (p.stance == Stances::SWEEPKICK)
			{
				if (p.distances.distance3 < 60)
				{
					draw->bold28->Print(400, 400, RGB::yellow, "JUMP");
					shouldJump = true; jumpToggler = true;
					break; 
				}
			}
		}
	}

	if (shouldCrouch)
	{
		act.Do(DoAction::CROUCH);
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_CROUCH;
	}
	else if (!shouldCrouch && crouchToggler)
	{
		act.Stop(DoAction::CROUCH);
		crouchToggler = false;
	}

	if (shouldJump)
	{
		act.Do(DoAction::JUMP);
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_JUMP;
	}
	else if (!shouldJump && jumpToggler)
	{
		act.Stop(DoAction::JUMP);
		jumpToggler = false;
	}

}
void MainEvents::AutoDodge()
{
	if (!(configFlags & ConfigFlags::SET_AUTODODGE))
		return;
	static bool isDodge = false;

	if (isDodge)
	{
		act.Stop(DoAction::DODGE);
		isDodge = false;
	}

	for (auto&p: players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
			continue;
		if ((p.playerFlags & PlayerFlags::IS_LOOKING_AT_ME) 
			&& me.myConfig.find(ConfigVals::DODGE) != me.myConfig.end()
			&& me.myConfig[ConfigVals::DODGE] != 0
			&& me.team != p.team
			&& p.wpInfo.num != Weapons::WP_MELEE
			&& p.wpInfo.num != Weapons::WP_LS
				)
		{
			isDodge = true;
			act.Do(DoAction::DODGE);
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_DODGE;
			return;
		}
	}
}

//nospread
void MainEvents::RestoreBinds()
{
	if (!rw)
		return;
	std::string bindAtt = "bind " + rw->myBinds[MyBindsEnum::ATTACK_BIND].name + " +attack; " + " bind " + rw->myBinds[MyBindsEnum::ALTATTACK_BIND].name + " +altattack" + "\n";
	sendConsoleCommand(bindAtt.c_str());
}
bool MainEvents::BindUnbindAttackButtons()
{
	static bool isUnboundAttackKey = false;
	
	if ((configFlags & ConfigFlags::SET_NO_SPREAD) && (me.wpInfo.fireRate != 0) 
		&& me.gameMode == GameModes::OPEN 
		&& isConsoleOpen == 0
		)
	{
		if (!isUnboundAttackKey)
		{
			std::string unbindAtt = "unbind " + rw->myBinds[MyBindsEnum::ATTACK_BIND].name + "; unbind " + rw->myBinds[MyBindsEnum::ALTATTACK_BIND].name + "\n";
			sendConsoleCommand(unbindAtt.c_str());
			isUnboundAttackKey = true;
		}
	}
	else
	{
		if (isUnboundAttackKey)
		{
			std::string bindAtt = "bind " + rw->myBinds[MyBindsEnum::ATTACK_BIND].name + " +attack; " + " bind " + rw->myBinds[MyBindsEnum::ALTATTACK_BIND].name + " +altattack" + "\n";
			sendConsoleCommand(bindAtt.c_str());
			isUnboundAttackKey = false;
		}
		return false;
	}
	return true;
}
void MainEvents::ShootNoSpread()
{
	static int frameCounter = 0;

	bool isPrimary = GetAsyncKeyState(rw->myBinds[MyBindsEnum::ATTACK_BIND].id);
	bool isSecondary = GetAsyncKeyState(rw->myBinds[MyBindsEnum::ALTATTACK_BIND].id);

	if (isPrimary)
		me.myFlags |= MyFlags::IS_ATTACK;
	else if (isSecondary)
		me.myFlags |= MyFlags::IS_ALTATTACK;

	int a = act.CheckState(DoAction::LEFT);
	int s = act.CheckState(DoAction::BACK);
	int d = act.CheckState(DoAction::RIGHT);
	int w = act.CheckState(DoAction::FORWARD);

	bool isW = GetAsyncKeyState(rw->myBinds[MyBindsEnum::W_BIND].id);
	bool isA = GetAsyncKeyState(rw->myBinds[MyBindsEnum::A_BIND].id);
	bool isS = GetAsyncKeyState(rw->myBinds[MyBindsEnum::S_BIND].id);
	bool isD = GetAsyncKeyState(rw->myBinds[MyBindsEnum::D_BIND].id);

	if (isPrimary || isSecondary || frameCounter != 0)
	{
		//release keys on the first frame
		if (frameCounter == 0)
		{
			noSpreadFireTimer.Start();
			if (a)
				act.Stop(DoAction::LEFT);
			if (d)
				act.Stop(DoAction::RIGHT);
			if (w)
				act.Stop(DoAction::FORWARD);
			if (s)
				act.Stop(DoAction::BACK);
		}

		//shoot on the next frame
		if (frameCounter == 1)
		{
			if (isPrimary)
				act.Do(DoAction::ATTACK);
			else if (isSecondary)
				act.Do(DoAction::ALT_ATTACK);
		}

		//return everything as it was
		if (frameCounter == 2)
		{
			if (isPrimary)
				act.Stop(DoAction::ATTACK);
			else if (isSecondary)
				act.Stop(DoAction::ALT_ATTACK);

			if (isW)
				act.Do(DoAction::FORWARD);
			if (isS)
				act.Do(DoAction::BACK);
			if (isA)
				act.Do(DoAction::LEFT);
			if (isD)
				act.Do(DoAction::RIGHT);
		}

		frameCounter++;

		if (noSpreadFireTimer.ElapsedCurrentMs() >= me.wpInfo.fireRate+5)
		{
			auto t = noSpreadFireTimer.ElapsedMs();
			frameCounter = 0;
			noSpreadFireTimer.Stop();
		}
	}

	if (!isPrimary)
		act.Stop(DoAction::ATTACK);
	 if (!isSecondary)
		act.Stop(DoAction::ALT_ATTACK);
}
void MainEvents::NoSpread()
{
	if (!BindUnbindAttackButtons() || isRobot || (me.myFlags & MyFlags::IS_NOCLIP))
		return;

	ShootNoSpread();
}
//nospread
void MainEvents::GetMaxPlayerId()
{
	if (add == nullptr)
		return;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		int bufferId = *(int*)(add->entBase + i * *(int*)add->playerOffset);
		if (bufferId > maxPlayerId)
			maxPlayerId = bufferId;
	}
	maxPlayerId = MAX_PLAYERS - 1;
}
void MainEvents::GetTrajectory(const Vec3& startPos, const Vec3& startVelocity,
	const float& timeLimit, std::vector<Vec3>& traj, const TRAJECTORY_TYPE& trajType,
	const uint32_t& trajectoryFlags, Vec3&lastNormal, Vec3&lastPoint)
{
	if (trajType == TRAJECTORY_TYPE::TR_GRAVITY)
	{
		Utils::Tracer::trace_t trace;
		Vec3 g(0, 0, -800);

		float step = 0.01f;
		float projectilSize = 3;
		float totalTime = 0;

		bool isCollided = false;

		float bounce = 0.65f;
		Vec3 nextPoint;
		Vec3 start = startPos;
		Vec3 velVec = startVelocity;
		Vec3 previousPoint;
		Vec3 min{ -projectilSize,-projectilSize,-projectilSize }, max{ projectilSize,projectilSize,projectilSize };

		previousPoint = start;

		if (trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD)
		{
			traj.reserve(timeLimit * 100);
			if (!(trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION))
				traj.push_back(start);
		}

		lastPoint = start;

		for (float t = 0; t < 10; t += step) //0,01 nade time is for 0.01
		{
			totalTime += step;
			if (totalTime > timeLimit)
			{
				lastPoint = nextPoint;
				lastNormal = trace.plane.normal;
				if (lastNormal == 0)
					lastNormal = { 0,0,1 };
				break;
			}

			nextPoint = start + velVec * t + (g * 0.5 * t * t);
			tracer.traceLine(&trace, previousPoint, min, max, nextPoint, 0, CONTENTS_SOLID, 0);

			if (trace.entityNum < 1023)
			{
				isCollided = true;
				traj.push_back(trace.endpos);
				Vec3 velVecAtTouchPoint = velVec + g * t;
				velVec = vecs::ReflectVector(velVecAtTouchPoint, trace.plane.normal) * bounce;
				start = trace.endpos;
				t = 0;
				if (trajectoryFlags & TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION)
				{
					lastPoint = nextPoint;
					lastNormal = trace.plane.normal;
					if (lastNormal == 0)
						lastNormal = { 0,0,1 };
					return;
				}
				continue;
			}

			if ( (trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD) && (trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION) && isCollided)
				traj.push_back(nextPoint);
			else if ((trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD) && !(trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION))
				traj.push_back(nextPoint);

			previousPoint = nextPoint;
		}
	}
	else if (trajType == TRAJECTORY_TYPE::TR_LINEAR)
	{
		Utils::Tracer::trace_t trace;
		float projectilSize = 3;
		float timeL = timeLimit;
		Vec3 nextPoint;
		Vec3 min{ -projectilSize,-projectilSize,-projectilSize }, max{ projectilSize,projectilSize,projectilSize };

		if (timeLimit == 0)
			timeL = 5.0;

		nextPoint = startPos + startVelocity * timeL;
		tracer.traceLine(&trace, startPos, min, max, nextPoint, 0, CONTENTS_SOLID, 0);
		if (trace.entityNum < 1023)
		{
			lastNormal = trace.plane.normal;
			if (trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD)
			{
				traj.push_back(startPos);
				traj.push_back(trace.endpos);
				lastPoint = trace.endpos;
			}
		}
		else
		{
			lastNormal = { 0,0,1 };
			if (trajectoryFlags & TrajectoryFlags::TRAJECTORY_RECORD)
			{
				traj.push_back(startPos);
				traj.push_back(nextPoint);
				lastPoint = nextPoint;
			}
		}
	}
	
}
void MainEvents::PredictMissilePath()
{
	predictMissileTimer.Start();
	Vec3 lookingAt;
	Vec3 offset{0,0,0};
	uint32_t trajFlags = 0;
	
	float angleOffsetBottom = 7.6, angleOffsetTop = 7.41;
	float offsetForOffset = 0;
	float offsetAngle = 0;
	float pitchRad = 0;
	float yawRad = 0;
	float modifier = 0;
	float initVelocity = 908;
	float lifeTime = 0;

	trajFlags |= (TrajectoryFlags::TRAJECTORY_RECORD | TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION);

	me.colData.trajectory.clear();


	if (
		!(me.wpInfo.num >= Weapons::WP_THERMAL_NADE
			&& me.wpInfo.num <= Weapons::WP_CONC)
		&& me.wpInfo.num != Weapons::WP_M5
		&& me.wpInfo.num != Weapons::WP_CR
		&& me.wpInfo.num != Weapons::WP_REPEATER
		)
		return;

	switch (me.wpInfo.num)
	{
	case Weapons::WP_PULSE:
		lifeTime = MissileLifetimes::WP_PULSE_LIFETIME;
		break;
	case Weapons::WP_CONC:
		lifeTime = MissileLifetimes::WP_CONC_LIFETIME;
		break;
	case Weapons::WP_CRYO:
		lifeTime = MissileLifetimes::WP_CRYO_LIFETIME;
		break;
	case Weapons::WP_FIRE:
		lifeTime = MissileLifetimes::WP_FIRE_LIFETIME;
		if (me.myFlags & MyFlags::IS_ALTATTACK)
			trajFlags |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION;
		break;
	case Weapons::WP_FRAG:
		lifeTime = MissileLifetimes::WP_FRAG_LIFETIME;
		break;
	case Weapons::WP_THERMAL:
		lifeTime = MissileLifetimes::WP_THERMAL_LIFETIME;
		break;
	case Weapons::WP_THERMAL_NADE:
		lifeTime = MissileLifetimes::WP_THERMAL_NADE_LIFETIME;
		break;
	case Weapons::WP_SONIC:
		lifeTime = MissileLifetimes::WP_SONIC_LIFETIME;
		break;
	case Weapons::WP_PLX:
		lifeTime = MissileLifetimes::WP_PLX_LIFETIME;
		break;
	case Weapons::WP_MERR_SONN:
		lifeTime = MissileLifetimes::WP_MERR_SONN_LIFETIME;
		break;
	case Weapons::WP_CR:
		if (me.myConfig.find(ConfigVals::ION) != me.myConfig.end())
			if (me.myConfig[ConfigVals::ION] == 0)
				return;
		lifeTime = MissileLifetimes::WP_CR_LIFETIME;
		initVelocity = 2100.0f;
		trajFlags |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION;
		break;
	case Weapons::WP_M5:
		if (me.myConfig.find(ConfigVals::SCOPE) != me.myConfig.end())
			if (me.myConfig[ConfigVals::SCOPE] != 0)
				return;
		lifeTime = MissileLifetimes::WP_M5_LIFETIME;
		initVelocity = 1360.0f;
		trajFlags |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION;
		trajFlags |= TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION;
		break;
	case Weapons::WP_TRIP:
		trajFlags |= TrajectoryFlags::TRAJECTORY_RECORD_AFTER_FIRST_COLLISION;
		lifeTime = 2.0f;
		initVelocity = 256.0f;
		trajFlags |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION;
		break;
	case Weapons::WP_REPEATER:
		lifeTime = MissileLifetimes::WP_REPEATER_LIFETIME;
		initVelocity = 1101.0f;
		trajFlags |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION;
		angleOffsetBottom = 1.4; angleOffsetTop = 1.4;
		break;
	default:
		lifeTime = 1.5f;
		break;
	}

	if (-me.pitch < 0)
	{
		if (abs(me.pitch) < 45)
		{
			offsetForOffset = tan(me.pitch * DEGREE_TO_RAD);
		}
		else
		{
			offsetForOffset = tan((90.0f - me.pitch) * DEGREE_TO_RAD);
		}

		offsetAngle = angleOffsetBottom * cos(-me.pitch * DEGREE_TO_RAD) + offsetForOffset;


		pitchRad = -me.pitch + offsetAngle;
		yawRad = me.yaw;

		pitchRad *= DEGREE_TO_RAD;
		yawRad *= DEGREE_TO_RAD;

		//lookign at

		lookingAt.x = std::cos(yawRad) * std::cos(pitchRad);
		lookingAt.y = std::sin(yawRad) * std::cos(pitchRad);
		lookingAt.z = std::sin(pitchRad);
		offset = vecs::NormalizeVector(lookingAt) * 12;
		lookingAt = vecs::NormalizeVector(lookingAt) * initVelocity;
		//lookign at

		modifier = 1 + sin(-me.pitch * DEGREE_TO_RAD) * 0.141;

		lookingAt = lookingAt * modifier;
	}
	else
	{
		if (abs(me.pitch) < 45)
		{
			offsetForOffset = -tan(-me.pitch * DEGREE_TO_RAD);
		}
		else
		{
			offsetForOffset = -tan((90.0f + me.pitch) * DEGREE_TO_RAD);
		}

		offsetAngle = angleOffsetTop * cos(-me.pitch * DEGREE_TO_RAD) + offsetForOffset;

		pitchRad = -me.pitch + offsetAngle;
		yawRad = me.yaw;

		pitchRad *= DEGREE_TO_RAD;
		yawRad *= DEGREE_TO_RAD;

		//lookign at

		lookingAt.x = std::cos(yawRad) * std::cos(pitchRad);
		lookingAt.y = std::sin(yawRad) * std::cos(pitchRad);
		lookingAt.z = std::sin(pitchRad);
		offset = vecs::NormalizeVector(lookingAt) * 12;
		lookingAt = vecs::NormalizeVector(lookingAt) * initVelocity;
		//lookign at

		modifier = 1 + sin(-me.pitch * DEGREE_TO_RAD) * 0.12335;

		lookingAt = lookingAt * modifier;
	}

	if (me.wpInfo.num == Weapons::WP_CR)
	{
		lookingAt.x = std::cos(yawRad) * std::cos(-me.pitch * DEGREE_TO_RAD);
		lookingAt.y = std::sin(yawRad) * std::cos(-me.pitch * DEGREE_TO_RAD);
		lookingAt.z = std::sin(-me.pitch * DEGREE_TO_RAD);
		lookingAt = vecs::NormalizeVector(lookingAt) * initVelocity;
	}
	if (me.wpInfo.num == Weapons::WP_THERMAL
		|| me.wpInfo.num == Weapons::WP_THERMAL_NADE
		|| me.wpInfo.num == Weapons::WP_FRAG
		)
	{
		offset.z += 6.0;
	}

	Vec3 lastPoint;


	GetTrajectory(me.position.posGun + offset, lookingAt, lifeTime, me.colData.trajectory, TRAJECTORY_TYPE::TR_GRAVITY, trajFlags,  me.colData.lastNormal, lastPoint);
	
	predictMissileTimer.Stop();
}
void MainEvents::MissilePaths()
{
	//if (!(wallhackFlags & WALLHACK_FLAGS::DRAW_ALL_NADE_PREDICTION))
	//	return;

	for (auto& m : missiles)
	{
		if (m.second.missileFlags & MissileFlags::IS_TRAJ_CALCULATED)
			continue;

		//bool isStopCollide = false;
		Vec3 lastNormal, lastPoint; 

		m.second.missileFlags |= MissileFlags::IS_TRAJ_CALCULATED;
		m.second.misSpeed = vecs::VecMagnitude(m.second.velVec);
		m.second.trajectory.clear();

		float projXY_length = std::sqrt(m.second.velVec.x * m.second.velVec.x + m.second.velVec.y * m.second.velVec.y);
		m.second.angleXY = std::atan2(m.second.velVec.z, projXY_length) * RADIAN;

		uint32_t trajFlag = 0;
		trajFlag |= TrajectoryFlags::TRAJECTORY_RECORD;

		switch (m.second.trajectoryType)
		{
		case TRAJECTORY_TYPE::TR_GRAVITY:
			if (m.second.missileFlags & MissileFlags::IS_EXPLODE_ON_IMPACT)
				trajFlag |= TrajectoryFlags::TRAJECTORY_QUIT_ON_FIRST_COLLISION; //false stopcollide
			GetTrajectory(m.second.startPos, m.second.velVec, m.second.lifeTime, m.second.trajectory, TRAJECTORY_TYPE::TR_GRAVITY, trajFlag, m.second.destinationNormal, m.second.destination);
			break;
		case TRAJECTORY_TYPE::TR_LINEAR:
			GetTrajectory(m.second.startPos, m.second.velVec, m.second.lifeTime, m.second.trajectory, TRAJECTORY_TYPE::TR_LINEAR, trajFlag, m.second.destinationNormal, m.second.destination);
			break;
		default:
			break;
		}
		int a = 3;
	}

	//drawlines (temp)
	

}
void MainEvents::InitializeMissiles()
{
	initializeEntsTimer.Start();
	uint32_t start = add->entList + 4 + MAX_PLAYERS * playerOffset;
	uint32_t end = add->entList + playerOffset * MAX_ENTITIES;
	entityType_t entType = entityType_t::ET_GENERAL;
	int id = 0;

	if (*(int*)add->mbiiBaseEnt == 0)
	{
		missiles.clear();
		if (world)
			world->moverEntities.clear();
	}

	for (size_t i = start; i < end; i += playerOffset)
	{
		entType = *(entityType_t*)(i);

		//fill missiles
		if (entType != entityType_t::ET_NPC
			 && *(bool*)(i + 0x214) //only if mis is alive
			)
		{
			id = *(int*)(i - 4);
			if (*(int*)(i + 0x124)) //if parentgun 
				missiles[id].Refresh(i, players);
		}
		//fill deka
		//if (entType == entityType_t::ET_NPC)
		//{
		//	for (auto& pl : players)
		//	{
		//		if (pl.entClass == EntClass::CL_DEKA && pl.id == *(int*)(i + 0x114))
		//		{
		//				pl.FillDeka(i);
		//		}
		//	}
		//}
	}

	misTodelete.clear();
	misTodelete.reserve(12);

	//refresh missiles
	for (auto& mis : missiles)
	{
		mis.second.Refresh(mis.second.baseAddress, players);
		if (!(mis.second.missileFlags & MissileFlags::IS_EXIST))
		{
			misTodelete.push_back(mis.second.id);
			mis.second.Clear();
		}
	}

	//delete dead missiles
	for (auto& mis : misTodelete)
	{
		if (mis == 0)
			break;
		missiles.erase(mis);
	}

	if (missiles.size() > 1)
		int a = 3;

	if (ui.menuBlocks[menu::DEBUG_INFO_BLOCK].isDraw && !missiles.empty())
	{
		for (auto&m: missiles)
		{
			float misVel = m.second.misSpeed = vecs::VecMagnitude(m.second.velVec);
			ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_WEAPON_VEL_FACT].value = std::to_string((float)misVel);
			break;
		}
	}

	initializeEntsTimer.Stop();
}
void MainEvents::GetColors()	
{
	for (auto&p:players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
			continue;

		if (me.team == p.team 
			&& !(p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
			&& !(p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
			)
		{
			p.screenInfo.screenColor[0] = rw->colors[Colors::COL_ALLIES][0];
			p.screenInfo.screenColor[1] = rw->colors[Colors::COL_ALLIES][1];
			p.screenInfo.screenColor[2] = rw->colors[Colors::COL_ALLIES][2];
			p.screenInfo.screenColor[3] = rw->colors[Colors::COL_ALLIES][3];
		}
		else if (me.team != p.team
			&& !(p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
			&& !(p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
			)
		{
			p.screenInfo.screenColor[0] = rw->colors[Colors::COL_ENEMIES][0];
			p.screenInfo.screenColor[1] = rw->colors[Colors::COL_ENEMIES][1];
			p.screenInfo.screenColor[2] = rw->colors[Colors::COL_ENEMIES][2];
			p.screenInfo.screenColor[3] = rw->colors[Colors::COL_ENEMIES][3];
		}
		else if ((p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
			&& !(p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
			)
		{
			p.screenInfo.screenColor[0] = rw->colors[Colors::COL_FRIENDS][0];
			p.screenInfo.screenColor[1] = rw->colors[Colors::COL_FRIENDS][1];
			p.screenInfo.screenColor[2] = rw->colors[Colors::COL_FRIENDS][2];
			p.screenInfo.screenColor[3] = rw->colors[Colors::COL_FRIENDS][3];
		}
		else if (!(p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND)
			&& (p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
			)
		{
			p.screenInfo.screenColor[0] = rw->colors[Colors::COL_TARGETS][0];
			p.screenInfo.screenColor[1] = rw->colors[Colors::COL_TARGETS][1];
			p.screenInfo.screenColor[2] = rw->colors[Colors::COL_TARGETS][2];
			p.screenInfo.screenColor[3] = rw->colors[Colors::COL_TARGETS][3];
		}

		if (!(p.permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
		{
			p.screenInfo.screenColor[3] /=2;
			p.screenInfo.lineWidth = 1;
		}
		else
			p.screenInfo.lineWidth = 2;
	}
}
void MainEvents::ChangeTargetTeamToOpposite(Player& p)
{
	if (me.team == Teams::REB)
		p.team = Teams::IMP;
	else
		p.team = Teams::REB;
}
void MainEvents::SwitchSpectator()
{

	if ((me.playerFlags & PlayerFlags::IS_ALIVE) || !isRobot || spectatorSwitchTimer.ElapsedContinuous() < 1000)
		return;
	spectatorSwitchTimer.Stop();

	int anyId = -1;
	int enemyId = -1;

	static int oldId = -1;

	if (isRoundBegin)
		oldId = -1;

	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_RENDERED_ON_MAIN_WINDOW) && p.team != Teams::NONE && p.team != Teams::SPECTATOR)
		{
			anyId = p.id;	
			break;
		}
	}

	//draw->bold28->Print(400, 300, RGB::yellow, "following " + std::to_string(anyId));

	if (oldId != anyId)
	{
		if (anyId != -1)
		{
			std::string command = "+moveup; wait 5; -moveup; follow " + std::to_string(anyId) + '\n';
			sendConsoleCommand(command.c_str());
		}
		oldId = anyId;
	}
}
void MainEvents::GetLookingAtCells()
{
	if (!world || (configFlags & ConfigFlags::SET_MAP_EDITOR_ENABLED))
		return;
	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_ALIVE))
			continue;

		p.botInfo.cellLookingAt = 0;
		p.botInfo.currentCubeFace = CubeFaces::NONE;
		p.botInfo.currentCubeIntersection = 0;

		if (p.permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)
			p.botInfo.cellLookingAt = world->cast_world_ray(p.position.posHead, p.uvec, 5000, me.botInfo.currentCubeFace, p.botInfo.currentCubeIntersection);
	}
}
void MainEvents::InitializePlayers()
{
	GetMaxPlayerId();

	initializePlayersTimer.Start();

	me.RefreshValues(*(int*)add->trueId * playerOffset, *(int*)add->trueId * classOffset, add, isRoundBegin, isRobot);
	me.FillMe(isRoundBegin, add);



	int counter = 0;
	int maxValidPlayerId = 0;

	for (auto& p : players)
	{
		if (counter > maxPlayerId)
			break;

		p.RefreshValues(counter * playerOffset, counter * classOffset, add, isRoundBegin, isRobot);

		if (me.forceFocusedId == p.id + 1)
			p.playerFlags |= PlayerFlags::IS_FORCE_FOCUSED;

		if ((botConfigFlags & BotConfigFlags::MAKE_MAIN_WINDOW_LEADER) && p.id == me.trueId && !isRobot)
		{
			p.permanentPlayerFlags |= PermanentPlayerFlags::IS_LEADER;
			p.permanentPlayerFlags &= ~PermanentPlayerFlags::IS_NOT_LEADER;
		}

		if (p.playerFlags & PlayerFlags::IS_ALIVE)
			maxValidPlayerId = p.id;
		
		counter++;
	}

	maxPlayerId = maxValidPlayerId;

	//fill dekas
	uint32_t start = add->entList + 4 + MAX_PLAYERS * playerOffset;
	uint32_t end = add->entList + playerOffset * MAX_ENTITIES;
	entityType_t entType = entityType_t::ET_GENERAL;
	for (size_t i = start; i < end; i += playerOffset)
	{
		entType = *(entityType_t*)(i);

		if (entType == entityType_t::ET_NPC)
		{
			for (auto& pl : players)
			{
				if (pl.entClass == EntClass::CL_DEKA && pl.id == *(int*)(i + 0x114))
				{
					pl.FillDeka(i,add);
				}
			}
		}
	}

	if (me.team != Teams::SPECTATOR && me.trueId != me.id)
		me.playerFlags |= PlayerFlags::IS_ALIVE;

	WriteSharedData();
	ReadSharedData();

	if (input->IsKeyToggled(MyKeysEnum::TK_KEYS))
	{
		IS_TK = !IS_TK;
	}

	if (IS_TK)
	{
		for (auto& p : players)
		{
			if (!(p.playerFlags & PlayerFlags::IS_VALID))
				continue;
			ChangeTargetTeamToOpposite(p);
		}
	}

	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
			continue;
		if ((p.permanentPlayerFlags & PermanentPlayerFlags::IS_FRIEND))
			p.team = me.team;
		if ((p.permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER) && (botConfigFlags & BotConfigFlags::MAKE_LEADER_FRIENDLY))
			p.team = me.team;
		else if (p.permanentPlayerFlags & PermanentPlayerFlags::IS_TARGET)
		{
			ChangeTargetTeamToOpposite(p);
		}
	}

	GetPlayerNames();
	initializePlayersTimer.Stop();
	VisibilityChecker();
}


void MainEvents::MainLoop()
{
	input->CheckState(isRobot);
	IsServerTick();
	GetFps();
	OnRoundBegin();
	SenseWH();
	totalMainEventTimer.Start();
	ReadLastLineConsole();
	FunnyReplies();
	GetMapNamePath();
	MakeFriendsAndEnemies();
	InitializePlayers();
	SwitchSpectator();
	InitializeMissiles();
	MissilePaths();
	PredictMissilePath();
	MakeMyModelTransparent();
	NoSpread();
	InitializeWeapons();
	CrouchWhenAttacked();
	AutoDodge();
	Aim();

	totalMainEventTimer.Stop();
	SetTimers();

	//map editor
	MapEditor();
}


//botstuff--------------------------------------------------------------------------------------------------------------
void MainEvents::CheckMoversForChange()
{
	if (!world)
		return;

	bool isRebuildGraph = false;

	std::vector<uint16_t> affectedEntities;

	for (auto& doorEnt : world->moverEntities)
	{	
		if (doorEnt.second.IsUpdated())
		{
			isRebuildGraph = true;
			affectedEntities.push_back(doorEnt.first);
		}
	}

	if (isRebuildGraph)
	{
		world->unlock_banned_area_all(affectedEntities);
		me.bot.oldEntityAhead = 0;
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
	}
}
void MainEvents::FillMoverEnts()
{
	if (!world)
		return;
	if (world->fill_mover_ents(me.bot.entityAhead))
	{
		world->rescan_area(me.bot.myCellCoordinates);
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
	}
}
void MainEvents::DoorProbe()
{
	if (!world)
		return;
	//DOOR PROBERAY
	float rayLength = 55;

	Utils::Tracer::trace_t probeDoor;
	Vec3 direction = me.uvec; direction.z = 0; direction = vecs::NormalizeVector(direction);

	Vec3 end = direction * rayLength + me.position.posChest; //end.z -= 80;
	Vec3 start = me.position.posChest;

	Vec3 min_probe{ -8,-8,-8 }; Vec3 max_probe{ 8,8,8 };
	tracer.traceLine(&probeDoor, start, min_probe, max_probe, end, 0, 1, 0);

	//draw->DrawLine(start, end, 2, RGB::yellow);
	me.bot.entityAhead = probeDoor.entityNum;

}
void MainEvents::GetMyCell()
{
	Vec3 myPosAdjusted = me.position.posFeet; myPosAdjusted.z += WorldConstants::CELL_SIZE;
	Cell* cell = world->get_cell(myPosAdjusted, 3, me.bot.myCellCoordinates);

	Cell* factualCell = world->get_cell(me.position.posFeet, 0, me.bot.myFactualCellCoordinates);
	me.bot.entityAhead = 0;

	if (cell)
	{
		me.bot.myLastValidCellCoordinates = me.bot.myCellCoordinates;
	}

	if (cell && (cell->flags & CellFlags::IS_ELEVATOR_COLUMN))
	{
		if (factualCell && (factualCell->flags & CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP))
			me.bot.myCellCoordinates = me.bot.myFactualCellCoordinates;
	}
}
Cell* MainEvents::GetNESWPositionCell(const Vec3& uvec, const Vec3& position)
{
	Vec3 fwdVec = uvec; fwdVec.z = 0;
	fwdVec = vecs::NormalizeVector(fwdVec) * me.bot.distanceTargetFromMeToBots;
	fwdVec += position;

	Utils::Tracer::trace_t t;
	tracer.traceLine(&t, position, 0, 0, fwdVec, 0, 0x1011, 0);
	if (t.entityNum != 1023)
		return nullptr;

	CellCoordinates cellTemp;
	Cell*tgtCell = world->get_cell(fwdVec, 3, cellTemp);

	//if (tgtCell && tgtCell->graphNode)
	//	draw->DrawLine(position, fwdVec, 2, RGB::yellow);
	return tgtCell;
}
Cell* MainEvents::GetNESWPositionCells(const Vec3& uvec, const Vec3& position)
{
	Cell* fwdCell = nullptr;
	Cell* rightCell = nullptr;
	Cell* leftCell = nullptr;
	Cell* backCell = nullptr;

	Vec3 vecRight = uvec; vecRight.x = uvec.y; vecRight.y = -uvec.x;
	rightCell = GetNESWPositionCell(vecRight, position);

	if (!rightCell || !rightCell->graphNode)
	{
		Vec3 vecLeft = uvec; vecLeft.x = -uvec.y; vecLeft.y = uvec.x;
		leftCell = GetNESWPositionCell(vecLeft, position);
	}
	else
		return rightCell;

	if (!leftCell || !leftCell->graphNode)
	{
		Vec3 vecBack = uvec; vecBack.x = -uvec.x; vecBack.y = -uvec.y;
		backCell = GetNESWPositionCell(vecBack, position);
	}
	else
		return leftCell;

	if (!backCell || !backCell->graphNode)
	{
		Vec3 vecFwd = uvec;
		fwdCell = GetNESWPositionCell(vecFwd, position);
	}
	else
		return backCell;

	return fwdCell;
}
void MainEvents::GetNESWPositionLeaderCells(Player*p)
{
	Vec3 uvec = p->uvec;
	Vec3 vecRight = p->uvec; vecRight.x = uvec.y; vecRight.y = -uvec.x;
	p->gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT] = world->get_cell_coordinates(GetNESWPositionCell(vecRight, p->position.posCrotch));

	Vec3 vecLeft = uvec; vecLeft.x = -uvec.y; vecLeft.y = uvec.x;
	p->gridPosition.leaderBotSlots[BotLeaderPosition::LEFT] = world->get_cell_coordinates(GetNESWPositionCell(vecLeft, p->position.posCrotch));
	
	Vec3 vecBack = uvec; vecBack.x = -uvec.x; vecBack.y = -uvec.y;
	p->gridPosition.leaderBotSlots[BotLeaderPosition::BACK] = world->get_cell_coordinates(GetNESWPositionCell(vecBack, p->position.posCrotch));

	Vec3 vecFwd = uvec;
	p->gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD] = world->get_cell_coordinates(GetNESWPositionCell(vecFwd, p->position.posCrotch));
}
void MainEvents::GetPlayerCells()
{
	if (!world)
		return;



	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
			continue;

		if (!(p.permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER))
		{
			if (p.distances.distance3 < 400)
				p.gridPosition.cellCoordinates = world->get_cell_coordinates(GetNESWPositionCells(p.uvec, p.position.posChest));
			else
				world->get_cell(p.position.posFeet, 3, p.gridPosition.cellCoordinates);
		}
		else
		{
			for (auto& p : p.gridPosition.leaderBotSlots)
			{
				p.second = 0;
			}

			if (p.distances.distance3 < 500)
			{
				GetNESWPositionLeaderCells(&p);

				Cell* leftC = world->get_cell(p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT]);
				Cell* rightC = world->get_cell(p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT]);
				Cell* forwardC = world->get_cell(p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD]);
				Cell* backC = world->get_cell(p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK]);

				if (me.bot.botLeaderPosition == BotLeaderPosition::RIGHT)
				{
					if (p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT] != 0 && rightC && !(rightC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD] != 0 && forwardC && !(forwardC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK] != 0 && backC && !(backC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT] != 0 && leftC && !(leftC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT];
				}
				else if (me.bot.botLeaderPosition == BotLeaderPosition::LEFT)
				{
					if (p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT] != 0 && leftC && !(leftC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK] != 0 && backC && !(backC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD] != 0 && forwardC && !(forwardC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT] != 0 && rightC && !(rightC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT];
				}
				else if (me.bot.botLeaderPosition == BotLeaderPosition::BACK)
				{
					if (p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK] != 0 && backC && !(backC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::BACK];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT] != 0 && rightC && !(rightC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::RIGHT];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT] != 0 && leftC && !(leftC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::LEFT];
					else if (p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD] != 0 && forwardC && !(forwardC->flags & CellFlags::IS_BANNED))
						p.gridPosition.cellCoordinates = p.gridPosition.leaderBotSlots[BotLeaderPosition::FORWARD];
				}
			}
			else
			{
				world->get_cell(p.position.posFeet, 3, p.gridPosition.cellCoordinates);
			}
		}
	}
	GetMyCell();
}
void MainEvents::AttemptToAddNewArea()
{
	if (!(me.myFlags & MyFlags::IS_NOCLIP) && world)
	{
		world->add_new_area(me.bot.myCellCoordinates);

		if (world->oldValidCellsCount == 0)
		{
			mapReader->SaveMap(rw->mapFolderPath, currentMapW, world);
			world->oldValidCellsCount = world->validCellsCount;
		}
	}
	if (world)
	{
		if (world->oldValidCellsCount != world->validCellsCount)
		{
			worldFlags |= WorldFlags::IS_SAVE_REQURED;
		}
	}
}
void MainEvents::ReadSavedMap()
{
	if (!world)
	{
		world = mapReader->ReadMap(currentMapPath, &tracer, add->entList, *(int*)add->playerOffset);
		if (world)
		{
			worldFlags |= WorldFlags::IS_GENERATED;
			worldFlags &= ~WorldFlags::IS_MAP_CHANGE;
		}
	}
}
void MainEvents::DeleteWorld()
{
	EraseAllTargetsAndPath();
	delete(world);
	world = nullptr;
	worldFlags &= ~WorldFlags::IS_GENERATED;
}
void MainEvents::TriggerStuff()
{
	if (!world)
		return;
	if (isServerTicked)
	{
		world->tick_triggers(me.surface);
	}
}
void MainEvents::GenerateWorld()
{
	Vec3 startWorldPos = me.position.posFeet;

	if (world && (worldFlags & WorldFlags::IS_MAP_CHANGE) || reloadThisBotMap || reloadMapNow)
	{
		DeleteWorld();
	}

	ReadSavedMap();
	AttemptToAddNewArea();

	if (me.surface == 1023 || me.surface < 32 || (worldFlags & WorldFlags::IS_GENERATED) || isRobot)
		return;

	if (world != nullptr)
	{
		delete(world);
		world = nullptr;
	}

	world = new World(startWorldPos, &tracer, add->entList, *(int*)add->playerOffset);

	worldFlags |= WorldFlags::IS_GENERATED;
}
void MainEvents::GetTargetCell()
{
	if (!(GetAsyncKeyState(0x30) & 1) || !world) //0
		return;

	me.bot.tgtCells[TargetCells::MANUAL_TARGET_CELL] = me.bot.myCellCoordinates;

	if (me.bot.tgtCells[TargetCells::MANUAL_TARGET_CELL] != me.bot.myOldTargetCoordinates)
	{
		Cell* previousDestinationCell = world->get_cell(me.bot.myOldTargetCoordinates);
		if (previousDestinationCell && previousDestinationCell->graphNode)
		{
			previousDestinationCell->graphNode->flags &= ~GraphFlags::IS_TARGET;
		}

		Cell* destinationCell = world->get_cell(me.bot.tgtCells[TargetCells::MANUAL_TARGET_CELL]);
		if (destinationCell && destinationCell->graphNode)
		{
			destinationCell->graphNode->flags |= GraphFlags::IS_TARGET;
		}

		me.bot.myOldTargetCoordinates = me.bot.tgtCells[TargetCells::MANUAL_TARGET_CELL];
	}
}
void MainEvents::PerfectAimBot(const bool& isFire, const bool& altFire)
{
	if (!isFire)
		return;

	static int frameCounter = 0;
	double elapsedTimeSinceLastShot = botFireTimer.ElapsedContinuous();

	bool isD = me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_RIGHT;
	bool isA = me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_LEFT;
	bool isW = me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_FORWARD;
	bool isS = me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_BACK;

	if ((!isD && !isA && !isW && !isS)
		|| (me.gameMode == GameModes::LEGENDS)
		|| me.wpInfo.num == Weapons::WP_CPISTOL
		|| me.wpInfo.num == Weapons::WP_PISTOL
		|| me.wpInfo.num == Weapons::WP_WPISTOL
		|| me.wpInfo.num == Weapons::WP_EE3_CARABINE
		)
	{
		if (!altFire)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_ATTACK;
		else
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_ALTATTACK;
		return;
	}

	//release keys on the first frame
	if (frameCounter == 0)
	{
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_RIGHT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_LEFT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_BACK;
	}

	//shoot on the next frame
	if (frameCounter == 1)
	{
		if (!altFire)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_ATTACK;
		else
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_ALTATTACK;

		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_RIGHT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_LEFT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_BACK;
	}

	//return everything as it was
	if (frameCounter == 2)
	{
		if (!altFire)
			me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ATTACK;
		else
			me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ALTATTACK;

		if (isW)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_FORWARD;
		if (isS)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_BACK;
		if (isA)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_LEFT;
		if (isD)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_RIGHT;
	}

	frameCounter++;


	if (elapsedTimeSinceLastShot > me.wpInfo.fireRate + 5)
	{
		frameCounter = 0;
		botFireTimer.Stop();
	}
}
void MainEvents::RollIfOnFire()
{
	static size_t frame = 0;
	static bool isForward = false;
	static bool isCrouch = false;

	if (!(me.myFlags & MyFlags::IS_ONFIRE))
	{
		frame = 0;
		isForward = false;
		isCrouch = false;
		return;
	}
	me.bot.enemyTarget = nullptr;
	me.bot.botStateFlag |= BotStateFlags::BOT_STATE_ROLLING_FIRE;

	if (frame==0)
	{
		me.bot.previousWeapon = me.wpInfo.num;
		std::string prevWeaponString = "weapon 2; wait 240; weapon " + std::to_string((int)me.bot.previousWeapon) + "\n";
		sendConsoleCommand(prevWeaponString.c_str());
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_JUMP;
		isForward = true;
	}
	if (frame == 1)
	{
		isCrouch = true;
	}
	if (frame == (int)(fps*1.50f))
	{
		isForward = false;
		isCrouch = false;
		//std::string prevWeaponString = "weapon " + std::to_string((int)me.bot.previousWeapon) + "\n";
		//sendConsoleCommand(prevWeaponString.c_str());
	}

	if (isForward)
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_FORWARD;
	if (isCrouch)
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_CROUCH;

	frame++;

	if (frame == (int)(fps * 1.50f) + (int)(fps))
	{
		frame = 0;
	}
}
void MainEvents::SelectWeapon()
{
	static bool isWeaponChanged = false;

	if (me.isInstantDeathFlag || isRoundBegin)
		isWeaponChanged = false;

	if (me.timeAlive > 2500 && !isWeaponChanged)
	{
		isWeaponChanged = true;

		switch (me.entClass)
		{
		case EntClass::CL_CLONE:
		{
			std::string wpName = "weapon " + std::to_string((int)Weapons::WP_CR);
			sendConsoleCommand(wpName.c_str());
			break;
		}
		case EntClass::CL_HERO:
		{
			std::string wpName = "weapon " + std::to_string((int)Weapons::WP_E11);
			sendConsoleCommand(wpName.c_str());
			break;
		}
		case EntClass::CL_BH:
		{
			if (me.myConfig.find(ConfigVals::E11) != me.myConfig.end())
			{
				if (me.myConfig[ConfigVals::E11] == 3 || me.myConfig[ConfigVals::E11] == 2)
				{
					std::string wpName = "weapon " + std::to_string((int)Weapons::WP_E11);
					sendConsoleCommand(wpName.c_str());
				}
			}
			break;
		}
		default:
			break;
		}
	}
}
void MainEvents::BotAttack()
{

	me.bot.isBotShooting = false;

	//if (!me.bot.enemyTarget)
	//	return;

	bool isAttack = false;
	bool isAltattack = false;

	float e11AltattackThreshold = 300;

	//me.projectileRifleFireTimer.Start();

	if (me.bot.enemyTarget)
		switch (me.wpInfo.num)
		{
		case Weapons::WP_E11:
		{
			if (me.bot.enemyTarget->distances.distance3 > e11AltattackThreshold)
				isAttack = true;
			else
			{
				isAttack = true;
				isAltattack = true;
			}
			break;
		}
		case Weapons::WP_T21:
		{
			isAttack = true;
			isAltattack = true;
			break;
		}
		case Weapons::WP_PROJ:
		{
			isAttack = false;
			isAltattack = false;

			static bool shouldFireProj = false;

			if (!shouldFireProj)
			{
				me.projectileRifleFireTimer.Start();
				shouldFireProj = true;
			}

			float timeEl = me.projectileRifleFireTimer.ElapsedCurrentMs();
			if (timeEl > 5200)
			{
				shouldFireProj = false;
				timeEl = 0;
			}

			if (timeEl == 0 && me.clipAmmo != 0)
			{
				if (!(me.myFlags & MyFlags::IS_SCOPE))
					sendConsoleCommand("+altattack; wait 180; +attack; wait 5; -attack; wait 5; -altattack;");
				else
					sendConsoleCommand("+attack; wait 5; -attack; -altattack;");
			}

			break;
		}
		default:
			isAttack = true;
			break;
		}

	//reload if half a clip spent
	if ((me.clipAmmo <= (int)(me.clipSize / 2) && me.leftAmmo != 0) && me.stance2 != Stances2::RELOADING)
	{
		if (me.entClass != EntClass::CL_DEKA && me.wpInfo.num != Weapons::WP_MELEE && me.wpInfo.num != Weapons::WP_LS)
		{
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_RELOAD;
			isAttack = false;
			isAltattack = false;
			return;
		}
	}

	if (me.leftAmmo == 0 && me.clipAmmo == 0)
	{
		isAttack = false;
		isAltattack = false;
		return;
	}

	if (!me.bot.enemyTarget)
		return;

	me.bot.isAltAttaking = isAltattack;
	PerfectAimBot(isAttack, isAltattack);
	GetPlayerTrajectory(me.bot.enemyTarget);
	me.bot.botStateFlag |= BotStateFlags::BOT_STATE_SHOOT;
	me.bot.isBotShooting = true;

}
void MainEvents::AddWeightToPlayerNode()
{
	if (!world)
		return;
	for (auto& p : sortedPlayers)
	{
		if (p->distances.distance3 > 450)
			continue;
		CellCoordinates cc;
		Cell* c = world->get_cell(p->position.posCrotch, 4, cc);
		if (!c || !c->graphNode)
			continue;

		if (p->gridPosition.previousOccupiedGraphNode != c->graphNode)
		{
			auto it = world->graph.find((uintptr_t)p->gridPosition.previousOccupiedGraphNode);
			if (it != world->graph.end())
			{
				p->gridPosition.previousOccupiedGraphNode->weight = p->gridPosition.previousOccupiedGraphNodeWeight;
			}
			p->gridPosition.previousOccupiedGraphNodeWeight = c->graphNode->weight;
			p->gridPosition.previousOccupiedGraphNode = c->graphNode;

			if (p->distances.distance3 < 350)
				c->graphNode->weight = 1000;
		}
	}
}
void MainEvents::Elections()
{
	if (!world)
		return;

	//me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = 0;

	//choose target to attack
	me.bot.enemyTarget = SmartChooseTarget();

	//shoot down mines and sonics
	for (auto& m : missiles)
	{
		if ((m.second.parentGun == Weapons::WP_TRIP && m.second.trajectoryType == TRAJECTORY_TYPE::TR_STATIONARY)
			|| (m.second.parentGun == Weapons::WP_SONIC && m.second.trajectoryType == TRAJECTORY_TYPE::TR_INTERPOLATE)
			)
		{
			Vec3 aimAtPos = m.second.startPos;
			if (vecs::VecDistance(me.position.posFeet, aimAtPos) > (m.second.radius + 150.0f))
				continue;
			Utils::Tracer::trace_t t;

			tracer.traceLine(&t, me.position.posGun, 0, 0, aimAtPos, 0, 0x1111, 0);
			if (t.entityNum == 1023 ||  t.entityNum == m.second.id)
			{
				me.bot.enemyTarget = &players[me.trueId];
				GetAimAngles(me.position.posGun, m.second.startPos, me.yaw, me.pitch, me.bot.enemyTarget->angles.me_to_this_target.x, me.bot.enemyTarget->angles.me_to_this_target.y);
				break;
			}
		}

	}

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	if (!myCell || !myCell->graphNode)
		return;

	bool isRefreshTargetNode = false;
	float elapsedTime = me.bot.newTargetTimer.ElapsedContinuous();
	if (elapsedTime > me.bot.refreshTargetTimeLimit)
	{
		me.bot.newTargetTimer.Stop();
		isRefreshTargetNode = true;
	}

	bool isRandomRefreshTargetNode = Utils::RandomPercent(1); 
	//choose who to follow
	bool isLeaderChosen = false;
	for (auto& p : sortedPlayers)
	{
		if (!(p->playerFlags & PlayerFlags::IS_VALID) || world->get_cell(p->gridPosition.cellCoordinates) == nullptr)
			continue;

		if (!(p->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE) && !isRefreshTargetNode)
			continue;

		Cell* playerCell = world->get_cell(p->gridPosition.cellCoordinates);

		if (!playerCell || !playerCell->graphNode)
			continue;

		if ((playerCell->graphNode->islandNum != myCell->graphNode->islandNum) || (playerCell->graphNode->flags & GraphFlags::IS_BRIDGE_NODE))
			continue;

		if (p->permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)
		{
			isLeaderChosen = true;
			me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = p->gridPosition.cellCoordinates;
		}
		if (p->permanentPlayerFlags & (PermanentPlayerFlags::IS_TARGET))
		{
			isLeaderChosen = true;
			me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = p->gridPosition.cellCoordinates;
			break;
		}
	}

	//choose whatever player
	std::vector<int> selectedPlayerids;
	if (!isLeaderChosen)
	{
		for (auto& p : sortedPlayers)
		{
			Cell* playerCell = world->get_cell(p->gridPosition.cellCoordinates);

			if (!playerCell || !playerCell->graphNode)
				continue;

			if (!(p->playerFlags & PlayerFlags::IS_VALID) || (p->team == me.team && !(p->permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)))
				continue;

			if ((botConfigFlags & BotConfigFlags::TARGET_ONLY_VISIBLE) && !(p->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
				continue;

			if (!isRandomRefreshTargetNode && !(p->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
				continue;


			if ((playerCell->graphNode->islandNum == myCell->graphNode->islandNum) && !(playerCell->graphNode->flags & GraphFlags::IS_BRIDGE_NODE))
			{
				isLeaderChosen = true;
				me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = p->gridPosition.cellCoordinates;
				break;
			}
			selectedPlayerids.push_back(p->id);
		}
	}

	//find the closest node to player on another island
	float shortestDistance = 99999;
	if (!isLeaderChosen && selectedPlayerids.size())
	{
		GraphNode* closestNode = nullptr;

		int a = 0;
		for (auto& ch : world->validChunks)
		{
			Chunk* chunk = world->get_chunk(ch);
			if (vecs::VecDistance(chunk->locationFloat, players[selectedPlayerids[0]].position.posFeet) > 1200)
				continue;
			
			for (auto& pn : chunk->nodes)
			{
				float currentDistance = vecs::VecDistance(pn.second->vertex, players[selectedPlayerids[0]].position.posFeet);
				if (!(pn.second->flags & GraphFlags::IS_BRIDGE_NODE) && pn.second->islandNum == myCell->graphNode->islandNum && shortestDistance > currentDistance)
				{
					shortestDistance = currentDistance;
					closestNode = pn.second;
				}
			}
		}

		if (closestNode != nullptr)
			me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = world->unpack_cell_and_chunk(closestNode->cells[0]);
		else
			me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] = 0;
	}

	if (me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] != me.bot.myOldPlayerCoordinates
		&& generatedPathLastError != PathfindingErrors::UNREACHABLE 
		&& generatedPathLastError != PathfindingErrors::NONE)
	{
		me.bot.myOldPlayerCoordinates = me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL];
		draw->bold28->Print(250, 300, RGB::red, "DESTINATION CHANGED " + std::to_string((int)generatedPathLastError));
	}
}

//bot movement
void MainEvents::EraseAllTargetsAndPath()
{
	pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;

	Cell* destinationCell = world->get_cell(me.bot.tgtCells[TargetCells::MANUAL_TARGET_CELL]);
	if (destinationCell && destinationCell->graphNode)
	{
		destinationCell->graphNode->flags &= ~GraphFlags::IS_TARGET;
	}

	for (auto& tgt : me.bot.tgtCells)
	{
		tgt.second = 0;
	}

	me.bot.currentStep = 0;
	ErasePath();
}
void MainEvents::ErasePath()
{
	if (!world)
		return;
	for (auto& n : navigationPath)
	{
		GraphNode* currentCode = world->node_validity_check(n);
		if (currentCode != nullptr)
		{
			currentCode->flags &= ~GraphFlags::IS_PATH_NODE;
		}
	}
	me.bot.currentTriggersInPath.clear();
	navigationPath.clear();
	navigationPathPoints.clear();
	navigationPathPointsUnedited.clear();
	me.bot.currentStep = 0;
	generatedPathLastError = PathfindingErrors::NONE;
}
void MainEvents::GenerateMinionPath()
{
	if (!world)
		return;
	for (auto& p : sortedPlayers)
	{
		if (p->botInfo.minionDestination != p->botInfo.oldMinionDestination)
		{
			p->botInfo.minionNavigationPath.clear();
			p->permanentPlayerFlags &= ~PermanentPlayerFlags::IS_MINION_PATH_GENERATED;
			p->botInfo.oldMinionDestination = p->botInfo.minionDestination;
		}

		if (p->botInfo.minionNavigationPath.size() < 2 || p->botInfo.minionDestination == 0)
		{
			p->botInfo.minionNavigationPath.clear();
		}

		if (!(p->permanentPlayerFlags & PermanentPlayerFlags::IS_MINION_PATH_GENERATED))
		{
			Cell* startingCell = world->get_cell(p->gridPosition.cellCoordinates);
			Cell* destinationCell = world->get_cell(p->botInfo.minionDestination);
			if (!startingCell || !destinationCell || !startingCell->graphNode || !destinationCell->graphNode)
				continue;
			world->generate_path(destinationCell->graphNode, startingCell->graphNode, p->botInfo.minionNavigationPath);
			p->permanentPlayerFlags |= PermanentPlayerFlags::IS_MINION_PATH_GENERATED;
		}
	}
}
void MainEvents::DeleteCurrentDestination()
{
	//me.bot.elevatorButtonPressDelay.Stop();
	auto it = me.bot.tgtCells.find(me.bot.selectedDestination);
	if (it != me.bot.tgtCells.end())
	{
		Cell* curCell = world->get_cell(me.bot.tgtCells[me.bot.selectedDestination]);
		if (curCell && curCell->graphNode)
			curCell->graphNode->flags &= ~GraphFlags::IS_TARGET;
		me.bot.tgtCells[me.bot.selectedDestination] = { 0,0 };
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
		me.bot.currentStep = 0;
		me.bot.currentTriggersInPath.clear();

		ErasePath();
	}
}
Cell* MainEvents::SelectDestination(Cell* myCell)
{
	if (me.bot.selectedDestination != TargetCells::NONE)
		me.bot.oldSelectedDestination = me.bot.selectedDestination;

	me.bot.selectedDestination = TargetCells::NONE;

	if (!myCell || !myCell->graphNode)
		return nullptr;

	Cell* destinationCell = nullptr;

	for (auto& ds : me.bot.tgtCells)
	{
		Cell* currentTargetCell = world->get_cell(ds.second);
		if (currentTargetCell && currentTargetCell->graphNode && myCell->graphNode->islandNum != currentTargetCell->graphNode->islandNum)
		{
			DeleteCurrentDestination();
		}
	}



	for (auto& ds : me.bot.tgtCells)
	{
		Cell* returnCell = world->get_cell(ds.second);
		if (returnCell && returnCell->graphNode)
		{
			//get the id from the list
			me.bot.selectedDestination = ds.first;

			if (me.bot.myOldDestination != ds.second )
			{
				me.bot.myOldDestination = ds.second;
				pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			}

			destinationCell = world->get_cell(ds.second);
			break;
		}
	}

	return destinationCell;
}
void MainEvents::CheckElevatorPath()
{
	std::vector<Trigger*> potentialTriggers;
	std::vector<int> potentialTriggerLocations;
	for (int i = 0; i < navigationPath.size(); i++)
	{
		GraphNode* currentNode = world->node_validity_check(navigationPath[i]);

		if (world->get_cell(currentNode->cells[0])->flags & (CellFlags::IS_ELEVATOR_DETECTOR | CellFlags::IS_ELEVATOR_DETECTOR_UP))
		{
			Trigger* t = world->find_trigger(currentNode);
			Trigger* otherT = nullptr;
			if (t)
				otherT = t->other;
			if (!t || !otherT)
				continue;

			potentialTriggers.push_back(t);
			potentialTriggerLocations.push_back(i);
		}
	}

	if (potentialTriggers.empty())
		return;

	for (int i = 0; i < potentialTriggers.size() - 1; i++)
	{
		if (potentialTriggers[i]->other == potentialTriggers[i + 1])
		{
			std::pair<int, CellCoordinates> trigPair1{ potentialTriggerLocations[i], potentialTriggers[i]->triggerBottom };
			std::pair<int, CellCoordinates> trigPair2{ potentialTriggerLocations[i + 1], potentialTriggers[i + 1]->triggerBottom };
			me.bot.currentTriggersInPath.insert(trigPair1);
			me.bot.currentTriggersInPath.insert(trigPair2);
		}
	}

	if (me.bot.currentTriggersInPath.empty())
	{
		return;
	}

	auto t = me.bot.currentTriggersInPath.begin();

	//go to button if elevator hasn't been activated


	Trigger* trigger = world->find_trigger(t->second);
	Cell* elevatorButton = world->get_cell(trigger->elevatorButton);
	Cell* elevatorButtonCall = world->get_cell(trigger->elevatorButtonCall);

	if (elevatorButtonCall == nullptr)
	{
		if (elevatorButton
			&& !(trigger->elevatorStates & ElevatorStates::ACTIVATED_BY_PLAYER)
			&& (elevatorButton->flags & CellFlags::IS_ELEVATOR_BUTTON_1)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButton;
			return;
		}

		//press first time
		if (elevatorButton
			&& (elevatorButton->flags & CellFlags::IS_ELEVATOR_BUTTON_2)
			&& !(trigger->elevatorStates & ElevatorStates::ACTIVATED_BY_PLAYER)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButton;
			return;
		}

		if (elevatorButton
			//&& !(trigger->elevatorStates & ElevatorStates::ACTIVE)
			&& (elevatorButton->flags & CellFlags::IS_ELEVATOR_BUTTON_2)
			&& (trigger->elevatorStates & ElevatorStates::READY_FOR_REACTIVATION)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButton;
			return;
		}
	}
	else
	{
		if (elevatorButtonCall
			&& !(trigger->elevatorStates & ElevatorStates::ACTIVE)
			&& !(trigger->elevatorStates & ElevatorStates::ACTIVATED_BY_PLAYER)
			&& !(trigger->elevatorStates & ElevatorStates::READY_FOR_REACTIVATION)
			&& (elevatorButtonCall->flags & CellFlags::IS_ELEVATOR_BUTTON_CALL)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButtonCall;
			return;
		}

		if (elevatorButtonCall
			&& (trigger->elevatorStates & ElevatorStates::ACTIVE)
			&& (trigger->elevatorStates & ElevatorStates::READY_FOR_REACTIVATION)
			&& (elevatorButton->flags & CellFlags::IS_ELEVATOR_BUTTON_1)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButton;
			return;
		}
		if (elevatorButtonCall
			&& (trigger->elevatorStates & ElevatorStates::ACTIVE)
			&& !(trigger->elevatorStates & ElevatorStates::ACTIVATED_BY_PLAYER)
			&& (elevatorButton->flags & CellFlags::IS_ELEVATOR_BUTTON_1)
			)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.tgtCells[TargetCells::ELEVATOR_BUTTON_TARGET_CELL] = trigger->elevatorButton;
			return;
		}
	}

}
bool MainEvents::GenerateNewPathCooldown()
{
	return (generateNewPathCoolDownTimer.ElapsedContinuous() > me.bot.generateNewPathCooldown);
}
void MainEvents::GeneratePath()
{
	if (!world || !GenerateNewPathCooldown()) 
		return;

	pathfindingFlags &= ~PathfindingFlags::IS_UPDATED;

	if (isRoundBegin)
		ErasePath();
	
	if (isRoundBegin || me.isRespawnFlag)
	{
		EraseAllTargetsAndPath();
	}

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	Cell* destinationCell = SelectDestination(myCell);

	if (!destinationCell)
		return;

	if (pathfindingFlags & PathfindingFlags::IS_GENERATED)
		return;

	//==========================================================================================

	ErasePath();

    generatedPathLastError = world->generate_path(destinationCell->graphNode, myCell->graphNode, navigationPath);

	if (navigationPath.empty())
	{
		DeleteCurrentDestination();
		return;
	}

	if (navigationPath.size() > 1)
	{
		me.bot.currentStep = 1;
	}

	if (generatedPathLastError != PathfindingErrors::SUCCESS && generatedPathLastError != PathfindingErrors::START_AND_FINISH_SAME_NODE)
	{
		DeleteCurrentDestination();
		return;
	}

	for (auto&n: navigationPath)
	{
		navigationPathPointsUnedited.push_back(world->node_validity_check(n)->vertex);
	}

	pathfindingFlags |= PathfindingFlags::IS_GENERATED;
	pathfindingFlags |= PathfindingFlags::IS_UPDATED;

	CheckElevatorPath();

	generateNewPathCoolDownTimer.Stop();
}

bool MainEvents::PointReachCondition(const Vec3&point, GraphNode* currentNode)
{
	if (me.bot.selectedDestination == TargetCells::ELEVATOR_BUTTON_TARGET_CELL)
	{
		CellCoordinates elevatorCC = world->unpack_cell_and_chunk(currentNode->cells[0]);
		Cell* elevatorCell = world->get_cell(elevatorCC);
		if ((elevatorCell->flags & (CellFlags::IS_ELEVATOR_BUTTON_1 | CellFlags::IS_ELEVATOR_BUTTON_2 | CellFlags::IS_ELEVATOR_BUTTON_CALL)))
		{
			if (me.stance2 == Stances2::USE_BUTTON)
			{
				for (auto& trigger : world->customTriggers)
				{
					if (trigger.second.elevatorButton == elevatorCC || trigger.second.elevatorButtonCall == elevatorCC)
					{
						trigger.second.activate();
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			return vecs::VecDistance(me.position.posFeet, point) < me.bot.reachNextNodeDistance;
	}
	else
		return vecs::VecDistance(me.position.posFeet, point) < me.bot.reachNextNodeDistance;
}
bool MainEvents::IsPathTooFarAway(const Vec3& currentPoint)
{
	float maxDistance = 2*WorldConstants::GRAPH_MESH_MAX_SIZE * WorldConstants::CELL_SIZE;
	return (vecs::VecDistance(me.position.posFeet, currentPoint) > maxDistance);
}
bool MainEvents::GoToPoint(const Vec3& point, GraphNode* currentNode)
{
	static float oldAngleX = 0;
	static float oldAngleY = 0;
	static float angleX_min = 0;
	static float angleY_min = 0;
	static float angleX_inc = 0;
	static float angleY_inc = 0;

	static float angle_div = 4;

	static Vec3 oldPoint = point;

	static bool redo = false;

	if (oldPoint != point || redo)
	{
		redo = false;

		oldAngleX = 0;
		angleX_min = 0;
		angleX_inc = 0;
		oldAngleY = 0;
		angleY_min = 0;
		angleY_inc = 0;
		angle_div = 0;

		if (oldPoint == 0)
			angle_div = 1;
		else
		{
			if (oldPoint != point)
			{
				angle_div = vecs::VecDistance(point, oldPoint) / 12;
				if (angle_div < 1)
					angle_div = 1;
				if (angle_div > 10)
					angle_div = 8;
			}
		}

		oldPoint = point;
		Vec3 raisedPoint = point; raisedPoint.z = me.position.posHead.z;
		GetAimAngles(me.position.posChest, raisedPoint, me.yaw, me.pitch, oldAngleX, oldAngleY);

		if (angle_div != 0)
		{
			angleX_min = oldAngleX / angle_div;
			angleY_min = oldAngleY / angle_div;
		}
		else
		{
			angleX_min = oldAngleX;
			angleY_min = oldAngleY;
		}
	}

	//look and walk
	if (!me.bot.isBotShooting)
	{
		//lookign slightly below horizon
		me.bot.pathTurnAngleY = me.editPitch - me.pitch + 15;

		if (abs(angleX_inc) < abs(oldAngleX))
		{
			if (abs(abs(oldAngleX) - abs(angleX_inc)) > 0.01)
			{
				me.bot.pathTurnAngleX = me.editYaw + angleX_min;
				//me.bot.pathTurnAngleY = me.editPitch + angleY_min;
				me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_TO_TARGET_AIM;
			}

			angleX_inc += angleX_min;
			angleY_inc += angleY_min;
		}
		else
		{
			redo = true;
		}
	}
	else
	{
		//shoot and walk
		float horAngle = 0; float vertAngle = 0;
		GetAimAngles(me.position.posChest, point, me.yaw, me.pitch, horAngle, vertAngle);

		if (abs(horAngle) < 45)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_FORWARD;
		if (horAngle > 20 && horAngle < 165)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_LEFT;
		if (horAngle < -20 && horAngle > -165)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_RIGHT;
		if (abs(horAngle) > 135)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_BACK;
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_TO_TARGET_WASD;
	}

	if (PointReachCondition(point, currentNode))
	{
		redo = true;
		return true;
	}
	else
	{
		if (!me.bot.isBotShooting)
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_FORWARD;
	}

	return false;
}
bool MainEvents::IsNextElevatorTriggerOff()
{
	// if next elevator trigger is in render and off stop this path
	if (me.surface == 1022 && !me.bot.currentTriggersInPath.empty())
	{
		for (auto& firstEl : me.bot.currentTriggersInPath)
		{
			Trigger* t = world->find_trigger(firstEl.second);
			if (t)
			{
				if (!(t->elevatorStates & ElevatorStates::ACTIVE) && !(t->elevatorStates & ElevatorStates::OUTOFRENDER))
				{
					return true;
				}
			}
			break;
		}
	}
	return false;
}
void MainEvents::RemovePassedElevatorTriggers()
{
	// if passed the trigger remove it
	if (!me.bot.currentTriggersInPath.empty())
	{
		std::unordered_set<int> idsToDelete;
		for (auto& tp : me.bot.currentTriggersInPath)
		{
			if (tp.first < me.bot.currentStep)
			{
				Trigger* t = world->find_trigger(tp.second);
				idsToDelete.insert(tp.first);
			}
		}
		for (auto& id : idsToDelete)
		{
			auto it = me.bot.currentTriggersInPath.find(id);
			if (it != me.bot.currentTriggersInPath.end())
			{
				me.bot.currentTriggersInPath.erase(it);
			}
		}
	}
}
bool MainEvents::IsNextPointReachedTimeout(GraphNode* currentNode)
{
	static GraphNode* oldNode = currentNode;

	if (me.surface < 1022 && world->check_if_ent_is_opening(me.surface))
		return false;

	if (currentNode != oldNode)
	{
		oldNode = currentNode;
		nextNodeReachTimer.Stop();
	}

	if (me.bot.currentStep < navigationPath.size())
	{
		GraphNode* nextNode = world->node_validity_check(navigationPath[me.bot.currentStep]);
		if (!nextNode)
		{
			oldNode = nullptr;
			return true;
		}
		float distance = vecs::VecDistance(currentNode->vertex, nextNode->vertex);
		float timeToReach = (distance / me.maxSpeed) * 1000;
		float timeElapsed = nextNodeReachTimer.ElapsedContinuous();

		if (timeToReach < 600)
			timeToReach = 600;

		if (timeElapsed > timeToReach * 2.5)
		{
			oldNode = nullptr;
			return true;
		}
	}
	return false;
}
bool MainEvents::SkipPath(const Vec3& currentPoint)
{
	int startCount = me.bot.currentStep;

	for (int i = startCount + 1; i < navigationPathPoints.size(); i++)
	{
		if (currentPoint == navigationPathPoints[i])
		{
			me.bot.currentStep = i;
		}
		else
			break;
	}

	return startCount != me.bot.currentStep;
}
void MainEvents::FlattenPath(std::vector<Vec3>& navPathPoints)
{
	if (navPathPoints.empty())
		return;

	int lastEditedStep = -1;
	for (int i = 0; i < navPathPoints.size() - 1; i++)
	{
		GraphNode* node = world->node_validity_check(navigationPath[i + 1]);

		if (vecs::VecDistance2(navPathPoints[i], navPathPoints[i + 1]) == 0 && !(node->flags & GraphFlags::IS_ELEVATOR))
		{
			navPathPoints[i + 1].z = navPathPoints[i].z;
			lastEditedStep = i + 1;
		}
	}

	if (lastEditedStep != -1 && lastEditedStep < navPathPoints.size() + 1)
	{
		navPathPoints[lastEditedStep + 1].z = navPathPoints[lastEditedStep].z;
	}
}
void MainEvents::GetNavigationPathPoints()
{
	//get node points on update
	if (!(pathfindingFlags & PathfindingFlags::IS_UPDATED))
		return;

	navigationPathPoints.clear();
	for (auto& n : navigationPath)
	{
		GraphNode* node = world->node_validity_check(n);
		navigationPathPoints.push_back(node->vertex);
	}
	FlattenPath(navigationPathPoints);

}
void MainEvents::ChangePointHeight(Vec3& currentPoint, const GraphNode* currentNode)
{
	if (abs(me.position.posFeet.z - currentPoint.z) < 48)
		currentPoint.z = me.position.posFeet.z;

	//bridge cells are same as my height
	Cell* currentCell = world->get_cell(world->unpack_cell_and_chunk(currentNode->cells[0]));
	if (currentCell && (currentCell->flags & CellFlags::IS_ELEVATOR_BRIDGE))
		currentPoint.z = me.position.posFeet.z;
}
bool MainEvents::DontWalkOnElevator(const GraphNode* currentNode)
{
	return ((currentNode->flags & GraphFlags::IS_ELEVATOR) && abs(currentNode->vertex.z - me.position.posFeet.z) > 50);
}
void MainEvents::FollowCurrentPath()
{
	if (!(pathfindingFlags & PathfindingFlags::IS_GENERATED))
	{
		return;
	}

	me.bot.reachNextNodeDistance = 20.0f;

	GetNavigationPathPoints();

	//reached target
	if (me.bot.currentStep == navigationPath.size())
	{
		DeleteCurrentDestination();
		return;
	}

	GraphNode* currentNode = world->node_validity_check(navigationPath[me.bot.currentStep]);
	if (currentNode == nullptr)
	{
		DeleteCurrentDestination();
		return;
	}

	GraphNode* finalNode = world->node_validity_check(navigationPath[navigationPath.size() - 1]);
	if (finalNode == nullptr)
	{
		DeleteCurrentDestination();
		return;
	}
	else
		me.bot.targetDistanceCrowFlight = vecs::VecDistance2(me.position.posFeet, finalNode->vertex);

	static GraphNode* previousNode = currentNode;
	//static Vec3 pointRaised = currentNode->vertex;

	if (IsPathTooFarAway(navigationPathPoints[me.bot.currentStep]))
	{
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
		return;
	}


	if (!me.bot.currentTriggersInPath.empty())
	{
		auto it = me.bot.currentTriggersInPath.begin();
		Trigger* t = world->find_trigger(it->second);
		if (t && (t->elevatorStates & ElevatorStates::READY_FOR_REACTIVATION))
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			return;
		}
	}


	if (IsNextElevatorTriggerOff())
	{
		return;
	}

	if (me.surface < 1022)
	{
		for (auto& t : me.bot.currentTriggersInPath)
		{
			Trigger* trig = world->find_trigger(t.second);
			if (trig->entityNum == me.surface && world->check_if_ent_is_opening(me.surface))
				return;
		}
	}
	

	if (previousNode != currentNode)
	{
		//check next node for safey
		if (!world->is_next_node_safe(currentNode))
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			return;
		}

		RemovePassedElevatorTriggers();

		if (SkipPath(navigationPathPoints[me.bot.currentStep]))
			return;

		previousNode = currentNode;
	}

	//don't walk while on elevator
	if (DontWalkOnElevator(currentNode))
		return;
	
	ChangePointHeight(navigationPathPoints[me.bot.currentStep], currentNode);

	if (me.bot.currentStep == navigationPath.size() - 1 
		&& me.bot.selectedDestination != TargetCells::EXPLOSION_TARGET_CELL		
		&& me.bot.selectedDestination != TargetCells::ANTI_SABER_TARGET_CELL	
		) 
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_SHIFT;

	if (IsNextPointReachedTimeout(currentNode))
	{
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
		return;
	}

	if (GoToPoint(navigationPathPoints[me.bot.currentStep], currentNode))
		me.bot.currentStep++;
}

bool MainEvents::CompareChunkByDistance(const uint32_t& _ch1, const uint32_t& _ch2)
{
	Chunk* ch1 = world->get_chunk(_ch1);
	Chunk* ch2 = world->get_chunk(_ch2);
	return false;

}
bool MainEvents::SortChunksForRoam(Cell* spawnCell)
{
	std::vector<uint32_t> sortedChunks;

	int spawnIslandNumber = spawnCell->graphNode->islandNum;

	if (!world->islands.count(spawnIslandNumber))
		return false;

	Chunk* startChunk = world->get_chunk(me.bot.spawnCellCoordiantes.chunkLocation);

	for (uint32_t ch : world->islands[spawnIslandNumber].islandChunks)
	{
		Chunk* chunk = world->get_chunk(ch);
		float distance = vecs::VecDistance(chunk->locationFloat, startChunk->locationFloat);

		world->sortedChunkPairs.emplace_back(ch, distance);
	}

	std::sort(world->sortedChunkPairs.begin(), world->sortedChunkPairs.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
		return a.second > b.second;
		});
}
bool MainEvents::GetSpawnChunk()
{
	if (!(me.playerFlags & PlayerFlags::IS_ALIVE))
	{
		me.bot.spawnCellCoordiantes = 0;
		return false;
	}
	//get spawn chunk and sort chunks accodring to distance from me
	if (me.bot.spawnCellCoordiantes == 0 && me.surface != 1023)
	{
		me.bot.spawnCellCoordiantes = me.bot.myCellCoordinates;
		Cell* spawnCell = world->get_cell(me.bot.spawnCellCoordiantes);
		if (!spawnCell || !spawnCell->graphNode)
			return false;

		SortChunksForRoam(spawnCell);
	}

	if (me.bot.spawnCellCoordiantes == 0)
		return false;

	return true;
}
void MainEvents::Roam()
{
	if (!world || !(botConfigFlags & BotConfigFlags::BOT_ROAM) || me.bot.tgtCells[TargetCells::PLAYER_TARGET_CELL] != 0 || me.bot.tgtCells[TargetCells::ROAM_TARGET_CELL] != 0)
		return;
	if (me.isInstantDeathFlag)
	{
		for (auto& ch : world->validChunks)
		{
			world->get_chunk(ch)->flags &= ~ChunkFlags::IS_VISITED_BY_BOT;
		}
		world->sortedChunkPairs.clear();
	}
	if (!GetSpawnChunk())
		return;
	if (world->sortedChunkPairs.empty())
	{
		for (auto& ch : world->validChunks)
		{
			world->get_chunk(ch)->flags &= ~ChunkFlags::IS_VISITED_BY_BOT;
		}
		me.bot.spawnCellCoordiantes = 0;
		return;
	}

	Chunk* myChunk = world->get_chunk(me.bot.myCellCoordinates.chunkLocation);

	if (myChunk == nullptr)
		return;

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	if (!myCell || !myCell->graphNode)
		return;
	Cell* spawnCell = world->get_cell(me.bot.spawnCellCoordiantes);
	if (!spawnCell || !spawnCell->graphNode)
	{
		me.bot.spawnCellCoordiantes = 0;
		return;
	}

	if (myCell->graphNode->islandNum != spawnCell->graphNode->islandNum)
	{
		me.bot.spawnCellCoordiantes = 0;
	}


	//mark visited chunks and erase from sorted
	if (!(myChunk->flags & ChunkFlags::IS_VISITED_BY_BOT))
	{
		myChunk->flags |= ChunkFlags::IS_VISITED_BY_BOT;

		for (auto it = world->sortedChunkPairs.begin(); it != world->sortedChunkPairs.end(); ++it)
		{
			if (it->first == me.bot.myCellCoordinates.chunkLocation)
			{
				world->sortedChunkPairs.erase(it);
				break;
			}
		}
	}

	if (world->sortedChunkPairs.empty())
	{
		me.bot.tgtCells[TargetCells::ROAM_TARGET_CELL] = 0;
		return;
	}

	if (me.bot.tgtCells[TargetCells::ROAM_TARGET_CELL] != 0 && (generatedPathLastError == PathfindingErrors::UNREACHABLE))
	{
		me.bot.tgtCells[TargetCells::ROAM_TARGET_CELL] = 0;
		return;
	}

	int indexChunkMaxRandom = world->sortedChunkPairs.size() / 4;
	int randomFarChunk = Utils::GenerateRandomInt(0, indexChunkMaxRandom);

	Chunk* selectedChunk = world->get_chunk(world->sortedChunkPairs[randomFarChunk].first);
	selectedChunk->flags |= ChunkFlags::IS_VISITED_BY_BOT;


	std::vector<GraphNode*> nodesOnTheSameIslandAsMe;
	for (auto& n : selectedChunk->nodes)
	{
		if (spawnCell->graphNode->islandNum == n.second->islandNum)
		{
			nodesOnTheSameIslandAsMe.push_back(n.second);
		}
	}

	if (nodesOnTheSameIslandAsMe.empty())
		return;

	int indexofMaxNode = nodesOnTheSameIslandAsMe.size() - 1;
	int randomNodeInChunk = Utils::GenerateRandomInt(0, indexofMaxNode);

	me.bot.tgtCells[TargetCells::ROAM_TARGET_CELL] = world->unpack_cell_and_chunk(nodesOnTheSameIslandAsMe[randomNodeInChunk]->cells[0]);

	for (auto it = world->sortedChunkPairs.begin(); it != world->sortedChunkPairs.end(); ++it)
	{
		if (it->first == world->sortedChunkPairs[randomFarChunk].first)
		{
			world->sortedChunkPairs.erase(it);
			break;
		}
	}

}

void MainEvents::BotMovement()
{
	if (restartPathfinderTimer.ElapsedContinuous() > REFRESH_PATH_TIME)
	{
		pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
		restartPathfinderTimer.Stop();
	}
}

Vec3 MainEvents::GetOffsetPoint(const Vec3& position, bool keyW, bool keyS, bool keyA, bool keyD) 
{
	Vec3 direction(0.0f, 0.0f, 0.0f);

	if (keyW && !keyS)
		direction.y += 1.0f;
	if (keyS && !keyW)
		direction.y -= 1.0f;
	if (keyD && !keyA)
		direction.x += 1.0f;
	if (keyA && !keyD)
		direction.x -= 1.0f;

	if (direction.x == 0.0f && direction.y == 0.0f)
		return position;

	if (direction != 0)
		direction = vecs::NormalizeVector(direction);

	float yaw = (me.yaw - 90) * DEGREE_TO_RAD;

	// Rotate inputDir by yaw around Y axis
	float sinYaw = std::sin(yaw);
	float cosYaw = std::cos(yaw);

	Vec3 rotatedDir;
	rotatedDir.x = direction.x * cosYaw - direction.y * sinYaw;
	rotatedDir.y = direction.x * sinYaw + direction.y * cosYaw;
	rotatedDir.z = 0.0f;

	return position + rotatedDir * 6.0f;
}
void MainEvents::AutoJumpCrouch()
{
	if (!world)
		return;

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	if (!myCell || !myCell->graphNode)
		return;

	//int entityNum = 1023;
	GLfloat col[4]{ 1,1,1,1 };
	static Utils::Tracer::trace_t tBottom, tTop, tLeft, tRight;
	float side = me.playerModel.defaultModelWidth/2;
	int stepheight = 14; int jumpheight = 28;

	//BOTTOM VISOR

	Vec3 bottom = GetOffsetPoint(me.position.posFeet,
		me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_FORWARD,
		me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_BACK,
		me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_LEFT,
		me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_RIGHT
		);

	//bottom = me.position.posFeet; 
	bottom.z += stepheight;

	Vec3 top = bottom; top.z += jumpheight; //auto jump height
	Vec3 min{ -side, -side, 0 }; Vec3 max{ side, side, 0 };

	if (isServerTicked)
	{
		tracer.traceLine(&tBottom, top, min, max, bottom, me.id, 0x1011, 0);
	}

	if (tBottom.entityNum != 1023)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_OBSTACLE_BOTTOM;
		col[3] = 0.2;
	}

	

	if (botConfigFlags & BotConfigFlags::DRAW_BOT_BBOXES)
		draw->DrawRotatedBBox(bottom, top, min, max, me.yaw, 1, col);

	//TOP VISOR
	col[3] = 1;
	Vec3 highBot, highTop; highBot = top; highTop = highBot; highTop.z += me.playerModel.modelHeight / 1.8;

	if (isServerTicked)
		tracer.traceLine(&tTop, highTop, min, max, highBot, me.id, 0x1011, 0);

	if (tTop.entityNum != 1023)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_OBSTACLE_TOP;
		col[3] = 0.2;
	}

	if (botConfigFlags & BotConfigFlags::DRAW_BOT_BBOXES)
		draw->DrawRotatedBBox(highBot, highTop, min, max, me.yaw, 1, col);

	col[3] = 1;

	//left VISOR
	Vec3 leftDetectorStart; leftDetectorStart.x = 8; leftDetectorStart.y = 14; leftDetectorStart.z = me.playerModel.defaultModelHeight - 4;
	Vec3 leftDetectorEnd = leftDetectorStart; leftDetectorEnd.x += 8;
	Vec3 minLeft, maxleft; minLeft = { -2, -2, -(me.playerModel.defaultModelHeight - 18) }; maxleft = { 2, 2, 2 };

	float cosAlpha = cos((me.yaw) * DEGREE_TO_RAD);
	float sinAlpha = sin((me.yaw) * DEGREE_TO_RAD);


	Vec3 resLeft;
	resLeft.x = leftDetectorStart.x * cosAlpha - leftDetectorStart.y * sinAlpha; resLeft.z = leftDetectorStart.z;
	resLeft.y = leftDetectorStart.x * sinAlpha + leftDetectorStart.y * cosAlpha;
	resLeft = resLeft + me.position.posFeet;


	Vec3 resLeftEnd;
	resLeftEnd.x = leftDetectorEnd.x * cosAlpha - leftDetectorEnd.y * sinAlpha; resLeftEnd.z = leftDetectorStart.z;
	resLeftEnd.y = leftDetectorEnd.x * sinAlpha + leftDetectorEnd.y * cosAlpha;
	resLeftEnd = resLeftEnd + me.position.posFeet;

	if (isServerTicked)
		tracer.traceLine(&tLeft, resLeft, minLeft, maxleft, resLeftEnd, me.id, 0x1111, 0);

	if (tLeft.entityNum != 1023)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_OBSTACLE_LEFT;
		col[3] = 0.2;
	}

	if (botConfigFlags & BotConfigFlags::DRAW_BOT_BBOXES)
		draw->DrawRotatedBBox(resLeft, resLeftEnd, minLeft, maxleft, me.yaw, 1, col);

	col[3] = 1;

	//RIGHT VISOR
	leftDetectorStart; leftDetectorStart.x = 8; leftDetectorStart.y = -14; leftDetectorStart.z = me.playerModel.defaultModelHeight - 4;
	leftDetectorEnd = leftDetectorStart; leftDetectorEnd.x += 8;
	minLeft, maxleft; minLeft = { -2, -2, -(me.playerModel.defaultModelHeight - 18) }; maxleft = { 2, 2, 2 };

	cosAlpha = cos((me.yaw) * PI / 180);
	sinAlpha = sin((me.yaw) * PI / 180);


	resLeft;
	resLeft.x = leftDetectorStart.x * cosAlpha - leftDetectorStart.y * sinAlpha; resLeft.z = leftDetectorStart.z;
	resLeft.y = leftDetectorStart.x * sinAlpha + leftDetectorStart.y * cosAlpha;
	resLeft = resLeft + me.position.posFeet;


	resLeftEnd;
	resLeftEnd.x = leftDetectorEnd.x * cosAlpha - leftDetectorEnd.y * sinAlpha; resLeftEnd.z = leftDetectorStart.z;
	resLeftEnd.y = leftDetectorEnd.x * sinAlpha + leftDetectorEnd.y * cosAlpha;
	resLeftEnd = resLeftEnd + me.position.posFeet;

	if (isServerTicked)
		tracer.traceLine(&tRight, resLeft, minLeft, maxleft, resLeftEnd, me.id, 0x1111, 0);


	if (tRight.entityNum != 1023)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_OBSTACLE_RIGHT;
		col[3] = 0.2;
	}

	if (botConfigFlags & BotConfigFlags::DRAW_BOT_BBOXES)
		draw->DrawRotatedBBox(resLeft, resLeftEnd, minLeft, maxleft, me.yaw, 1, col);

	//left right 
	if ((me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_LEFT) && !(me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_RIGHT) && isRobot)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_RIGHT;
	}
	else if (!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_LEFT) && (me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_RIGHT) && isRobot)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_LEFT;
	}

	// jump crouch
	if ((me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_TOP) && !(me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_BOTTOM) && isRobot)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_CROUCH;
	}
	else if (!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_TOP) && (me.bot.botStateFlag & BotStateFlags::BOT_STATE_OBSTACLE_BOTTOM) && isRobot)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_JUMP;
	}


	if (myCell && myCell->flags & CellFlags::IS_JUMP)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_JUMP;
	}
	if (myCell && myCell->flags & CellFlags::IS_USE)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_USE;
	}
}
void MainEvents::AntiJediWook()
{
	if (me.bot.botStateFlag |= BotStateFlags::BOT_STATE_GRENADE_DANGER)
		return;

	me.bot.isJediDanger = false;
	me.bot.isJediSaberDanger = false;

	for (auto& p : sortedPlayers)
	{
		if ((p->entClass == EntClass::CL_SITH || p->entClass == EntClass::CL_JEDI)
			&& p->team != me.team
			&& p->distances.distance3 < PUSH_DISTANCE
			&& p->saberAnim == 1
			&& p->stance2 != Stances2::LIGHTNING
			&& p->stance2 != Stances2::LIGHTNING_SABER_OUT
			)
		{
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_SHIFT;
			me.bot.isJediDanger = true;
			break;
		}
	}
	for (auto& p : sortedPlayers)
	{
		if ((p->wpInfo.num == Weapons::WP_LS)
			&& p->team != me.team
			&& p->distances.distance3 < SABER_DANGER_DISTANCE
			&& p->saberAnim != 1
			)
		{
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_BACK;
			me.bot.isJediSaberDanger = true;
			break;
		}
	}
}
void MainEvents::AntiStuck()
{
	if (!world || me.surface == 1023 || !(me.playerFlags & PlayerFlags::IS_ALIVE) || (me.myFlags & MyFlags::IS_NOCLIP))
		return;

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	static bool isStuck = false;
	if (!myCell&& me.bot.myLastValidCellCoordinates != 0)
	{
		float time = me.bot.stuckTimer.ElapsedContinuous();
		if (time > 800)
		{
			isStuck = true;
		}
	}

	if (isStuck && !myCell && me.bot.myLastValidCellCoordinates != 0)
	{
		Cell* cell = world->get_cell(me.bot.myLastValidCellCoordinates);
		if (cell && cell->graphNode)
		{
			me.bot.reachNextNodeDistance = 2.0f;
			Vec3 point = cell->graphNode->vertex; point.z = me.position.posFeet.z;
			GoToPoint(point, cell->graphNode);
		}
	}

	if (myCell)
	{
		me.bot.stuckTimer.Stop();
		isStuck = false;
	}
}
void MainEvents::Strafe()
{
	bool isDodge = false;
	static bool dodgeLock = false;
	static bool leftRight = false;
	static float timeStrafe = 0;

	for (auto& p : sortedPlayers)
	{
		if (p->team != me.team 
			&& (p->playerFlags & PlayerFlags::IS_LOOKING_AT_ME) 
			&& (p->permanentPlayerFlags & PermanentPlayerFlags::IS_VISIBLE))
		{
			isDodge = true;
			break;
		}
	}
	if (!isDodge)
	{
		dodgeLock = false;
		return;
	}

	me.bot.botStateFlag |= BotStateFlags::BOT_STATE_STRAFING;

	if (dodgeLock == false)
	{
		leftRight = Utils::GenerateRandomInt(0, 1);
		timeStrafe = Utils::GenerateRandomFloat(1500, 3000);
		dodgeLock = true;
	}

	if (leftRight)
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_LEFT;
	else
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_RIGHT;

	if (me.bot.strafeTimer.IsElapsedPeriod(timeStrafe))
	{
		dodgeLock = false;
	}
	else
	{
		
	}
}
void MainEvents::GrenadeDodge()
{
	if (!world)
		return;

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	//me.bot.isGrenadeDanger = false;
	if (!myCell || !myCell->graphNode)
		return;

	bool isChooseNewNode = false;
	bool isGrenadeDanger = false;
	//get explosions (fire nade are annoying, that's why)
	for (auto& m : missiles)
	{
		if (explosions.find(m.second.uniqueId) == explosions.end()
			&&
			(((m.second.trajectoryType == TRAJECTORY_TYPE::TR_GRAVITY) && m.second.parentGun != Weapons::WP_DETPACK && m.second.parentGun != Weapons::WP_TRIP)
				|| (m.second.parentGun == Weapons::WP_PLX)
				|| ((m.second.parentGun == Weapons::WP_DETPACK || m.second.parentGun == Weapons::WP_TRIP) && m.second.trajectoryType == TRAJECTORY_TYPE::TR_STATIONARY)
				)
			)
		{
			float grenadeLifetime = m.second.lifeTime * 1000.0f + 500.0f;
			float grenadeRadius = m.second.radius + 200.0f;
			Vec3 grenadeLocationFinal = m.second.destination;

			isChooseNewNode = true;

			if (m.second.parentGun == Weapons::WP_PLX)
			{
				grenadeLifetime = vecs::VecDistance(m.second.startPos, m.second.destination) / WeaponVelocities::WP_PLX_VELOCITY + 400.0f;
				grenadeRadius = m.second.radius;
			}
			else if ((m.second.parentGun == Weapons::WP_DETPACK || m.second.parentGun == Weapons::WP_TRIP))
			{
				grenadeLifetime = m.second.lifeTime * 1000.0f + 500.0f;
				grenadeRadius = m.second.radius + 40.0f;
				grenadeLocationFinal = m.second.startPos;
			}

			ExplosionData expl(grenadeLifetime, grenadeRadius, grenadeLocationFinal, m.second.id, m.second.parentGun);

			Vec3 grenadePositionRaised = grenadeLocationFinal; grenadePositionRaised.z += 24.0;
			Cell* projectedCell = world->get_cell(grenadePositionRaised, 100, me.bot.myCellCoordinates);
			if (!projectedCell)
				continue;

			std::vector<Chunk*> neighborChunks;
			projectedCell->parentChunk->get_all_neighbors(neighborChunks); neighborChunks.push_back(projectedCell->parentChunk);

			int count = 0;
			for (auto& nCh: neighborChunks)
			{
				for (auto& node : nCh->nodes)
				{
					GraphNode* n = node.second;
					Utils::Tracer::trace_t traceResult;
					float distanceVertexNade = vecs::VecDistance(expl.location, n->vertex);
					count++;
					if (distanceVertexNade < expl.radius)
					{
						if (n->cells.empty())
							continue;
						Vec3 start = grenadeLocationFinal; start.z += 30.0f;
						bool isTracedNodeSafe = true;

						if (n->size > 1)
						{
							for (auto& c : n->cells)
							{
								Cell* cell = world->get_cell(world->unpack_cell_and_chunk(c));
								Vec3 end = cell->GetCenter(); end.z += 80.0f;
								tracer.traceLine(&traceResult, start, 0, 0, end, 0, 0x1011, 0);
								if (traceResult.entityNum == 1023 || traceResult.entityNum < 1022)
								{
									isTracedNodeSafe = false;
									break;
								}
							}
						}
						else
							isTracedNodeSafe = false;


						if (isTracedNodeSafe)
							continue;

						expl.dangerCells.push_back(n->cells[0]);
						n->flags |= GraphFlags::IS_AFFECTED_BY_EXPLOSION;
					}
				}
			}
			
			explosions.insert({ m.second.uniqueId, expl });
		}
	}

	//prepare explosions for deletion 
	std::vector<int> explosionsToDeleteIds;

	for (auto& x : explosions)
	{
		if (x.second.weaponType == Weapons::WP_TRIP || x.second.weaponType == Weapons::WP_DETPACK)
		{
			auto it = missiles.find(x.second.realId);
			if ((it == missiles.end()))
			{
				explosionsToDeleteIds.push_back(x.first);
				continue;
			}
		}
		if (x.second.TimeLeft())
		{
			explosionsToDeleteIds.push_back(x.first);
		}
	}

	//delete explosions
	bool isDeletion = false;
	for (auto& expl : explosionsToDeleteIds)
	{
		isDeletion = true;

		for (auto& c : explosions.at(expl).dangerCells)
		{
			Cell* affectedCell = world->get_cell(world->unpack_cell_and_chunk(c));
			if (!affectedCell || !affectedCell->graphNode)
				continue;
			else
			{
				affectedCell->graphNode->flags &= ~GraphFlags::IS_AFFECTED_BY_EXPLOSION;
			}
		}

		explosions.erase(expl);
	}

	//redo cells
	if (isDeletion)
	{
		//readd explosion areas after deletion
		for (auto& x : explosions)
		{
			for (auto& c : x.second.dangerCells)
			{
				Cell* affectedCell = world->get_cell(world->unpack_cell_and_chunk(c));
				if (!affectedCell || !affectedCell->graphNode)
					continue;
				affectedCell->graphNode->flags |= GraphFlags::IS_AFFECTED_BY_EXPLOSION;
			}
		}
	}

	//choose a safe node
	if ((myCell->graphNode->flags & GraphFlags::IS_AFFECTED_BY_EXPLOSION))
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_GRENADE_DANGER;
		std::vector<GraphNode*> safeNodes;
		//me.bot.isGrenadeDanger = true;

		if (!isChooseNewNode)
			return;
		for (auto& x : explosions)
		{
			for (auto& c : x.second.dangerCells)
			{
				Cell* dangerCell = world->get_cell(world->unpack_cell_and_chunk(c));
				if (!dangerCell || !dangerCell->graphNode)
				{
					continue;
				}
				for (auto& neighbor : dangerCell->graphNode->neighbors)
				{
					if (!(neighbor.second->flags & GraphFlags::IS_AFFECTED_BY_EXPLOSION))
					{
						safeNodes.push_back(neighbor.second);
					}
				}
			}
		}

		float closestDistance = 9999;
		for (auto& safeNode : safeNodes)
		{
			float distanceMeNode = vecs::VecDistance(safeNode->vertex, me.position.posFeet);
			if (closestDistance > distanceMeNode
				&& myCell->graphNode->islandNum == safeNode->islandNum
				&& !safeNode->neighbors.empty()
				)
			{
				closestDistance = distanceMeNode;
				me.bot.tgtCells[TargetCells::EXPLOSION_TARGET_CELL] = world->unpack_cell_and_chunk(safeNode->cells[0]);
			}
		}
	}
	else
	{
		me.bot.tgtCells[TargetCells::EXPLOSION_TARGET_CELL] = 0;
	}
}
void MainEvents::SaberEvade()
{
	if (!world)
		return;

	Cell* myCell = world->get_cell(me.bot.myCellCoordinates);
	//me.bot.isGrenadeDanger = false;

	//get dangerous cells
	std::vector<GraphNode*> saberNodes;
	for (auto& p : sortedPlayers)
	{
		for (auto& c : p->botInfo.cellsAroundSaber)
		{
			Cell* cell = world->get_cell(world->unpack_cell_and_chunk(c));
			if (!cell || !cell->graphNode)
				continue;
			if (cell->graphNode->flags & GraphFlags::IS_NEAR_SABER)
			{
				cell->graphNode->weight -= 1000;
				cell->graphNode->flags &= ~GraphFlags::IS_NEAR_SABER;
			}
		}

		if (!((p->wpInfo.num == Weapons::WP_LS || p->entClass == EntClass::CL_WOOK) && p->team != me.team && (p->distances.distance3 < me.bot.saberDistanceKeep)))
			continue;

		p->botInfo.cellsAroundSaber.clear();

		CellCoordinates exactPlayerCellCoordinates;
		world->get_cell(p->position.posChest, 100, exactPlayerCellCoordinates);
		Chunk* playerChunk = world->get_chunk(exactPlayerCellCoordinates.chunkLocation);
		if (!playerChunk)
			continue;

		std::vector<Chunk*> neighborChunks;
		playerChunk->get_all_neighbors(neighborChunks); neighborChunks.push_back(playerChunk);

		if (p->wpInfo.num == Weapons::WP_LS && p->entClass != EntClass::CL_WOOK)
		{
			for (auto& nCh : neighborChunks)
			{
				for (auto& node : nCh->nodes)
				{
					GraphNode* g = node.second;
					float distance = vecs::VecDistance(p->position.posChest, g->vertex);
					float degree = vecs::AngleBetweenVec(p->uvec, g->vertex - p->position.posChest);

					if (distance < me.bot.saberDistanceKeep && !(g->cells.empty()) && degree < 90)
					{
						p->botInfo.cellsAroundSaber.push_back(g->cells[0]);
						g->flags |= GraphFlags::IS_NEAR_SABER;
						g->weight += 1000;
						saberNodes.push_back(g);
					}
				}
			}
		}
		else if (p->entClass == EntClass::CL_WOOK)
		{
			for (auto& nCh : neighborChunks)
			{
				for (auto& node : nCh->nodes)
				{
					GraphNode* g = node.second;
					float distance = vecs::VecDistance(p->position.posChest, g->vertex);

					if (distance < me.bot.saberDistanceKeep && !(g->cells.empty()))
					{
						p->botInfo.cellsAroundSaber.push_back(g->cells[0]);
						g->flags |= GraphFlags::IS_NEAR_SABER;
						g->weight += 1000;
						saberNodes.push_back(g);
					}
				}
			}
		}
	}

	if (!myCell || !myCell->graphNode)
		return;

	if ((myCell->graphNode->flags & GraphFlags::IS_NEAR_SABER))
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_NEAR_SABER;
		std::vector<GraphNode*> safeNodes;

		for (auto& sn : saberNodes)
		{
			for (auto& neighbor : sn->neighbors)
			{
				if (!(neighbor.second->flags & GraphFlags::IS_NEAR_SABER))
				{
					safeNodes.push_back(neighbor.second);
				}
			}
		}

		float closestDistance = 9999;
		for (auto& safeNode : safeNodes)
		{
			float distanceMeNode = vecs::VecDistance(safeNode->vertex, me.position.posFeet);
			if (closestDistance > distanceMeNode
				&& myCell->graphNode->islandNum == safeNode->islandNum
				&& !safeNode->neighbors.empty()
				)
			{
				closestDistance = distanceMeNode;
				me.bot.tgtCells[TargetCells::ANTI_SABER_TARGET_CELL] = world->unpack_cell_and_chunk(safeNode->cells[0]);
			}
		}
	}
	else
	{
		me.bot.tgtCells[TargetCells::ANTI_SABER_TARGET_CELL] = 0;
	}

}
void MainEvents::RetryRouteIfStandingStill()
{
	if (me.speedMag == 0 && me.bot.selectedDestination != TargetCells::NONE)
	{
		float time = me.bot.standingStillTimer.ElapsedContinuous();
		if (time > 2000)
		{
			pathfindingFlags &= ~PathfindingFlags::IS_GENERATED;
			me.bot.standingStillTimer.Stop();
		}
	}
}
void MainEvents::AuthorizeBotRequestActions()
{
	if (!(me.playerFlags & PlayerFlags::IS_ALIVE))
		return;

	//hold use if next to elevator button
	if (me.bot.selectedDestination == TargetCells::ELEVATOR_BUTTON_TARGET_CELL && me.bot.targetDistanceCrowFlight < 30)
	{
		me.bot.botStateFlag |= BotStateFlags::BOT_STATE_USE;
	}

	//if i am shooting and not in grenade danger no aimwalking
	if ((me.bot.botStateFlag & BotStateFlags::BOT_STATE_SHOOT)
		&& !(me.bot.botStateFlag & BotStateFlags::BOT_STATE_GRENADE_DANGER)
		)
	{
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_TO_TARGET_AIM;

		if (me.bot.enemyTarget->distances.distance3 < me.bot.distanceRetreat && me.bot.enemyTarget->distances.distance3 != 0)
		{
			me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
			me.bot.botStateFlag |= BotStateFlags::BOT_STATE_WALKING_BACK;
		}
	}

	//if aimwalking no attack
	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_TO_TARGET_AIM)
	{
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ATTACK;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ALTATTACK;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_SHOOT;
	}

	if ((me.bot.botStateFlag & BotStateFlags::BOT_STATE_ROLLING_FIRE) && !me.bot.isJediSaberDanger)
	{
		//me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_LEFT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_RIGHT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_BACK;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ATTACK;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_ALTATTACK;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_STUCK;
	}

	//stop if weapon is proj
	if (!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_STRAFING)
		&& !(me.bot.botStateFlag & BotStateFlags::BOT_STATE_GRENADE_DANGER)
		&& me.wpInfo.num == Weapons::WP_PROJ 
		&& me.bot.enemyTarget
		&& !me.bot.isJediSaberDanger)
	{
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_LEFT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_RIGHT;
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_BACK;
	}

	//if strafing no W
	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_STRAFING)
	{
		me.bot.botStateFlag &= ~BotStateFlags::BOT_STATE_WALKING_FORWARD;
	}

	AutoJumpCrouch();

	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_RIGHT)
		act.Do(DoAction::RIGHT);
	else if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_LEFT)
		act.Do(DoAction::LEFT);

	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_FORWARD)
		act.Do(DoAction::FORWARD);
	else if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_BACK)
		act.Do(DoAction::BACK);

	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_JUMP)
		act.Do(DoAction::JUMP);
	else if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_CROUCH)
		act.Do(DoAction::CROUCH);

	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_ATTACK)
		act.Do(DoAction::ATTACK);
	else if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_ALTATTACK)
		act.Do(DoAction::ALT_ATTACK);


	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_RELOAD)
		act.Do(DoAction::RELOAD);
	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_SHIFT)
		act.Do(DoAction::SHIFT);
	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_DODGE)
		act.Do(DoAction::DODGE);
	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_USE)
		act.Do(DoAction::USE);

	if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_TURN_LEFT)
		act.Do(DoAction::TURN_LEFT);
	else if (me.bot.botStateFlag & BotStateFlags::BOT_STATE_TURN_RIGHT)
		act.Do(DoAction::TURN_RIGHT);

	if (me.bot.enemyTarget != nullptr
		&& (me.bot.botStateFlag & BotStateFlags::BOT_STATE_SHOOT)
		&& (!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_STUCK))
		//&& (!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_STRAFING))
		)
		AimLockThisTarget(me.bot.enemyTarget->angles.me_to_this_target.x, me.bot.enemyTarget->angles.me_to_this_target.y);


	if ((me.bot.botStateFlag & BotStateFlags::BOT_STATE_WALKING_TO_TARGET_AIM)
		&&
		!(me.bot.botStateFlag & BotStateFlags::BOT_STATE_STUCK))
	{
		*(float*)add->myRawYaw = me.bot.pathTurnAngleX;
		*(float*)add->myRawPitch = me.bot.pathTurnAngleY;
	}
}
void MainEvents::BotLoop()
{
	if (isGameUnminimised)
	{
		act.DeInit();
	}

	GetTargetCell();
	GetPlayerCells();
	GetLookingAtCells();
	GenerateWorld();
	TriggerStuff();
	RetryRouteIfStandingStill();
	//GenerateMinionPath();

	if (!isRobot 
		|| !(botConfigFlags & BotConfigFlags::ENABLE_BOT) 
		|| testQuit
		)
		return;

	act.DeInit();

	//AddWeightToPlayerNode();
	DoorProbe();
	FillMoverEnts();
	CheckMoversForChange();
	Elections();
	Roam();
	GrenadeDodge();
	GeneratePath();

	SelectWeapon();
	AntiJediWook();
	FollowCurrentPath();
	Strafe();
	BotAttack();

	AntiStuck();
	RollIfOnFire();
	SaberEvade();

	//test
	AuthorizeBotRequestActions();
}

//bptstuff--------------------------------------------------------------------------------------------------------------

//draw
void MainEvents::DrawDamage(Player& player)
{
	if (player.isDrawDamage)
	{
		player.hpTimer.Start();
	}

	double elTime = player.hpTimer.ElapsedCurrentMs();
	if (elTime > player.showDamaeMs)
	{
		player.hpTimer.Stop();
		return;
	}

	GLfloat col[4];
	if (abs(player.damage) < 11)
		memcpy(col, RGB::green, sizeof(col));
	else if (abs(player.damage) > 11 && abs(player.damage) < 21)
		memcpy(col, RGB::yellow, sizeof(col));
	else if (abs(player.damage) > 21)
		memcpy(col, RGB::red, sizeof(col));

	if (elTime < player.showDamaeMs && elTime > 1)
	{
		draw->bold28->Print(player.screenInfo.posSymbol.x, player.screenInfo.posSymbol.y - elTime/10, col, std::to_string(player.damage));
	}
}
void MainEvents::DrawPlayerInfo()
{
	drawPlayerInfoTimer.Start();
	//get my screen pos
	draw->WTS(me.position.posGun, me.screenInfo.screenSpacePos);

	bool isDrawAllyLines = wallhackFlags & WALLHACK_FLAGS::DRAW_LINES_TO_ALLIES;
	bool isDrawEnemyLines = wallhackFlags & WALLHACK_FLAGS::DRAW_LINES_TO_ENEMIES;
	bool isDrawAllyBoxes = wallhackFlags & WALLHACK_FLAGS::DRAW_ALLY_BOXES;
	bool isDrawEnemyBoxes = wallhackFlags & WALLHACK_FLAGS::DRAW_ENEMY_BOXES;

	for (auto& p : players)
	{
		if (!(p.playerFlags & PlayerFlags::IS_VALID))
			continue;

		if (p.playerFlags & PlayerFlags::IS_LOOKING_AT_ME)
			p.screenInfo.lineWidth = 4;
		if (p.playerFlags & PlayerFlags::IS_TELECOMMUNICATED)
			memcpy(p.screenInfo.screenColor, RGB::blue, sizeof(RGB::blue));
		if (p.permanentPlayerFlags & PermanentPlayerFlags::IS_LEADER)
			memcpy(p.screenInfo.screenColor, RGB::white, sizeof(RGB::white));

		Vec3 testPos = p.position.posHead; testPos.z += 20;
		draw->WTS(testPos, p.screenInfo.posSymbol);
		draw->WTSrotated(p.position.posAim, p.screenInfo.screenSpacePos, me.screenInfo.screenSpacePos);
		draw->WTSrotated(p.predictedPosition.posAim, p.screenInfo.predictedScreenSpacePos, me.screenInfo.screenSpacePos);

		if (isDrawAllyLines && me.team == p.team)
			draw->DrawLine(me.screenInfo.screenSpacePos, p.screenInfo.screenSpacePos, p.screenInfo.lineWidth, p.screenInfo.screenColor);
		else if (isDrawEnemyLines && me.team != p.team)
			draw->DrawLine(me.screenInfo.screenSpacePos, p.screenInfo.screenSpacePos, p.screenInfo.lineWidth, p.screenInfo.screenColor);
		
		if (isDrawAllyBoxes && me.team == p.team)
			draw->DrawRotatedBBox(p.playerModel.bottom, p.playerModel.top, p.playerModel.min, p.playerModel.max, p.yaw, p.screenInfo.lineWidth, p.screenInfo.screenColor);
		else if (isDrawEnemyBoxes && me.team != p.team)
			draw->DrawRotatedBBox(p.playerModel.bottom, p.playerModel.top, p.playerModel.min, p.playerModel.max, p.yaw, p.screenInfo.lineWidth, p.screenInfo.screenColor);

		DrawDamage(p);
		

#ifdef SHOW_TARGET_FLAGS
		if ((p.targetFlags & TargetFlags::IS_DANGER_JEDI_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "JEDI DANGER");
		else if ((p.targetFlags & TargetFlags::IS_DANGER_WOOK_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "WOOK DANGER");
		else if ((p.targetFlags & TargetFlags::IS_DEFLECTING_AT_ME_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "DEFLECTING AT ME");
		else if ((p.targetFlags & TargetFlags::IS_SABERIST_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "SABERIST");
		else if ((p.targetFlags & TargetFlags::IS_SHOOTING_AT_ME_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "SHOOTING AT ME");
		else if ((p.targetFlags & TargetFlags::IS_VIABLE_SABERIST_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "VIABLE SABERIST");
		else if ((p.targetFlags & TargetFlags::IS_LOWEST_HP_TGT))
			draw->bold28->Print(p.screenInfo.posSymbol.x, p.screenInfo.posSymbol.y, RGB::yellow, "LOWEST HP");
#endif // DEBUG
	}

	if (me.closestPlayer.player != nullptr && me.closestPlayer.player->angles.me_to_this_target3D < 12)
	{
		Vertex2 pos = me.closestPlayer.player->screenInfo.posSymbol;
		float offsetY = 20;
		float firstOffsetY = offsetY;
		float offsetX = 20;
		float firstOffsetX = offsetX;
		float scaleFactor = 1.0f / (1.0f + me.closestPlayer.player->distances.distance3 / 1000);
		firstOffsetY *= scaleFactor;
		firstOffsetX *= scaleFactor;
		draw->bold28->CenterPrint(pos.x, pos.y - 2*firstOffsetY, CHARSIZES::CALIBRI28, me.closestPlayer.player->screenInfo.screenColor, me.closestPlayer.player->shortName);
		draw->regular24->Print(pos.x + firstOffsetX, pos.y + firstOffsetY, me.closestPlayer.player->screenInfo.screenColor, EnClassesNames[me.closestPlayer.player->entClass]);
		draw->regular24->Print(pos.x + firstOffsetX, pos.y + firstOffsetY + offsetY, me.closestPlayer.player->screenInfo.screenColor, std::to_string(me.closestPlayer.player->hp));
	}

	drawPlayerInfoTimer.Stop();
}
void MainEvents::DrawPredictedTrajectories()
{
	draw->DrawTrajectory(me.colData.trajectory, 1, RGB::yellow);

	if (me.colData.trajectory.size())
	{
		GLfloat color[4]{ 0.8,0.1,0.1,0.3f };
		Vec3 finalPoint = me.colData.trajectory[me.colData.trajectory.size() - 1];
		draw->DrawImpactFigure(me.colData.trajectory[me.colData.trajectory.size() - 1], me.colData.lastNormal, 32, color);
	}

	for (auto& m : missiles)
	{
		//draw box for mines etc
		if (m.second.trajectoryType == TRAJECTORY_TYPE::TR_STATIONARY
			|| m.second.trajectoryType == TRAJECTORY_TYPE::TR_INTERPOLATE
			)
		{
			draw->DrawBBox(m.second.startPos, m.second.startPos, { -6,-6,-6 }, { 6,6,6 }, 3, RGB::red);
		}

		if (!m.second.trajectory.empty() /*&& vecs::VecDistance(m.second.trajectory[m.second.trajectory.size() - 1], me.position.posFeet) < 600.0f*/)
		{

			GLfloat color[4];
			if (m.second.team != me.team && m.second.parentEnt != me.trueId)
			{
				color[0] = rw->colors[Colors::COL_ENEMIES][0]; color[1] = rw->colors[Colors::COL_ENEMIES][1];
				color[2] = rw->colors[Colors::COL_ENEMIES][2]; color[3] = rw->colors[Colors::COL_ENEMIES][3];
			}
			else if (m.second.parentEnt != me.trueId)
			{
				color[0] = rw->colors[Colors::COL_ALLIES][0]; color[1] = rw->colors[Colors::COL_ALLIES][1];
				color[2] = rw->colors[Colors::COL_ALLIES][2]; color[3] = rw->colors[Colors::COL_ALLIES][3];
			}
			else
			{
				memcpy(color, RGB::white, sizeof(color));
			}

			//draw trajectory
			if (m.second.trajectoryType == TRAJECTORY_TYPE::TR_GRAVITY
				|| m.second.parentGun == Weapons::WP_PLX
				|| m.second.parentGun == Weapons::WP_MERR_SONN
				)
				draw->DrawTrajectory(m.second.trajectory, 1, color);

			//draw impact
			if (m.second.trajectory.size() && m.second.radius != 0)
			{

				Vec3 finalPoint = m.second.trajectory[m.second.trajectory.size() - 1];
				draw->DrawImpactFigure(m.second.trajectory[m.second.trajectory.size() - 1], m.second.destinationNormal, m.second.radius, color);
			}
		}

	}
}
void MainEvents::DrawSsetMyLocation()
{
	if (ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].isDraw && world != nullptr)
	{


		Vec3_ui8 chLoc = world->get_chunk_coordinates_from_index(me.bot.myCellCoordinates.chunkLocation);
		Vec3_ui8 cLoc = world->unpack_coordinates(me.bot.myCellCoordinates.cellLocation);
		uint32_t flag = 0;
		uint32_t maskedFlag = 0;
		uint16_t entNum = 0;
		uintptr_t graphNodeAddress = 0;
		
		Cell* cell = world->get_cell(me.bot.myCellCoordinates.chunkLocation, (me.bot.myCellCoordinates.cellLocation));
		if (cell)
		{
			flag = world->get_cell(me.bot.myCellCoordinates.chunkLocation, (me.bot.myCellCoordinates.cellLocation))->flags;
			//maskedFlag = flag & CellFlags::flagMask;
			entNum = cell->entNum;
			graphNodeAddress = (uintptr_t)cell->graphNode;
		}

		std::string chLocStr, cLocStr, flagStr, maskedFlagStr, entNumStr, writtenFlags, graphNode;
		chLocStr = std::to_string(chLoc.x) + " " + std::to_string(chLoc.y) + " " + std::to_string(chLoc.z) + "  " + std::to_string(me.bot.myCellCoordinates.chunkLocation);
		cLocStr = std::to_string(cLoc.x) + " " + std::to_string(cLoc.y) + " " + std::to_string(cLoc.z) + "  " + std::to_string(me.bot.myCellCoordinates.cellLocation);
		flagStr = std::to_string(flag);
		maskedFlagStr = std::to_string(maskedFlag);
		entNumStr = std::to_string(entNum);
		graphNode = std::to_string(graphNodeAddress);

		if (flag & CellFlags::WALKABLE)
			writtenFlags += "WALK |";
		if (flag & CellFlags::IS_MOVER)
			writtenFlags += "MOVER |";
		if (flag & CellFlags::IS_EDGE)
			writtenFlags += "EDGE |";
		if (flag & CellFlags::IS_EDGE2)
			writtenFlags += "EDGE2 |";
		if (flag & CellFlags::IS_EDGE3)
			writtenFlags += "EDGE3 |";
		if (flag & CellFlags::IS_BANNED)
			writtenFlags += "BANNED |";
		if (flag & CellFlags::REFRESH)
			writtenFlags += "REFRESH |";
		if (flag & CellFlags::IS_RESCANNED)
			writtenFlags += "RESCANNED |";

		if (!writtenFlags.empty())
			writtenFlags.pop_back();


		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MESH_TOTAL_SCANS].value = std::to_string(world->scansCount);
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MESH_TOTAL_CELLS].value = std::to_string(world->validCellsCount);
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MESH_TOTAL_GRAPHNODES].value = std::to_string(world->graph.size());
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MY_CHUNK_LOCATION].value = chLocStr;
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MY_CELL_LOCATION].value = cLocStr;
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MY_CELL_FLAG_LOCATION].value = flagStr;
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MY_CELL_GRAPH_NODE].value = graphNode;
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::MY_MASKED_CELL_FLAG_LOCATION].value = maskedFlagStr;
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::ENUMERATE_CELL_FLAGS].value = writtenFlags; memcpy(ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::ENUMERATE_CELL_FLAGS].color, RGB::yellow, sizeof(RGB::yellow));
		ui.menuBlocks[menu::MY_CELL_LOCATION_BLOCK].items[menu::ENT_NUM_LOCATION].value = entNumStr;
	}
}
void MainEvents::DrawMyPathStats()
{
	if (!ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].isDraw || world == nullptr)
		return;

	std::string lastErrorStr;
	std::string totalLengthStrU, totalLengthStrM, etaStr;
	float totalLength = 0;

	switch (generatedPathLastError)
	{
	case PathfindingErrors::NONE:
		lastErrorStr = "NONE";
		break;
	case PathfindingErrors::SUCCESS:
		lastErrorStr = "SUCCESS";
		break;
	case PathfindingErrors::START_OR_FINISH_WAS_INVALID:
		lastErrorStr = "START_OR_FINISH_WAS_INVALID";
		break;
	case PathfindingErrors::TOO_FAR_AWAY:
		lastErrorStr = "TOO_FAR_AWAY";
		break;
	case PathfindingErrors::UNREACHABLE:
		lastErrorStr = "UNREACHABLE";
		break;
	case PathfindingErrors::START_AND_FINISH_SAME_NODE:
		lastErrorStr = "START_AND_FINISH_SAME_NODE";
		break;
	default:
		break;
	}

	if (!navigationPath.empty())
		for (int i = 0; i < navigationPath.size() - 1; i++)
		{
			totalLength += vecs::VecDistance(navigationPathPoints[i], navigationPathPoints[i + 1]);
		}

	totalLengthStrU = std::to_string((int)totalLength);
	totalLengthStrM = std::to_string((int)(totalLength * 0.023f));
	etaStr = std::to_string((int)(totalLength / me.maxSpeed));

	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_ERRORS].value = lastErrorStr;
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_SIZE].value = std::to_string(navigationPath.size());
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_TIME].value = Utils::MrTimer::RemoveTrailingZeros(world->pathGenTimer.ElapsedMcs() / 1000, 3) + " ms";
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_LENGTH].value = totalLengthStrU + " u  " + totalLengthStrM + " m";
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_ETA].value = etaStr + " seconds";
	ui.menuBlocks[menu::GENERATED_PATH_INFO_BLOCK].items[menu::GENERATED_PATH_CURRENT_STEP].value = std::to_string(me.bot.currentStep);

}
void MainEvents::SetTimers()
{
	if (ui.menuBlocks[menu::TIMERS_BLOCK].isDraw)
	{
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::GET_KEYS_TIMER].value = std::to_string((int)getKeysTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::INIT_PLAYERS_TIMER].value = std::to_string((int)initializePlayersTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::INIT_ENTS_TIMER].value = std::to_string((int)initializeEntsTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::SET_WEAPONS_TIMER].value = std::to_string((int)setWeaponsTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::VISIBILITY_TIMER].value = std::to_string((int)CheckVisibilityTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::PREDICT_MISSILE_PATH_TIMER].value = std::to_string((int)predictMissileTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::DRAW_PLAYER_INFO].value = std::to_string((int)drawPlayerInfoTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::READ_SHARED_MEMORY_TIMER].value = std::to_string((int)readSharedMemoryTimer.ElapsedAverage(20)) + " mcs";
		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::LAST_NAME_INSERTION_TIMER].value = std::to_string((int)lastNameInsertionTimer.ElapsedMcs()) + " mcs";

		ui.menuBlocks[menu::TIMERS_BLOCK].items[menu::TOTAL_MAINEVENT_TIMER].value = std::to_string((int)totalMainEventTimer.ElapsedAverage(20)) + " mcs";
	}
	if (ui.menuBlocks[menu::MESH_TIMERS_BLOCK].isDraw && world != nullptr)
	{
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_WORLD_GEN_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->cellsGenTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_WORLD_CLEANUP_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->cellsCleanupTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_WORLD_POSTGEN_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->cellsPostGenTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_NODE_CULLING_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->nodeCullingTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::ISLAND_SCAN_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->islandScanTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_MESH_SPLIT_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->splitMeshTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_MAP_WRITTEN_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->mapWriteTime / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_MAP_READ_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->mapReadTime / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_DOOR_SCAN_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->rescanAreaTimer.ElapsedMcs() / 1000, 3) + " ms";
		ui.menuBlocks[menu::MESH_TIMERS_BLOCK].items[menu::GET_UNBAN_AREA_TIMER].value = Utils::MrTimer::RemoveTrailingZeros(world->unbanAreaTimer.ElapsedMcs() / 1000, 3) + " ms";
	}

}
void MainEvents::GetPlayerInfo()
{
	if (ui.menuBlocks[menu::DEBUG_INFO_BLOCK].isDraw)
	{
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_WEAPON_DBG].value = std::to_string((int)me.wpInfo.num);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_WEAPON_VEL].value = std::to_string((int)me.wpInfo.speed);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_WEAPON_FIRERATE].value = std::to_string((int)me.wpInfo.fireRate);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_CLASS_DBG].value = std::to_string((int)me.entClass);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_STANCE1_DBG].value = std::to_string((int)me.stance);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_STANCE2_DBG].value = std::to_string((int)me.stance2);
		ui.menuBlocks[menu::DEBUG_INFO_BLOCK].items[menu::MY_SABER_ANIM_DBG].value = std::to_string((int)me.saberAnim);
	}

	int counter = 0;
	//record players
	if (!ui.menuBlocks[menu::PLAYERS_BLOCK].isDraw)
		return;
	for (auto& p : players)
	{
		if (counter > maxPlayerId)
			break;

		if (!p.shortName.empty())
		{
			ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].item = std::to_string(p.id);
			ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].value = p.shortName
				+ " " + std::to_string((int)p.team)
				+ " " + std::to_string((int)p.entClass)
				+ " " + std::to_string((int)p.position.posFeet.x)
				;
			if (p.team == Teams::REB)
				memcpy(ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].color, RGB::green, sizeof(RGB::green));
			else if (p.team == Teams::IMP)
				memcpy(ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].color, RGB::red, sizeof(RGB::green));
			if (!(p.playerFlags & PlayerFlags::IS_ALIVE))
			{
				memcpy(ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].color, RGB::white, sizeof(RGB::white));
			}
		}
		else
		{
			ui.menuBlocks[menu::PLAYERS_BLOCK].items[counter].value = "";
		}

		counter++;
	}
}
void MainEvents::GetBuild()
{
	if (!ui.menuBlocks[menu::BUILD_BLOCK].isDraw)
		return;
	int counter = 0;
	GLfloat col;
	for (auto& i : ui.menuBlocks[menu::BUILD_BLOCK].items)
	{
		i.second.item = "";
		i.second.value = "";
	}
	for (auto&i:me.myConfig)
	{
		if (counter == MAX_BUILD_ITEMS)
			break;
		ui.menuBlocks[menu::BUILD_BLOCK].items[counter].item = ConfigValNames[i.first];
		ui.menuBlocks[menu::BUILD_BLOCK].items[counter].value = std::to_string(i.second);

		switch (i.second)
		{
		case 1:
			memcpy(ui.menuBlocks[menu::BUILD_BLOCK].items[counter].color, RGB::green, sizeof(RGB::green));
			break;
		case 2:
			memcpy(ui.menuBlocks[menu::BUILD_BLOCK].items[counter].color, RGB::yellow, sizeof(RGB::green));
			break;
		case 3:
			memcpy(ui.menuBlocks[menu::BUILD_BLOCK].items[counter].color, RGB::red, sizeof(RGB::green));
			break;
		default:
			break;
		}

		counter++;
	}
}
void MainEvents::DrawBulletTrace()
{
	for (auto& m : missiles)
	{
		if (!m.second.trajectory.empty() && m.second.trajectoryType == TRAJECTORY_TYPE::TR_LINEAR)
		{
			bulletTrajectoriesToDraw.push_back({ m.second.trajectory.front(), m.second.trajectory.back() });
		}
	}
	for (auto& t : bulletTrajectoriesToDraw)
	{
		draw->DrawLine(t.start, t.end, 2, RGB::yellow);
	}
	if (GetAsyncKeyState(VK_RETURN))
		bulletTrajectoriesToDraw.clear();
}
void MainEvents::DrawBotStates()
{
	std::vector<std::string> commands;

	for (const auto& stateNamePair : botStateNamesMap)
	{
		if (me.bot.botStateFlag & stateNamePair.first)
		{
			commands.push_back(stateNamePair.second);
		}
	}


	Vertex2 pos; 

	float offset = 14.0f; pos.x = 200.0f; pos.y = 200.0f;
	for (auto&c: commands)
	{	
		pos.y += offset;
		draw->regular24->Print(pos, RGB::yellow, c);
	}

	Vertex2 posTgtCells; posTgtCells.x = 200; posTgtCells.y = draw->viewport[3] / 1.4;
	for (auto& ds : me.bot.tgtCells)
	{
		if (ds.second != 0)
		{
			posTgtCells.y += offset;
			draw->regular24->Print(posTgtCells, RGB::yellow, TargetCellNames[ds.first]);
		}
	}
}
void MainEvents::DrawTargetCube()
{
	if (!world)
		return;

	Cell* targetCell = nullptr;
	for (auto& ds : me.bot.tgtCells)
	{
		if (ds.second != 0)
			targetCell = world->get_cell(ds.second);
	}

	if (targetCell)
	{
		Vec3 bot, top = targetCell->GetCenter(); top.z += 20;
		draw->DrawBBox(targetCell->GetCenter(), top, { -8,-8,-8 }, { 8,8,8 }, 2, RGB::yellow);
		draw->DrawLine(top, me.position.posHead, 1, RGB::yellow);
	}
}
void MainEvents::DrawLookingAtCube()
{
	if (!world)
		return;

	float halfCell = WorldConstants::CELL_SIZE / 2;
	Vec3 min{ -halfCell ,-halfCell ,-halfCell }, max{ halfCell,halfCell,halfCell };
	GLfloat col[4]{ RGB::yellow[0],RGB::yellow[1], RGB::yellow[2], 0.23 };
	GLfloat colFace[4]{ RGB::red[0],RGB::red[1], RGB::red[2], 0.4 };

	for (auto& p : players)
	{
		if (p.botInfo.cellLookingAt == 0 || !(p.playerFlags & PlayerFlags::IS_ALIVE))
			continue;
		Cell* cellLookingAt = world->get_cell(p.botInfo.cellLookingAt);
		if (cellLookingAt)
		{
			Vec3 center = cellLookingAt->GetCenter();

			std::vector<Chunk*>neigh;
			cellLookingAt->parentChunk->get_all_neighbors(neigh);
			neigh.push_back(cellLookingAt->parentChunk);
			for (auto& n : neigh)
			{
				for (auto& cell : n->validCells)
				{
					Cell* cellAround = world->get_cell(cell);
					Vec3 cellAroundLoc = cellAround->GetCenter();
					float dist = vecs::VecDistance(center, cellAroundLoc);
					if (dist < 80 && cellAround->loc != cellLookingAt->loc)
					{
						Vec3 xn_yn, xp_yn, xn_yp, xp_yp;
						xn_yn.x = cellAroundLoc.x - WorldConstants::HALF_CELL_SIZE; xn_yn.y = cellAroundLoc.y - WorldConstants::HALF_CELL_SIZE; xn_yn.z = cellAroundLoc.z;
						xp_yn.x = cellAroundLoc.x + WorldConstants::HALF_CELL_SIZE; xp_yn.y = cellAroundLoc.y - WorldConstants::HALF_CELL_SIZE; xp_yn.z = cellAroundLoc.z;
						xn_yp.x = cellAroundLoc.x - WorldConstants::HALF_CELL_SIZE; xn_yp.y = cellAroundLoc.y + WorldConstants::HALF_CELL_SIZE; xn_yp.z = cellAroundLoc.z;
						xp_yp.x = cellAroundLoc.x + WorldConstants::HALF_CELL_SIZE; xp_yp.y = cellAroundLoc.y + WorldConstants::HALF_CELL_SIZE; xp_yp.z = cellAroundLoc.z;

						
						draw->DrawFilledPolygon(xn_yn , xp_yn ,xp_yp ,xn_yp, col);
					}
				}
			}

			draw->DrawBBox(center, center, min, max, 4, RGB::yellow);		

			if (p.botInfo.currentCubeIntersection != 0)
				draw->DrawLine(p.position.posHead, p.botInfo.currentCubeIntersection, 2, RGB::white);
		}
	}

	
}
void MainEvents::DrawMinionPaths()
{
	if (!world)
		return;
	for (auto& p : sortedPlayers)
	{
		if (!p->botInfo.minionNavigationPath.empty())
		{
			draw->DrawPath(world->graph, p->botInfo.minionNavigationPath, botConfigFlags);
		}
	}
}
void MainEvents::DrawUI()
{
	if (testQuit)
		return;

	GetColors();
	GetBuild();
	GetPlayerInfo();
	DrawPredictedTrajectories();
	DrawProbeRay();
	DrawPlayerInfo();
	DrawSsetMyLocation();
	DrawMyPathStats();


	//DrawBulletTrace();

	if ((isRobot || (botConfigFlags & BotConfigFlags::MAKE_MAIN_WINDOW_BOT)) && (botConfigFlags & BotConfigFlags::ENABLE_BOT))
	{
		draw->bold28->Print(draw->viewport[2]/2, 200, RGB::yellow, "I AM A BOT");
	}

	if ((botConfigFlags & BotConfigFlags::DRAW_CELL_GRID) && !isConsoleOpen)
		draw->DrawWorld(world, me.position.posFeet, me.bot.myCellCoordinates, me.bot.myFactualCellCoordinates, rw->meshColors);
	if (world && (botConfigFlags & BotConfigFlags::DRAW_GRAPH) && !isConsoleOpen)
		draw->DrawGraph(world->graph, me.position.posFeet, botConfigFlags, rw->graphColors);

	//draw->DrawPath(world->graph, navigationPath, botConfigFlags);
	draw->DrawPath(navigationPathPointsUnedited, botConfigFlags);

	if (botConfigFlags & BotConfigFlags::DRAW_BOT_STATES)
		DrawBotStates();

	if ((botConfigFlags & BotConfigFlags::DRAW_UI) && !(configFlags & ConfigFlags::SET_MAP_EDITOR_ENABLED))
		draw->DrawUI(ui);

	DrawMinionPaths();
	DrawTargetCube();
	DrawLookingAtCube();
	DrawTriggers();

	//Vertex2 posTimes{ 200, 400 }; int offset = 20;
	//int counter = 0;
	//for (auto& combo : input->keys)
	//{
	//	for (auto& k : combo.second)
	//	{
	//		draw->regular24->Print(posTimes.x, posTimes.y + counter*offset,RGB::yellow, std::to_string(k.timePressed));
	//	}
	//	counter++;
	//}
}

//map editor
void MainEvents::DrawTriggers()
{
	if (!world ||!(botConfigFlags & BotConfigFlags::DRAW_ELEVATOR_FLAGS))
		return;

	GLfloat colorInactive[4], colorActive[4], colorNotLinked[4], colorChosen[4];

	memcpy(colorInactive, RGB::white, sizeof(RGB::white));
	memcpy(colorActive, RGB::yellow, sizeof(RGB::white));
	memcpy(colorNotLinked, RGB::red, sizeof(RGB::white));
	memcpy(colorChosen, RGB::blue, sizeof(RGB::white));

	int counter = 0;

	Vec3 min = -(float)WorldConstants::HALF_CELL_SIZE, max = (float)WorldConstants::HALF_CELL_SIZE;
	for (auto& c : world->customTriggers)
	{
		Cell* triggerBot = world->get_cell(c.second.triggerBottom);
		Cell* triggerTop = world->get_cell(c.second.triggerTop);

		if (triggerBot == nullptr || triggerTop == nullptr)
			continue;

		Vec3 centerBot = triggerBot->GetCenter();
		Vec3 centerTop = triggerTop->GetCenter();

		if (c.second.elevatorStates & ElevatorStates::LINKED)
		{
			counter++;
			if (c.second.entBottom >= 1022)
				draw->DrawBBox(centerBot, centerBot, min, max, 1, colorInactive);
			else
				draw->DrawBBox(centerBot, centerBot, min, max, 1, colorActive);

			if (c.second.entTop >= 1022)
				draw->DrawBBox(centerTop, centerTop, min, max, 1, colorInactive);
			else
				draw->DrawBBox(centerTop, centerTop, min, max, 1, colorActive);

			if (c.second.elevatorStates & ElevatorStates::BOTTOM)
			{
				Vec3 centerBotTopTrigger = world->get_cell(c.second.other->triggerBottom)->GetCenter();
				draw->DrawLine(centerTop, centerBotTopTrigger, 1, RGB::white);
			}
			else
			{
				Vec3 centerTopTopTrigger = world->get_cell(c.second.other->triggerTop)->GetCenter();
				draw->DrawLine(centerBot, centerTopTopTrigger, 1, RGB::white);
			}
			if (c.second.elevatorButton != 0)
			{
				Cell* elevatorButton = world->get_cell(c.second.elevatorButton);
				if (elevatorButton)
				{
					draw->DrawLine(centerBot, elevatorButton->GetCenter(), 1, RGB::pink);
				}
			}
			if (c.second.elevatorButtonCall != 0)
			{
				Cell* elevatorButton = world->get_cell(c.second.elevatorButtonCall);
				if (elevatorButton)
				{
					draw->DrawLine(centerBot, elevatorButton->GetCenter(), 1, RGB::blue);
				}
			}

			Vertex2 loc; draw->WTS(centerTop, loc);
			//loc = { 400, 100 };

			std::string elStatesStr;

			for (auto& es : elevatorStatesList)
			{
				if (c.second.elevatorStates & es.first)
					elStatesStr += es.second + " | ";
			}
			if (elStatesStr.size() > 2)
			{
				elStatesStr.pop_back(); elStatesStr.pop_back();
			}

			draw->regular24->Print(loc/*.x, loc.y+counter*40*/, RGB::yellow, elStatesStr);
			//draw->regular24->Print(loc.x, loc.y + 30, RGB::yellow, std::to_string(c.second.elevatorStateChangesCounter));
		}
		else
		{
			draw->DrawBBox(centerBot, centerBot, min, max, 1, colorNotLinked);
			draw->DrawBBox(centerTop, centerTop, min, max, 1, colorNotLinked);
		}

	}
}

void MainEvents::ManuallySaveMap()
{
	reloadMapNow = false;
	if (!(worldFlags & WorldFlags::IS_SAVE_REQURED) || !world || isRobot)
		return;

	draw->bold28->Print(draw->viewport[2] / 1.4 - 100, 230, RGB::yellow, "PRESS CTRL + SHIFT + S to save the map");

	if (input->IsKeyToggled(MyKeysEnum::SAVE_MAP_KEYS))
	{
		reloadMapNow = true;
		reloadBotMaps = true;
		mapReader->SaveMap(rw->mapFolderPath, currentMapW, world);
		worldFlags &= ~WorldFlags::IS_SAVE_REQURED;
		world->oldValidCellsCount = world->validCellsCount;
	}
}
void MainEvents::DrawInfoBlock()
{

	int stepSmall = 16;
	int stepBig = 20;
	Vertex2 infoDescrLoc = { draw->viewport[2] / 8, 200 + 0 * stepSmall };
	Vertex2 infoLoc = { draw->viewport[2] / 4, 200 + 0 * stepSmall };

	std::string cellLocationStr, chunkLocationStr;
	std::string cellFlagsStr;
	std::string entNumStr;
	std::string cellTypeStr;
	std::string graphNodeStr;
	std::string graphNodeFlagsStr;

	Cell* cellLookingAtReal = world->get_cell(me.botInfo.cellLookingAt);
	if (!cellLookingAtReal)
		return;

	//cell location-------------------------------------------
	Vec3_ui8 cellCrdUnpacked = world->unpack_coordinates(me.botInfo.cellLookingAt.cellLocation);
	cellLocationStr = std::to_string(me.botInfo.cellLookingAt.cellLocation) + "   " + std::to_string(cellCrdUnpacked.x) + ": " + std::to_string(cellCrdUnpacked.y) + ": " + std::to_string(cellCrdUnpacked.z);
	Vec3_ui8 chunkCrdUnpacked = world->get_chunk_coordinates_from_index(me.botInfo.cellLookingAt.chunkLocation);
	chunkLocationStr = "   chunk: " + std::to_string(me.botInfo.cellLookingAt.chunkLocation) + "   " + std::to_string(chunkCrdUnpacked.x) + ": " + std::to_string(chunkCrdUnpacked.y) + ": " + std::to_string(chunkCrdUnpacked.z);
	//------------------------------------------- 

	//flags-------------------------------------------
	for (auto& cf : cellFlagsList)
	{
		if (cellLookingAtReal->flags & cf.first)
			cellFlagsStr += cf.second + " | ";
	}
	if (cellFlagsStr.size() > 2)
	{
		cellFlagsStr.pop_back(); cellFlagsStr.pop_back();
	}
	//------------------------------------------------

	//graphNodeFlags-------------------------------------------
	for (auto& cf : graphNodeFlagsList)
	{
		if (cellLookingAtReal->graphNode && (cellLookingAtReal->graphNode->flags & cf.first))
			graphNodeFlagsStr += cf.second + " | ";
	}
	if (graphNodeFlagsStr.size() > 2)
	{
		graphNodeFlagsStr.pop_back(); graphNodeFlagsStr.pop_back();
	}
	//------------------------------------------------

	//entnum------------------------------------------------
	entNumStr = std::to_string(cellLookingAtReal->entNum);

	//------------------------------------------------

	//cell type selector------------------------------------------------
	static int specialCellVectorIndex = 0;
	if (input->IsKeyToggled(MyKeysEnum::SWITCH_CELL_TYPE_LEFT_KEYS)) //u
	{
		specialCellVectorIndex--;
		if (specialCellVectorIndex < 0)
			specialCellVectorIndex++;

	}
	if (input->IsKeyToggled(MyKeysEnum::SWITCH_CELL_TYPE_RIGHT_KEYS)) //i
	{
		specialCellVectorIndex++;
		if (specialCellVectorIndex >= specialCellFlagList.size())
			specialCellVectorIndex--;
	}


	cellTypeStr = specialCellFlagList[specialCellVectorIndex].second;
	me.bot.newCellFlag = specialCellFlagList[specialCellVectorIndex].first;

	if (me.bot.newCellFlag & CellFlags::IS_BANNED)
	{
		memcpy(me.bot.specialCellColor, CELL_TYPE_COLORS::banned, sizeof(me.bot.specialCellColor));
	}
	else if (me.bot.newCellFlag & CellFlags::IS_BANNED)
	{
		memcpy(me.bot.specialCellColor, CELL_TYPE_COLORS::banned, sizeof(me.bot.specialCellColor));
	}

	else if (me.bot.newCellFlag & CellFlags::IS_WALKABLE_DOWN)
	{
		memcpy(me.bot.specialCellColor, CELL_TYPE_COLORS::downOnly, sizeof(me.bot.specialCellColor));
	}

	else if (me.bot.newCellFlag & CellFlags::IS_WALKABLE_UP)
	{
		memcpy(me.bot.specialCellColor, CELL_TYPE_COLORS::upOnly, sizeof(me.bot.specialCellColor));
	}

	else if (me.bot.newCellFlag & CellFlags::IS_JUMP)
	{
		memcpy(me.bot.specialCellColor, CELL_TYPE_COLORS::jump, sizeof(me.bot.specialCellColor));
	}

	if (cellLookingAtReal->graphNode)
		graphNodeStr = std::to_string((uintptr_t)cellLookingAtReal->graphNode);
	else
		graphNodeStr = "NULLPTR";

	//------------------------------------------------

	//write------------------------------------------------
	draw->regular24->Print(infoDescrLoc.x, infoDescrLoc.y, RGB::white, "Cell location: ");
	draw->regular24->Print(infoLoc.x, infoLoc.y, RGB::yellow, cellLocationStr + chunkLocationStr);

	draw->regular24->Print(infoDescrLoc.x, infoDescrLoc.y + 1 * stepSmall, RGB::white, "Cell flags: ");
	draw->regular24->Print(infoLoc.x, infoLoc.y + 1 * stepSmall, RGB::yellow, cellFlagsStr);

	draw->regular24->Print(infoDescrLoc.x, infoDescrLoc.y + 2 * stepSmall, RGB::white, "Entity: ");
	draw->regular24->Print(infoLoc.x, infoLoc.y + 2 * stepSmall, RGB::yellow, entNumStr);

	draw->bold28->Print(infoDescrLoc.x, infoDescrLoc.y + 5 * stepBig, RGB::white, "New cell type: ");
	draw->bold28->Print(infoLoc.x, infoLoc.y + 5 * stepBig, me.bot.specialCellColor, cellTypeStr);

	draw->bold28->Print(infoDescrLoc.x, infoDescrLoc.y + 6 * stepBig, RGB::white, "GraphNode: ");
	draw->bold28->Print(infoLoc.x, infoLoc.y + 6 * stepBig, me.bot.specialCellColor, graphNodeStr + "  flags:" + graphNodeFlagsStr);
	//------------------------------------------------

}
void MainEvents::MapEditorAddCell()
{
	//add cell
	if (me.botInfo.cellLookingAt == 0)
		return;

	//info block
	DrawInfoBlock();

	//draw cube to be edited
	Vec3 cellMin = -(float)WorldConstants::CELL_SIZE / 2, cellMax = (float)WorldConstants::CELL_SIZE / 2;
	CellCoordinates offsetCell = { 0,0 };
	Vec3 offsetCellLoc = 0;

	switch (me.botInfo.currentCubeFace)
	{
	case CubeFaces::TOP:
	{
		int8_t offset[3]{ 0,0,1 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	case CubeFaces::BOTTOM:
	{
		int8_t offset[3]{ 0,0,-1 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	case CubeFaces::BACK:
	{
		int8_t offset[3]{ 0,-1,0 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	case CubeFaces::FRONT:
	{
		int8_t offset[3]{ 0,1,0 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	case CubeFaces::LEFT:
	{
		int8_t offset[3]{ -1,0,0 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	case CubeFaces::RIGHT:
	{
		int8_t offset[3]{ 1,0,0 };
		offsetCell = world->get_offset_coordinates(me.botInfo.cellLookingAt, offset);
		offsetCellLoc = world->get_cell_float_coordinates_from_location(offsetCell);
		break;
	}
	default:
		break;
	}

	draw->DrawBBox(offsetCellLoc, offsetCellLoc, cellMin, cellMax, 1, me.bot.specialCellColor);

	//draw faces
	Cell* aimCell = world->get_cell(me.botInfo.cellLookingAt);
	if (aimCell)
	{
		Vec3 center = aimCell->GetCenter();
		Vertex2 faceVertices[4];
		Vec3 xn_yn_b, xp_yn_b, xn_yp_b, xp_yp_b; Vec3 xn_yn_t, xp_yn_t, xn_yp_t, xp_yp_t;
		xn_yn_b.x = center.x - WorldConstants::HALF_CELL_SIZE; xn_yn_b.y = center.y - WorldConstants::HALF_CELL_SIZE; xn_yn_b.z = center.z - WorldConstants::HALF_CELL_SIZE;
		xp_yn_b.x = center.x + WorldConstants::HALF_CELL_SIZE; xp_yn_b.y = center.y - WorldConstants::HALF_CELL_SIZE; xp_yn_b.z = center.z - WorldConstants::HALF_CELL_SIZE;
		xn_yp_b.x = center.x - WorldConstants::HALF_CELL_SIZE; xn_yp_b.y = center.y + WorldConstants::HALF_CELL_SIZE; xn_yp_b.z = center.z - WorldConstants::HALF_CELL_SIZE;
		xp_yp_b.x = center.x + WorldConstants::HALF_CELL_SIZE; xp_yp_b.y = center.y + WorldConstants::HALF_CELL_SIZE; xp_yp_b.z = center.z - WorldConstants::HALF_CELL_SIZE;

		xn_yn_t.x = center.x - WorldConstants::HALF_CELL_SIZE; xn_yn_t.y = center.y - WorldConstants::HALF_CELL_SIZE; xn_yn_t.z = center.z + WorldConstants::HALF_CELL_SIZE;
		xp_yn_t.x = center.x + WorldConstants::HALF_CELL_SIZE; xp_yn_t.y = center.y - WorldConstants::HALF_CELL_SIZE; xp_yn_t.z = center.z + WorldConstants::HALF_CELL_SIZE;
		xn_yp_t.x = center.x - WorldConstants::HALF_CELL_SIZE; xn_yp_t.y = center.y + WorldConstants::HALF_CELL_SIZE; xn_yp_t.z = center.z + WorldConstants::HALF_CELL_SIZE;
		xp_yp_t.x = center.x + WorldConstants::HALF_CELL_SIZE; xp_yp_t.y = center.y + WorldConstants::HALF_CELL_SIZE; xp_yp_t.z = center.z + WorldConstants::HALF_CELL_SIZE;

		GLfloat colFace[4]{ RGB::red[0],RGB::red[1], RGB::red[2], 0.4 };
		switch (me.botInfo.currentCubeFace)
		{
		case CubeFaces::TOP:
		{
			draw->DrawFilledPolygon(xn_yn_t, xp_yn_t, xp_yp_t, xn_yp_t, colFace);
			break;
		}
		case CubeFaces::BOTTOM:
		{
			draw->DrawFilledPolygon(xn_yn_b, xp_yn_b, xp_yp_b, xn_yp_b, colFace);
			break;
		}
		case CubeFaces::BACK:
		{
			draw->DrawFilledPolygon(xn_yn_b, xp_yn_b, xp_yn_t, xn_yn_t, colFace);
			break;
		}
		case CubeFaces::FRONT:
		{
			draw->DrawFilledPolygon(xn_yp_b, xp_yp_b, xp_yp_t, xn_yp_t, colFace);
			break;
		}
		case CubeFaces::LEFT:
		{
			draw->DrawFilledPolygon(xn_yp_b, xn_yn_b, xn_yn_t, xn_yp_t, colFace);
			break;
		}
		case CubeFaces::RIGHT:
		{
			draw->DrawFilledPolygon(xp_yp_b, xp_yn_b, xp_yn_t, xp_yp_t, colFace);
			break;
		}
		default:
			break;
		}

		draw->DrawBBox(center, center, cellMin, cellMax, 4, RGB::white);

		if (me.botInfo.currentCubeIntersection != 0)
			draw->DrawLine(me.position.posHead, me.botInfo.currentCubeIntersection, 2, RGB::white);
	}

	//add cell
	if (input->IsKeyToggled(MyKeysEnum::ADD_CELL_KEYS, 250) && aimCell) //n
	{
		if (!(me.bot.newCellFlag & CellFlags::IS_ELEVATOR_DETECTOR))
		{
			uint16_t entNum = 0;
			uint32_t cellFlag = me.bot.newCellFlag;

			if (me.bot.newCellFlag & CellFlags::WALKABLE)
			{
				entNum = aimCell->entNum;
				cellFlag = aimCell->flags;
			}

			world->add_cell_manually(offsetCell, cellFlag, entNum);
		}
		else
		{
			world->create_trigger(offsetCell);
		}
	}

	//add cell
}
void MainEvents::MapEditorDeleteCell()
{
	if (input->IsKeyToggled(MyKeysEnum::DELETE_CELL_KEYS, 250))
	{
		world->delete_trigger(me.botInfo.cellLookingAt);
		world->delete_cell_manually(me.botInfo.cellLookingAt);
	}
}
void MainEvents::MapEditorDeleteIsland()
{
	//delete island
	if (input->IsKeyToggled(MyKeysEnum::DELETE_ISLAND_KEYS))
	{
		Cell* tgtCell = world->get_cell(me.botInfo.cellLookingAt);
		std::vector<uint32_t> cellsToremove;
		if (tgtCell && tgtCell->graphNode)
		{
			std::vector<uintptr_t> nodesToDelete;
			for (auto& node : world->graph)
			{
				if (tgtCell->graphNode->islandNum != node.second->islandNum || node.second->islandNum == 0)
					continue;
				cellsToremove.insert(cellsToremove.end(), node.second->cells.begin(), node.second->cells.end());
				nodesToDelete.push_back((uintptr_t)node.second);
			}

			for (auto& n : nodesToDelete)
				world->delete_node(n);
			for (auto& ctrm : cellsToremove)
				world->delete_cell_manually(world->unpack_cell_and_chunk(ctrm));

		}
		world->delete_cell_manually(me.botInfo.cellLookingAt);
	}
}
void MainEvents::CastRayEditor()
{
	me.botInfo.cellLookingAt = 0;
	me.botInfo.currentCubeFace = CubeFaces::NONE;
	me.botInfo.currentCubeIntersection = 0;

	me.botInfo.cellLookingAt = world->cast_world_ray(me.position.posHead, me.uvec, 300, me.botInfo.currentCubeFace, me.botInfo.currentCubeIntersection);
}
void MainEvents::CreateElevator()
{
	if (!input->IsKeyToggled(MyKeysEnum::CREATE_ELEVATOR_KEYS) || !world)
		return;

	world->create_elevator(me.bot.myCellCoordinates);
}
void MainEvents::MapEditor()
{
	if (!world)
		return;

	if (input->IsKeyToggled(MyKeysEnum::SWITCH_MODE_EDITOR_NORMAL_KEYS))
	{
		if (configFlags & ConfigFlags::SET_MAP_EDITOR_ENABLED)
			rw->configFlags &= ~ConfigFlags::SET_MAP_EDITOR_ENABLED;
		else
			rw->configFlags |= ConfigFlags::SET_MAP_EDITOR_ENABLED;
	}

	if (!(configFlags & ConfigFlags::SET_MAP_EDITOR_ENABLED) || isRobot || !world)
		return;
	draw->bold28->Print(draw->viewport[2] / 1.4 -100, 150, RGB::yellow, "MAP EDITOR MODE");

	ManuallySaveMap();

	CastRayEditor();
	MapEditorAddCell();
	MapEditorDeleteCell();
	CreateElevator();
	//MapEditorDeleteIsland();

}
