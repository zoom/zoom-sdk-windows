#include <iostream>
#include "ntundoc.h"

NTQUERYOBJECT NtQueryObject;
NTQUERYSYSTEMINFORMATION NtQuerySystemInformation;

const WCHAR wszHandleName[] = L"ZoomSDK.95E92796-3066-4b68-9EA7-BBC0DCA0498B";

void doCloseGlobalEventHandleHack() {
  // Initialize the NTAPI functions we need
  HMODULE ntdll_handle = ::GetModuleHandle(L"ntdll.dll");
  if (!ntdll_handle) {
    printf("[ERROR] Cannot load ntdll.dll. Error %ld\r\n", ::GetLastError());
    return;
  }
  NtQueryObject = reinterpret_cast<NTQUERYOBJECT>(
      GetProcAddress(ntdll_handle, "NtQueryObject"));
  NtQuerySystemInformation = reinterpret_cast<NTQUERYSYSTEMINFORMATION>(
      GetProcAddress(ntdll_handle, "NtQuerySystemInformation"));
  if (!NtQueryObject || !NtQuerySystemInformation) {
    printf("[ERROR] Cannot load all NT functions. Error %ld\r\n",
           ::GetLastError());
    return;
  }
  // Get the number of handles on the system
  DWORD buffer_size = 0;
  SYSTEM_HANDLE_INFORMATION_EX temp_info;
  NTSTATUS status = NtQuerySystemInformation(
      SystemHandleInformation, &temp_info, sizeof(temp_info), &buffer_size);
  if (!buffer_size) {
    printf("[ERROR] Get the number of handles. Error 0x%lX\r\n", status);
    return;
  }

  buffer_size += 8192;
  SYSTEM_HANDLE_INFORMATION_EX *system_handles =
      reinterpret_cast<SYSTEM_HANDLE_INFORMATION_EX *>(new BYTE[buffer_size]);
  status = NtQuerySystemInformation(SystemHandleInformation, system_handles,
                                    buffer_size, &buffer_size);
  if (STATUS_SUCCESS != status) {
    printf("[ERROR] Failed to get the handle list. Error 0x%lX\r\n", status);
    delete[] system_handles;
    return;
  }

  for (ULONG i = 0; i < system_handles->NumberOfHandles; ++i) {
    USHORT h = system_handles->Information[i].Handle;
    if (system_handles->Information[i].ProcessId != ::GetCurrentProcessId())
      continue;

    DWORD dwAccess = system_handles->Information[i].GrantedAccess;

    /* Skip handles with the following access codes as the next call
       to NtDuplicateObject() or NtQueryObject() might hang forever. */
    if ((dwAccess == 0x0012019f) || (dwAccess == 0x001a019f) ||
        (dwAccess == 0x00120189) || (dwAccess == 0x00100000)) {
      continue;
    }

    OBJECT_NAME_INFORMATION *name = NULL;
    ULONG name_size = 0;
    // Query the name information a first time to get the size of the name.
    status = NtQueryObject(reinterpret_cast<HANDLE>(h), ObjectNameInformation,
                           name, name_size, &name_size);
    if (name_size) {
      name = reinterpret_cast<OBJECT_NAME_INFORMATION *>(new BYTE[name_size]);
      // Query the name information a second time to get the name of the
      // object referenced by the handle.
      status = NtQueryObject(reinterpret_cast<HANDLE>(h), ObjectNameInformation,
                             name, name_size, &name_size);
    }

    if (!name->ObjectName.Buffer ||
        !wcsstr(name->ObjectName.Buffer, wszHandleName)) {
      delete[] name;
      continue;
    }
    printf("Found handle\r\n");

    if (!CloseHandle((HANDLE)h)) {
      printf("[ERROR] Failed to close handle\r\n");
    }

    if (name) {
      delete[] name;
    }
    break;
  }
  if (system_handles) {
    delete[] system_handles;
  }
}
