typedef struct {
  char *artifactId;
  char *version;
  char *groupId;
  char *resourceURI;
} NexusArtifact_t;
typedef struct{
  char *repository;
  char *artifactId;
  char *version;
  char *groupId;
  char *resourceURI;
} NexusSearch_t;


void NXS_Init();
void NXS_CleanUp();
void NXS_Search(WCHAR*);
//void NXS_Upload();
//void NXS_Delete();
