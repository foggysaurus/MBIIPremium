#include "Hook.h"

Hook::Hook(BYTE* _dst) : dst(_dst)
{
	HMODULE openGL32 = GetModuleHandle(L"opengl32.dll");
	if (openGL32)
		owglSwapBuffers = (twglSwapBuffers)GetProcAddress(openGL32, "wglSwapBuffers");
	src = (BYTE*)owglSwapBuffers;
	gateway = src;
	//owglSwapBuffers = (twglSwapBuffers)TrampHook32();
	if (!owglSwapBuffers)
	{
		//return 0;
	}
}
bool Hook::IsHooked()
{
	return (*src == 0xE9);
}
Hook::~Hook()
{

}
bool Hook::Detour32()
{
	if (len < 5) return false;

	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t  relativeAddress = dst - src - 5;


	*src = 0xE9;

	*(uintptr_t*)(src + 1) = relativeAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}
BYTE* Hook::TrampHook32()
{
	if (len < 5) return 0;

	if ((*(src) != 0x8B) || (*(src + 1) != 0xFF) || (*(src + 2) != 0x55) || (*(src + 3) != 0x8B) || (*(src + 4) != 0xEC))
	{
		Utils::Error::ShowError(L"Failed to attach. Turn off all graphic mods or overlays like MSI Afterburner");
		return 0;
	}

	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (gateway)
		memcpy(gateway, src, len);

	uintptr_t  gatewayRelativeAddr = src - gateway - 5;

	*(gateway + len) = 0xE9;

	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

	Detour32();

	return gateway;
}
bool Hook::ReturnBytes(BYTE* dst)
{
	BYTE* src = (BYTE*)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	BYTE* gateway = (BYTE*)owglSwapBuffers;

	if (len < 5) return false;

	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t  relativeAddress = dst - src - 5;

	memcpy(src, gateway, len);

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}