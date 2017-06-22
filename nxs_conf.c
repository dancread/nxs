#include <windows.h>
#include <stdio.h>
#include "nxs.h"
#include "nxs_conf.h"

#define READ_BUFFER_SIZE 200
void _NXS_ConfExtractValue(WCHAR *dest, WCHAR *src);
BOOL NXS_ConfLoad() {
  DWORD iBytesRead;
  WCHAR *pFileContent = NULL;
  WCHAR *pConfiguration = NULL;
  size_t file_content_size = 0;
  WCHAR buffer[READ_BUFFER_SIZE];
  WCHAR *ptrTok;
  HANDLE hFile = CreateFileW(NXS_CONF_FILENAME,               // file to open
                       GENERIC_READ,          // open for reading
                       FILE_SHARE_READ,       // share for reading
                       NULL,                  // default security
                       OPEN_EXISTING,         // existing file only
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);                 // no attr. template
  if (hFile == INVALID_HANDLE_VALUE) {
    wprintf(L"Unable to open configuration file %s.\n", NXS_CONF_FILENAME);
    return FALSE;
  }
  // TODO: Ugh, weird loop, fix
  do {
    ReadFile(hFile, &buffer, sizeof(WCHAR) * READ_BUFFER_SIZE, &iBytesRead, NULL);
    //wprintf(L"%d ",iBytesRead);
    //wprintf(L"%s\n",buffer);
    if(!pFileContent && iBytesRead > 0){
      file_content_size = iBytesRead + sizeof(WCHAR);
      pFileContent = malloc(file_content_size);
      ZeroMemory(pFileContent, iBytesRead + sizeof(WCHAR));
      //strncpy(pFileContent, buffer, iBytesRead);
      memcpy(pFileContent, buffer, iBytesRead);
      //wprintf(L"malloc %s\n", pFileContent);
    }
    else if (iBytesRead > 0) {
      file_content_size = file_content_size + iBytesRead + sizeof(WCHAR);
      pFileContent = realloc(pFileContent, file_content_size);
      wcscat(pFileContent, buffer);
      //wprintf(L"realloc %s\n", pFileContent);
    }
  } while(iBytesRead>0);
  CloseHandle(hFile);
  // Load configuration struct
  pConfiguration  = wcstok(pFileContent, L"\n", &ptrTok);
  while (pConfiguration != NULL) {
    // +1 to move past '='
    if(wcsncmp(L"nexus_server", pConfiguration, wcslen(L"nexus_server"))) {
      _NXS_ConfExtractValue(configuration.nexus_server, wcschr(pConfiguration, '=') + 1);
    }
    if(wcsncmp(L"nexus_context", pConfiguration, wcslen(L"nexus_context"))) {
      _NXS_ConfExtractValue(configuration.nexus_context, wcschr(pConfiguration, '=') + 1);
    }
    pConfiguration = wcstok(NULL,L"\n", &ptrTok);
  }
  return TRUE;
}
void NXS_GetValue(WCHAR *key, WCHAR *value) {
 if(wcscmp(key,L"nexus_server")) {
    value = configuration.nexus_server;
  }
 if(wcscmp(key,L"nexus_context")) {
    value = configuration.nexus_context;
  }
}
void _NXS_ConfExtractValue(WCHAR *dest, WCHAR *src) {
  WCHAR *ptr = NULL;
  INT length = 0;
  ptr = src;
  while(*ptr != '\n' && *ptr != '\0'){
    ptr++;
    length++;
  }
  wcsncpy(dest, src, length-1);
  //wprintf(L"%d ", length);
  //wprintf(L"%s\n",dest);
}
