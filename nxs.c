#include <windows.h>
#include <stdio.h>
#include "nxs_http.h"
#include "nxs.h"
void PrintArtifact(NexusArtifact_t*);
int wmain(INT argc, WCHAR **argv){
  NXS_Init();
  NXS_Search(argv[1]);
  NXS_CleanUp();
  return 0;
}
void NXS_Search(WCHAR *query){
  NXS_XMLParseSearch(NXS_HTTPQuery(query));
  //NXS_HTTPQuery(query);
}
void NXS_Init(){
  NXS_HTTPInit();
}
void NXS_CleanUp(){
  // Free Allocations
}
void PrintArtifact(NexusArtifact_t *artifact){
  //printf("%s\n", artifact->artifactId); 
}
