List all modules (DLLs and EXEs) loaded into the target process.
- Can be used to get the **base address** of the main executable


Structure
```c++
BOOL EnumProcessModules(
	HANDLE hProcess, // HANDLE from OpenProcess
	HMODULE *lphModule, // Array to store modules
	DWORD cb, // Size of array in bytes
	LPDWORD lpcbNeeded // Out parameter saying how many         bytes were returned
) 
```
**HMODULE** - handle to a module 


## Why do I need this?
You need this for `ReadProcessMemory` to get base address
