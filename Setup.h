#pragma once
#include <Windows.h>
#include <string>

#include "psapi.h"
#include "Addresses.h"
#include "Enums.h"
#include "ReadWrite.h"
#include "Utils.h"

class Setup
{
public:
	struct ModuleInfo
	{
		size_t size;
		uintptr_t handle;
		std::wstring name;
	};

	Setup();
	~Setup();


	bool IsOjkLoaded(ReadWrite* readWrite);


	ModuleInfo mbiiModule, ojkModule, secondaryOjkModule;
	Addresses addresses;
	HMODULE oldOjkHandle = NULL;
	bool isRobot = false;
	bool isRefreshConfig = false;
	bool isGameUnminimised = false;
private:
	HMODULE GetModId(const TCHAR* modName, ModuleInfo& modInfo, const bool& isBreak);
	MODULEINFO GetModuleInfo(const HMODULE& module);
	bool RecalculateOJKModuleIfItChanged();
	void CheckAllAddressesValidity();
	bool ShouldRefreshConfig(ReadWrite* rw);
	bool IsMemoryRegionValid(const uint32_t& memRegion);
	uintptr_t GetAddressFromSignature(const BYTE& moduleName, const std::vector<BYTE>& sig);
	void BytePatcher(const uintptr_t& add, const std::vector<BYTE>& bytesToWrite);
	void PatchBytesUnlockCvarsEtc();
	void ScanSignatures(ReadWrite* rw);

	bool isAllAddressesGood = false;
};