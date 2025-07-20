#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

#include "Enums.h"
#include "Utils.h"



class Input
{
public:
	Input() {};
	void GetKeys(const MyKeysEnum& keyIdentifier, const std::string& str);
	void GetAllPossibleKeys();
	void CheckState(const bool&isRobot);
	bool IsKeyPressed(const MyKeysEnum& keyIdentifier);
	bool IsKeyToggled(const MyKeysEnum& keyIdentifier, const float& timeToRelease = 0);

private:
	struct Key
	{
		int id = -1;
		bool isHeld = false;
		bool isToggled = false;
		int timePressed = 0;
		Utils::MrTimer t;
	};
	std::unordered_map<MyKeysEnum, std::vector<Key>> keys;

	std::unordered_map<int, Key> allKeys;
};

