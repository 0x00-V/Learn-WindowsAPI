#include <windows.h>
#include <iostream>

int main()
{
    DWORD pid = 6816; // Process ID of your choosing

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if(hProcess == NULL)
    {
        std::cout << "Failed to open process.\n";
        return 1;
    }
    std::cout << "Successfully opened process!\n";
    CloseHandle(hProcess);
    return 0;
}