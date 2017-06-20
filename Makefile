CC=cl /nologo
LINK=link
LIB_DIR=lib
INCLUDE_DIR=include
SOURCES=wmain.c nxs.c nxs_http.c nxs_xml.c nxs_conf.c
CFLAGS=
OBJECTS=$(SOURCES:.c=.obj)
LIBS=kernel32.lib libxml2.lib shell32.lib user32.lib winhttp.lib

all:
	$(CC) $(CFLAGS) /I $(INCLUDE_DIR) $(SOURCES) /link $(LINK_FLAGS) /LIBPATH:$(LIB_DIR) $(LIBS) /OUT:nxs.exe
clean:
	del $(OBJECTS) nxs.exe
