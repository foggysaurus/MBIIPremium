#include "Entity.h"

Player::Player()
{

}
Player::~Player()
{

}
void Player::RefreshValues(const uint32_t& _playerOffset, const uint32_t& _classOffset, Addresses* a, const bool& isRoundBegin, const bool& isRobot)
{
    targetFlags = 0;
    playerFlags = 0;

    playerOffset = _playerOffset;
    classOffset = _classOffset;
    uintptr_t base = a->entBase + playerOffset;

    id = *(int*)(base);

    entClass = *(EntClass*)(a->enClass + classOffset);
    team = *(Teams*)(a->team + classOffset);
    name = (char*)(a->team + classOffset - 0x40);
    charScale = *(int*)(base + 0x14C);
    position.posDefault = *(Vec3*)(base + 0x5A8);
    hp = *(int*)(base + 0x170);
    surface = *(int*)(base + 0xC4);
    swordOn = *(int*)(base + 0x100);

    speed = *(Vec3*)(base + 0x28);
    maxSpeed = *(float*)(base + 0xA8);
    colors = *(Vec3_ui8*)(base + 0x160);
    pitch = *(float*)(base + 0x40);
    yaw = *(float*)(base + 0x44);
    stance = *(Stances*)(base + 0x12C);
    stance2 = *(Stances2*)(base + 0x130);
    saberAnim = *(int*)(base + 0xF8);
    wpInfo.num = *(Weapons*)(base + 0x128);

    speedMag = vecs::VecMagnitude(speed);

    GetShortName();

    if (entClass == EntClass::CL_SITH && *(int*)a->trueId != 1)
    {
        bool adsad = *(bool*)(base + 0x448);
        int a = 3;
    }

    if (*(bool*)(base + 0x448))
        playerFlags |= PlayerFlags::IS_RENDERED;
    if (*(bool*)(base + 0x10C) && entClass != EntClass::CL_NONE && stance != Stances::NONE && wpInfo.num != Weapons::WP_NONE)
        playerFlags |= PlayerFlags::IS_ALIVE;
    if (!(playerFlags & PlayerFlags::IS_ALIVE) && *(int*)a->trueId != id)
        return;

    if (*(int*)(base + 0xE4) == 3)
        playerFlags |= PlayerFlags::IS_SHOOTING;
    if (charScale == 0)
        charScale = 100;

    if ((!hp || hp > 500) && ((entClass == EntClass::CL_SOLDREB) || (entClass == EntClass::CL_SOLDIMP)))
        hp = 50;
    else if ((!hp || hp > 500) && ((entClass == EntClass::CL_ETREB) || (entClass == EntClass::CL_ETIMP)))
        hp = 80;
    else if ((!hp || hp > 500) && entClass == EntClass::CL_WOOK)
        hp = 450;
    else if ((!hp || hp > 500) && entClass == EntClass::CL_CLONE)
        hp = 80;
    else if (!hp || hp > 500)
        hp = 100;

    isDrawDamage = false;

    if (isRoundBegin)
    {
        previousHp = hp;
        damage = 0;
    }
    if (hp != previousHp)
    {
        isDrawDamage = true;
        damage = hp - previousHp;
        previousHp = hp;
    }

    position.posFeet = position.posDefault;
    position.posChest = position.posDefault;
    position.posCrotch = position.posDefault;
    position.posHead = position.posDefault;
    position.posGun = position.posDefault;

    uvec = vecs::GetUnitVector(pitch, yaw);

    if (
        stance == Stances::CROUCH
        || stance == Stances::CROUCH_WAD
        || stance == Stances::CROUCH_S
        || stance == Stances::MEDITATE
        )
        playerFlags |= PlayerFlags::IS_CROUCHING;
    else if (
        stance == Stances::FALLEN
        || stance == Stances::SOLD_GETUP
        || stance == Stances::GETUP_W
        || stance == Stances::GETUP_S
        || stance == Stances::ROLL_A
        || stance == Stances::ROLL_D
        )
        playerFlags |= PlayerFlags::IS_FALLEN;

    if (stance2 == Stances2::BLOCK_BLUE
        || stance2 == Stances2::BLOCK_RED
        || stance2 == Stances2::BLOCK_CYAN
        || stance2 == Stances2::BLOCK_DUALS
        || stance2 == Stances2::BLOCK_YELLOW
        || stance2 == Stances2::BLOCK_PURPLE
        || stance2 == Stances2::BLOCK_STAFF
        )
        playerFlags |= PlayerFlags::IS_SABERBLOCKING;

    if (stance == Stances::WALK_S
        || stance == Stances::WALK_WAD
        )
        playerFlags |= PlayerFlags::IS_RUNNING;

    if (playerFlags & PlayerFlags::IS_SHOOTING)
        playerFlags |= PlayerFlags::IS_SHOOTING;

    if (playerFlags & (PlayerFlags::IS_RENDERED)
        && wpInfo.num != Weapons::WP_NONE
        && entClass != EntClass::CL_NONE
        && stance != Stances::NONE
        && playerFlags & (PlayerFlags::IS_RENDERED)
        && playerFlags & (PlayerFlags::IS_ALIVE)
        && *(int*)a->trueId != id
        )
        playerFlags |= PlayerFlags::IS_VALID;

    if (stance == Stances::JET_W
        || stance == Stances::JET_S
        || stance == Stances::JET_A
        || stance == Stances::JET_D
        || stance == Stances::JET_IDLE
        )
        playerFlags |= PlayerFlags::IS_JETPACK;

    if (!isRobot && (playerFlags & PlayerFlags::IS_RENDERED))
        playerFlags |= PlayerFlags::IS_RENDERED_ON_MAIN_WINDOW;

    timeUnmoved = moveTimer.ElapsedContinuous();
    timeAlive = aliveTimer.ElapsedContinuous();

    if (!(playerFlags & PlayerFlags::IS_ALIVE))
    {
        aliveTimer.Stop();
        timeAlive = 0;
    }


    isInstantDeathFlag = false;
    isRespawnFlag = false;
    bool test = (playerFlags & PlayerFlags::IS_ALIVE);
    if (isPreviousAlive != test)
    {
        isPreviousAlive = test;
        if (!(playerFlags & PlayerFlags::IS_ALIVE))
            isInstantDeathFlag = true;
        else
            isRespawnFlag = true;
    }

    if (speedMag > 40)
    {
        moveTimer.Stop();
    }

    ModelHeightAdjustment();
}
void Player::ModelHeightAdjustment()
{
    float modelHeight = playerModel.defaultModelHeight;

    modelHeight = modelHeight * (float)(charScale / 100.0f);
    playerModel.modelHeight = modelHeight;
    playerModel.modelWidth = playerModel.defaultModelWidth;

    float multiplierForSmallerModels = 1;
    if (charScale > 100)
        multiplierForSmallerModels = 1;
    else
        multiplierForSmallerModels = (float)(charScale / 100.0f);

    position.posFeet.z -= modelHeight / 3.1f;

    position.posCrotch.z = position.posFeet.z;
    position.posChest.z = position.posFeet.z;
    position.posHead.z = position.posFeet.z;
    position.posGun.z = position.posFeet.z;

    position.posCrotch.z += modelHeight * 0.4f;
    position.posChest.z += modelHeight * 0.63 * multiplierForSmallerModels;
   // position.posHead.z += modelHeight * 0.92f;
    position.posHead.z += modelHeight * 0.84f;
    position.posGun.z += modelHeight * 0.71 + modelHeight / 12.25f;


    playerModel.bottom = position.posFeet; playerModel.bottom.z -= 2.0f;
    playerModel.top = playerModel.bottom; playerModel.top.z += modelHeight;


    if (playerFlags & PlayerFlags::IS_CROUCHING)
    {
        position.posChest.z -= modelHeight / 3.0f;
        position.posHead.z -= modelHeight / 3.0f;
        position.posGun.z -= modelHeight / 3.4f;
        position.posAim.z = position.posChest.z;
        playerModel.top.z -= modelHeight / 3.0f;
    }

    if (playerFlags & PlayerFlags::IS_FALLEN)
    {
        position.posChest.z -= modelHeight / 1.6f;
        position.posHead.z -= modelHeight / 1.6f;
        position.posGun.z -= modelHeight / 1.6f;
        position.posAim.z = position.posChest.z;
        playerModel.top.z -= modelHeight / 1.6f;
    }

    //pos.aimPos = pos.posChest;
    if (entClass == EntClass::CL_DEKA)
        position.posAim = position.posCrotch;
}
void Player::GetShortName()
{
    if (oldName == name)
        return;
    std::regex regex("[\\^][0-9]");
    shortName = std::regex_replace(name, regex, "");
    oldName = name;
}
void Player::FillDeka(const uintptr_t& memLoc, Addresses* a)
{
    if (*(int*)(memLoc + 0x214))
    {
        playerFlags |= PlayerFlags::IS_ALIVE;
        playerFlags |= PlayerFlags::IS_RENDERED;
        if (*(int*)a->trueId != id)
            playerFlags |= PlayerFlags::IS_VALID;
    }

    stance = *(Stances*)(memLoc + 0x128);
    pitch = *(float*)((memLoc + 0x3C));
    yaw = *(float*)((memLoc + 0x3C + 4));


    position.posDefault = *(Vec3*)((memLoc + 0x18));

    position.posChest = position.posDefault;
    position.posCrotch = position.posDefault;
    position.posFeet = position.posDefault;
    position.posHead = position.posDefault;
    position.posGun = position.posDefault;

    speed = *(Vec3*)((memLoc + 0x24));

    entityNum = *(int*)(memLoc + 0xE4);

    ModelHeightAdjustment();
}


void Me::FillMe(const bool& isRoundBegin, Addresses* a)
{
    myFlags = 0;
    bot.botStateFlag = 0;

    trueId = *(int*)a->trueId;
    forceFocusedId = *(int*)(a->forceFocused + trueId * playerOffset);
    editPitch = *(float*)(a->myRawPitch);
    editYaw = *(float*)(a->myRawYaw);
    ping = *(int*)(a->ping);
    gameMode = *(GameModes*)a->gameMode;
    //clipAmmo = *(int*)a->ammo;
    leftAmmo = *(int*)(a->ammo + classOffset);
    clipAmmo = *(int*)(a->ammo + classOffset +4);
    clipSize = *(int*)(a->ammo + classOffset + 8);
    sbdBattery = *(int*)a->sbdBattery;
    uvec = *(Vec3*)a->lookingToUVec;

    if (*(int*)(a->isNoclip))
        myFlags |= (uintptr_t)MyFlags::IS_NOCLIP;
    if (*(int*)(a->IsScope))
        myFlags |= (uintptr_t)MyFlags::IS_SCOPE;
    if (*(int*)(a->IsAltFire) & 0x10000)
        myFlags |= (uintptr_t)MyFlags::IS_ALTFIRE;
    if (*(bool*)(a->crouch))
        myFlags |= (uintptr_t)MyFlags::IS_CROUCH;
    if (*(bool*)(a->att))
        myFlags |= (uintptr_t)MyFlags::IS_ATTACK;
    if (*(bool*)(a->altAttack))
        myFlags |= (uintptr_t)MyFlags::IS_ALTATTACK;
    if (*(bool*)(a->speed))
        myFlags |= (uintptr_t)MyFlags::IS_SPEED;
    if (*(bool*)(a->w))
        myFlags |= (uintptr_t)MyFlags::IS_W;
    if (*(bool*)(a->a))
        myFlags |= (uintptr_t)MyFlags::IS_A;
    if (*(bool*)(a->s))
        myFlags |= (uintptr_t)MyFlags::IS_S;
    if (*(bool*)(a->d))
        myFlags |= (uintptr_t)MyFlags::IS_D;
    if (*(bool*)(a->button12))
        myFlags |= (uintptr_t)MyFlags::IS_RELOADING;
    if (*(int*)(a->isOnFire + trueId * playerOffset) == 2)
        myFlags |= (uintptr_t)MyFlags::IS_ONFIRE;

    if (isRoundBegin)
    {
        GetConfig(a);
    }
}
void Me::GetConfig(Addresses*a)
{
    std::string config = (char*)(a->config);
    if (config.empty())
        return;
    int spaceCounter = 0;
    size_t configStartPos = 0;
    size_t configEndPos = 0;
    for (size_t i = 0; i < config.size(); i++)
    {
        if (config[i] == '-')
            spaceCounter++;
        if (spaceCounter == 2) { configStartPos = i; break; }
    }
    for (size_t i = configStartPos + 1; i < config.size(); i++)
    {
        if (config[i] == ' ')
        {
            configEndPos = i; break;
        }
    }

    config = config.substr(configStartPos + 1, configEndPos - configStartPos - 1);

    //MyConfig tempCfg;
    //myConfig = tempCfg;
    myConfig.clear();

    if (gameMode == GameModes::LEGENDS || gameMode == GameModes::FULL_AUTHENTIC || gameMode == GameModes::DUEL || config.size() < 17)
    {
        return;
    }

    switch (entClass)
    {
    case EntClass::CL_SOLDREB:
    {
        myConfig[ConfigVals::PISTOL]        = config[1]  - '0';
        myConfig[ConfigVals::E11]           = config[3]  - '0';
        myConfig[ConfigVals::REINFORCEMENT] = config[10] - '0';
        myConfig[ConfigVals::FRAG]          = config[0]  - '0';
        myConfig[ConfigVals::CONC]          = config[14] - '0';
        myConfig[ConfigVals::CLOSE_COMBAT]  = config[17] - '0';
        myConfig[ConfigVals::ARMOR]         = config[15] - '0';
        myConfig[ConfigVals::AMMO]          = config[16] - '0';
    }
    break;
    case EntClass::CL_SOLDIMP:
    {
        myConfig[ConfigVals::PISTOL]        = config[1]  - '0';
        myConfig[ConfigVals::E11]           = config[3]  - '0';
        myConfig[ConfigVals::REINFORCEMENT] = config[6]  - '0';
        myConfig[ConfigVals::FRAG]          = config[13] - '0';
        myConfig[ConfigVals::CONC]          = config[14] - '0';
        myConfig[ConfigVals::CLOSE_COMBAT]  = config[17] - '0';
        myConfig[ConfigVals::ARMOR]         = config[15] - '0';
        myConfig[ConfigVals::AMMO]          = config[16] - '0';
    }
    break;
    case EntClass::CL_ETREB:
    {
        myConfig[ConfigVals::PISTOL]        = config[1]  - '0';
        myConfig[ConfigVals::E11]           = config[3]  - '0';
        myConfig[ConfigVals::A280]          = config[5]  - '0';
        myConfig[ConfigVals::REINFORCEMENT] = config[10] - '0';
        myConfig[ConfigVals::RALLY]         = config[4]  - '0';
        myConfig[ConfigVals::SONIC]         = config[9]  - '0';
        myConfig[ConfigVals::DODGE]         = config[0]  - '0';
        myConfig[ConfigVals::FRAG]          = config[17] - '0';
        myConfig[ConfigVals::ARMOR]         = config[15] - '0';
        myConfig[ConfigVals::AMMO]          = config[16] - '0';
    }
    break;
    case EntClass::CL_ETIMP:
    {
        myConfig[ConfigVals::PISTOL]        = config[1]  - '0';
        myConfig[ConfigVals::E11]           = config[3]  - '0';
        myConfig[ConfigVals::T21]           = config[7]  - '0';
        myConfig[ConfigVals::REINFORCEMENT] = config[6]  - '0';
        myConfig[ConfigVals::RALLY]         = config[8]  - '0';
        myConfig[ConfigVals::FIRE]          = config[14] - '0';
        myConfig[ConfigVals::DODGE]         = config[13] - '0';
        myConfig[ConfigVals::FRAG]          = config[17] - '0';
        myConfig[ConfigVals::ARMOR]         = config[15] - '0';
        myConfig[ConfigVals::AMMO]          = config[16] - '0';
    }
    break;
    case EntClass::CL_CLONE:
    {
        myConfig[ConfigVals::PISTOL]        = config[1]  - '0';
        myConfig[ConfigVals::CLONE_RIFLE]   = config[3]  - '0';
        myConfig[ConfigVals::BLOB]          = config[9]  - '0';
        myConfig[ConfigVals::ION]           = config[11] - '0';
        myConfig[ConfigVals::REINFORCEMENT] = config[10] - '0';
        myConfig[ConfigVals::STAMINA]       = config[0]  - '0';
        myConfig[ConfigVals::ARMOR]         = config[15] - '0';
        myConfig[ConfigVals::AMMO]          = config[16] - '0';
    }
    break;
    case EntClass::CL_WOOK:
    {
        myConfig[ConfigVals::PISTOL]    = config[1]  - '0';
        myConfig[ConfigVals::BOWCASTER] = config[14] - '0';
        myConfig[ConfigVals::HEALTH]    = config[10] - '0';
        myConfig[ConfigVals::STRENGTH]  = config[0]  - '0';
        myConfig[ConfigVals::FRAG]      = config[2]  - '0';
        myConfig[ConfigVals::FURY]      = config[6]  - '0';
        myConfig[ConfigVals::AMMO]      = config[16] - '0';
    }
    break;
    case EntClass::CL_JEDI:
    {
        myConfig[ConfigVals::JUMP]            = config[1]  - '0';
        myConfig[ConfigVals::PUSH]            = config[3]  - '0';
        myConfig[ConfigVals::PULL]            = config[4]  - '0';
        myConfig[ConfigVals::SEEING]          = config[14] - '0';
        myConfig[ConfigVals::SPEED]           = config[2]  - '0';
        myConfig[ConfigVals::MT]              = config[5]  - '0';
        myConfig[ConfigVals::FAST]            = config[9]  - '0';
        myConfig[ConfigVals::MEDIUM]          = config[15] - '0';
        myConfig[ConfigVals::STRONG]          = config[8]  - '0';
        myConfig[ConfigVals::DEFENCE]         = config[16] - '0';
        myConfig[ConfigVals::BLOCK]           = config[0]  - '0';
        myConfig[ConfigVals::DEFLECT]         = config[11] - '0';
        myConfig[ConfigVals::BLASTER_DEFENCE] = config[13] - '0';
        myConfig[ConfigVals::ATTUNEMENT]      = config[6]  - '0';
    }
    break;
    case EntClass::CL_SITH:
    {
        myConfig[ConfigVals::JUMP]            = config[1]  - '0';
        myConfig[ConfigVals::PUSH]            = config[3]  - '0';
        myConfig[ConfigVals::PULL]            = config[4]  - '0';
        myConfig[ConfigVals::SEEING]          = config[14] - '0';
        myConfig[ConfigVals::LIGHTNING]       = config[7]  - '0';
        myConfig[ConfigVals::GRIP]            = config[6]  - '0';
        myConfig[ConfigVals::FAST]            = config[9]  - '0';
        myConfig[ConfigVals::MEDIUM]          = config[15] - '0';
        myConfig[ConfigVals::STRONG]          = config[8]  - '0';
        myConfig[ConfigVals::DEFENCE]         = config[16] - '0';
        myConfig[ConfigVals::BLOCK]           = config[0]  - '0';
        myConfig[ConfigVals::DEFLECT]         = config[11] - '0';
        myConfig[ConfigVals::BLASTER_DEFENCE] = config[13] - '0';
        myConfig[ConfigVals::ATTUNEMENT]      = config[6]  - '0';
    }
    break;
    case EntClass::CL_HERO:
    {
        myConfig[ConfigVals::PISTOL]      = config[1]  - '0';
        myConfig[ConfigVals::E11]         = config[3]  - '0';
        myConfig[ConfigVals::PROJ]        = config[4]  - '0';
        myConfig[ConfigVals::FRAG]        = config[2]  - '0';
        myConfig[ConfigVals::DASH]        = config[5]  - '0';
        myConfig[ConfigVals::QUICK_THROW] = config[9]  - '0';
        myConfig[ConfigVals::DODGE]       = config[10] - '0';
        myConfig[ConfigVals::HEAL]        = config[0]  - '0';
        myConfig[ConfigVals::ARMOR]       = config[15] - '0';
        myConfig[ConfigVals::AMMO]        = config[16] - '0';
    }
    break;
    case EntClass::CL_ARC:
    {
        myConfig[ConfigVals::PISTOL]    = config[1] - '0';
        myConfig[ConfigVals::M5]        = config[5] - '0';
        myConfig[ConfigVals::SCOPE]     = config[6] - '0';
        myConfig[ConfigVals::LAUNCHER]  = config[7] - '0';
        myConfig[ConfigVals::PLX]       = config[3] - '0';
        myConfig[ConfigVals::PULSE]     = config[2] - '0';
        myConfig[ConfigVals::DEXTERITY] = config[10] - '0';
        myConfig[ConfigVals::STAMINA]   = config[0] - '0';
        myConfig[ConfigVals::ARMOR]     = config[15] - '0';
        myConfig[ConfigVals::AMMO]      = config[16] - '0';
    }
    break;
    case EntClass::CL_BH:
    {
        myConfig[ConfigVals::PISTOL]    = config[1]  - '0';
        myConfig[ConfigVals::E11]       = config[3]  - '0';
        myConfig[ConfigVals::A280]      = config[4]  - '0';
        myConfig[ConfigVals::PROJ]      = config[17] - '0';
        myConfig[ConfigVals::DISRUPTOR] = config[6]  - '0';
        myConfig[ConfigVals::THERMAL]   = config[14] - '0';
        myConfig[ConfigVals::POISON]    = config[13] - '0';
        myConfig[ConfigVals::TRACK]     = config[7]  - '0';
        myConfig[ConfigVals::ARMOR]     = config[15] - '0';
        myConfig[ConfigVals::AMMO]      = config[16] - '0';
    }
    break;
    case EntClass::CL_MANDA:
    {
        myConfig[ConfigVals::PISTOL] = config[1]  - '0';
        myConfig[ConfigVals::EE3]    = config[3]  - '0';
        myConfig[ConfigVals::BESKAR] = config[5]  - '0';
        myConfig[ConfigVals::FUEL]   = config[6]  - '0';
        myConfig[ConfigVals::AMBAN]  = config[4]  - '0';
        myConfig[ConfigVals::BIRDS]  = config[12] - '0';
        myConfig[ConfigVals::FLAME]  = config[13] - '0';
        myConfig[ConfigVals::WRIST]  = config[14] - '0';
        myConfig[ConfigVals::ROCKET] = config[7]  - '0';
        myConfig[ConfigVals::ARMOR]  = config[15] - '0';
        myConfig[ConfigVals::AMMO]   = config[16] - '0';
    }
    break;
    case EntClass::CL_SBD:
    {
        myConfig[ConfigVals::HULL_STRENGTH]    = config[6]  - '0';
        myConfig[ConfigVals::FIREPOWER]        = config[13] - '0';
        myConfig[ConfigVals::RECHARGE]         = config[7]  - '0';
        myConfig[ConfigVals::LOGIC]            = config[8]  - '0';
        myConfig[ConfigVals::TARGETING]        = config[12] - '0';
        myConfig[ConfigVals::RADAR]            = config[17] - '0';
        myConfig[ConfigVals::CORTOSIS]         = config[4]  - '0';
        myConfig[ConfigVals::BLAST_ARMOR]      = config[3]  - '0';
        myConfig[ConfigVals::MAGNETIC_PLATING] = config[14] - '0';
        myConfig[ConfigVals::AMMO]             = config[16] - '0';
    }
    break;
    case EntClass::CL_DEKA:
    {
        myConfig[ConfigVals::SHIELD_PROJECTOR] = config[4]  - '0';
        myConfig[ConfigVals::SHIELD_STRENGTH]  = config[6]  - '0';
        myConfig[ConfigVals::HULL_STRENGTH]    = config[13] - '0';
        myConfig[ConfigVals::FIREPOWER]        = config[7]  - '0';
        myConfig[ConfigVals::LOGIC]            = config[3]  - '0';
        myConfig[ConfigVals::DISCHARGE]        = config[8]  - '0';
        myConfig[ConfigVals::QUICK_DEPLOY]     = config[14] - '0';
        myConfig[ConfigVals::POWER_MANAGEMENT] = config[17] - '0';
    }
    break;
    default:
        break;
    }
}

void Missile::Clear()
{
    missileFlags = 0;
    parentGun = Weapons::WP_NONE;
    parentEnt = 0;
    baseAddress = 0;
    id = 0;
    startPos = 0;
    velVec = 0;
    pos = 0;
}
void Missile::Refresh(uintptr_t&loc, const std::array<Player, 32>& players)
{
    //missileFlags = 0;
    if (loc == 0)
        return;
    if (!*(bool*)(loc + 0x214))
    {
        missileFlags &= ~MissileFlags::IS_EXIST;
        return;
    }
    else
        missileFlags |= MissileFlags::IS_EXIST;

    parentGun = *(Weapons*)(loc + 0x124);
    parentEnt = *(int*)(loc + 0x114);
    if (parentEnt >= 0 && parentEnt < 32)
        team = players[parentEnt].team;
    else
        team = Teams::NONE;
    baseAddress = loc;
    id = *(int*)(loc - 4);
    startPos = *(Vec3*)(loc + 0x18);
    pos = *(Vec3*)(loc + 0x374);
    velVec = *(Vec3*)(loc + 0x24);
    trajectoryType = *(TRAJECTORY_TYPE*)(loc + 0xC);

    if (!isSpawned)
    {
        uniqueId =Utils::GenerateRandomInt(999, 1000000000);
        gameTime = *(int*)(loc + 0x244);
        isSpawned = true;
    }

    //only highlight these weapons
    if (trajectoryType == TRAJECTORY_TYPE::TR_STATIONARY
        && parentGun != Weapons::WP_SONIC
        && parentGun != Weapons::WP_TRIP
        && parentGun != Weapons::WP_DETPACK
        )
    {
        missileFlags &= ~MissileFlags::IS_EXIST;
        return;
    }

    if (*(int*)(loc + 4) == 1024)
        missileFlags |= MissileFlags::IS_SECONDARY;

    if (trajectoryType == TRAJECTORY_TYPE::TR_GRAVITY
        || parentGun == Weapons::WP_PLX
        || parentGun == Weapons::WP_MERR_SONN
        )
    {
        GetRadiusAndLifeTime();
    }
    if (trajectoryType == TRAJECTORY_TYPE::TR_STATIONARY
     || trajectoryType == TRAJECTORY_TYPE::TR_INTERPOLATE)
        trajectory.clear();

    if (parentEnt >= 0 && parentEnt < 32)
    {
        if (players[parentEnt].wpInfo.num == Weapons::WP_M5 && parentGun == Weapons::WP_PULSE)
            missileFlags |= IS_EXPLODE_ON_IMPACT;
        else if (parentGun == Weapons::WP_TRIP || parentGun == Weapons::WP_DETPACK)
        {
            radius = 15;
            lifeTime = 60;
            missileFlags |= IS_EXPLODE_ON_IMPACT;
        }
        else if (parentGun == Weapons::WP_FIRE && *(int*)(loc + 0xC8) == 0)
        {
            missileFlags |= IS_EXPLODE_ON_IMPACT;
            radius = 85;
            lifeTime = 15;
        }
    }
}
void Missile::GetRadiusAndLifeTime()
{
    switch (parentGun)
    {
    case Weapons::WP_PULSE:
        radius = 250;
        lifeTime = MissileLifetimes::WP_PULSE_LIFETIME;
        break;
    case Weapons::WP_CONC:
        radius = 150;
        lifeTime = MissileLifetimes::WP_CONC_LIFETIME;
        break;
    case Weapons::WP_CRYO:
        radius = 310;
        lifeTime = MissileLifetimes::WP_CRYO_LIFETIME;
        break;
    case Weapons::WP_FIRE:
        if (missileFlags & MissileFlags::IS_SECONDARY)
            missileFlags |= IS_EXPLODE_ON_IMPACT;
        radius = 175;
        lifeTime = MissileLifetimes::WP_FIRE_LIFETIME;
        break;
    case Weapons::WP_FRAG:
        if (missileFlags & MissileFlags::IS_SECONDARY)
            radius = 45;
        else
        radius = 290;
        lifeTime = MissileLifetimes::WP_FRAG_LIFETIME;
        break;
    case Weapons::WP_THERMAL:
        radius = 310;
        lifeTime = MissileLifetimes::WP_THERMAL_LIFETIME;
        break;
    case Weapons::WP_THERMAL_NADE:
        radius = 100;
        lifeTime = MissileLifetimes::WP_THERMAL_NADE_LIFETIME;
        break;
    case Weapons::WP_SONIC:
        if (missileFlags & MissileFlags::IS_SECONDARY)
            radius = 0;
        else
            radius = 330;
        lifeTime = MissileLifetimes::WP_SONIC_LIFETIME;
        break;
    case Weapons::WP_PLX:
        radius = 330;
        lifeTime = MissileLifetimes::WP_PLX_LIFETIME;
        break;
    case Weapons::WP_MERR_SONN:
        radius = 100;
        lifeTime = MissileLifetimes::WP_MERR_SONN_LIFETIME;
        break;
    case Weapons::WP_CR:
        radius = 45;
        lifeTime = MissileLifetimes::WP_CR_LIFETIME;
        missileFlags |= IS_EXPLODE_ON_IMPACT;
        break;
    case Weapons::WP_M5:
        radius = 45;
        lifeTime = MissileLifetimes::WP_M5_LIFETIME;
        missileFlags |= IS_EXPLODE_ON_IMPACT;
        break;
    case Weapons::WP_REPEATER:
        radius = 45;
        lifeTime = MissileLifetimes::WP_REPEATER_LIFETIME;
        missileFlags |= IS_EXPLODE_ON_IMPACT;
        break;
    default:
        radius = 0;
        lifeTime = 1.5f;
        break;
    }
}

Missile::~Missile()
{

}