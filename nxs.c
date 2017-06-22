#include <windows.h>
#include <stdio.h>
#include "nxs_http.h"
#include "nxs_conf.h"
#include "nxs.h"
void _NXS_PrintArtifact(NexusArtifact_t*);
void NXS_Search(WCHAR *query){
  NXS_XMLParseSearch(NXS_HTTPQuery(query), _NXS_PrintArtifact);
  //NXS_HTTPQuery(query);
}
void NXS_Init(){
  if(!NXS_ConfLoad() || !NXS_HTTPInit()){
    wprintf(L"Failed to initialize nxs.\n");
    ExitProcess(1);
  }
}
void NXS_CleanUp(){
  NXS_HTTPCleanUp();
}
void _NXS_PrintArtifact(NexusArtifact_t *artifact){
  // Skip entries with classifiers
  if(*artifact->classifier == '\0') {
    printf("%s %s %s %s\n", artifact->groupId, artifact->artifactId, artifact->version, artifact->classifier); 
  }
}
