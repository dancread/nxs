#include <windows.h>
#define NXS_CONF_FILENAME L"nxs.ini"

typedef struct {
  WCHAR nexus_server[500];
  WCHAR nexus_context[500];
} NXS_Conf_t;

/*
 * Globals
 */
NXS_Conf_t configuration;

BOOL NXS_ConfLoad();
void NXS_GetValue(WCHAR *key, WCHAR *value);
