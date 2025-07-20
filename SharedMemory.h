#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <locale>
#include "Utils.h"
#include "Enums.h"
#include "Entity.h"

struct HackLocation
{
    wchar_t test[MAX_PATH];
};


struct PlayerData
{
    struct CommonData
    {
        int id = 0;

        Teams team = Teams::NONE;
        EntClass entClass = EntClass::CL_NONE;
        Stances stance = Stances::NONE;
        Weapons weapon = Weapons::WP_NONE;
        Player::Position position;
        Player::PlayerModel playerModel;
        uint32_t playerFlags = PlayerFlags::IS_NONE;

        float yaw = 0;
        float pitch = 0;

        Vec3 uvec = 0;
    };

    struct LeaderToBot
    {

    };

    struct BotToLeader
    {

    };

    CommonData commonData;
};
struct PlayersToSend
{
    struct LeaderToBot
    {
        bool iRefreshedMap = false;
        int bossId = 0;
        int leaderId = -1;
    };

    struct BotToLeader
    {
        bool iRefreshedMap = false;
        int botId = 0;
    };

    int maxId = 0;

    LeaderToBot leaderToBot;
    BotToLeader botToLeader;

    PlayerData playersData[32];
};

template <typename T>
class SharedMemory
{
public:
    SharedMemory(const T& info, const char* _sharedMemoryName) : data(info), sharedMemoryName(_sharedMemoryName) {}
    SharedMemory() {};
    ~SharedMemory()
    {
        KillSharedMemoryReader();
        KillSharedMemoryWriter();
        KillMultipleSharedMemoryReaders();
    }

    void CreateSharedMemory()
    {
        if (hMapFile_w || pBuf_w)
            return;

        // Generate unique shared memory name using process ID
        std::wstring smName = L"game_" + std::to_wstring(static_cast<unsigned int>(GetCurrentProcessId()));
        BUF_SIZE = sizeof(T);  // Define buffer size

        hMapFile_w = CreateFileMappingW(
            INVALID_HANDLE_VALUE,  // No backing file
            NULL,                  // Default security attributes
            PAGE_READWRITE,        // Read/write access
            0,                     // Maximum object size (high-order DWORD)
            BUF_SIZE,              // Maximum object size (low-order DWORD)
            smName.c_str()         // Name of mapping object
        );

        if (hMapFile_w == NULL) {
            return;
        }

        pBuf_w = static_cast<T*>(MapViewOfFile(
            hMapFile_w,           // Handle to the map object
            FILE_MAP_ALL_ACCESS,  // Read/write access
            0, 0, BUF_SIZE        // Offset and size
        ));

        if (pBuf_w == NULL) {
            CloseHandle(hMapFile_w);
            hMapFile_w = NULL;  // Reset handle
            return;
        }
    }
    void CreateSharedMemoryReader()
    {
        if (hMapFile_r || pBuf_r)
            return;

        BUF_SIZE = sizeof(T);  // Buffer size for shared memory

        hMapFile_r = OpenFileMappingA(
            FILE_MAP_READ,          // Access mode: read
            FALSE,                  // Do not inherit the handle
            sharedMemoryName.c_str() // Name of the shared memory object
        );

        if (hMapFile_r == NULL)
        {
            std::cerr << "Could not open file mapping object (" << GetLastError() << ")." << std::endl;
            return;
        }

        pBuf_r = (T*)MapViewOfFile(
            hMapFile_r,             // Handle to the mapped object
            FILE_MAP_READ,          // Read access
            0,
            0,
            BUF_SIZE
        );

        if (pBuf_r == NULL)
        {
            std::cerr << "Could not map view of file (" << GetLastError() << ")." << std::endl;
            CloseHandle(hMapFile_r);
            return;
        }
    }
    void CreateMultipleSharedMemoryReaders()
    {
        BUF_SIZE = sizeof(T);  // Define buffer size for shared memory

        processesToRead.clear();
        mbiiIds.clear();

        Utils::GetMbiiId(mbiiIds);
        for (auto& pid : mbiiIds)
        {
            ProcessInfo pi;
            pi.pid = pid;
            processesToRead.push_back(pi);
        }

        for (auto& pi : processesToRead)
        {
            if (pi.hMapFile_r || pi.pBuf_r)
                continue;

            std::wstring smName = L"game_" + std::to_wstring(pi.pid);
            pi.hMapFile_r = OpenFileMappingW(
                FILE_MAP_READ,   // Read-only access
                FALSE,           // Do not inherit handle
                smName.c_str()   // Name of the mapping object
            );

            if (pi.hMapFile_r == NULL) 
            {
                continue;
            }

            pi.pBuf_r = static_cast<T*>(MapViewOfFile(
                pi.hMapFile_r,     // Handle to the map object
                FILE_MAP_READ,     // Read-only access
                0, 0, BUF_SIZE     // Offset and size
            ));

            if (pi.pBuf_r == NULL) {
                CloseHandle(pi.hMapFile_r);  // Close handle
                pi.hMapFile_r = NULL;        // Reset handle
                continue;
            }
        }
    }
    void WriteMemory()
    {
        if (pBuf_w == nullptr)
        {
            std::cerr << "Shared memory not initialized!" << std::endl;
            return;
        }

        T* sharedData = (T*)pBuf_w;
        *sharedData = data;
    }
    void WriteMemory(const T& value)
    {
        if (pBuf_w == nullptr)
        {
            return;
        }
        T* sharedData = static_cast<T*>(pBuf_w);
        *sharedData = value;
    }
    T ReadMemory()
    {
        if (pBuf_r == nullptr) {
            return T(); 
        }

        T* sharedData = (T*)pBuf_r; 
        return *sharedData;
    }
    std::vector<T> ReadMultipleMemories()
    {
        std::vector<T> dataVector;
        for (auto& pi : processesToRead)
        {
            if (pi.pBuf_r == nullptr) 
            {
                continue;
            }
            T* sharedData = (T*)pi.pBuf_r;
            dataVector.push_back(*sharedData);
        }
        return dataVector;
    }

    void KillSharedMemoryReader()
    {
        if (pBuf_r != NULL)
        {
            UnmapViewOfFile(pBuf_r);
            pBuf_r = NULL;
        }
        if (hMapFile_r != NULL)
        {
            CloseHandle(hMapFile_r);
            hMapFile_r = NULL;
        }
    }
    void KillSharedMemoryWriter()
    {
        if (pBuf_w != NULL)
        {
            UnmapViewOfFile(pBuf_w);
            pBuf_w = NULL;
        }
        if (hMapFile_w != NULL)
        {
            CloseHandle(hMapFile_w);
            hMapFile_w = NULL;
        }
    }
    void KillMultipleSharedMemoryReaders()
    {
        for (auto& pi : processesToRead)
        {
            if (pi.pBuf_r != NULL)
            {
                UnmapViewOfFile(pi.pBuf_r);
                pi.pBuf_r = NULL;
            }
            if (pi.hMapFile_r != NULL)
            {
                CloseHandle(pi.hMapFile_r);
                pi.hMapFile_r = NULL;
            }
        }
        processesToRead.clear();
    }

private:
    std::string sharedMemoryName;
    int BUF_SIZE;
    void* pBuf_r = nullptr;
    HANDLE hMapFile_r = NULL;

    void* pBuf_w = nullptr;
    HANDLE hMapFile_w = NULL;
    T data;

    std::vector<uintptr_t> mbiiIds;
    struct ProcessInfo
    {
        HANDLE hMapFile_r = NULL;
        void* pBuf_r = nullptr;
        uintptr_t pid;
    };
    std::vector<ProcessInfo> processesToRead;
};
