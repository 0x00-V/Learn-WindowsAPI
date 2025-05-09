
**Why do I need this?**
This will be used when doing things like DLL injection
Used to start a new thread within the target process. (Will have a thread call `LoadLibraryA`)

**Structure**
```cpp
HANDLE CreateRemoteThread(
  HANDLE                 process_handle,           // Handle to the target process
  LPSECURITY_ATTRIBUTES  lpThreadAttributes, // Security attributes (usually NULL)
  SIZE_T                 dwStackSize,        // Size of the stack (0 to use default)
  LPTHREAD_START_ROUTINE lpStartAddress,     // The function to run (e.g., LoadLibraryA)
  LPVOID                 lpParameter,        // Parameter to pass (DLL path)
  DWORD                  dwCreationFlags,    // Flags for thread creation (usually 0)
  LPDWORD                lpThreadId          // Pointer to store thread ID (optional)
);
```


**Requires OpenProcess Flags**
- `PROCESS_CREATE_THREAD`
- `PROCESS_QUERY_INFORMATION`
- `PROCESS_VM_OPERATION`
- `PROCESS_VM_WRITE`
- `PROCESS_VM_READ`
Or `PROCESS_ALL_ACCESS` - Typically overkill

### Example Usage (DLL Injection)
```cpp

int main()
{
	const char* dll_path = "C:\\?"
	const char* process_name = "example.exe";

	while(!process_id)
	{
		process_id(process_name) // Some function to retreive the process id from the name
		Sleep(100);
	}

	HANDLE  process_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);

	if(process_handle && process_handle != INVALID_HANDLE_VALUE)
	{
		void* location = VirtualAllocEx(process_handle, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		HANDLE thread_handle = CreateRemoteThread(process_handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0, 0);

		if(thread_handle)
		{
			CloseHandle(thread_handle);
		}
	}

	if(process_handle)
	{
		CloseHandle(process_handle);
	}

}
```