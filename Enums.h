#pragma once
#include <unordered_map>
#include <string>
#include <map>

enum class AddressesNames
{
	//ADD MBII BASE ADDRESSES ONLY HERE! IMPORTANT FOR CHECKING VALIDITY
	ADD_CONSOLE,
	ADD_INCOMING_COMMAND,
	ADD_INCOMING_COMMAND_SIZE,
	ADD_PITCH,
	ADD_ISCONSOLEOPEN,
	ADD_MBIIBASEENT,
	ADD_TRUEID,
	ADD_MAXPLAYERS,
	CHEAT_ADD,

	//ADD OJK BASE ADDRESSES ONLY HERE
	ADD_BASEENT_OJK,
	ADD_CLASS_OJK,
	ADD_TEAM_OJK,
	ADD_TRACE_OJK,
	ADD_FAST_TRACE_OJK,
	ADD_FOV_OJK,
	ADD_PLAYEROFFSET_OJK,
	ADD_CLASSOFFSET_OJK,
	ADD_PITCH360_OJK,
	ADD_FAST_PITCH,
	//ADD_EXTRA_WEAPONS,
	ADD_WEAPON_VELOCITIES,
	ADD_ENTLIST,
	ADD_ROUND_BEGIN,
	ADD_TOTAL_AMMO,
	ADD_GAME_TIME,
	ADD_SEND_CONSOLE_COMMAND,
	ADD_ANTI_LAUNCHER,
	//ADD_SOUND_COMMAND,
	ADD_CG_THIRDPERSONRANGE,
	ADD_CG_THIRDPERSONALPHA,
	ADD_CG_FOV1,
	ADD_CG_FOV2,
	ADD_CL_TIMENUDGE1,
	ADD_CL_TIMENUDGE2,
	ADD_EXEC_ADD,

	//ojk secondary
	ADD_MOUSE_POINTER,

	ADD_ENUM_COUNT,
};

enum ConfigFlags
{
	SET_TOGGLE_AIM               = 1 << 0,
	SET_AIM_SELECTOR             = 1 << 1,
	SET_AUTO_SWITCH_JEDI         = 1 << 2,
	SET_AUTO_SWITCH_WOOK         = 1 << 3,
	SET_ANTICROUCH               = 1 << 4,
	SET_AUTOPULL                 = 1 << 5,
	SET_TARGET_PRIORITY          = 1 << 6,
	SET_PBLOCKS                  = 1 << 7,
	SET_AUTOPUSH                 = 1 << 8,
	SET_AUTODODGE                = 1 << 9,
	SET_AUTOFIRE_AMBAN_DISRUPTOR = 1 << 10,
	SET_NO_SPREAD                = 1 << 11,
	SET_SPEC_TRACKER             = 1 << 12,
	SET_ANTI_TK                  = 1 << 13,
	SET_ON_KILL_TAUNTS           = 1 << 14,
	ON_KILL_TAUNTS_GENERAL_CHAT  = 1 << 15,
	SET_MAP_EDITOR_ENABLED       = 1 << 16,
};

enum WALLHACK_FLAGS
{
	DRAW_WALLHACK                     = 1 << 0,
	DRAW_LINES_TO_ALLIES              = 1 << 1,
	DRAW_LINES_TO_ENEMIES             = 1 << 2,
	DRAW_ENEMY_BOXES                  = 1 << 3,
	DRAW_ALLY_BOXES                   = 1 << 4,
	DRAW_PREDICTION                   = 1 << 5,
	DRAW_MY_NADE_PREDICTION           = 1 << 6,
	DRAW_MY_NADE_PREDICTION_ION_PULSE = 1 << 7,
	DRAW_ALL_NADE_PREDICTION          = 1 << 8,
	DRAW_OLDWH                        = 1 << 9,
	DRAW_OLDWH1                       = 1 << 10,
	DRAW_OLDWH2                       = 1 << 11,
	DRAW_OLDWH3                       = 1 << 12,
};

enum BotConfigFlags
{
	DRAW_CELL_GRID          = 1 << 0,
	DRAW_GRAPH              = 1 << 1,
	DRAW_GRAPH_CONNECTIONS  = 1 << 2,
	DRAW_GRAPH_NODES        = 1 << 3,
	DRAW_GRAPH_BBOXES       = 1 << 4,
	DRAW_GRAPH_WEIGHTS      = 1 << 5,
	DRAW_GRAPH_PATH         = 1 << 6,
	DRAW_UI                 = 1 << 7,
	MAKE_MAIN_WINDOW_BOT    = 1 << 8,
	ENABLE_BOT              = 1 << 9,
	DRAW_BOT_BBOXES         = 1 << 10,
	DRAW_BOT_STATES         = 1 << 11,
	MAKE_MAIN_WINDOW_LEADER = 1 << 12,
	MAKE_LEADER_FRIENDLY    = 1 << 13,
	BOT_ROAM                = 1 << 14,
	TARGET_ONLY_VISIBLE     = 1 << 15,
	ENABLE_VOICE_COMMANDS   = 1 << 16,
	DRAW_ELEVATOR_FLAGS     = 1 << 17,
};
enum BotStateFlags : uint32_t
{
	BOT_STATE_IDLE                   = 0,
	BOT_STATE_WALKING_FORWARD        = 1 << 0,
	BOT_STATE_WALKING_LEFT           = 1 << 1,
	BOT_STATE_WALKING_RIGHT          = 1 << 2,
	BOT_STATE_WALKING_BACK           = 1 << 3,
	BOT_STATE_CROUCH                 = 1 << 4,
	BOT_STATE_JUMP                   = 1 << 5,
	BOT_STATE_RELOAD                 = 1 << 6,
	BOT_STATE_ATTACK                 = 1 << 7,
	BOT_STATE_ALTATTACK              = 1 << 8,
	BOT_STATE_SHIFT                  = 1 << 9,
	BOT_STATE_DODGE                  = 1 << 10,
	BOT_STATE_SCOPE                  = 1 << 11,
							         
	BOT_STATE_OBSTACLE_BOTTOM        = 1 << 12,
	BOT_STATE_OBSTACLE_TOP           = 1 << 13,
	BOT_STATE_OBSTACLE_LEFT          = 1 << 14,
	BOT_STATE_OBSTACLE_RIGHT         = 1 << 15,
	BOT_STATE_SHOOT                  = 1 << 16,
	BOT_STATE_WALKING_TO_TARGET_AIM  = 1 << 17,
	BOT_STATE_WALKING_TO_TARGET_WASD = 1 << 18,
	BOT_STATE_ROAMING                = 1 << 19,
	BOT_STATE_STUCK                  = 1 << 20,
	BOT_STATE_TURN_LEFT              = 1 << 21,
	BOT_STATE_TURN_RIGHT             = 1 << 22,
	BOT_STATE_STRAFING               = 1 << 23,
	BOT_STATE_ROLLING_FIRE           = 1 << 24,
	BOT_STATE_GRENADE_DANGER	     = 1 << 25,
	BOT_STATE_NEAR_SABER             = 1 << 26,
	BOT_STATE_USE					 = 1 << 27,

};

static std::map<uint32_t, std::string> botStateNamesMap 
{
	{BotStateFlags::BOT_STATE_IDLE, "BOT_STATE_IDLE"},
	{BotStateFlags::BOT_STATE_WALKING_FORWARD, "BOT_STATE_WALKING_FORWARD"},
	{BotStateFlags::BOT_STATE_WALKING_LEFT, "BOT_STATE_WALKING_LEFT"},
	{BotStateFlags::BOT_STATE_WALKING_RIGHT, "BOT_STATE_WALKING_RIGHT"},
	{BotStateFlags::BOT_STATE_WALKING_BACK, "BOT_STATE_WALKING_BACK"},
	{BotStateFlags::BOT_STATE_CROUCH, "BOT_STATE_CROUCH"},
	{BotStateFlags::BOT_STATE_JUMP, "BOT_STATE_JUMP"},
	{BotStateFlags::BOT_STATE_RELOAD, "BOT_STATE_RELOAD"},
	{BotStateFlags::BOT_STATE_ATTACK, "BOT_STATE_ATTACK"},
	{BotStateFlags::BOT_STATE_ALTATTACK, "BOT_STATE_ALTATTACK"},
	{BotStateFlags::BOT_STATE_DODGE, "BOT_STATE_DODGE"},
	{BotStateFlags::BOT_STATE_SCOPE, "BOT_STATE_SCOPE"},
	{BotStateFlags::BOT_STATE_OBSTACLE_TOP, "BOT_STATE_OBSTACLE_TOP"},
	{BotStateFlags::BOT_STATE_OBSTACLE_LEFT, "BOT_STATE_OBSTACLE_LEFT"},
	{BotStateFlags::BOT_STATE_OBSTACLE_RIGHT, "BOT_STATE_OBSTACLE_RIGHT"},
	{BotStateFlags::BOT_STATE_OBSTACLE_BOTTOM, "BOT_STATE_OBSTACLE_BOTTOM"},
	{BotStateFlags::BOT_STATE_SHOOT, "BOT_STATE_SHOOT"},
	{BotStateFlags::BOT_STATE_WALKING_TO_TARGET_AIM, "BOT_STATE_WALKING_TO_TARGET_AIM"},
	{BotStateFlags::BOT_STATE_WALKING_TO_TARGET_WASD, "BOT_STATE_WALKING_TO_TARGET_WASD"},
	{BotStateFlags::BOT_STATE_ROAMING, "BOT_STATE_ROAMING"},
	{BotStateFlags::BOT_STATE_STUCK, "BOT_STATE_STUCK"},
	{BotStateFlags::BOT_STATE_TURN_LEFT, "BOT_STATE_TURN_LEFT"},
	{BotStateFlags::BOT_STATE_TURN_RIGHT, "BOT_STATE_TURN_RIGHT"},
	{BotStateFlags::BOT_STATE_STRAFING, "BOT_STATE_STRAFING"},
	{BotStateFlags::BOT_STATE_ROLLING_FIRE, "BOT_STATE_ROLLING_FIRE"},
	{BotStateFlags::BOT_STATE_GRENADE_DANGER, "BOT_STATE_GRENADE_DANGER"},
	{BotStateFlags::BOT_STATE_NEAR_SABER, "BOT_STATE_NEAR_SABER"},
	// ... and so on for all states
};


enum class ModuleNames
{
	MOD_OJK,
	MOD_MBII,
	MOD_OJK_SECONDARY,
};

enum class MyKeysEnum : int
{
	AIM_KEYS,
	TK_KEYS,
	AIM_TOGGLE_KEYS,
	EXIT_KEYS,
	HITSCAN_KEYS,
	MAKE_FRIEND_KEYS,
	MAKE_TARGET_KEYS,
	SAVE_MAP_KEYS,
	SWITCH_MODE_EDITOR_NORMAL_KEYS,
	ADD_CELL_KEYS,
	DELETE_CELL_KEYS,
	DELETE_ISLAND_KEYS,
	SWITCH_CELL_TYPE_LEFT_KEYS,
	SWITCH_CELL_TYPE_RIGHT_KEYS,
	RELOAD_MAP_KEYS,
	CREATE_ELEVATOR_KEYS,

	LAST_KEY,
};

enum class MyBindsEnum : int
{
	ATTACK_BIND,
	ALTATTACK_BIND,
	W_BIND,
	A_BIND,
	S_BIND,
	D_BIND,
	CROUCH_BIND,
	JUMP_BIND,
	SHIFT_BIND,
	RELOAD_BIND,
};

enum MyFlags
{
	IS_CROUCH			  =	1 << 0,
	IS_ATTACK			  = 1 << 1,
	IS_ALTATTACK          = 1 << 2,
	IS_LAUNCHEDPROJECTILE = 1 << 3,
	IS_IBOT				  = 1 << 4,
	IS_SCOPE			  = 1 << 5,
	IS_ALTFIRE			  = 1 << 6,
	IS_SPEED			  = 1 << 7,
	IS_W				  = 1 << 8,
	IS_A				  = 1 << 9,
	IS_S				  = 1 << 10,
	IS_D				  = 1 << 11,
	IS_ONFIRE			  = 1 << 12,
	IS_RELOADING		  = 1 << 13,
	IS_NOCLIP			  = 1 << 14,
};

enum MyState
{
	ME_CROUCHING = 0x1,
	ME_ATTACKING = 0x2,
	ME_ALTATTACKING = 0x4,
	ME_FORWARD = 0x8,
	ME_BACK = 0x10,
	ME_LEFT = 0x20,
	ME_RIGHT = 0x40,
	ME_JUMPING = 0x80,
	ME_RELOADING = 0x100,
	ME_SHIFT = 0x200,
	ME_DODGING = 0x400,
	ME_TURN_LEFT = 0x800,
	ME_TURN_RIGHT = 0x1000,
};

enum class DoAction
{
	NONE,
	CROUCH,
	ATTACK,
	ALT_ATTACK,
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	JUMP,
	RELOAD,
	SHIFT,
	DODGE,
	TURN_LEFT,
	TURN_RIGHT,
	USE,
};

enum  TargetFlags
{
	IS_VIABLE_SABERIST_TGT  = 1 << 0,
	IS_SABERIST_TGT         = 1 << 1,
	IS_LOWEST_HP_TGT        = 1 << 2,
	IS_DANGER_WOOK_TGT      = 1 << 3,
	IS_DANGER_JEDI_TGT      = 1 << 4,
	IS_SHOOTING_AT_ME_TGT   = 1 << 5,
	IS_DEFLECTING_AT_ME_TGT = 1 << 6,
};

enum class Weapons
{
	WP_NONE,
	WP_STUN_BATON,
	WP_MELEE,
	WP_LS,
	WP_PISTOL,
	WP_CPISTOL,
	WP_WPISTOL,
	WP_E11,
	WP_DISR,
	WP_BOW,
	WP_REPEATER,
	WP_CR,
	WP_FLAMETROWER,
	WP_MINIGUN,
	WP_DEMP2,
	WP_SHOTGUN,
	WP_FLECHETTE,
	WP_A280,
	WP_DLT,
	WP_M5,
	WP_T21,
	WP_MERR_SONN,
	WP_PLX,
	WP_THERMAL_NADE,
	WP_FRAG,
	WP_THERMAL,
	WP_TRIP,
	WP_PULSE,
	WP_FIRE,
	WP_SONIC,
	WP_CRYO,
	WP_CONC,
	WP_DETPACK,
	WP_CONCUSSION_RIFLE,
	WP_ARM_BLASTER,
	WP_BRYAR = 37,
	WP_EE3_CARABINE,
	WP_EE4_CARABINE,
	WP_AMBAN,
	WP_CR2_HEAVY_BLASTER,
	WP_PROJ,

};


class WeaponFireRates
{
public:
	static constexpr float WP_E11_P = 350.0f;
	static constexpr float WP_E11_S = 200.0f;
	static constexpr float WP_BOW_1 = 350.0f;
	static constexpr float WP_BOW_2 = 300.0f;
	static constexpr float WP_BOW_3 = 275.0f;
	static constexpr float WP_REPEATER = 100.0f;
	static constexpr float WP_CR_1 = 185.0f;
	static constexpr float WP_CR_2 = 150.0f;
	static constexpr float WP_CR_3 = 100.0f;
	static constexpr float WP_MINIGUN = 125.0f;
	static constexpr float WP_A280_P = 300.0f;
	//static constexpr float WP_M5_P = 200.0f;
	static constexpr float WP_T21_P = 200.0f;
	static constexpr float WP_T21_S = 200.0f;
	static constexpr float WP_ARM_BLASTER_0 = 275.0f;
	static constexpr float WP_ARM_BLASTER_1 = 225.0f;
	static constexpr float WP_ARM_BLASTER_2 = 175.0f;
	static constexpr float WP_ARM_BLASTER_3 = 125.0f;
};


//static std::unordered_map<WeaponFireRates, float> WeaponFireRatesMap
//{
//	{WeaponFireRates::WP_E11_P, 350.0f},
//	{WeaponFireRates::WP_E11_S, 200.0f},
//	{WeaponFireRates::WP_BOW_1, 350.0f},
//	{WeaponFireRates::WP_BOW_2, 300.0f},
//	{WeaponFireRates::WP_BOW_3, 275.0f},
//	{WeaponFireRates::WP_REPEATER, 100.0f},
//	{WeaponFireRates::WP_CR_1, 200.0f},
//	{WeaponFireRates::WP_CR_2, 150.0f},
//	{WeaponFireRates::WP_CR_3, 100.0f},
//	{WeaponFireRates::WP_MINIGUN, 125.0f},
//	{WeaponFireRates::WP_A280_P, 300.0f},
//	{WeaponFireRates::WP_M5_P, 200.0f},
//	{WeaponFireRates::WP_T21_P, 350.0f},
//	{WeaponFireRates::WP_T21_S, 200.0f},
//	{WeaponFireRates::WP_ARM_BLASTER_0, 275.0f},
//	{WeaponFireRates::WP_ARM_BLASTER_1, 225.0f},
//	{WeaponFireRates::WP_ARM_BLASTER_2, 175.0f},
//	{WeaponFireRates::WP_ARM_BLASTER_3, 125.0f},
//};


class WeaponVelocities
{
public:
	static constexpr float MAX_FLOAT = 3.402823466e+38F;
	static constexpr float WP_NONE_VELOCITY = MAX_FLOAT;
	static constexpr float WP_STUN_BATON_VELOCITY = MAX_FLOAT;
	static constexpr float WP_MELEE_VELOCITY = MAX_FLOAT;
	static constexpr float WP_LS_VELOCITY = MAX_FLOAT;
	static constexpr float WP_PISTOL_VELOCITY = 6325.0f;
	static constexpr float WP_CPISTOL_VELOCITY = 6325.0f;
	static constexpr float WP_WPISTOL_VELOCITY = 6325.0f;
	static constexpr float WP_E11_VELOCITY = 6325.0f;
	static constexpr float WP_E11_ALT_VELOCITY = 4600.0f;
	static constexpr float WP_DISR_VELOCITY = MAX_FLOAT;
	static constexpr float WP_BOW_VELOCITY = 7625.0f;
	static constexpr float WP_REPEATER_VELOCITY = 2600.0f;
	static constexpr float WP_CR_VELOCITY = 4600.0f;
	static constexpr float WP_FLAMETROWER_VELOCITY = MAX_FLOAT;
	static constexpr float WP_MINIGUN_VELOCITY = 4600.0f;
	static constexpr float WP_DEMP2_VELOCITY = 1800.0f;
	static constexpr float WP_DEMP2_ALT_VELOCITY = 1800.0f;
	static constexpr float WP_SHOTGUN_VELOCITY = 6325.0f;
	static constexpr float WP_FLECHETTE_VELOCITY = 6325.0f;
	static constexpr float WP_A280_VELOCITY = 5350.0f;
	static constexpr float WP_A280_ALT_VELOCITY = 8075.0f;
	static constexpr float WP_DLT_VELOCITY = 5350.0f;
	static constexpr float WP_DLT_ALT_VELOCITY = 8075.0f;
	static constexpr float WP_M5_VELOCITY = 4600.0f;
	static constexpr float WP_M5_ALT_VELOCITY = 9825.0f;
	static constexpr float WP_T21_VELOCITY = 5600.0f;
	static constexpr float WP_T21_ALT_VELOCITY = 5100.0f;
	static constexpr float WP_MERR_SONN_VELOCITY = 900.0f;
	static constexpr float WP_MERR_SONN_ALT_VELOCITY = 450.0f;
	static constexpr float WP_PLX_VELOCITY = 1610.0f;
	static constexpr float WP_THERMAL_NADE_VELOCITY = 908.0f;
	static constexpr float WP_FRAG_VELOCITY = 908.0f;
	static constexpr float WP_THERMAL_VELOCITY = 908.0f;
	static constexpr float WP_TRIP_VELOCITY = 908.0f;
	static constexpr float WP_PULSE_VELOCITY = 908.0f;
	static constexpr float WP_FIRE_VELOCITY = 908.0f;
	static constexpr float WP_SONIC_VELOCITY = 908.0f;
	static constexpr float WP_CRYO_VELOCITY = 908.0f;
	static constexpr float WP_CONC_VELOCITY = 908.0f;
	static constexpr float WP_DETPACK_VELOCITY = 908.0f;
	static constexpr float WP_CONCUSSION_RIFLE_VELOCITY = 6325.0f;
	static constexpr float WP_CONCUSSION_RIFLE_ALT_VELOCITY = MAX_FLOAT;
	static constexpr float WP_ARM_BLASTER_VELOCITY = 4600.0f;
	static constexpr float WP_BRYAR_VELOCITY = 6325.0f;
	static constexpr float WP_EE3_CARABINE_VELOCITY = 6750.0f;
	static constexpr float WP_EE3_CARABINE_ALT_VELOCITY = 7000.0f;
	static constexpr float WP_EE4_CARABINE_VELOCITY = 6325.0f;
	static constexpr float WP_EE4_CARABINE_ALT_VELOCITY = 9825.0f;
	static constexpr float WP_AMBAN_VELOCITY = 9825.0f;
	static constexpr float WP_CR2_HEAVY_BLASTER_VELOCITY = 6325.0f;
	static constexpr float WP_PROJ_VELOCITY = 10500.0f;
	static constexpr float DEKA_VELOCITY = 4025.0f;


};

static std::unordered_map<Weapons, float> WeaponVelocitiesMap
{
	{Weapons::WP_NONE, WeaponVelocities::WP_NONE_VELOCITY},
	{Weapons::WP_STUN_BATON, WeaponVelocities::WP_STUN_BATON_VELOCITY},
	{Weapons::WP_MELEE, WeaponVelocities::WP_MELEE_VELOCITY},
	{Weapons::WP_LS, WeaponVelocities::WP_LS_VELOCITY},
	{Weapons::WP_PISTOL, WeaponVelocities::WP_PISTOL_VELOCITY},
	{Weapons::WP_CPISTOL, WeaponVelocities::WP_CPISTOL_VELOCITY},
	{Weapons::WP_WPISTOL, WeaponVelocities::WP_WPISTOL_VELOCITY},
	{Weapons::WP_E11 ,WeaponVelocities::WP_E11_VELOCITY},
	{Weapons::WP_DISR, WeaponVelocities::WP_DISR_VELOCITY},
	{Weapons::WP_BOW ,WeaponVelocities::WP_BOW_VELOCITY},
	{Weapons::WP_REPEATER, WeaponVelocities::WP_REPEATER_VELOCITY},
	{Weapons::WP_CR, WeaponVelocities::WP_CR_VELOCITY},
	{Weapons::WP_FLAMETROWER, WeaponVelocities::WP_FLAMETROWER_VELOCITY},
	{Weapons::WP_MINIGUN, WeaponVelocities::WP_MINIGUN_VELOCITY},
	{Weapons::WP_DEMP2, WeaponVelocities::WP_DEMP2_VELOCITY},
	{Weapons::WP_SHOTGUN, WeaponVelocities::WP_SHOTGUN_VELOCITY},
	{Weapons::WP_FLECHETTE, WeaponVelocities::WP_FLECHETTE_VELOCITY},
	{Weapons::WP_A280, WeaponVelocities::WP_A280_VELOCITY},
	{Weapons::WP_DLT, WeaponVelocities::WP_DLT_VELOCITY},
	{Weapons::WP_M5, WeaponVelocities::WP_M5_VELOCITY},
	{Weapons::WP_T21, WeaponVelocities::WP_T21_VELOCITY},
	{Weapons::WP_MERR_SONN, WeaponVelocities::WP_MERR_SONN_VELOCITY},
	{Weapons::WP_PLX, WeaponVelocities::WP_PLX_VELOCITY},
	{Weapons::WP_THERMAL_NADE, WeaponVelocities::WP_THERMAL_NADE_VELOCITY},
	{Weapons::WP_FRAG, WeaponVelocities::WP_FRAG_VELOCITY},
	{Weapons::WP_THERMAL, WeaponVelocities::WP_THERMAL_VELOCITY},
	{Weapons::WP_TRIP, WeaponVelocities::WP_TRIP_VELOCITY},
	{Weapons::WP_PULSE, WeaponVelocities::WP_PULSE_VELOCITY},
	{Weapons::WP_FIRE, WeaponVelocities::WP_FIRE_VELOCITY},
	{Weapons::WP_SONIC, WeaponVelocities::WP_SONIC_VELOCITY},
	{Weapons::WP_CRYO, WeaponVelocities::WP_CRYO_VELOCITY},
	{Weapons::WP_CONC, WeaponVelocities::WP_CONC_VELOCITY},
	{Weapons::WP_DETPACK, WeaponVelocities::WP_DETPACK_VELOCITY},
	{Weapons::WP_CONCUSSION_RIFLE, WeaponVelocities::WP_CONCUSSION_RIFLE_VELOCITY},
	{Weapons::WP_ARM_BLASTER, WeaponVelocities::WP_ARM_BLASTER_VELOCITY},
	{Weapons::WP_BRYAR, WeaponVelocities::WP_BRYAR_VELOCITY},
	{Weapons::WP_EE3_CARABINE, WeaponVelocities::WP_EE3_CARABINE_VELOCITY},
	{Weapons::WP_EE4_CARABINE, WeaponVelocities::WP_EE4_CARABINE_VELOCITY},
	{Weapons::WP_AMBAN, WeaponVelocities::WP_AMBAN_VELOCITY},
	{Weapons::WP_CR2_HEAVY_BLASTER, WeaponVelocities::WP_CR2_HEAVY_BLASTER_VELOCITY},
	{Weapons::WP_PROJ, WeaponVelocities::WP_PROJ_VELOCITY},
};

static std::unordered_map<Weapons, float> WeaponOffsets
{
	{Weapons::WP_NONE,			    0.0f},
	{Weapons::WP_STUN_BATON,		0.0f},
	{Weapons::WP_MELEE,				0.0f},
	{Weapons::WP_LS,			    0.0f},
	{Weapons::WP_PISTOL,		    6.0f},
	{Weapons::WP_CPISTOL,			6.0f},
	{Weapons::WP_WPISTOL,			6.0f},
	{Weapons::WP_E11,			    6.0f},
	{Weapons::WP_DISR,		        0.0f},
	{Weapons::WP_BOW,			    3.0f},
	{Weapons::WP_REPEATER,			0.0f},
	{Weapons::WP_CR,				6.0f},
	{Weapons::WP_FLAMETROWER,		0.0f},
	{Weapons::WP_MINIGUN,			6.0f},
	{Weapons::WP_DEMP2,				6.0f},
	{Weapons::WP_SHOTGUN,			0.0f},
	{Weapons::WP_FLECHETTE,			0.0f},
	{Weapons::WP_A280,				0.0f},
	{Weapons::WP_DLT,				0.0f},
	{Weapons::WP_M5,			    0.0f},
	{Weapons::WP_T21,			    2.0f},
	{Weapons::WP_MERR_SONN,			6.0f},
	{Weapons::WP_PLX,			    6.0f},
	{Weapons::WP_THERMAL_NADE,	    0.0f},
	{Weapons::WP_FRAG,			    0.0f},
	{Weapons::WP_THERMAL,			0.0f},
	{Weapons::WP_TRIP,			    0.0f},
	{Weapons::WP_PULSE,				0.0f},
	{Weapons::WP_FIRE,			    0.0f},
	{Weapons::WP_SONIC,				0.0f},
	{Weapons::WP_CRYO,				0.0f},
	{Weapons::WP_CONC,				0.0f},
	{Weapons::WP_DETPACK,			0.0f},
	{Weapons::WP_CONCUSSION_RIFLE,  6.0f},
	{Weapons::WP_ARM_BLASTER,	    13.0f},
	{Weapons::WP_BRYAR,			    6.0f},
	{Weapons::WP_EE3_CARABINE,	    0.0f},
	{Weapons::WP_EE4_CARABINE,	    0.0f},
	{Weapons::WP_AMBAN,			    0.0f},
	{Weapons::WP_CR2_HEAVY_BLASTER, 0.0f},
	{Weapons::WP_PROJ,				0.0f}
};

enum class ConfigVals
{
	PISTOL,
	E11,
	T21,
	A280,
	CLONE_RIFLE,
	BOWCASTER,
	BLOB,
	ION,
	FRAG,
	FIRE,
	CONC,
	SONIC,
	PROJ,
	M5,
	PLX,
	PULSE,
	LAUNCHER,
	SCOPE,
	DISRUPTOR,
	AMBAN,
	BIRDS,
	THERMAL,
	POISON,
	TRACK,
	EE3,
	WRIST,
	ROCKET,
	FLAME,

	REINFORCEMENT,
	RALLY,
	HEALTH,
	STRENGTH,
	DEXTERITY,
	FURY,
	STAMINA,
	CLOSE_COMBAT,
	MAGNETIC_PLATING,
	DODGE,
	DASH,
	HEAL,
	QUICK_THROW,
	FUEL,
	BESKAR,
	HULL_STRENGTH,
	FIREPOWER,
	RECHARGE,
	LOGIC,
	TARGETING,
	RADAR,
	CORTOSIS,
	BLAST_ARMOR,
	SHIELD_PROJECTOR,
	SHIELD_STRENGTH,
	DISCHARGE,
	QUICK_DEPLOY,
	POWER_MANAGEMENT,

	JUMP,
	PUSH,
	PULL,
	SEEING,
	SPEED,
	MT, 
	LIGHTNING, 
	GRIP,
	FAST,
	MEDIUM,
	STRONG,
	DEFENCE,
	ATTUNEMENT,
	BLASTER_DEFENCE,
	DEFLECT,
	BLOCK,

	ARMOR,
	AMMO,

};

static std::unordered_map<ConfigVals, const char*> ConfigValNames
{
	{ConfigVals::PISTOL,                "PISTOL"},
	{ConfigVals::E11,					"E11"},
	{ConfigVals::T21,					"T21"},
	{ConfigVals::A280,					"A280"},
	{ConfigVals::CLONE_RIFLE,			"CLONE_RIFLE"},
	{ConfigVals::BOWCASTER,				"BOWCASTER"},
	{ConfigVals::BLOB,					"BLOB"},
	{ConfigVals::ION, 					"ION"},
	{ConfigVals::FRAG,           		"FRAG"},
	{ConfigVals::FIRE,					"FIRE"},
	{ConfigVals::CONC,					"CONC"},
	{ConfigVals::SONIC,					"SONIC"},
	{ConfigVals::PROJ,					"PROJ"},
	{ConfigVals::M5,					"M5"},
	{ConfigVals::PLX,					"PLX"},
	{ConfigVals::PULSE,					"PULSE"},
	{ConfigVals::LAUNCHER,				"LAUNCHER"},
	{ConfigVals::SCOPE,					"SCOPE"},
	{ConfigVals::DISRUPTOR,				"DISRUPTOR"},
	{ConfigVals::AMBAN,					"AMBAN"},
	{ConfigVals::BIRDS,					"BIRDS"},
	{ConfigVals::THERMAL,				"THERMAL"},
	{ConfigVals::POISON,				"POISON"},
	{ConfigVals::TRACK,					"TRACK"},
	{ConfigVals::EE3,					"EE3"},
	{ConfigVals::WRIST,					"WRIST"},
	{ConfigVals::ROCKET,				"ROCKET"},
	{ConfigVals::FLAME,					"FLAME"},
	{ConfigVals::REINFORCEMENT,			"REINFORCEMENT"},
	{ConfigVals::RALLY,					"RALLY"},
	{ConfigVals::HEALTH,				"HEALTH"},
	{ConfigVals::STRENGTH,				"STRENGTH"},
	{ConfigVals::DEXTERITY,				"DEXTERITY"},
	{ConfigVals::FURY,					"FURY"},
	{ConfigVals::STAMINA,				"STAMINA"},
	{ConfigVals::CLOSE_COMBAT,			"CLOSE_COMBAT"},
	{ConfigVals::MAGNETIC_PLATING,		"MAGNETIC_PLATING"},
	{ConfigVals::DODGE,					"DODGE"},
	{ConfigVals::DASH,					"DASH"},
	{ConfigVals::HEAL,					"HEAL"},
	{ConfigVals::QUICK_THROW,			"QUICK_THROW"},
	{ConfigVals::FUEL,					"FUEL"},
	{ConfigVals::BESKAR,				"BESKAR"},
	{ConfigVals::HULL_STRENGTH,			"HULL_STRENGTH"},
	{ConfigVals::FIREPOWER,				"FIREPOWER"},
	{ConfigVals::RECHARGE,				"RECHARGE"},
	{ConfigVals::LOGIC,					"LOGIC"},
	{ConfigVals::TARGETING,				"TARGETING"},
	{ConfigVals::RADAR,					"RADAR"},
	{ConfigVals::CORTOSIS,				"CORTOSIS"},
	{ConfigVals::BLAST_ARMOR,			"BLAST_ARMOR"},
	{ConfigVals::SHIELD_PROJECTOR,		"SHIELD_PROJECTOR"},
	{ConfigVals::SHIELD_STRENGTH,		"SHIELD_STRENGTH"},
	{ConfigVals::DISCHARGE,				"DISCHARGE"},
	{ConfigVals::QUICK_DEPLOY,			"QUICK_DEPLOY"},
	{ConfigVals::POWER_MANAGEMENT,		"POWER_MANAGEMENT"},
	{ConfigVals::JUMP,					"JUMP"},
	{ConfigVals::PUSH,					"PUSH"},
	{ConfigVals::PULL,					"PULL"},
	{ConfigVals::SEEING,				"SEEING"},
	{ConfigVals::SPEED,					"SPEED"},
	{ConfigVals::MT,					"MT"},
	{ConfigVals::LIGHTNING,				"LIGHTNING"},
	{ConfigVals::GRIP,					"GRIP"},
	{ConfigVals::FAST,					"FAST"},
	{ConfigVals::MEDIUM,				"MEDIUM"},
	{ConfigVals::STRONG,				"STRONG"},
	{ConfigVals::DEFENCE,				"DEFENCE"},
	{ConfigVals::ATTUNEMENT,			"ATTUNEMENT"},
	{ConfigVals::BLASTER_DEFENCE,		"BLASTER_DEFENCE"},
	{ConfigVals::DEFLECT,				"DEFLECT"},
	{ConfigVals::BLOCK,					"BLOCK"},
	{ConfigVals::ARMOR,					"ARMOR"},
	{ConfigVals::AMMO,                  "AMMO"},
};

enum class EntClass
{
	CL_NONE,
	CL_SOLDIMP,
	CL_SOLDREB,
	CL_ETIMP,
	CL_ETREB,
	CL_SITH,
	CL_JEDI,
	CL_BH,
	CL_HERO,
	CL_SBD,
	CL_WOOK,
	CL_DEKA,
	CL_CLONE,
	CL_MANDA,
	CL_ARC,
};

static std::unordered_map<EntClass, const char*> EnClassesNames
{
	{EntClass::CL_SOLDIMP,"SOLD"},
	{EntClass::CL_SOLDREB,"SOLD"},
	{EntClass::CL_ETIMP,"ET"},
	{EntClass::CL_ETREB,"ET"},
	{EntClass::CL_SITH,"SITH"},
	{EntClass::CL_JEDI,"JEDI"},
	{EntClass::CL_BH,"BH"},
	{EntClass::CL_HERO,"HERO"},
	{EntClass::CL_SBD,"SBD"},
	{EntClass::CL_WOOK,"WOOK"},
	{EntClass::CL_DEKA,"DEKA"},
	{EntClass::CL_CLONE,"CLONE"},
	{EntClass::CL_MANDA,"MANDA"},
	{EntClass::CL_ARC,"ARC"},
};

enum class Colors : int
{
	COL_ALLIES,
	COL_ENEMIES,
	COL_FRIENDS,
	COL_TARGETS,
	COL_PREDICTION_POINT,
};
enum class MeshColors : int
{
	WALKABLE_COLOR,
	EDGE_COLOR,
	EDGE2_COLOR,
	EDGE3_COLOR,
	MOVER_COLOR,
	BANNED_COLOR,
	MY_CELL_COLOR,
	ELEVATOR_CELL_COLOR,
	BRIDGE_CELL_COLOR,
	COLUMN_CELL_COLOR,
	JUMP_CELL_COLOR,
	DOWN_PNLY_CELL_COLOR,
	UP_PNLY_CELL_COLOR,
	HIGHCOST_CELL_COLOR,
	ELEVATOR_BUTTON_CELL_COLOR,
	ELEVATOR_BUTTON_2_CELL_COLOR,
	ELEVATOR_BUTTON_CALL_CELL_COLOR,

	COUNT_COLOR,
};
enum class GraphColors : int
{
	TILE_GRAPH_COLOR,
	CONNECTOR_GRAPH_COLOR,
	BBOX_GRAPH_COLOR,
};

enum PlayerFlags
{
	IS_NONE                    = 0,
	IS_VALID		           = 1 << 0,
	IS_RENDERED		           = 1 << 1,
	IS_ALIVE		           = 1 << 2,
	IS_SHOOTING		           = 1 << 3,
	IS_FALLEN		           = 1 << 4,
	IS_CROUCHING	           = 1 << 5,
	IS_SABERBLOCKING           = 1 << 6,
	IS_FORCE_FOCUSED           = 1 << 7,
	IS_LOOKING_AT_ME           = 1 << 8,
	IS_IN_TK_RANGE             = 1 << 9,
	IS_GONNA_KNOCK_ME_DOWN     = 1 << 10,
	IS_RUNNING                 = 1 << 11,
	IS_JETPACK                 = 1 << 12,
	IS_TELECOMMUNICATED        = 1 << 13,
	IS_RENDERED_ON_MAIN_WINDOW = 1 << 14,
};

enum MissileFlags
{
	IS_EXIST                         = 1 << 0,
	IS_SECONDARY                     = 1 << 1,
	IS_TRAJ_CALCULATED               = 1 << 2,
	IS_GREN_COVERED_CELLS_CALCULATED = 1 << 3,
	IS_EXPLODE_ON_IMPACT             = 1 << 4,
};

enum class TRAJECTORY_TYPE : uint8_t
{
	TR_STATIONARY,
	TR_INTERPOLATE,
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_NONLINEAR_STOP,
	TR_SINE,
	TR_GRAVITY
};

enum TrajectoryFlags
{
	TRAJECTORY_RECORD                        = 1 << 0,
	TRAJECTORY_RECORD_AFTER_FIRST_COLLISION  = 1 << 1,
	TRAJECTORY_QUIT_ON_FIRST_COLLISION       = 1 << 2
};

enum PermanentPlayerFlags
{
	IS_FRIEND				 = 1 << 0,
	IS_TARGET				 = 1 << 1,
	IS_LEADER				 = 1 << 2,
	IS_NOT_LEADER			 = 1 << 3,
	IS_VISIBLE				 = 1 << 4,
	IS_AIM_CHEST			 = 1 << 5,
	IS_AIM_HEAD				 = 1 << 6,
	IS_MINION_PATH_GENERATED = 1 << 7,
};

enum class Stances
{
	NONE = 0,
	IDLE = 992, 

	CROUCH = 1082, 
	CROUCH_WAD = 1083, 
	CROUCH_S = 1084, 

	WALK_WAD = 1191,
	WALK_S = 1213,

	JET_W = 1715,
	JET_A = 1717,
	JET_S = 1714,
	JET_D = 1716,

	JET_IDLE = 1229,

	GETUP_S = 1316,
	GETUP_W = 1317,
	ROLL_A = 1318, 
	ROLL_D = 1319, 

	FALLEN = 1296, 
	SOLD_GETUP = 1301,

	SHIFTWALK_WAD = 1179, 
	SHIFTWALK_S = 1212, 

	KICK_W = 964, 
	KICK_A = 967, 
	KICK_S = 965, 
	KICK_D = 966, 

	SLAP = 1694, 
	ROUNDHOUSE_SLAP_RIGHT = 1695, 
	ROUNDHOUSE_SLAP_LEFT = 1696, 
	UPPERCUT = 1705, 

	MEDITATE = 1266, 

	FLYKICK_W = 972, 
	FLYKICK_A = 975, 
	FLYKICK_S = 973, 
	FLYKICK_D = 974, 

	JUMPKICK = 1704, 
	SWEEPKICK = 1699,
};

enum class Stances2
{
	NONE = 0,
	BLOCK_YELLOW = 994,
	BLOCK_DUALS = 929, 
	BLOCK_STAFF = 930, 
	BLOCK_RED = 928, 
	BLOCK_BLUE = 927, 
	BLOCK_PURPLE = 1720, 
	BLOCK_CYAN = 1717, 

	MELEE_L = 122,  
	MELEE_R = 123,  
	PUSH = 1408,  
	PULL = 1409,  

	SLAP = 1694,  

	FLYKICK_W = 972, 
	FLYKICK_A = 975, 
	FLYKICK_S = 973, 
	FLYKICK_D = 974, 

	RELOADING = 1473,   

	SBD_SLAP = 1804,  
	WOOK_SLAP = 1673,  
	WOOK_BARGE = 1451,  

	LIGHTNING = 1430, 
	LIGHTNING_SABER_OUT = 1414, 

	USE_BUTTON = 1405,
};

enum class Teams
{
	NONE,
	REB,
	IMP,
	SPECTATOR,
};

enum class GameModes
{
	OPEN,
	SEMI_AUTHENTIC,
	FULL_AUTHENTIC,
	DUEL,
	LEGENDS,
};


#define CONTENTS_NONE			(0x00000000u)
#define	CONTENTS_SOLID			(0x00000001u)	// Default setting. An eye is never valid in a solid
#define	CONTENTS_LAVA			(0x00000002u)	//
#define	CONTENTS_WATER			(0x00000004u)	//
#define	CONTENTS_FOG			(0x00000008u)	//
#define	CONTENTS_PLAYERCLIP		(0x00000010u)	// Player physically blocked
#define	CONTENTS_MONSTERCLIP	(0x00000020u)	// NPCs cannot physically pass through
#define CONTENTS_BOTCLIP		(0x00000040u)	// do not enter - NPCs try not to enter these
#define CONTENTS_SHOTCLIP		(0x00000080u)	// shots physically blocked
#define	CONTENTS_BODY			(0x00000100u)	// should never be on a brush, only in game
#define	CONTENTS_CORPSE			(0x00000200u)	// should never be on a brush, only in game
#define	CONTENTS_TRIGGER		(0x00000400u)	//
#define	CONTENTS_NODROP			(0x00000800u)	// don't leave bodies or items (death fog, lava)
#define CONTENTS_TERRAIN		(0x00001000u)	// volume contains terrain data
#define CONTENTS_LADDER			(0x00002000u)	//
#define CONTENTS_ABSEIL			(0x00004000u)	// used like ladder to define where an NPC can abseil
#define CONTENTS_OPAQUE			(0x00008000u)	// defaults to on, when off, solid can be seen through
#define CONTENTS_OUTSIDE		(0x00010000u)	// volume is considered to be in the outside (i.e. not indoors)
#define CONTENTS_SLIME			(0x00020000u)	// CHC needs this since we use same tools
#define CONTENTS_LIGHTSABER		(0x00040000u)	// ""
#define CONTENTS_TELEPORTER		(0x00080000u)	// ""
#define CONTENTS_ITEM			(0x00100000u)	// ""
#define CONTENTS_UNUSED00200000	(0x00200000u)	//
#define CONTENTS_UNUSED00400000	(0x00400000u)	//
#define CONTENTS_UNUSED00800000	(0x00800000u)	//
#define CONTENTS_UNUSED01000000	(0x01000000u)	//
#define CONTENTS_UNUSED02000000	(0x02000000u)	//
#define CONTENTS_UNUSED04000000	(0x04000000u)	//
#define	CONTENTS_DETAIL			(0x08000000u)	// brushes not used for the bsp
#define	CONTENTS_INSIDE			(0x10000000u)	// volume is considered to be inside (i.e. indoors)
#define CONTENTS_UNUSED20000000	(0x20000000u)	//
#define CONTENTS_UNUSED40000000	(0x40000000u)	//
#define	CONTENTS_TRANSLUCENT	(0x80000000u)	// don't consume surface fragments inside
#define CONTENTS_ALL			(0xFFFFFFFFu)

#define SURF_NONE				(0x00000000u)
#define SURF_UNUSED00000001		(0x00000001u)	//
#define SURF_UNUSED00000002		(0x00000002u)	//
#define SURF_UNUSED00000004		(0x00000004u)	//
#define SURF_UNUSED00000008		(0x00000008u)	//
#define SURF_UNUSED00000010		(0x00000010u)	//
#define SURF_UNUSED00000020		(0x00000020u)	//
#define SURF_UNUSED00000040		(0x00000040u)	//
#define SURF_UNUSED00000080		(0x00000080u)	//
#define SURF_UNUSED00000100		(0x00000100u)	//
#define SURF_UNUSED00000200		(0x00000200u)	//
#define SURF_UNUSED00000400		(0x00000400u)	//
#define SURF_UNUSED00000800		(0x00000800u)	//
#define SURF_UNUSED00001000		(0x00001000u)	//
#define	SURF_SKY				(0x00002000u)	// lighting from environment map
#define	SURF_SLICK				(0x00004000u)	// affects game physics
#define	SURF_METALSTEPS			(0x00008000u)	// CHC needs this since we use same tools (though this flag is temp?)
#define SURF_FORCEFIELD			(0x00010000u)	// CHC ""			(but not temp)
#define SURF_UNUSED00020000		(0x00020000u)	//
#define	SURF_NODAMAGE			(0x00040000u)	// never give falling damage
#define	SURF_NOIMPACT			(0x00080000u)	// don't make missile explosions
#define	SURF_NOMARKS			(0x00100000u)	// don't leave missile marks
#define	SURF_NODRAW				(0x00200000u)	// don't generate a drawsurface at all
#define	SURF_NOSTEPS			(0x00400000u)	// no footstep sounds
#define	SURF_NODLIGHT			(0x00800000u)	// don't dlight even if solid (solid lava, skies)
#define	SURF_NOMISCENTS			(0x01000000u)	// no client models allowed on this surface
#define	SURF_FORCESIGHT			(0x02000000u)	// not visible without Force Sight
#define SURF_UNUSED04000000		(0x04000000u)	//
#define SURF_UNUSED08000000		(0x08000000u)	//
#define SURF_UNUSED10000000		(0x10000000u)	//
#define SURF_UNUSED20000000		(0x20000000u)	//
#define SURF_UNUSED40000000		(0x40000000u)	//
#define SURF_UNUSED80000000		(0x80000000u)	//

class MissileLifetimes
{
public:
	static constexpr float WP_PULSE_LIFETIME		= 2.0f;
	static constexpr float WP_CONC_LIFETIME			= 2.0f;
	static constexpr float WP_CRYO_LIFETIME			= 2.5f;
	static constexpr float WP_FIRE_LIFETIME			= 2.0f;
	static constexpr float WP_FRAG_LIFETIME			= 2.5f;
	static constexpr float WP_CR_LIFETIME			= 2.5f;
	static constexpr float WP_M5_LIFETIME			= 3.5f;
	static constexpr float WP_REPEATER_LIFETIME		= 4.5f;
	static constexpr float WP_THERMAL_LIFETIME		= 2.5f;
	static constexpr float WP_THERMAL_NADE_LIFETIME = 2.5f;
	static constexpr float WP_SONIC_LIFETIME		= 2.0f;
	static constexpr float WP_PLX_LIFETIME			= 10.0f;
	static constexpr float WP_MERR_SONN_LIFETIME	= 10.0f;
};

enum class entityType_t
{
	ET_GENERAL,
	ET_PLAYER,
	ET_ITEM,
	ET_MISSILE,
	ET_SPECIAL,				// rww - force fields
	ET_HOLOCRON,			// rww - holocron icon displays
	ET_MOVER,
	ET_BEAM,
	ET_PORTAL,
	ET_SPEAKER,
	ET_PUSH_TRIGGER,
	ET_TELEPORT_TRIGGER,
	ET_INVISIBLE,
	ET_NPC,					// ghoul2 player-like entity
	ET_TEAM,
	ET_BODY,
	ET_TERRAIN,
	ET_FX,

	ET_EVENTS				// any of the EV_* events can be added freestanding
							// by setting eType to ET_EVENTS + eventNum
							// this avoids having to set eFlags and eventNum
};

namespace CHARSIZES
{
	constexpr int CALIBRI24 = 9;
	constexpr int CALIBRI28 = 11;
}