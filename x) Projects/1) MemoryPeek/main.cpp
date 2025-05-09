#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <tchar.h>


HMODULE hModules[1024];
DWORD cbNeeded;


uintptr_t GetBaseAddress(HANDLE hProcess)
{
    
    if(EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
    {
        uintptr_t base_address = (uintptr_t)hModules[0];
        return base_address;
    }
    std::cout << "[X] Coulnd't obtain a base address\n";
    return 0;
}

void ListModules(HANDLE hProcess, uintptr_t base_address)
{
    if(base_address)
    {
        int module_count = cbNeeded / sizeof(HMODULE);
    wchar_t module_name[MAX_PATH];
    for(int i = 0; i < module_count; i++)
    {
        if(GetModuleBaseNameW(hProcess, hModules[i], module_name, MAX_PATH))
        {
            std::wcout << L"[+] Module " << module_name << L" | Module Base Address: 0x" << std::hex << (uintptr_t)hModules[i] << std::dec << '\n';
        }
    }
    }
    else 
    {
        std::cout << "[X] Failed to get modules.\n";
    }
    
}

int main()
{
    // 
    DWORD process_id = 0;
    std::cout << "[?] Enter a process ID for your target application: ";
    std::cin >> process_id;

    std::cout << "--------------------------------------------------\n";
    std::cout << "|               Process Modules                   |\n";
    std::cout << "--------------------------------------------------\n";

    // 
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
    if(!hProcess)
    {
        std::cout << "[X] Couldn't open process!\n";
        return 1;
    }


    //
    uintptr_t base_address = GetBaseAddress(hProcess);
    ListModules(hProcess, base_address);
    std::cout << "--------------------------------------------------\n";
    std::cout << "Process Information:\n";
    std::cout << "Process ID: " << process_id << '\n';
    std::cout << "Base Address: 0x" << std::hex << base_address << std::dec;
    std::cout << "\n--------------------------------------------------\n";

    CloseHandle(hProcess);

}