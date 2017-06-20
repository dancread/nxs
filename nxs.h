#include <windows.h>
#define STRING_SIZE 1000

typedef struct {
  char repository[STRING_SIZE];
  char artifactId[STRING_SIZE];
  char version[STRING_SIZE];
  char groupId[STRING_SIZE];
  char classifier[STRING_SIZE];
  char resourceURI[STRING_SIZE];
} NexusArtifact_t;
typedef struct {
  char repository[STRING_SIZE];
  char artifactId[STRING_SIZE];
  char version[STRING_SIZE];
  char groupId[STRING_SIZE];
  char classifier[STRING_SIZE];
} NexusSearch_t;


void NXS_Init();
void NXS_CleanUp();
void NXS_Search(WCHAR*);
//void NXS_Upload();
//void NXS_Delete();
