#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <string>

DWORD GetProcessID(const wchar_t* process_name)
{
    DWORD process_id = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snapshot == INVALID_HANDLE_VALUE)
    {
        std::cout << "[X] Failed to obtain process.\n";
        return 1;
    }

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(entry);

    if(Process32FirstW(snapshot, &entry)) 
    {
        do
        {
            if (_wcsicmp(entry.szExeFile, process_name) == 0)
            {
                process_id = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapshot, &entry));
    }
    CloseHandle(snapshot);
    return process_id;

}


DWORD GetModuleBaseAddress(DWORD process_id, const std::wstring& module_name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE, process_id);
    if(snapshot == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32W me32;
    me32.dwSize = sizeof(me32);

    if(Module32FirstW(snapshot, &me32))
    {
        do 
        {
            if(_wcsicmp(me32.szModule, module_name.c_str()) == 0)
            {
                CloseHandle(snapshot);
                return reinterpret_cast<uintptr_t>(me32.modBaseAddr);
            }
        } while (Module32NextW(snapshot, &me32));
    }
    CloseHandle(snapshot);
    return 0;
}

int main()
{
    std::wstring process_name;
    std::wcout << L"Enter a program you'd like to search for: ";
    std::getline(std::wcin, process_name);
    
    DWORD process_id = GetProcessID(process_name.c_str());
    if(process_id != 0)
    {
       std::wcout << L"---------------------\n"
                  << L"Info for: " << process_name << L"\n"
                  << L"Process ID: " << process_id << L"\n"; 
        uintptr_t base_address = GetModuleBaseAddress(process_id, process_name);
        if(base_address)
        {
            std::wcout << L"Base Address: 0x" <<  std::hex << base_address << std::dec 
                       << L"\n---------------------"; 
        }
        else 
        {
            std::wcout << L"[X] Failed to obtain module base address\n";
        }
    } 
    else
    {
        std::wcout << L"[X] Couldn't find process " << process_name << L"\n";
    }
    
    return 0;
}
