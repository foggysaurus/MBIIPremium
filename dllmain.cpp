#include "Hook.h"
#include "Draw.h"
#include "Setup.h"
#include "ReadWrite.h"
#include "SharedMemory.h"
#include "Utils.h"
#include "MainEvents.h"
#include "Input.h"

HMODULE thisDLLHmod = NULL;
Hook* hook = nullptr;
Draw* draw = nullptr;
Setup* setup = nullptr;
MainEvents* mainEvents = nullptr;
ReadWrite* readWrite = nullptr;
Input* input = nullptr;

Utils::MrTimer totalTime;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    if (GetAsyncKeyState(VK_F1) && GetAsyncKeyState(VK_CONTROL) || input->IsKeyToggled(MyKeysEnum::EXIT_KEYS))
    {
        mainEvents->RestoreBinds();
        readWrite->WriteNameList();
        hook->bUnhook = true;
        hook->ReturnBytes((BYTE*)hkwglSwapBuffers);
        return hook->owglSwapBuffers(hDc);
    }

    if (!draw->CreateContext(hDc))
    {
        draw->RestoreContext(hDc);
        return hook->owglSwapBuffers(hDc);
    }
   
    
    totalTime.Start();
    if (!setup->IsOjkLoaded(readWrite))
    {
        draw->RestoreContext(hDc);
        return hook->owglSwapBuffers(hDc);
    }

    draw->Init(&setup->addresses);
    mainEvents->Init(&setup->addresses, draw, readWrite, setup->isRobot, setup->isRefreshConfig, setup->isGameUnminimised);
    mainEvents->MainLoop();
    mainEvents->BotLoop();
    mainEvents->DrawUI();

    totalTime.Stop();

    draw->regular24->Print(100, 100, RGB::red, Utils::MrTimer::RemoveTrailingZeros(totalTime.ElapsedAverage(60), 1));
    draw->RestoreContext(hDc);

    //glDisable(GL_DEPTH_TEST);
    return hook->owglSwapBuffers(hDc);
}

DWORD WINAPI MainThread(HMODULE thisDLLHmod)
{
    Sleep(500);

    HackLocation hl;
    const char* receiveFolderLocation = "Local\\SendFolderLocationMemory";
    SharedMemory<HackLocation> sh(hl, receiveFolderLocation);
    sh.CreateSharedMemoryReader();

    draw = new Draw();
    input = new Input();
    readWrite = new ReadWrite(input);
    hook = new Hook((BYTE*)hkwglSwapBuffers);
    setup = new Setup();
    mainEvents = new MainEvents(draw, input);

    //read shared memory sent from launcher
    int errorCounter = 500;
    while (readWrite->hackLocationPath.empty() || errorCounter == 0)
    {
        if (errorCounter == 0)
        {
            hook->bUnhook = true;
            Utils::Error::ShowError(L"Failed to read shared memory");
            break;
        }

        readWrite->hackLocationPath = sh.ReadMemory().test;
        errorCounter--;
        Sleep(20);
    }


    if (!hook->bUnhook)
    {
        readWrite->ReadConfig();
        hook->owglSwapBuffers = (Hook::twglSwapBuffers)hook->TrampHook32();
    }

    while (true)
    {
        Sleep(100);
        if (hook->bUnhook)
        {
            Sleep(1000);
            break;
        }
    }


    delete(draw);
    delete(input);
    delete(readWrite);
    delete(hook); 
    delete(setup);
    delete(mainEvents);

    FreeLibraryAndExitThread(thisDLLHmod, 0);
    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        thisDLLHmod = hModule;
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(MainThread), hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:

    case DLL_PROCESS_DETACH:

        break;
    }
    return TRUE;
}

