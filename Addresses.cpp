#include "Addresses.h"
Addresses::Addresses()
{
	
}
Addresses::~Addresses()
{

}
bool Addresses::GetMBbaseAdd(const uintptr_t& _mbiiBase)
{
	mbiiBase = _mbiiBase;

	consoleSize = addressesMap[AddressesNames::ADD_CONSOLE];
	consoleOpen = addressesMap[AddressesNames::ADD_ISCONSOLEOPEN];
	myRawPitch = addressesMap[AddressesNames::ADD_PITCH];
	trueId = addressesMap[AddressesNames::ADD_TRUEID];
	maxPlayers = addressesMap[AddressesNames::ADD_MAXPLAYERS];
	incomingCommand = addressesMap[AddressesNames::ADD_INCOMING_COMMAND] + 0xC;
	incomingCommandSize = addressesMap[AddressesNames::ADD_INCOMING_COMMAND_SIZE];
	cheat_add = addressesMap[AddressesNames::CHEAT_ADD];
	mbiiBaseEnt = addressesMap[AddressesNames::ADD_MBIIBASEENT];


	consoleSize += mbiiBase;
	consoleOpen += mbiiBase;
	myRawPitch += mbiiBase;
	trueId += mbiiBase;
	maxPlayers += mbiiBase;
	incomingCommand += mbiiBase;
	incomingCommandSize += mbiiBase;
	cheat_add += mbiiBase;
	mbiiBaseEnt += mbiiBase;

	consoleStart = consoleSize - 0x10000;
	myRawYaw = myRawPitch + 4;
	IsAltFire = mbiiBaseEnt + 0x84;
	IsScope = mbiiBaseEnt + 0x540;
	//ammo = mbiiBaseEnt + 0x11C;
	isGameFocused = mbiiBase + 0x1164B2C;
	gameMode = mbiiBase + 0x14A0BC;
	isNoclip = mbiiBase + 0x63DBE4;
	ping = myRawYaw + 0x20;
	w = consoleOpen - 0x280;
	s = w + 0x18;
	a = w + 0x60;
	d = w + 0x78;
	turnLeft = s - 0x48;
	turnRight = s - 0x30;
	speed = w + 0xA8;
	jump = w + 0xC0;
	crouch = w + 0xD8;
	att = w + 0xF0;
	altAttack = w + 0x198;
	use = w + 0x168;
	button10 = w + 0x1E0;
	button12 = w + 0x210;
	button13 = w + 0x228;
	button14 = w + 0x240;
	return false;
}

bool Addresses::GetOJKbaseAdd(const uintptr_t& _ojk, const uintptr_t& _ojkSecondary)
{
	ojkBase = _ojk;
	ojkSecondaryBase = _ojkSecondary;

	entBase = addressesMap[AddressesNames::ADD_BASEENT_OJK];
	enClass = addressesMap[AddressesNames::ADD_CLASS_OJK];
	team = addressesMap[AddressesNames::ADD_TEAM_OJK];
	traceLine = addressesMap[AddressesNames::ADD_TRACE_OJK];
	fastTraceLine = addressesMap[AddressesNames::ADD_FAST_TRACE_OJK];
	fovX = addressesMap[AddressesNames::ADD_FOV_OJK];
	playerOffset = addressesMap[AddressesNames::ADD_PLAYEROFFSET_OJK];
	classOffset = addressesMap[AddressesNames::ADD_CLASSOFFSET_OJK];
	pitch360 = addressesMap[AddressesNames::ADD_PITCH360_OJK];
	fastPitch = addressesMap[AddressesNames::ADD_FAST_PITCH];
	//newWeaponsFuncAddress = addressesMap[AddressesNames::ADD_EXTRA_WEAPONS];
	entList = addressesMap[AddressesNames::ADD_ENTLIST];
	startVelocitiesPoint = addressesMap[AddressesNames::ADD_WEAPON_VELOCITIES];
	isRound = addressesMap[AddressesNames::ADD_ROUND_BEGIN];
	totalAmmo = addressesMap[AddressesNames::ADD_TOTAL_AMMO];
	sendConsoleCommand = addressesMap[AddressesNames::ADD_SEND_CONSOLE_COMMAND];
	mousePinterCrd = addressesMap[AddressesNames::ADD_MOUSE_POINTER];
	gameTime = addressesMap[AddressesNames::ADD_GAME_TIME];

	antiLauncher = addressesMap[AddressesNames::ADD_ANTI_LAUNCHER]; //all ojk
	exec_add = addressesMap[AddressesNames::ADD_EXEC_ADD];
	//soundCommand = addressesMap[AddressesNames::ADD_SOUND_COMMAND];
	CG_thirdpersonrange_add = addressesMap[AddressesNames::ADD_CG_THIRDPERSONRANGE];
	CG_thirdpersonalpha_add = addressesMap[AddressesNames::ADD_CG_THIRDPERSONALPHA];
	CG_fov_add = addressesMap[AddressesNames::ADD_CG_FOV1];
	CG_fov_add2 = addressesMap[AddressesNames::ADD_CG_FOV2];
	cl_timenudge_add1 = addressesMap[AddressesNames::ADD_CL_TIMENUDGE1];
	cl_timenudge_add2 = addressesMap[AddressesNames::ADD_CL_TIMENUDGE2];

	mousePinterCrd += ojkSecondaryBase;
	gameTime += ojkBase;
	antiLauncher += ojkBase;
	exec_add += ojkBase;
	//soundCommand += ojkBase;
	CG_thirdpersonrange_add += ojkBase;
	CG_thirdpersonalpha_add += ojkBase;
	CG_fov_add += ojkBase;
	CG_fov_add2 += ojkBase;
	cl_timenudge_add1 += ojkBase;
	cl_timenudge_add2 += ojkBase;

	totalAmmo += ojkBase;
	entList += ojkBase;
	entBase += ojkBase;
	enClass += ojkBase;
	sendConsoleCommand += ojkBase;
	team += ojkBase;
	traceLine += ojkBase;
	fastTraceLine += ojkBase;
	newWeaponsFuncAddress += ojkBase;
	fovX += ojkBase;
	playerOffset += ojkBase;
	classOffset += ojkBase;
	pitch360 += ojkBase; //-bd0       
	fastPitch += ojkBase;
	isRound += ojkBase;
	startVelocitiesPoint += ojkBase;//ojkBase + 0x14C278; //find 10500 and the first velocity value slightly above it //8075... 5350
	endVelocitiesPoint = startVelocitiesPoint + 0xB08;
	extraWeaponsArray += ojkBase; //+ 0x4E58EC8; //4E58EC8 find czerka rifle -> what accesses it -> IDA -> find 0xA00
	sbdBattery = fovX - 0x71C;
	isOnFire = entBase + 0x124;
	config = enClass - 0xE5F9; //-
	mapName = fovX + 0x5468;
	hitCounter = pitch360 - 0xBD0;
	lastAttackedEntity = pitch360 - 0xBBC;
	hasLaunchedProjectile = entBase + 0xE4;
	stanceDeathCheck = entBase + 0x35C;
	yaw360 = pitch360 + 4;
	fastYaw = fastPitch + 4;
	forceFocused = entBase + 0x7E4;
	fovY = fovX + 4;
	lookingToUVec = fovX + 0x20;
	cameraPos = fovY + 4;
	myHp = enClass - 0x2C4; //CALSS + 2A54
	lastAttacker = fovY - 0xBAC;
	tkPoints = fovY - 0xBD0;
	ammo = enClass + 0xF70;
	gameRefreshRate = enClass - 0x8BA8;
	//clipSize = enClass + 0xF8C;
	color1 = enClass - 0x2A44; //53E0A58
	return false;
}
