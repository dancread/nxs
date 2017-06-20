#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include "nxs_http.h"

char *http_buffer;
long http_buffer_size;
void NXS_HTTPInit() {
  http_buffer_size=0;
}
void NXS_HTTPCleanUp() {
  free(http_buffer);
}
char *NXS_HTTPQuery(WCHAR *query){
  DWORD dwSize = 0;
  DWORD dwDownloaded = 0;
  LPSTR pszOutBuffer;
  BOOL  bResults = FALSE;
  WCHAR query_url[1000];
  DWORD dwFlags =
                SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
                SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
                SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
  HINTERNET  hSession = NULL,
             hConnect = NULL,
             hRequest = NULL;

  // Use WinHttpOpen to obtain a session handle.
  hSession = WinHttpOpen( L"NXS /1.0",
                          WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                          WINHTTP_NO_PROXY_NAME,
                          WINHTTP_NO_PROXY_BYPASS, 0 );

  // Specify an HTTP server.
  if( hSession )
    hConnect = WinHttpConnect( hSession, L"nexus.edi.cerner.corp",
                               INTERNET_DEFAULT_HTTPS_PORT, 0 );

  // Create an HTTP request handle.
  wcscpy(query_url,L"service/local/data_index?r=proxy&q=");
  wcscat(query_url,query);
  if( hConnect )
    hRequest = WinHttpOpenRequest( hConnect, L"GET", query_url,
                                   NULL, WINHTTP_NO_REFERER,
                                   WINHTTP_DEFAULT_ACCEPT_TYPES,
                                   WINHTTP_FLAG_SECURE );

  // Next two call are for SSL failures
  // Send a request.
  if( hRequest )
    bResults = WinHttpSendRequest( hRequest,
                                   WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                   WINHTTP_NO_REQUEST_DATA, 0,
                                   0, 0 );
  WinHttpSetOption(
                hRequest,
                WINHTTP_OPTION_SECURITY_FLAGS,
                &dwFlags,
                sizeof(dwFlags));
  if( hRequest )
    bResults = WinHttpSendRequest( hRequest,
                                   WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                   WINHTTP_NO_REQUEST_DATA, 0,
                                   0, 0 );



  // End the request.
  if( bResults )
    bResults = WinHttpReceiveResponse( hRequest, NULL );

  // Keep checking for data until there is nothing left.
  if( bResults )
  {
    do
    {
      //printf("%d\n",hRequest);
      // Check for available data.
      dwSize = 0;
      if( !WinHttpQueryDataAvailable( hRequest, &dwSize ) ) {
        printf( "Error %u in WinHttpQueryDataAvailable.\n", GetLastError( ) );
      }

      // Allocate space for the buffer.
      pszOutBuffer = malloc(dwSize+1);
      //printf("BUFFER SIZE: %d\n", dwSize);
      http_buffer_size = http_buffer_size + dwSize + 1;
      //printf("HTTP BUFFER SIZE: %d\n", http_buffer_size);
      if(!http_buffer){
        http_buffer = malloc(http_buffer_size);
        ZeroMemory( http_buffer, http_buffer_size );
      }
      else {
        http_buffer = realloc(http_buffer, http_buffer_size);
      }
      if( !pszOutBuffer || !http_buffer )
      {
        printf( "Out of memory\n" );
        //free(http_buffer);
        dwSize=0;
      }
      else
      {
        // Read the data.
        ZeroMemory( pszOutBuffer, dwSize+1 );

        if( !WinHttpReadData( hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded ) ){
          printf( "Error %u in WinHttpReadData.\n", GetLastError( ) );
        }
        else {
          //printf( "GET: %s\n", pszOutBuffer );
          //printf( "BUFFER: %s\n", http_buffer );
          if(http_buffer[0] == '\0') {
            strcpy(http_buffer, pszOutBuffer);
          }
          else {
            strcat(http_buffer,pszOutBuffer);
          }
          //printf( "BUFFER: %s\n", http_buffer );
          //printf( "%s\n", http_buffer);
        }
        // Free the memory allocated to the buffer.
        free(pszOutBuffer);
      }
    } while( dwSize > 0 );
  }


  // Report any errors.
  if( !bResults )
    printf( "Error %d has occurred.\n", GetLastError( ) );

  // Close any open handles.
  if( hRequest ) WinHttpCloseHandle( hRequest );
  if( hConnect ) WinHttpCloseHandle( hConnect );
  if( hSession ) WinHttpCloseHandle( hSession );
  //printf("HTTP Response: %s\n", http_buffer);
  return http_buffer;
}
