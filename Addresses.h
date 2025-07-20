#pragma once
#include <vector>
#include <unordered_map>
#include <windows.h>
#include "Enums.h"

class Addresses
{
public:

	Addresses();
	~Addresses();

	uintptr_t ojkBase = 0;
	uintptr_t ojkSecondaryBase = 0;
	uintptr_t mbiiBase = 0;

	bool isAddFound = false;

	std::unordered_map <AddressesNames, uintptr_t> addressesMap;

	//std::vector<BYTE> sigEnt = { 0x05, 0, 0, 0, 0, 0x89, 0x4c }; //ent +3 // find X coordinate, what accessess and scroll down a b
	std::vector<BYTE> sigEnt = { 0x5, 0, 0, 0, 0, 0x50, 0x8D, 0x41 }; //new sigEnt test
	std::vector<BYTE> sigClass = { 0x8b, 0x80, 0, 0, 0, 0, 0x83, 0xF8, 0, 0x74, 0x5 }; //+2
	std::vector<BYTE> sigTeam = { 0x83, 0xb8, 0, 0, 0, 0, 0x03, 0, 0, 0, 0, 0, 0, 0x83, 0xBF }; //+2
	std::vector<BYTE> sigTrace = { 0x55, 0x8b, 0xEC, 0x83, 0xEC, 0, 0xA1, 0, 0, 0, 0, 0x33, 0xC5, 0x89, 0, 0, 0x8b, 0x45, 0, 0x8b, 0x4d, 0, 0x53, 0x8b, 0x5d, 0, 0x56 }; //traceline
	std::vector<BYTE> sigFastTrace = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x24, 0xA1, 0, 0, 0, 0, 0x33, 0xC5, 0x89, 0x45, 0xFC, 0x8B, 0x45, 0x18 };
	std::vector<BYTE> sigFov = { 0xF3, 0x0F, 0x10, 0x05, 0,0,0,0, 0xF3, 0x0F, 0x59, 0x05, 0, 0, 0, 0, 0xF3, 0x0F, 0x59, 0xD };
	std::vector<BYTE> sigConsole = { 0x89, 0x15, 0, 0, 0, 0, 0x3D, 0, 0, 0, 0, 0x0f, 0x4f, 0xc6 }; //mbii
	std::vector<BYTE> sigIncomingCommand = { 0xA1, 0,0,0,0, 0x56, 0x52 }; //mbii +1
	std::vector<BYTE> sigIncomingCommandSize = { 0x8B, 0x15, 0, 0, 0, 0, 0x33, 0xC0, 0x57, 0x33, 0xFF, 0x89 }; //mbii +2
	std::vector<BYTE> sigPitch = { 0xf3, 0x0f, 0x11, 0x05, 0, 0, 0, 0, 0x8b, 0xe5, 0x5D };
	std::vector<BYTE> sigIsConsoleOpen = { 0x89, 0x35, 0, 0, 0, 0, 0x5e, 0x5d, 0xc3, 0xcc, 0xcc, 0xcc, 0x55, 0x8b, 0xec }; //+0x2
	std::vector<BYTE> sigMbiiBaseEnt = { 0x33, 0xD2, 0xF3, 0xA5, 0x8B, 0x35, 0, 0, 0, 0, 0x8B, 0x3D }; //+C
	std::vector<BYTE> sigTrueID = { 0xA3, 0, 0, 0, 0, 0xE8,  0, 0, 0, 0, 0x57, 0xA3,  0, 0, 0, 0, 0xE8,  0, 0, 0, 0,  0xE8 }; //+C
	std::vector<BYTE> sigMaxPlayers = { 0xA3,   0, 0, 0, 0, 0xE8,  0, 0, 0, 0, 0x83, 0xFE, 0 }; //+1
	std::vector<BYTE> sigPlayerOffset = { 0x81, 0xC3, 0, 0, 0, 0, 0x40, 0x89, 0x45, 0xFC }; //+0x2
	std::vector<BYTE> sigClsOffset = { 0x69, 0xC1, 0, 0, 0, 0, 0x83, 0xb8, 0, 0, 0, 0, 0x3, 0x0f, 0x84 };
	std::vector<BYTE> sigPitch360 = { 0xf3, 0x0f, 0x11, 0x05,  0, 0, 0, 0, 0xf3, 0x0f, 0x10, 0x89,0, 0, 0, 0, 0xf3, 0x0f, 0x11, 0x0d,0, 0, 0, 0,  0xf3, 0x0f, 0x10, 0x91, 0, 0, 0, 0, 0xf3, 0x0f, 0x11, 0x15, 0, 0, 0, 0, 0xeb, 0x18 }; //+0x4
	std::vector<BYTE> sigFastPitch = { 0xF3, 0x0F, 0x11, 0x05, 0, 0, 0, 0, 0xF3, 0x0F, 0x11, 0x0D, 0, 0, 0, 0, 0xF3, 0x0F, 0x11, 0x15, 0, 0, 0, 0, 0x74, 0x2C, 0x3B, 0x15 }; //+0x4
	std::vector<BYTE> sigScreenSize = { 0xA1, 0, 0, 0, 0, 0x99, 0x2B, 0xC2, 0xD1, 0xF8, 0x50, 0xA1 }; //+0x1 // - 4
	std::vector<BYTE> sigExtraWeaponsFunc = { 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x10, 0x56 }; // -0x40
	std::vector<BYTE> sigEntList = { 0x85, 0xC9, 0x74, 0x0E, 0x8B, 0x88, 0, 0, 0, 0, 0x8B, 0xB0, 0, 0, 0, 0, 0xEB, 0x0C };
	std::vector<BYTE> sigVelocities = { 0, 0, 0, 0, 0, 0x58, 0xFC, 0x45, 0, 0, 0, 0, 0, 0x30, 0xA7, 0x45 };
	std::vector<BYTE> sigExtraWeaponsArray = { 0x8D, 0x96, 0, 0, 0, 0, 0x8B, 0xC1, 0x2B, 0xD0, 0x8D, 0xA4 }; //+0x2
	std::vector<BYTE> sigRoundBegin = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x1C, 0x83, 0x3D, 0, 0, 0, 0, 0 };
	std::vector<BYTE> sigTotalAmmo = { 0xFF, 0xD3, 0x83, 0xC4, 0x40, 0x89, 0x86, 0, 0, 0, 0, 0x8D, 0x47, 0x07 };
	std::vector<BYTE> sigAntiWaitScript = { 0x0F, 0, 0, 0, 0, 0, 0x68, 0, 0, 0, 0, 0x68, 0, 0, 0, 0, 0xFF, 0xD6, 0x83, 0xC4, 0x08, 0x85, 0xC0, 0x0F, 0 };
	std::vector<BYTE> sigCheatUnlock = { 0, 0x2E, 0x57, 0x68 };
	std::vector<BYTE> sigCg_thirdpersonrange = { 0, 0x09, 0x0F, 0x2F, 0, 0, 0, 0, 0, 0, 0x3E };
	std::vector<BYTE> sigCg_thirdpersonalpha = { 0x0F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0F, 0x2F, 0xC8, 0x0F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x83 };
	std::vector<BYTE> sigCg_fov1 = { 0, 0x11, 0x83, 0x3D };
	std::vector<BYTE> sigCg_fov2 = { 0, 0x0A, 0x0F, 0x28, 0xD1 };
	std::vector<BYTE> sig_timenudgeUnlocker1 = { 0, 0x12, 0x68, 0, 0, 0, 0, 0x68, 0, 0, 0, 0, 0xe8, 0, 0, 0, 0, 0x83, 0xc4, 0x08, 0x83, 0x3d, 0, 0, 0, 0, 0, 0x74, 0x0f };
	std::vector<BYTE> sig_timenudgeUnlocker2 = { 0, 0x07, 0x68, 0, 0, 0, 0, 0xeb, 0x0a, 0x83, 0xf8, 0x1E };
	std::vector<BYTE> sigSendConsoleCommand{ 0x55, 0x8B, 0xEC, 0xFF, 0x75, 0x08, 0x6A, 0x12 };
	std::vector<BYTE> sigSoundCommand{ 0, 0x25, 0x68, 0, 0, 0, 0, 0xE8, 0, 0, 0, 0, 0x83, 0xC4, 0x04, 0xC6, 0x05, 0, 0, 0, 0, 0, 0x33, 0xC0, 0x5E, 0x8B, 0x4D, 0xFC, 0x33, 0xCD, 0xE8, 0, 0, 0, 0, 0x8B, 0xE5, 0x5D, 0xC3, 0x68, 0, 0, 0, 0, 0x68, 0, 0, 0, 0, 0xE8, 0, 0, 0, 0, 0x83 };
	std::vector<BYTE> sigAntiLauncher{ 0x83, 0x3D, 0, 0, 0, 0, 0x0, 0x0F, 0, 0, 0, 0, 0, 0x83, 0x3D, 0, 0, 0, 0, 0x0, 0x0F, 0x85, 0, 0, 0, 0, 0x83, 0x3D, 0, 0, 0, 0, 0x0, 0x0F, 0x85, 0, 0, 0, 0, 0x68 };
	std::vector<BYTE> sigMousePointer{ 0xF3, 0x0F, 0x58, 0x05, 0, 0, 0, 0, 0x0F, 0x2F, 0xC8 };
	std::vector<BYTE> sigGameTime{ 0x2B, 0xD, 0, 0, 0, 0, 0x89}; //+2

	//mbii base
	uintptr_t incomingCommand = 0;
	uintptr_t incomingCommandSize = 0;
	uintptr_t consoleSize = 0;
	uintptr_t myRawPitch = 0;
	uintptr_t trueId = 0;
	uintptr_t maxPlayers = 0;
	uintptr_t isGameFocused = 0;
	uintptr_t gameMode = 0;
	uintptr_t ping = 0;
	uintptr_t myRawYaw = 0;
	uintptr_t w = 0;
	uintptr_t a = 0;
	uintptr_t s = 0;
	uintptr_t d = 0;
	uintptr_t turnLeft = 0;
	uintptr_t turnRight = 0;
	uintptr_t consoleOpen = 0;
	uintptr_t speed = 0;
	uintptr_t jump = 0;
	uintptr_t crouch = 0;
	uintptr_t att = 0;
	uintptr_t altAttack = 0;
	uintptr_t use = 0;
	uintptr_t button10 = 0; //Class Special 1 (dodge)
	uintptr_t button12 = 0; //Class Special 3
	uintptr_t button13 = 0; //Class Special 4
	uintptr_t button14 = 0; //reload                   //button2 Use Inventory button3 Slap/Gunbash
	uintptr_t mbiiBaseEnt = 0;
	uintptr_t consoleStart = 0;
	uintptr_t IsAltFire = 0;
	uintptr_t IsScope = 0;
	uintptr_t ammo = 0;
	uintptr_t totalAmmo = 0;
	uintptr_t mapName = 0;
	uintptr_t mousePinterCrd = 0;

	//ojk base
	uintptr_t isNoclip = 0;
	uintptr_t entList = 0;
	uintptr_t entBase = 0;
	uintptr_t enClass = 0;
	uintptr_t traceLine = 0;
	uintptr_t fastTraceLine = 0;
	uintptr_t newWeaponsFuncAddress = 0;
	uintptr_t fovX = 0;
	uintptr_t playerOffset = 0;
	uintptr_t classOffset = 0;
	uintptr_t pitch360 = 0;  
	uintptr_t fastPitch = 0;
	uintptr_t startVelocitiesPoint = 0;
	uintptr_t endVelocitiesPoint = 0;
	uintptr_t extraWeaponsArray = 0;
	uintptr_t sbdBattery = 0;
	uintptr_t isOnFire = 0;
	uintptr_t isRound = 0;
	uintptr_t config = 0;
	uintptr_t hitCounter = 0;
	uintptr_t lastAttackedEntity = 0;
	uintptr_t hasLaunchedProjectile = 0;
	uintptr_t stanceDeathCheck = 0;
	uintptr_t yaw360 = 0;
	uintptr_t fastYaw = 0;
	uintptr_t forceFocused = 0;
	uintptr_t fovY = 0;
	uintptr_t lookingToUVec = 0;
	uintptr_t cameraPos = 0;
	uintptr_t myHp = 0;
	uintptr_t lastAttacker = 0;
	uintptr_t tkPoints = 0;
	//uintptr_t clipSize = 0;
	uintptr_t team = 0;
	uintptr_t color1 = 0;
	uintptr_t sendConsoleCommand = 0;
	uintptr_t gameTime = 0;
	uintptr_t gameRefreshRate = 0;

	uintptr_t cheat_add = 0; //mbii

	uintptr_t antiLauncher = 0; //all ojk
	uintptr_t exec_add = 0;
	//uintptr_t soundCommand = 0;
	uintptr_t CG_thirdpersonrange_add = 0;
	uintptr_t CG_thirdpersonalpha_add = 0;
	uintptr_t CG_fov_add = 0;
	uintptr_t CG_fov_add2 = 0;
	uintptr_t cl_timenudge_add1 = 0;
	uintptr_t cl_timenudge_add2 = 0;


	bool GetMBbaseAdd(const uintptr_t& _mbiiBase);
	bool GetOJKbaseAdd(const uintptr_t& _ojkBase, const uintptr_t& _ojkSecondary);
};



