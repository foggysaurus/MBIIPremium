#pragma once


#include "pch.h"
#include "Action.h"
#include "Addresses.h"

#include <chrono>

class Action
{
public:
	Action() {}
	~Action() {}

	void DeInit()
	{
		if (!ads)
			return;
		for (auto& a : actions)
		{
			Stop(a.first);
		}
	}

	void Init(Addresses* _ads)
	{
		ads = _ads;
		actions[DoAction::FORWARD] = ads->w;
		actions[DoAction::LEFT] = ads->a;
		actions[DoAction::BACK] = ads->s;
		actions[DoAction::RIGHT] = ads->d;
		actions[DoAction::CROUCH] = ads->crouch;
		actions[DoAction::JUMP] = ads->jump;
		actions[DoAction::ALT_ATTACK] = ads->altAttack;
		actions[DoAction::ATTACK] = ads->att;
		actions[DoAction::SHIFT] = ads->speed;
		actions[DoAction::RELOAD] = ads->button14;
		actions[DoAction::DODGE] = ads->button10;
		actions[DoAction::TURN_LEFT] = ads->turnLeft;
		actions[DoAction::TURN_RIGHT] = ads->turnRight;
		actions[DoAction::USE] = ads->use;
	}
	bool CheckState(const DoAction& flag)
	{
		return actions[flag];
	}
	void Do(const DoAction& flag)
	{
		*(int*)actions[flag] = 1;
	}
	void Stop(const DoAction& flag)
	{
		*(int*)actions[flag] = 0;
	}

private:
	std::unordered_map<DoAction, uintptr_t> actions;
	bool isExecingOnceAuto = false;
	bool isExecingOnce = false;
	Addresses* ads = nullptr;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime, m_EndTime;
};