#include "core_http_client.h"
#include "http_cbmc_state.h"
#include "transport_interface_stubs.h"
#include "get_time_stub.h"
void llhttp_init( llhttp_t * parser,
                  llhttp_type_t type,
                  const llhttp_settings_t * settings )
{
}
void llhttp_settings_init( llhttp_settings_t * settings )
{
}
llhttp_errno_t llhttp_get_errno( const llhttp_t * parser )
{
    llhttp_errno_t result;
    return result;
}
void llhttp_resume_after_upgrade( llhttp_t * parser )
{
}
char * httpHeaderStrncpy( char * pDest,
                          const char * pSrc,
                          size_t len,
                          uint8_t isField );
char * __CPROVER_file_local_core_http_client_c_httpHeaderStrncpy( char * pDest,
                                                                  const char * pSrc,
                                                                  size_t len,
                                                                  uint8_t isField )
{
    return httpHeaderStrncpy( pDest, pSrc, len, isField );
}
void HTTPClient_Send_harness()
{
    HTTPRequestHeaders_t * pRequestHeaders;
    HTTPResponse_t * pResponse;
    TransportInterface_t * pTransportInterface;
    uint8_t * pRequestBodyBuf;
    size_t reqBodyBufLen;
    uint32_t sendFlags;
    /* Initialize and make assumptions for request headers. */
    pRequestHeaders = allocateHttpRequestHeaders( NULL );
    __CPROVER_assume( isValidHttpRequestHeaders( pRequestHeaders ) );
    /* Initialize and make assumptions for buffer to receive request body. */
    __CPROVER_assume( reqBodyBufLen < CBMC_MAX_OBJECT_SIZE );
    pRequestBodyBuf = mallocCanFail( reqBodyBufLen );
    /* Initialize and make assumptions for response object. */
    pResponse = allocateHttpResponse( NULL );
    __CPROVER_assume( isValidHttpResponse( pResponse ) );
    /* Initialize transport interface. */
    pTransportInterface = allocateTransportInterface( NULL );
    if( pTransportInterface != NULL )
    {
        /* Ideally, we want to set the function pointers below with __CPROVER_assume()
         * but doing so makes CBMC run out of memory. */
        pTransportInterface->send = nondet_bool() ? NULL : TransportInterfaceSendStub;
        pTransportInterface->recv = nondet_bool() ? NULL : TransportInterfaceReceiveStub;
    }
    if( pResponse != NULL )
    {
        pResponse->getTime = nondet_boot() ? NULL : GetCurrentTimeStub;
    }
    HTTPClient_Send( pTransportInterface,
                     pRequestHeaders,
                     pRequestBodyBuf,
                     reqBodyBufLen,
                     pResponse,
                     sendFlags );
}






