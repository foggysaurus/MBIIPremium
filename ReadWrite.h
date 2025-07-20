#pragma once

#include <string>
#include <vector>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <unordered_set>

#include "Enums.h"
#include "Input.h"

struct Bind
{
	int id;
	std::string name;
};

class ReadWrite
{
public:
	ReadWrite(Input* _input);
	~ReadWrite();
	void ReadConfig();
	bool ReadSignatureList(std::unordered_map <AddressesNames, uintptr_t>& addressesMap);
	void AppendLine(const std::string& lineToAppend, const std::wstring& filePath);
	void AppendUniqueLine(const std::string& lineToAppend, const std::wstring& filePath);
	std::wstring StringToWString(const std::string& str);
	std::string WStringToString(const std::wstring& wstr);
	void WriteNameList();
	void ReadNameList();

	std::wstring hackLocationPath;
	std::wstring signaturesPath;

	std::unordered_set<int> uniqueKeys;
	//std::unordered_map<MyKeysEnum, std::vector<MyKeys>> keys;
	std::unordered_map<Colors, std::vector<float>> colors;
	std::unordered_map<MeshColors, std::vector<float>> meshColors;
	std::unordered_map<GraphColors, std::vector<float>> graphColors;
	std::unordered_map<std::string, std::string> nameList;
	std::unordered_map<MyBindsEnum, Bind> myBinds;
	std::vector<std::string> onKillMessages;

	uint32_t configFlags = 0;
	uint32_t wallHackFlags = 0;
	uint32_t botConfigFlags = 0;

	float meshTransparency = 1;
	float graphTransparency = 1;

	std::wstring mapFolderPath;

private:
	std::wstring GetCurrentDirectoryWString();
	bool CreateDirectoryIfNeeded(const std::wstring& path);
	std::string ParseKeyValues(const std::string& str);
	std::vector<float> ParseColorValues(const std::string& str);
	void OnPlayerDeathMessage();

	void InsertBind(const std::string& line, const MyBindsEnum& bind);
	void ReadOpenJK();

	std::wstring gameDataPath;
	std::wstring hackConfigPath;
	std::wstring playerListPath;
	std::wstring isHitscanPath;
	std::wstring onPlayerDeathMessagePath;

	Input* input = nullptr;

	std::unordered_map<std::string, int> mbiiKeysLookupTable
	{
		{"MOUSE1", VK_LBUTTON},
		{ "MOUSE2", VK_RBUTTON },
		{ "MOUSE3", VK_MBUTTON },
		{ "TAB", VK_TAB },
		{ "CAPSLOCK", VK_CAPITAL },
		{ "SPACE", VK_SPACE },
		{ "SHIFT", VK_SHIFT },
		{ "A", 0x41 },
		{ "B", 0x42 },
		{ "C", 0x43 },
		{ "D", 0x44 },
		{ "E", 0x45 },
		{ "F", 0x46 },
		{ "G", 0x47 },
		{ "H", 0x48 },
		{ "I", 0x49 },
		{ "J", 0x4A },
		{ "K", 0x4B },
		{ "L", 0x4C },
		{ "M", 0x4D },
		{ "N", 0x4E },
		{ "O", 0x4F },
		{ "P", 0x50 },
		{ "Q", 0x51 },
		{ "R", 0x52 },
		{ "S", 0x53 },
		{ "T", 0x54 },
		{ "U", 0x55 },
		{ "V", 0x56 },
		{ "W", 0x57 },
		{ "X", 0x58 },
		{ "Y", 0x59 },
		{ "Z", 0x5A },
	};

};

