# VirtualProtect
- Change memory protection of a region within your own process
	- For example - you can change a block of code from `PAGE_EXECUTE_READ` to `PAGE_EXECUTE_READWRITE` so you can modify it

**Structure**
```cpp
BOOL VirtualProtect(
	LPVOID lpAddress, // Starting address of memory region
	SIZE_T dwSize, // Size of area to change
	DWORD flNewProtect, // New protection flags: e.g. PAGE_EXECUTE_READWRITE
	PDWORD lpfOldProtect // Old protection storage
);
```


**Common Flags**
- `PAGE_READONLY`
- `PAGE_READWRITE`
- `PAGE_EXECUTE_READ`
- `PAGE_EXECUTE_READWRITE` - Used when patching code


### Example Usage
```cpp
BYTE patch[] = {0x90, 0x90}; // NOP CODE
DWORD oldProtect; // Store old protection here

if(VirtualProtect((LPVOID)0x12345678, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect))
{
	memcpy((void*)0x12345678, patch, sizeof(patch));
	// After writing your patch, restore permission
	VirtualProtect((LPVOID)0x12345678, sizeof(patch), oldProtect, &oldProtect);
} else {
    MessageBoxA(0, "Failed to change memory protection", "Error", MB_OK);
}
```

***
# VirtualProtectEx
- Change protection of a memory region in a different process so you can use `WriteProcessMemory`

**Structure**
```cpp
BOOL VirtualProtectEx(
  HANDLE hProcess,            // Process handle
  LPVOID lpAddress,           // Starting address of the region to change
  SIZE_T dwSize,              // Size of the region
  DWORD  flNewProtect,        // New protection (e.g. PAGE_EXECUTE_READWRITE)
  PDWORD lpflOldProtect       // Stores the old protection value
);
```


### Example Usage
```cpp
HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);

BYTE patch[] = { 0x90, 0x90 }; 
DWORD oldProtect;


VirtualProtectEx(hProcess, (LPVOID)targetAddress, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect);


WriteProcessMemory(hProcess, (LPVOID)targetAddress, patch, sizeof(patch), NULL);


VirtualProtectEx(hProcess, (LPVOID)targetAddress, sizeof(patch), oldProtect, &oldProtect);
```



**Requirements:**
`PROCESS_VM_OPERATION`
`PROCESS_VM_WRITE`
`PROCESS_VM_READ` - If you're using `ReadProcessMemory`
