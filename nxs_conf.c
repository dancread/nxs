#include <windows.h>
#include <stdio.h>
#include "nxs_conf.h"
NXS_Conf_t configuration;
BOOL NXS_ConfLoad() {
  DWORD iBytesRead;
  char *pFileContent = NULL;
  char *pConfiguration = NULL;
  char *pEqualIterator = NULL;
  char *pEqual = NULL;
  int confValueLen = 0;
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
    if(strcmp(pConfiguration, "nexus_url")){
      pEqual = pEqualIterator = strchr(pConfiguration, '=');
      confValueLen = 0;
      pEqualIterator++; // Move past '='
      pEqual++; // Move past '='
      while(*pEqualIterator != '\n' && *pEqualIterator != '\0'){
        pEqualIterator++;
        confValueLen++;
      }
      printf("%d\n", confValueLen);
      strncpy(configuration.nexus_url, pEqual, confValueLen);
      printf("%s\n",configuration.nexus_url);
      }
    pConfiguration = strtok(NULL,"\n");
  }
  return TRUE;
}
void NXS_GetValue(char *key, char *value) {

}
