Used to find process by name
- List modules
- Enumerate threads

```cpp
HANDLE CreateToolhelp32Snapshot(
	DWORD dwFlags, // What you want to take a snapshot of
	DWORD th32ProcessID // Target process ID ( For modules/threads otherwise, use 0)
);
```


**Commonly Used Flags**
`TH32CS_SNAPPROCESS` - Snapshot of all running processes
`TH32CS_SNAPMODULE` - All ==DLLs== of a process
`TH32CS_SNAPMODULE32` - 32-bit modules on a 64-bit archtype
`TH32CS_SNAPTHREAD` - All threats of a process


Returns ==INVALID_HANDLE_VALUE== if the handle fails to obtain process


Commonly Used:
`_wcsicmp` - string comparison


**Essential Functions**

`Process32First` / `Process32Next` - Enumerate all active processes in a system
`Module32First` / `Module32Next` - Enumerate through all DLLs and main exe loaded into the process
- Can replace EnumProcessModules
`Thread32First` / `Thread32Next` - Enumerates threads belonging to a process

### Module32First/Module32Next

Structure
```cpp
MODULEENTRY32 me32;
me32.dwSize = sizeof(MODULEENTRY32W);
```
Provides fields:
- `szModule` - Name of module
- `modBaseAddr` - Base address of module
- `modBaseSize` - Size of module in memory

Requires the process_id of the process. You can obtain the process_id like I did in the main.cpp example

**Here's how you get a base address using Module32First/Module32Next** (This is also in main.cpp)
```cpp

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

uintptr_t GetModuleBaseAddress(DWORD pid, const std::wstring& module_name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32W me32;
    me32.dwSize = sizeof(me32);

    if (Module32FirstW(snapshot, &me32)) {
        do {
            if (_wcsicmp(me32.szModule, module_name.c_str()) == 0) {
                CloseHandle(snapshot);
                return reinterpret_cast<uintptr_t>(me32.modBaseAddr);
            }
        } while (Module32NextW(snapshot, &me32));
    }

    CloseHandle(snapshot);
    return 0;
}
```




We can then pass the process_id into ==OpenProcess== to obtain a handle

