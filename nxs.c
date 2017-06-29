#include <windows.h>
#include <stdio.h>
#include "nxs_artifact.h"
#include "nxs_http.h"
#include "nxs_conf.h"
#include "nxs.h"
char lastGroupIdEntry[300];
char lastArtifactIdEntry[300];
NexusArtifact_t *artifacts[];
int artifacts_length;
int artifact_count;
void _NXS_PrintArtifacts(NexusArtifact_t*);
void _NXS_AddArtifact(NexusArtifact_t*);
void NXS_Search(WCHAR *query){
  NXS_XMLParseSearch(NXS_HTTPQuery(query), _NXS_AddArtifact);
  _NXS_PrintArtifacts();
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
void _NXS_PrintArtifact(){
  // Skip entries with classifiers
  if(*artifact->classifier == '\0') {
    if(strncmp(artifact->groupId, lastGroupIdEntry, 300) == 0) {
      //printf("artifact: %s\n", lastArtifactIdEntry);
      if(strncmp(artifact->artifactId, lastArtifactIdEntry, 300) == 0) {
        printf("\t\t%s\n", artifact->version); 
      }
      else {
        printf("\t%s\n", artifact->artifactId);
      }
      strcpy(lastArtifactIdEntry,artifact->artifactId);
    }
    else {
      printf("%s\n", artifact->groupId);
    }
    strcpy(lastGroupIdEntry,artifact->groupId);
  }
}
void _NXS_AddArtifact(NexusArtifact_t* artifact) {
  if(!artifacts) {
    artifact_count = 0;
    artifacts_length = sizeof(NexusArtifact_t) * 5;
    artifacts = malloc(artifacts_length); 
  }
  else if(artifacts_count == rtifacts_length){
    artifacts_length += sizeof(NexusArtifact_t) * 5;
    artifacts = realloc(artifacts, sizeof(NexusArtifact_t) * artifacts_length); 
  }
  NXS_ArtifactCopy(&artifacts[artifacts_count], artifact);

}
