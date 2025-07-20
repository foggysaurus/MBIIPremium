#pragma once
#include <windows.h>
#include "Utils.h"

class Hook
{
public:
	Hook(BYTE* _dst);
	~Hook();

	bool Detour32();
	bool ReturnBytes(BYTE* dst);
	BYTE* TrampHook32();
	bool IsHooked();

	typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
	twglSwapBuffers owglSwapBuffers;
	bool bUnhook;
private:


	BYTE* src;
	BYTE* dst;
	BYTE* gateway;
	const uintptr_t len = 5;
};

