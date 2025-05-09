**OpenProcess** obtains a handle to a running process.
- Normally used in:
	- Read/write memory of other processes
	- DLL injection
	- Terminating processes
	- Getting process info



==HANDLE== - A number that the OS gives you to interact with a system resource
The handle LVALUE is defined as 
```c++
typedef void* HANDLE;
```
- A pointer used as a reference to an OS resource


**OpenProcess Function**:
```c++
HANDLE OpenProcess(
	DWORD dwDesiredAccess, // Permissions you want
	BOOL bInheritHandle, //Typically false
	DWORD dwProcessId, // The PID
)
```

==dwDesiredAccess==
- `PROCESS_QUERY_INFORMATION` - Basic info
- `PROCESS_VM_READ` - Read Memory
- `PROCESS_VM_WRITE` - Write Memory
- `PROCESS_VM_OPERATION` - Essential for memory manipulation. Needed for `VirtualAllocEx`
- `PROCESS_TERMINATE` - Kill process
- `PROCESS_ALL_ACCESS` - All permissions

==bInheritHandle== - If True, the child processes inherit handle

### RETURN Value
- Returns a HANDLE to the process.
- Returns NULL if failure occurs


Check error with `GetLastError()`


# ==**CloseHandle()**==
- Used to release a ==HANDLE== that was opened
- Tells windows that you don't need access to the target process anymore
- Similar to closing a file after opening it

Why do I need to do this?
You need to release the handle because, if you don't, it can cause a memory leak that can build up overtime

```c++
CloseHandle(hProcess);
```
***ALWAYS CLOSE HANDLE AFTER YOU'RE DONE FFS!***

## Why do I need to know this?
This is an essential function to learn, because you'll to obtain a HANDLE to a process which is utilised by many functions to interact with a process (e.g. `ReadProcessMemory`, `WriteProcessMemory`, `VirtualAllocEx`, `TerminateProcess`, etc.)
