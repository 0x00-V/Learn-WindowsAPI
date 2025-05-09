Allows you to write data to the memory space of a process

Structure:

```cpp
BOOL WriteProcessMemory(
  HANDLE  hProcess,      // Handle to the target process
  LPVOID  lpBaseAddress, // Pointer to the address in the target process's memory where data is written
  LPCVOID lpBuffer,      // Pointer to the data to write
  SIZE_T  nSize,         // The number of bytes to write
  SIZE_T *lpNumberOfBytesWritten // The number of bytes written
);

```

`lpNumberOfBytesWritten` - Is optional. It receives the number of bytes successfully written to the targets process memory


**Return Value** - Returns a 0 if failure
- Call GetLastError() for more details


Copies data from specified buffer in the current process to the address 


## Permissions from OpenProcess 
==PROCESS_VM_WRITE== and **==PROCESS_VM_OPERATION==**


Example usage 
```cpp
int new_health_value = 999;

WriteProcessMemory(
		process_handle, // From OpenProcess
		(LPVOID)health_address, // Memory address in game
		&new_health_value, // Pointer to the data to write
		sizeof(new_health_value), // Size of the data 
		NULL // Optional: Output for how many bytes writen
);
```
