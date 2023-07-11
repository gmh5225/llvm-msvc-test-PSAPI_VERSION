// #define PSAPI_VERSION 2
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <tchar.h>
// #pragma comment(lib, "Psapi.lib")

inline std::vector<std::string>
loaded_modules()
{
    // Get the handle to the current process
    HANDLE hProcess = GetCurrentProcess();

    // Get the array of loaded module handles
    HMODULE hModules[1024];
    DWORD cbNeeded;
    if (!EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        throw std::runtime_error("Failed to enumerate process modules");
    }

    // Get the filename of each module
    std::vector<std::string> filenames;
    for (DWORD i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
    {
        TCHAR szModName[MAX_PATH];
        if (GetModuleBaseNameA(hProcess, hModules[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
        {
            // Extract just the filename from the full path
            TCHAR *pszFilename = _tcsrchr(szModName, ('\\'));
            if (pszFilename)
            {
                pszFilename++;
            }
            else
            {
                pszFilename = szModName;
            }

            // Add the filename to the vector
            filenames.push_back(std::string(pszFilename));
        }
    }

    return filenames;
}

int
main()
{
    std::cout << "Hello from cmkr!\n";
    auto list = loaded_modules();
    for (auto &v : list)
    {
        std::cout << "v: " << v << "\n";
    }
    return 0;
}
