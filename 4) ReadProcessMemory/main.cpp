#include <iostream>
#include <windows.h>
#include <psapi.h>

uintptr_t GetBaseAddress(HANDLE hProcess)
{
    HMODULE hModules[1024];
    DWORD cbNeeded;
    if(EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        uintptr_t baseAddress = (uintptr_t)hModules[0];
        return baseAddress;
    }
    std::cout << "Couldn't obtain base address.\n";
    return 0;
}

void ListModules(HANDLE hProcess)
{
    HMODULE hModules[1024];
    DWORD cbNeeded;

    if(EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        int module_count = cbNeeded / sizeof(HMODULE);
        wchar_t module_name[MAX_PATH];

        for (int i = 0; i < module_count; i++)
        {
            if(GetModuleBaseNameW(hProcess, hModules[i], module_name, MAX_PATH))
            {
                std::wcout << L"[+] Module: " << module_name << L" | Base Address: 0x" << std::hex << (uintptr_t)hModules[i] << std::dec << '\n'; 
            }
        }
    } else 
    {
        std::cout << "Failed to get modules.\n";
    }
}

int main()
{
    
    DWORD pid = 0000;
    std::cout << "Enter a PID: ";
    std::cin >> pid;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);
    if(!hProcess)
    {
        std::cout << "Couldn't open process";
        return 1;
    }

    uintptr_t baseAddress = GetBaseAddress(hProcess);
    if(baseAddress == 0) {
        std::cout << "Failed to obtain base address.\n";
        CloseHandle(hProcess);
        return 1;
    }


    SIZE_T bytesRead;
    char buffer[256];

    if(ReadProcessMemory(hProcess, (LPCVOID)baseAddress, buffer, sizeof(buffer), &bytesRead))
    {
        std::cout << "The base address of "<< pid <<" is 0x" << std::hex << baseAddress << std::dec << '\n';
        std::cout << "Read successfully: " << bytesRead << '\n';
        std::cout << "Data: " << buffer << '\n';
        ListModules(hProcess);
    } else 
    {
        std::cout << "Couldn't read memory";
        return 1;
    }
    CloseHandle(hProcess);
    return 0;

}

// This reads module base address and outputs the first 256 bytes from the base address of the program
// Compile: g++ main.cpp -o main -lpsapi