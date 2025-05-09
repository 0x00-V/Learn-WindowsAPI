#include <windows.h>
#include <iostream>
#include <psapi.h>


DWORD GetBaseAddress(DWORD processId)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if(!hProcess)
    {
        std::cout << "Couldn't open process.\n";
        return 0;
    }
    
    HMODULE hModules[1024];
    DWORD cbNeeded;

    if(EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        uintptr_t baseAddress = (uintptr_t)hModules[0]; // Base address of first module (target.exe)
        CloseHandle(hProcess);
        return baseAddress;
    }
    CloseHandle(hProcess);
    std::cout << "Couldn't obtain base address.\n";
    return 0;
}


int main()
{
    DWORD pid = 14068; // Your process ID here
    DWORD base = GetBaseAddress(pid);

    if(base == 0) return 1;
    
    std::cout << "The base address of " << pid << "is: 0x" << std::hex << base << std::dec << '\n';
    return 0;
}