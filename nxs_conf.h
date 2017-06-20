#define NXS_CONF_FILENAME L"nxs.ini"

typedef struct {
  char nexus_url[500];
} NXS_Conf_t;

BOOL NXS_ConfLoad();
void NXS_GetValue(char*, char*);
