#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <tchar.h>


int main()
{
    DWORD process_id = 0000;
    DWORD new_health_value = 6969;


    // Obtain a handle with the previously learned OpenProcess
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, process_id);
    if(!hProcess)
    {
        std::cout << "[X] Couldn't open process.\n";
        return 1;
    }

    // This is the address where the health variable is stored
    // For now use cheat engine to obtain a memory address
    uintptr_t health_address = 0x0; // Memory address here 0x:


    // This is where we'll write the new_health_value to the target
    // memory location
    SIZE_T bytes_written;
    if(WriteProcessMemory(hProcess, (LPVOID)health_address, &new_health_value, sizeof(new_health_value), &bytes_written))
    {
        std::cout << "[+] Wrote value: " << new_health_value << "in the memory address 0x" << std::hex << health_address << std::dec << '\n';
        std::cout << "[+] Bytes written: " << bytes_written << '\n';
    } else 
    {
        std::cout << "[X] Failed to write to the memory region.\nError -" << GetLastError() << '\n';
        CloseHandle(hProcess);
        return -1;
    }
    CloseHandle(hProcess);
    return 0;
}

// g++ -o MemoryWriteExample.exe main.cpp -lpsapi -lkernel32