#pragma once


#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <sstream>  
#include <iterator>
#include <cmath>

#include "utils.h"
#include "ReadWrite.h"
#include "Draw.h"
#include "SharedMemory.h"
#include "Addresses.h"
#include "Entity.h"
#include "Action.h"
#include "Input.h"
#include "MapReader2.h"

#define ENABLE_TIMERS
#define DEBUG

constexpr int MAX_BUILD_ITEMS = 32;
constexpr int MAX_PLAYERS = 32;
constexpr int MAX_ENTITIES = 1024;
constexpr int MAX_MISSILES = 128;
constexpr int VISIBILITY_REFRESHRATE = 5; //every N frames
constexpr int REFRESH_PATH_TIME = 400;
constexpr int SABER_DANGER_DISTANCE = 200;
constexpr int PUSH_DISTANCE = 550;
constexpr int PULL_DISTANCE = 550;

class MainEvents
{
public:
	MainEvents(Draw* _draw, Input* _input);
	~MainEvents();
	void MainLoop();
	void BotLoop();
	void Init(Addresses* _addresses, Draw* _draw, ReadWrite* _rw, const bool& _isRobot, 
		const bool& _isConfigRefreshed, const bool& _isGameUnminimised);
	void DrawUI();
	void RestoreBinds();
private:
	//ui
	void DrawPlayerInfo();
	void DrawPredictedTrajectories();
	void DrawSsetMyLocation();
	void DrawMyPathStats();
	void SetTimers();
	void DrawDamage(Player& player);
	void GetBuild();
	void DrawBulletTrace();
	void DrawBotStates();
	void DrawTargetCube();
	void DrawLookingAtCube();
	void DrawMinionPaths();
	//ui

	//console
	void MakeFriendsAndEnemies();
	void AddFriend(Player* p);
	void ClearLeaders();
	void DeleteLeader(const int& id);
	void MakeLeader(const int& id);
	void AddFriend(const int& id);
	void AddTarget(Player* p);
	void AddTarget(const int& id);
	std::string ToLowerCase(const std::string& str);
	void DeathMessage();
	void FunnyReplies();
	void MakeFollowleader();
	void ReadConsoleCommands();
	void ReadLastLineConsole();
	void GetPlayerNames();
	//console
	void SortPLayersAngle();
	//init weapons
	float ExtremeAngleAdjustment(const float& angleSetY);
	double AngleBetween(const float& X, const float& Y);
	void GetAimAngles(const Vec3& from, const Vec3& to, const float& yaw, const float& pitch, float& yawSet, float& pitchSet);
	void GetAimVals();
	void TestLookingAtMe(Player& p);
	void AntiTk(Player& p, const float& travelTime);
	void CalculateMuzzleOffset();
	void ChangeTargetTeamToOpposite(Player& p);
	void InitializeWeapons();
	//init weapons

	//writesahreddata
	void WriteSDBotToLeader(PlayersToSend& playersData);
	void WriteSDLeaderToBot(PlayersToSend& playersData);
	void WriteSDCommon(PlayerData& playerData, const Player& p);
	void WriteSharedData();
	void ReadSDLeaderFromBot(PlayersToSend& playersData);
	void ReadSDCommon(PlayerData& playerData, const int& playerIndex);
	void ReadSDBotFromLeader(PlayersToSend& playersData);
	void ReadSharedData();

	//aim
	void GetPlayerTrajectory(Player* p);
	Player* ChooseClosestVisibleTarget();
	void SelectNewTarget(Player*& target, Player* oldTarget);
	void AimLockThisTarget(const float& angleHor, const float& angleVert);
	Player* SmartChooseTarget();
	void Aim();

	void GetFps();
	void GetColors();
	void GetPlayerInfo();
	void SenseWH();
	void MakeMyModelTransparent();
	void OnRoundBegin();
	void VisibilityChecker();
	void TestCrouch(Player& ent);
	void CrouchWhenAttacked();
	void AutoDodge();
	bool BindUnbindAttackButtons();
	void ShootNoSpread();
	void NoSpread();
	void GetMapNamePath();
	void IsServerTick();
	uintptr_t GetEntAddressFromId(const uint16_t& id);
	void DrawProbeRay();
	void PredictMissilePath();
	void GetTrajectory(const Vec3& startPos, const Vec3& startVelocity,
		const float& timeLimit, std::vector<Vec3>& traj, const TRAJECTORY_TYPE& trajType,
		const uint32_t& trajectoryFlags, Vec3& lastNormal, Vec3& lastPoint);
	void MissilePaths();
	void GetMaxPlayerId();
	void InitializeMissiles();
	void SwitchSpectator();
	void GetLookingAtCells();
	void InitializePlayers();

	//botstuff
	void AttemptToAddNewArea();
	void ReadSavedMap();
	void ManuallySaveMap();
	void DeleteWorld();
	void TriggerStuff();
	void GenerateWorld();
	void FillMoverEnts();
	void CheckMoversForChange();
	void DoorProbe();
	void GetMyCell();
	Cell* GetNESWPositionCell(const Vec3& uvec, const Vec3& position);
	Cell* GetNESWPositionCells(const Vec3& uvec, const Vec3& position);
	void GetNESWPositionLeaderCells(Player* p);
	void GetPlayerCells();
	void GetTargetCell();
	void AddWeightToPlayerNode();
	void Elections();
	void PerfectAimBot(const bool& isFire, const bool& altFire);
	void RollIfOnFire();
	void SelectWeapon();
	void BotAttack();
	void ErasePath();
	void EraseAllTargetsAndPath();
	void FlattenPath(std::vector<Vec3>& navPathPoints);
	bool DontWalkOnElevator(const GraphNode* currentNode);
	void ChangePointHeight(Vec3& currentPoint, const GraphNode* currentNode);
	void GetNavigationPathPoints();
	void GenerateMinionPath();
	void DeleteCurrentDestination();
	Cell* SelectDestination(Cell* myCell);
	void CheckElevatorPath();
	bool GenerateNewPathCooldown();
	void GeneratePath();
	bool CompareChunkByDistance(const uint32_t& _ch1, const uint32_t& _ch2);
	bool SortChunksForRoam(Cell* spawnCell);
	bool GetSpawnChunk();
	void Roam();
	bool IsPathTooFarAway(const Vec3& currentPoint);
	bool PointReachCondition(const Vec3& point, GraphNode* currentNode);
	bool GoToPoint(const Vec3& point, GraphNode* currentNode);
	bool IsNextElevatorTriggerOff();
	bool IsNextPointReachedTimeout(GraphNode* currentNode);
	void RemovePassedElevatorTriggers();
	bool SkipPath(const Vec3& currentPoint);

	void FollowCurrentPath();
	void BotMovement();
	void RetryRouteIfStandingStill();
	void AuthorizeBotRequestActions();
	void AntiJediWook();
	void AntiStuck();
	void Strafe();
	void GrenadeDodge();
	void SaberEvade();
	Vec3 GetOffsetPoint(const Vec3& position, bool keyW, bool keyS, bool keyA, bool keyD);
	void AutoJumpCrouch();

private:
	void CastRayEditor();
	void DrawTriggers();
	void DrawInfoBlock();
	void MapEditorAddCell();
	void MapEditorDeleteCell();
	void MapEditorDeleteIsland();
	void CreateElevator();
	void MapEditor();

	Utils::_SendConsoleCommand sendConsoleCommand;
	Utils::Tracer tracer;
	Draw* draw = nullptr;
	Input* input = nullptr;
	Addresses* add = nullptr;
	World* world = nullptr;
	//MapReader* mapReader = nullptr;
	MapReader2* mapReader = nullptr;

	std::array<Player, MAX_PLAYERS> players;
	std::vector<Player*> sortedPlayers;
	std::unordered_map<int, Missile> missiles;
	std::vector<uintptr_t> navigationPath;
	std::vector<Vec3> navigationPathPoints;
	std::vector<Vec3> navigationPathPointsUnedited;
	std::vector<int> misTodelete;
	std::vector<int> tickedAltAccounts;
	std::unordered_map<int, ExplosionData> explosions;


	Me me;
	ReadWrite* rw = nullptr;
	Action act;

	bool isRobot = false;
	bool isConfigRefreshed = false;
	bool isGameUnminimised = false;
	bool IS_TK = false;
	bool isConsoleOpen = false;
	bool isRoundBegin = false;
	bool testQuit = false;
	bool reloadMapNow = false;
	bool reloadBotMaps = false;
	bool reloadThisBotMap = false;
	bool isReplyRoger = false;
	bool isReplyYes = false;
	bool isReplyThanks = false;
	bool isReplySorry = false;
	bool isReplyHelp = false;
	bool isServerTicked = false;
	//bool isReadMap = false;
	//bool isMapChange = false;

	int maxPlayerId = 0;
	size_t currentFrame = 0;
	int fps = 120;
	int menuRefreshRate = 1;
	size_t gameTime = 0;
	uint32_t playerOffset = 0;
	uint32_t classOffset = 0;
	uint32_t configFlags = 0;
	uint32_t wallhackFlags = 0;
	uint32_t botConfigFlags = 0;
	uint32_t worldFlags = 0;
	uint32_t pathfindingFlags = 0;
	PathfindingErrors generatedPathLastError = PathfindingErrors::NONE;

	std::string lastLineOfconsole;

	Utils::MrTimer timeRandomStuff;
	Utils::MrTimer initializePlayersTimer;
	Utils::MrTimer initializeEntsTimer;
	Utils::MrTimer predictMissileTimer;
	Utils::MrTimer totalMainEventTimer;
	Utils::MrTimer getKeysTimer;
	Utils::MrTimer CheckVisibilityTimer;
	Utils::MrTimer setWeaponsTimer;
	Utils::MrTimer readSharedMemoryTimer;
	Utils::MrTimer drawPlayerInfoTimer;
	Utils::MrTimer lastNameInsertionTimer;
	Utils::MrTimer noSpreadFireTimer;
	Utils::MrTimer sharedMemoryReaderDelayTimer;
	Utils::MrTimer spectatorSwitchTimer;
	Utils::MrTimer restartPathfinderTimer;
	Utils::MrTimer botFireTimer;
	Utils::MrTimer unstuckTimer;
	Utils::MrTimer grenadeEvasionTimerReset;
	Utils::MrTimer jumpCrouchTimer;
	Utils::MrTimer elevatorStuckTimer;
	Utils::MrTimer nextNodeReachTimer;
	Utils::MrTimer retryPressingElevatorButtonTimer;
	Utils::MrTimer generateNewPathCoolDownTimer;

	//Utils::MrGameTimer shootCoolDownTimer;

	Utils::MrTimer tempTimer;

	std::string currentMap;
	std::wstring currentMapW;
	std::wstring currentMapPath;

	Utils::MrTimer fpsTimer;

	UI ui;


	struct BulletTrajectory
	{
		Vec3 start, end;
	};
	std::vector<BulletTrajectory> bulletTrajectoriesToDraw;

	SharedMemory<PlayersToSend> otherClientData;
};

