#define NXS_CONF_FILENAME L"nxs.ini"

typedef struct {
  char nexus_server[500];
  char nexus_context[500];
} NXS_Conf_t;

BOOL NXS_ConfLoad();
void NXS_GetValue(char *key, char *value);
