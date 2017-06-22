#include <windows.h>
#include <stdio.h>
#include "nxs_conf.h"
NXS_Conf_t configuration;

void _NXS_ConfExtractValue(char *dest, char *src);
BOOL NXS_ConfLoad() {
  DWORD iBytesRead;
  char *pFileContent = NULL;
  char *pConfiguration = NULL;
  size_t file_content_size = 0;
  char buffer[200];
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
    ReadFile(hFile, &buffer, 199, &iBytesRead, NULL);
    if(!pFileContent && iBytesRead > 0){
      file_content_size = iBytesRead + 1;
      pFileContent = malloc(file_content_size);
      ZeroMemory(pFileContent, iBytesRead+1);
      strncpy(pFileContent, buffer, iBytesRead);
    }
    else if (iBytesRead > 0) {
      file_content_size = file_content_size + iBytesRead + 1;
      pFileContent = realloc(pFileContent, file_content_size);
      strncat(pFileContent, buffer, iBytesRead);
    }
  } while(iBytesRead>0);
  CloseHandle(hFile);
  //printf("%s\n", pFileContent);
  // Load configuration struct
  pConfiguration  = strtok(pFileContent, "\n");
  while (pConfiguration != NULL) {
    // +1 to move past '='
    if(strncmp(pConfiguration, "nexus_server", strlen("nexus_server"))) {
      _NXS_ConfExtractValue(configuration.nexus_server, strchr(pConfiguration, '=') + 1);
    }
    if(strncmp(pConfiguration, "nexus_context", strlen("nexus_context"))) {
      _NXS_ConfExtractValue(configuration.nexus_context, strchr(pConfiguration, '=') + 1);
    }
    pConfiguration = strtok(NULL,"\n");
  }
  return TRUE;
}
void NXS_GetValue(char *key, char *value) {
 if(strcmp(key,"nexus_server")) {
    value = configuration.nexus_server;
  } 
 if(strcmp(key,"nexus_context")) {
    value = configuration.nexus_context;
  } 
}
void _NXS_ConfExtractValue(char *dest, char *src) {
  char *ptr = NULL;
  int length = 0;
  ptr = src;
  while(*ptr != '\n' && *ptr != '\0'){
    ptr++;
    length++;
  }
  printf("%d ", length);
  printf("%s\n",src);
  strncpy(dest, src, length);
}
