#include "Input.h"

void Input::GetKeys(const MyKeysEnum& keyIdentifier, const std::string& str)
{
	std::istringstream iss(str.c_str());
	std::string token;
	std::vector<Key> bindKeys;
	while (std::getline(iss, token, ','))
	{
		Key key;
		key.id = std::stoi(token);
		bindKeys.push_back(key);
	}
	keys[keyIdentifier] = bindKeys;
}

void Input::GetAllPossibleKeys()
{
	for (auto& combo : keys)
	{
		for (auto& key: combo.second)
		{
			allKeys[key.id] = key;
		}
	}
}

void Input::CheckState(const bool& isRobot)
{
	if (isRobot)
		return;
	
	for (auto& key : allKeys)
	{
		if (GetAsyncKeyState(key.first))
			key.second.isHeld = true;
		else
			key.second.isHeld = false;
	}

	for (auto& kVector : keys)
	{
		for (auto&k: kVector.second)
		{
			if (allKeys[k.id].isHeld)
			{
				k.isHeld = true;
				k.timePressed = k.t.ElapsedContinuous();
			}
			else
			{
				k.isHeld = false;
				k.timePressed = 0;
				k.t.Stop();
			}
		}
	}
}

bool Input::IsKeyPressed(const MyKeysEnum& keyIdentifier)
{
	for (auto&k: keys[keyIdentifier])
	{
		if (!k.isHeld)
		{
			return false;
		}
	}
	return true;
}

bool Input::IsKeyToggled(const MyKeysEnum& keyIdentifier, const float& timeToRelease)
{
	if (keys[keyIdentifier].empty())
		return false;

	bool allPressed = false;
	bool allPressedExceedTimeLimit = false;

	for (auto& k : keys[keyIdentifier])
	{
		if (!k.isHeld)
		{
			allPressed = false;
			break;
		}
		else
		{
			allPressed = true;
		}
	}

	if (timeToRelease != 0)
		for (auto& k : keys[keyIdentifier])
		{
			if (k.timePressed > timeToRelease)
			{
				allPressedExceedTimeLimit = true;
			}
			else
			{
				allPressedExceedTimeLimit = false;
				break;
			}
		}


	//if (timeToRelease == 0)
	//{
	//	if (allPressed)
	//	{
	//		if (!keys[keyIdentifier][0].isToggled)
	//		{
	//			keys[keyIdentifier][0].isToggled = true;
	//			return true;
	//		}
	//		return false;
	//	}
	//	else
	//	{
	//		keys[keyIdentifier][0].isToggled = false;
	//		return false;
	//	}
	//	return false;
	//}
	//else
	{
		bool result = false;
		if (allPressed)
		{
			if (!keys[keyIdentifier][0].isToggled)
			{
				keys[keyIdentifier][0].isToggled = true;
				return true;
			}
		}
		else
		{
			keys[keyIdentifier][0].isToggled = false;
		}

		if (allPressedExceedTimeLimit)
			return true;

		return false;
	}
}