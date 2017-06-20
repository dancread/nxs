#include <windows.h>
#include "nxs.h"
int wmain(INT argc, WCHAR **argv){
  NXS_Init();
  NXS_Search(argv[1]);
  NXS_CleanUp();
  return 0;
}
