#include "Setup.h"

Setup::Setup()
{
	mbiiModule.name = L"mbii.x86.exe";
	mbiiModule.handle = (uintptr_t)GetModuleHandle(mbiiModule.name.c_str());
	mbiiModule.size = GetModuleInfo((HMODULE)mbiiModule.handle).SizeOfImage;
}
Setup::~Setup()
{

}
void Setup::BytePatcher(const uintptr_t& add, const std::vector<BYTE>& bytesToWrite)
{
	if (!add)
		return;

	DWORD oldProtect;
	VirtualProtect((LPVOID)add, bytesToWrite.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

	for (int i = 0; i < bytesToWrite.size(); i++)
	{
		if (bytesToWrite[i] != '?')
		{
			*(byte*)(add + i) = bytesToWrite[i];
		}
	}

	VirtualProtect((LPVOID)add, bytesToWrite.size(), oldProtect, nullptr);
}
void Setup::CheckAllAddressesValidity()
{
	std::vector<int> invalidAddresses;
	for (int i = (int)AddressesNames::ADD_CONSOLE; i < (int)AddressesNames::ADD_BASEENT_OJK; i++)
	{

		if (!IsMemoryRegionValid(addresses.addressesMap[(AddressesNames)i] + mbiiModule.handle))
			invalidAddresses.push_back(i);
	}
	for (int i = (int)AddressesNames::ADD_BASEENT_OJK; i < (int)AddressesNames::ADD_MOUSE_POINTER; i++)
	{

		if (!IsMemoryRegionValid(addresses.addressesMap[(AddressesNames)i] + ojkModule.handle))
			invalidAddresses.push_back(i);
	}
	for (int i = (int)AddressesNames::ADD_MOUSE_POINTER; i < (int)AddressesNames::ADD_ENUM_COUNT; i++)
	{

		if (!IsMemoryRegionValid(addresses.addressesMap[(AddressesNames)i] + secondaryOjkModule.handle))
			invalidAddresses.push_back(i);
	}
	if (!invalidAddresses.empty())
	{
		isAllAddressesGood = false;
		Utils::Error::ShowError(L"Not all addresses are valid! Delete signatures.txt");
		return;
	}
	isAllAddressesGood = true;
}
void Setup::ScanSignatures(ReadWrite* rw)
{
	static bool isAddressesWrittenOnce = false;
	if (isAddressesWrittenOnce)
		return;

	addresses.addressesMap[AddressesNames::ADD_MBIIBASEENT] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigMbiiBaseEnt) + 0xC) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CONSOLE] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigConsole) + 0x2) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_INCOMING_COMMAND] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigIncomingCommand) + 0x1) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_INCOMING_COMMAND_SIZE] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigIncomingCommandSize) + 0x2) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_ISCONSOLEOPEN] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigIsConsoleOpen) + 0x2) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_PITCH] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigPitch) + 0x4) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_TRUEID] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigTrueID) + 0x1) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::ADD_MAXPLAYERS] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigMaxPlayers) + 0x1) - mbiiModule.handle;
	addresses.addressesMap[AddressesNames::CHEAT_ADD] = (GetAddressFromSignature((int)ModuleNames::MOD_MBII, addresses.sigCheatUnlock)) - mbiiModule.handle;
	//ojk

	addresses.addressesMap[AddressesNames::ADD_BASEENT_OJK] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigEnt) + 0x1) - ojkModule.handle; //PROBLEM
	addresses.addressesMap[AddressesNames::ADD_CLASS_OJK] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigClass) + 0x2) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_TEAM_OJK] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigTeam) + 0x2) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_TRACE_OJK] = GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigTrace) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_FAST_TRACE_OJK] = GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigFastTrace) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_FOV_OJK] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigFov) + 0x4) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_PLAYEROFFSET_OJK] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigPlayerOffset) + 0x2) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CLASSOFFSET_OJK] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigClsOffset) + 0x2) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_PITCH360_OJK] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigPitch360) + 0x4) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_FAST_PITCH] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigFastPitch) + 0x4) - ojkModule.handle; //PROBLEM

	//addresses.addressesMap[AddressesNames::ADD_EXTRA_WEAPONS] = GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigExtraWeaponsFunc) - 0x40 - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_ENTLIST] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigEntList) + 0x6) - ojkModule.handle + 0x100;
	addresses.addressesMap[AddressesNames::ADD_WEAPON_VELOCITIES] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigVelocities)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_ROUND_BEGIN] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigRoundBegin) + 0x8) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_TOTAL_AMMO] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigTotalAmmo) + 0x7) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_GAME_TIME] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigGameTime) + 0x2) - ojkModule.handle;

	addresses.addressesMap[AddressesNames::ADD_MOUSE_POINTER] = *(uintptr_t*)(GetAddressFromSignature((int)ModuleNames::MOD_OJK_SECONDARY, addresses.sigMousePointer) + 0x4) - secondaryOjkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_SEND_CONSOLE_COMMAND] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigSendConsoleCommand)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_ANTI_LAUNCHER] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigAntiLauncher)) - ojkModule.handle;
	//addresses.addressesMap[AddressesNames::ADD_SOUND_COMMAND] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigSoundCommand)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CG_THIRDPERSONRANGE] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigCg_thirdpersonrange)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CG_THIRDPERSONALPHA] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigCg_thirdpersonalpha)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CG_FOV1] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigCg_fov1)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CG_FOV2] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigCg_fov2)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CL_TIMENUDGE1] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sig_timenudgeUnlocker1)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_CL_TIMENUDGE2] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sig_timenudgeUnlocker2)) - ojkModule.handle;
	addresses.addressesMap[AddressesNames::ADD_EXEC_ADD] = (GetAddressFromSignature((int)ModuleNames::MOD_OJK, addresses.sigAntiWaitScript)) - ojkModule.handle;


	for (auto& add : addresses.addressesMap)
	{
		std::string lineToAppend = std::to_string((int)add.first) + " " + std::to_string(add.second);
		rw->AppendUniqueLine(lineToAppend, rw->signaturesPath);
	}

	isAddressesWrittenOnce = true;
}
uintptr_t Setup::GetAddressFromSignature(const BYTE& moduleName, const std::vector<BYTE>& sig)
{
	ModuleInfo modInfo;

	switch (moduleName)
	{
	case (int)ModuleNames::MOD_OJK:
		modInfo = ojkModule;
		break;
	case (int)ModuleNames::MOD_MBII:
		modInfo = mbiiModule;
		break;
	case (int)ModuleNames::MOD_OJK_SECONDARY:
		modInfo = secondaryOjkModule;
		break;
	default:
		break;
	}


	MEMORY_BASIC_INFORMATION mbi{ 0 };
	int protectFlags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);
	uintptr_t moduleStart = (uintptr_t)(modInfo.handle);

	for (size_t i = moduleStart; i < moduleStart + modInfo.size - sig.size(); i++)
	{
		if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi)))
		{
			if (mbi.Protect & protectFlags || !(mbi.State & MEM_COMMIT))
			{
				//bad region
				i += mbi.RegionSize;
				continue;
			}

			for (size_t k = (int)mbi.BaseAddress; k < (int)mbi.BaseAddress + mbi.RegionSize - sig.size(); k++)
			{
				for (size_t j = 0; j < sig.size(); j++)
				{
					if (sig.at(j) != 0 && sig.at(j) != *(BYTE*)(k + j))
						break;
					if (j + 1 == sig.size())
						return k;
				}
			}
			i = (int)mbi.BaseAddress + mbi.RegionSize;
		}
	}

	return NULL;
}
void Setup::PatchBytesUnlockCvarsEtc()
{
	static std::wstring oldOjk;
	if (ojkModule.handle && ojkModule.name != oldOjk)
	{
		std::vector<BYTE> antiLauncherUnlock;

		bool isServerGame = *(bool*)*(UINT*)(addresses.antiLauncher + 2);

		if (isServerGame)
		{
			antiLauncherUnlock = { '?', '?', '?', '?', '?', '?', '?', '?', 0x85 };
			BytePatcher(addresses.antiLauncher, antiLauncherUnlock);
			int a = 3;
		}

		const std::vector<BYTE> bytestopatch_exec = { '?', 0x80, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x80 };
		BytePatcher(addresses.exec_add, bytestopatch_exec);

		const std::vector<BYTE> bytestopatch_unlock = { 0xEB };
		BytePatcher(addresses.cheat_add, bytestopatch_unlock);

		//const std::vector<BYTE> soundCommand_unlock = { 0xEB };
		//BytePatcher(addresses.soundCommand, soundCommand_unlock);

		const std::vector<BYTE> CG_thirdpersonrange_unlock = { 0x74, '?', '?', '?', '?', '?', '?', '?', '?', 0x75 };
		BytePatcher(addresses.CG_thirdpersonrange_add, CG_thirdpersonrange_unlock);

		const std::vector<BYTE> CG_thirdpersonalpha_unlock = { '?', 0x80, '?', '?', '?', '?', '?', '?', '?', '?', 0x80 };
		BytePatcher(addresses.CG_thirdpersonalpha_add, CG_thirdpersonalpha_unlock);

		const std::vector<BYTE> CG_fov_unlock = { 0xEB };
		BytePatcher(addresses.CG_fov_add, CG_fov_unlock);

		const std::vector<BYTE> CG_fov_unlock2 = { 0xEB };
		BytePatcher(addresses.CG_fov_add2, CG_fov_unlock2);

		const std::vector<BYTE> cl_timenudge_unlock1 = { 0xEB };
		BytePatcher(addresses.cl_timenudge_add1, cl_timenudge_unlock1);

		const std::vector<BYTE> cl_timenudge_unlock2 = { 0xEB };
		BytePatcher(addresses.cl_timenudge_add2, cl_timenudge_unlock2);

		oldOjk = ojkModule.name;
	}
}
MODULEINFO Setup::GetModuleInfo(const HMODULE& module)
{
	MODULEINFO info = { 0 };
	GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(info));
	return info;
}
bool Setup::IsMemoryRegionValid(const uint32_t& memRegion)
{
	int protectFlags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);
	MEMORY_BASIC_INFORMATION mbi{ 0 };

	if (VirtualQuery((LPCVOID)memRegion, &mbi, sizeof(mbi)))
	{
		if (mbi.Protect & protectFlags || !(mbi.State & MEM_COMMIT))
		{
			return false;
		}
	}
	return true;
}
HMODULE Setup::GetModId(const TCHAR* modName, ModuleInfo& modInfo, const bool& isBreak)
{
	HMODULE hModule = NULL;
	HMODULE hMods[1024];
	DWORD cbNeeded;
	if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded))
	{
		for (size_t i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(GetCurrentProcess(), hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				TCHAR* module = szModName;
				std::wstring where = module;
				std::wstring what = modName;
				if (where.find(what) != std::string::npos)
				{
					hModule = hMods[i];
					modInfo.name = where;
					HMODULE handle = GetModuleHandle(modInfo.name.c_str());
					modInfo.size = GetModuleInfo(handle).SizeOfImage;
					modInfo.handle = (uintptr_t)handle;

					if (isBreak)
						return nullptr;
				}
			}
		}
	}
	return nullptr;
}
bool Setup::RecalculateOJKModuleIfItChanged()
{
	HMODULE currentOjkHandle = GetModuleHandle(ojkModule.name.c_str());
	if (currentOjkHandle != oldOjkHandle || currentOjkHandle == NULL)
	{
		GetModId(L"OJK", ojkModule, false);
		GetModId(L"OJK", secondaryOjkModule, true);
		oldOjkHandle = currentOjkHandle;
		if (currentOjkHandle == NULL || ojkModule.handle == secondaryOjkModule.handle)
			return false;

		if (!addresses.addressesMap.empty())
		{
			addresses.GetMBbaseAdd(mbiiModule.handle);
			addresses.GetOJKbaseAdd(ojkModule.handle, secondaryOjkModule.handle);
			CheckAllAddressesValidity();
			PatchBytesUnlockCvarsEtc();
		}
	}


	if (currentOjkHandle != NULL && ojkModule.handle != secondaryOjkModule.handle)
		return true;
	else
		return false;
}
bool Setup::ShouldRefreshConfig(ReadWrite* rw)
{
	isGameUnminimised = false;

	if (!*(int*)addresses.isGameFocused && *(int*)addresses.consoleOpen != 1)
	{
		isRefreshConfig = false;
		isRobot = true;
		return true;
	}
	else
	{
		if (!isRefreshConfig)
		{
			isRobot = false;
			rw->ReadConfig();
			isRefreshConfig = true;
			isGameUnminimised = true;
			return false;
		}
	}

	if (rw->botConfigFlags & BotConfigFlags::MAKE_MAIN_WINDOW_BOT)
		isRobot = true;
	return true;
}
bool Setup::IsOjkLoaded(ReadWrite* readWrite)
{
	if (!RecalculateOJKModuleIfItChanged())
		return false;

	if (addresses.addressesMap.empty())
	{
		if (!readWrite->ReadSignatureList(addresses.addressesMap) || addresses.addressesMap.empty())
		{
			ScanSignatures(readWrite);
		}
		addresses.GetMBbaseAdd(mbiiModule.handle);
		addresses.GetOJKbaseAdd(ojkModule.handle, secondaryOjkModule.handle);
		CheckAllAddressesValidity();
		PatchBytesUnlockCvarsEtc();
	}

	if (!isAllAddressesGood)
		return false;

	return ShouldRefreshConfig(readWrite);
}