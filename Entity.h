#pragma once
#include <glad/glad.h>
#include <string>
#include <regex>
#include <array>
#include <set>

#include "Utils.h"
#include "Addresses.h"
#include "Vectors.h"
#include "NavMesh.h"


enum class TargetCells
{
    NONE,
    EXPLOSION_TARGET_CELL,
    ANTI_SABER_TARGET_CELL,
    ELEVATOR_BUTTON_TARGET_CELL,
    MANUAL_TARGET_CELL,
    ORDER_TARGET_CELL,
    PLAYER_TARGET_CELL,
    ROAM_TARGET_CELL,
};

static std::map<TargetCells, std::string> TargetCellNames
{
    {TargetCells::NONE, "NONE"},
    {TargetCells::MANUAL_TARGET_CELL, "MANUAL_TARGET_CELL"},
    {TargetCells::ORDER_TARGET_CELL, "ORDER_TARGET_CELL"},
    {TargetCells::PLAYER_TARGET_CELL, "PLAYER_TARGET_CELL"},
    {TargetCells::ROAM_TARGET_CELL, "ROAM_TARGET_CELL"},
    {TargetCells::EXPLOSION_TARGET_CELL, "EXPLOSION_TARGET_CELL"},
    {TargetCells::ANTI_SABER_TARGET_CELL, "ANTI_SABER_TARGET_CELL"},
    {TargetCells::ELEVATOR_BUTTON_TARGET_CELL, "ELEVATOR_BUTTON_TARGET_CELL"},
};

enum class BotLeaderPosition
{
    LEFT,
    RIGHT,
    BACK,
    FORWARD,
};


class Missile;
class Player
{
public:
    struct WeaponInfo
    {
        Weapons num;
        float speed;
        float fireRate = 100;
    };
    struct Position
    {
        Vec3 posDefault = 0;
        Vec3 posFeet = 0;
        Vec3 posCrotch = 0;
        Vec3 posChest = 0;
        Vec3 posGun = 0;
        Vec3 posAim = 0;
        Vec3 posHead = 0;

        //Position() = default;
    };
    struct GridPosition
    {
        CellCoordinates cellCoordinates;
        CellCoordinates factualCellCoordinates;
        int previousOccupiedGraphNodeWeight = 0;
        GraphNode* previousOccupiedGraphNode = nullptr;

        std::unordered_map<BotLeaderPosition, CellCoordinates> leaderBotSlots
        {
            {BotLeaderPosition::RIGHT, {0,0}},
            {BotLeaderPosition::LEFT, {0,0}},
            {BotLeaderPosition::BACK, {0,0}},
            {BotLeaderPosition::FORWARD, {0,0}},
        };
    };
    struct ScreenInfo
    {
        Vertex2 screenSpacePos;
        Vertex2 predictedScreenSpacePos;
        Vertex2 posSymbol;
        Vertex2 posText;
        float symbolScale = 1;

        float screenColor[4];
        float lineWidth = 2;
    };
    struct PlayerModel
    {
        float defaultModelHeight = 64.118f;
        float defaultModelWidth = 30.0f;
        float modelHeight = 0;
        float modelWidth = 0;
        Vec3 bottom = 0, top = 0;
        Vec3 min{-7,-14, 0}, max{ 7,14, 0 };
    };
    struct Angles
    {
        Vec2 this_target_to_me;

        Vec2 me_to_this_target;
        float me_to_this_target3D = 0;
        float this_target_to_me3D = 0;
    };
    struct Distances
    {
        float distance3 = 0;
        float distance2 = 0;
    };
    struct BotInfo
    {
        int minionId = -1;
        CubeFaces currentCubeFace = CubeFaces::NONE;
        Vec3 currentCubeIntersection = 0;

        std::vector<uint32_t> cellsAroundSaber;
        CellCoordinates cellLookingAt = {0,0};
        CellCoordinates cellLookingAtSave = { 0,0 };
        CellCoordinates minionDestination{ 0,0 };
        CellCoordinates oldMinionDestination{ 0,0 };
        std::vector<uintptr_t> minionNavigationPath;
    };

	Player();
	~Player();
	void RefreshValues(const uint32_t& _playerOffset, const uint32_t& _classOffset, Addresses* a, const bool& isRoundBegin, const bool& isRobot);
    void FillDeka(const uintptr_t& memLoc, Addresses* a);

    uint32_t targetFlags = 0;
	uint32_t playerFlags = 0;
    uint32_t permanentPlayerFlags = 0;
	uint32_t playerOffset;
	uint32_t classOffset;

    EntClass entClass;
    Stances stance;
    Stances2 stance2;

	int id = 0;
    int entityNum = 0;
    Teams team;
	int charScale = 0;
    int hp = 0;
    int previousHp = 0;
    int damage = 0;
    int surface = 0;
    int swordOn = 0;
    int saberAnim = 0;

    int showDamaeMs = 400;

    bool isDrawDamage = false;
    bool isPreviousAlive = false; //TEMP
    bool isInstantDeathFlag = false;
    bool isRespawnFlag = false;

    std::string name;
    std::string oldName;
    std::string shortName;

    Vec3 speed;
    Vec3 uvec;

    float maxSpeed = 0;
    float pitch = 0;
    float yaw = 0;
    float speedMag = 0;
    float projTravelTimeToThisTarget = 0;
    float timeUnmoved = 0;
    float timeAlive = 0;

    Vec3_ui8 colors;

    Position position;
    Position predictedPosition;
    ScreenInfo screenInfo;
    WeaponInfo wpInfo;
    PlayerModel playerModel;
    Angles angles;
    Distances distances;
    Distances predictedDistances;
    GridPosition gridPosition;
    BotInfo botInfo;
    Utils::MrTimer hpTimer;
    
private:
    Utils::MrTimer moveTimer;
    Utils::MrTimer aliveTimer;

    void ModelHeightAdjustment();
    void GetShortName();
};

class Me : public Player
{
public:
    struct CollisionData
    {
        std::vector<Vec3> trajectory;
        Vec3 lastNormal;
    };

    struct ClosestPlayer
    {
        Player* player = nullptr;
        Player* enemy = nullptr;
        Player* teammate = nullptr;
    };

    struct Bot
    {
        uintptr_t myPid = 0;

        std::set<uintptr_t> allBotPids;
        std::unordered_set<uintptr_t> allBotIds;
        std::unordered_set<uintptr_t> minionIds;
        std::map<int, CellCoordinates> currentTriggersInPath;

        BotLeaderPosition botLeaderPosition = BotLeaderPosition::LEFT;

        CellCoordinates myCellCoordinates{ 0,0 };
        CellCoordinates myLastValidCellCoordinates{ 0,0 };
        CellCoordinates myFactualCellCoordinates{ 0,0 };
        CellCoordinates spawnCellCoordiantes{ 0,0 };
        CellCoordinates myOldTargetCoordinates{ 0,0 };
        CellCoordinates myOldPlayerCoordinates{ 0,0 };


        std::map<TargetCells, CellCoordinates> tgtCells
        {
            {TargetCells::ANTI_SABER_TARGET_CELL, {0,0}},
            {TargetCells::EXPLOSION_TARGET_CELL, {0,0}},
            {TargetCells::ORDER_TARGET_CELL, {0,0}},
            {TargetCells::MANUAL_TARGET_CELL, {0,0}},
            {TargetCells::ELEVATOR_BUTTON_TARGET_CELL, {0,0}},
            {TargetCells::PLAYER_TARGET_CELL, {0,0}},
            {TargetCells::ROAM_TARGET_CELL, {0,0}},        

        };
        CellCoordinates myOldDestination = {0,0};
        TargetCells selectedDestination = TargetCells::NONE;
        TargetCells oldSelectedDestination = TargetCells::NONE;

        uint16_t entityAhead = 0;
        uint16_t oldEntityAhead = 0;

        uint32_t currentStep = 0;

        uint32_t botStateFlag = BotStateFlags::BOT_STATE_IDLE;

        Player* enemyTarget = nullptr;

        uint32_t newCellFlag = CellFlags::NONE;
        GLfloat specialCellColor[4] = { 1, 1, 1,0.6 };

        bool isAltAttaking = false;
        bool isBotShooting = false;
        bool isJediDanger = false;
        bool isJediSaberDanger = false;
        bool ignoreElevators = false;
        bool calledElevatorForButton2 = false;
        bool isButtonPressed = false;
        
        float targetDistanceCrowFlight = 0;
        float targetDistance = 0;

        uint8_t isBotStuckBackOrForward = 0;

        float pathTurnAngleX = 0;
        float pathTurnAngleY = 0;
        float distanceKeep = 100;
        float distanceRetreat = 70;
        float saberDistanceKeep = 200;
        float refreshTargetTimeLimit = 2000;
        float distanceTargetFromMeToBots = 70;
        float reachNextNodeDistance = 20;
        float generateNewPathCooldown = 250;

        Utils::MrTimer strafeTimer;
        Utils::MrTimer newTargetTimer;
        Utils::MrTimer elevatorButtonPressDelay;
        Utils::MrTimer timeSpentOnBadCellTimer;
        Utils::MrTimer elevatorCallCoolDown;
        Utils::MrTimer elevatorSecondTimeButtonPressDelay;
        Utils::MrTimer standingStillTimer;
        Utils::MrTimer stuckTimer;

        Weapons previousWeapon = Weapons::WP_NONE;
    };

	Me() : Player() {};
	void FillMe(const bool& isRoundBegin, Addresses* a);
    void GetConfig(Addresses* a);

    uint32_t myFlags;

    int trueId;
    int forceFocusedId;
    int ping;
    int leftAmmo;
    int clipAmmo;
    int clipSize;
    int sbdBattery;

    GameModes gameMode;
    Bot bot;

    float editPitch;
    float editYaw;

    //MyConfig myConfig;
    std::unordered_map<ConfigVals, int> myConfig;
    CollisionData colData;
    ClosestPlayer closestPlayer;

    Utils::MrTimer projectileRifleFireTimer;
    Utils::MrTimer onFireTimer;
private:

};

struct ExplosionData
{
    ExplosionData(const float& _expirationTime, const float& _radius, const Vec3& _location, const int& _realId, const Weapons& _weaponType)
        : radius(_radius), expirationTime(_expirationTime), location(_location), realId(_realId), weaponType(_weaponType)
    {
        time.Start();
    }
    bool TimeLeft()
    {
        timePassed = time.ElapsedCurrentMs();
        if (timePassed > expirationTime)
            return true;

        return false;
    }
    std::vector<uint32_t> dangerCells;
    Vec3 location = 0;
    float radius = 0;
    float timePassed = 0;
    int realId = 0;
    Weapons weaponType = Weapons::WP_NONE;
private:
    Utils::MrTimer time;

    float expirationTime = 0;
};

class Missile
{
public:
    Missile() {}
    ~Missile();
    void Refresh(uintptr_t& loc, const std::array<Player, 32>& players);
    void Clear();

    uintptr_t baseAddress;

    Vec3 pos;
    Vec3 startPos;
    Vec3 velVec;
    Vec3 destination;
    Vec3 destinationNormal;
    float misSpeed = 0;
    float angleXY = 0;
    float gameTime = 0;

    Weapons parentGun = Weapons::WP_NONE;
    uint8_t parentEnt = 0;
    uint8_t parentTeam = 0;
    TRAJECTORY_TYPE trajectoryType = TRAJECTORY_TYPE::TR_STATIONARY;

    uint16_t id = 0;

    Teams team;

    uint32_t missileFlags = 0;

    float lifeTime = 0;
    float radius = 0;

    bool isSpawned = false;
    uint32_t uniqueId = 0;

    std::vector<Vec3> trajectory;
private:
    void GetLifeTime();
    void GetRadiusAndLifeTime();


};
