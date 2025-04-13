Essential for reading variables within another process
- Allows you to read memory of another process

Requires Knowledge of ==OpenProcess== to obtain process handle, and ==EnumProcessModules==`

Structure:
```c++
BOOL ReadProcessMemory(
	HANDLE hProcess, // Handle to the target
	LPCVOID lpBaseAddress, // Address to read from
	LPVOID lpBuffer, // Buffer to store read data
	SIZE_T nSize, // Number of bytes to read
	SITE_T* lpNumberOfBytesRead // Bytes that have been read
)
```

**LPVOID** - Pointer to any type 
**LPCVOID** - 32-bit pointer to a constant of any type
**SIZE_T** - Represent size of an object/number of elements in the array (unsigned int btw)


**Parameters**
- `hProcess` - the handle of the process obtained by `OpenProcess`
- `lpBaseAddress` - Address in the target process's memory to start reading
- `lpBuffer` - Pointer to a buffer that will receive data read from the process
	

\* A **buffer** is a temp storage area btw