//STD Library
#include <iostream>
#include <string>

#include <QUuid>
#include <QByteArray>

#include "cmdServices.h"
#include "cmdErrors.h"
#include "WSHttpBinding_USCORECCMovelSignature.nsmap"
#include "soapWSHttpBinding_USCORECCMovelSignatureProxy.h"

#include "Util.h"
#include "Config.h"
#include "MiscUtil.h"

#define CC_MOVEL_SERVICE_GET_CERTIFICATE    ( (char *)"http://Ama.Authentication.Service/CCMovelSignature/GetCertificate" )
#define CC_MOVEL_SERVICE_SIGN               ( (char *)"http://Ama.Authentication.Service/CCMovelSignature/CCMovelSign" )
#define CC_MOVEL_SERVICE_VALIDATE_OTP       ( (char *)"http://Ama.Authentication.Service/CCMovelSignature/ValidateOtp" )
#define ENDPOINT_CC_MOVEL_SIGNATURE         ( (const char *)"/Ama.Authentication.Service/CCMovelSignature.svc" )

#define STR_EMPTY                           ""
#define SOAP_MAX_RETRIES                    3

#define SOAP_RECV_TIMEOUT_DEFAULT           10 /*20*/
#define SOAP_SEND_TIMEOUT_DEFAULT           10 /*20*/
#define SOAP_CONNECT_TIMEOUT_DEFAULT        10 /*20*/
#define SOAP_MUST_NO_UNDERSTAND             0
#define SOAP_MUST_UNDERSTAND                1

static char logBuf[512];

namespace eIDMW{

/*  *********************************************************
    ***    CMDServices::CMDServices()       ***
    ********************************************************* */
xsd__base64Binary *encode_base64( soap *sp, std::string in_str ){

    if ( sp == NULL ){
        MWLOG_ERR( logBuf, "Null soap" );
        return NULL;
    }

    xsd__base64Binary *encoded = NULL;
    if ( in_str.empty() ){
        MWLOG_ERR( logBuf, "Empty in_str" );
        return NULL;
    }

    int len;
    char *c_ptr = getCPtr( in_str, &len );
    encoded = soap_new_set_xsd__base64Binary( sp
                                            , (unsigned char *)c_ptr, len
                                            , NULL, NULL, NULL);

    if ( encoded == NULL ){
        /* this is the same pointer as encoded->__ptr */
        if ( c_ptr != NULL ) free( c_ptr );
    }

    return encoded;
}

/*  *********************************************************
    ***    handleError()                                  ***
    ********************************************************* */
int handleError( WSHttpBinding_USCORECCMovelSignatureProxy proxy, int ret ){
    if ( ret != SOAP_OK ) {
        if ( ( proxy.soap_fault() != NULL )
            && ( proxy.soap_fault()->faultstring)) {
            MWLOG_ERR( logBuf
                        , "SOAP Fault! %s"
                        , proxy.soap_fault()->faultstring );
        }
        else{
            MWLOG_ERR( logBuf, "Unknown SOAP Fault! - ret: %d", ret );
        }

        return ret;
    }

    MWLOG_INFO( logBuf, "No Error" );
    return SOAP_OK;
}

/*  *******************************************************************************************************************
    ****
    **** CMDServices class - general methods
    ****
    ******************************************************************************************************************* */

/*  *********************************************************
    ***    CMDServices::CMDServices()                     ***
    ********************************************************* */
CMDServices::CMDServices( const char *endpoint ) {
    if ( !init( SOAP_RECV_TIMEOUT_DEFAULT
              , SOAP_SEND_TIMEOUT_DEFAULT
              , SOAP_CONNECT_TIMEOUT_DEFAULT
              , SOAP_MUST_NO_UNDERSTAND ) ) 
        return;

    const char *new_endpoint = NULL;
    std::string cmd_host = utilStringNarrow(CConfig::GetString(CConfig::EIDMW_CONFIG_PARAM_GENERAL_CMD_HOST));
    std::string cmd_endpoint = "https://" + cmd_host + ENDPOINT_CC_MOVEL_SIGNATURE;
      
    new_endpoint = ( NULL == endpoint ) ? cmd_endpoint.c_str() : endpoint;

    MWLOG_DEBUG(logBuf, "Using Endpoint: %s", new_endpoint);

    setEndPoint(strdup(new_endpoint));
}

/*  *********************************************************
    ***    CMDServices::~CMDServices()                    ***
    ********************************************************* */
CMDServices::~CMDServices() {
    soap *sp = getSoap();
    if ( NULL == sp ) return;

    soap_destroy( sp );
    soap_end( sp );

    setSoap( NULL );
}

/*  *********************************************************
    ***    CMDServices::init()                            ***
    ********************************************************* */
bool CMDServices::init(int recv_timeout, int send_timeout,
                        int connect_timeout, short mustUnderstand) {
    soap *sp = soap_new2( SOAP_C_UTFSTRING, SOAP_C_UTFSTRING );
    if ( sp == NULL ){
        MWLOG_ERR( logBuf, "Null soap" );
        return false;
    }

    setUserId( STR_EMPTY );

    //Don't change this: it serves as authentication for the service
    setApplicationID( std::string( "264af13f-c287-4703-9add-10a303b951a3" ) );

    //Define appropriate network timeouts
    sp->recv_timeout = recv_timeout;
    sp->send_timeout = send_timeout;
    sp->connect_timeout = connect_timeout;

    //Dont output mustUnderstand attributes
    sp->mustUnderstand = mustUnderstand;

    //TODO: this disables server certificate verification!!
    int ret = soap_ssl_client_context( sp
                                    , SOAP_SSL_NO_AUTHENTICATION
                                    , NULL, NULL, NULL, NULL, NULL );
    if ( ret != SOAP_OK ){
        soap_destroy( sp );
        setSoap( NULL );

        MWLOG_ERR( logBuf, "soap_ssl_client_context() failed - code: %d", ret );
        return false;
    }

    setSoap( sp );

    return true;
}

/*  *********************************************************
    ***    CMDServices::getSoap()                         ***
    ********************************************************* */
soap *CMDServices::getSoap(){
    return m_soap;
}

/*  *********************************************************
    ***    CMDServices::setSoap()                         ***
    ********************************************************* */
void CMDServices::setSoap( soap *in_soap ){
    m_soap = in_soap;
}

/*  *********************************************************
    ***    CMDServices::setEndPoint()                     ***
    ********************************************************* */
void CMDServices::setEndPoint( const char *endpoint ){
    m_endpoint = endpoint;
}

/*  *********************************************************
    ***    CMDServices::getEndPoint()                     ***
    ********************************************************* */
const char *CMDServices::getEndPoint(){
    return m_endpoint;
}

/*  *********************************************************
    ***    CMDServices::getProcessID()                    ***
    ********************************************************* */
std::string CMDServices::getProcessID(){
    return m_processID;
}

/*  *********************************************************
    ***    CMDServices::setProcessID()                    ***
    ********************************************************* */
void CMDServices::setProcessID( std::string processID ){
    m_processID = processID;
}

/*  *********************************************************
    ***    CMDServices::getApplicationID()                ***
    ********************************************************* */
std::string CMDServices::getApplicationID(){
    return m_applicationID;
}

/*  *********************************************************
    ***    CMDServices::setApplicationID()                ***
    ********************************************************* */
void CMDServices::setApplicationID( std::string applicationID ){
    m_applicationID = applicationID;
}

/*  *********************************************************
    ***    CMDServices::getUserId()                       ***
    ********************************************************* */
std::string CMDServices::getUserId(){
    return m_userId;
}

/*  *********************************************************
    ***    CMDServices::setUserId()                       ***
    ********************************************************* */
void CMDServices::setUserId( std::string in_userId ){
    m_userId = in_userId;
}

QString generateMsgID() {
    QUuid mmg_UUID = QUuid::createUuid();
    return mmg_UUID.toString();
}

/*  *******************************************************************************************************************
    ****
    **** GetCertificate
    ****
    ******************************************************************************************************************* */

/*  *********************************************************
    ***    CMDServices::get_GetCertificateRequest()       ***
    ********************************************************* */
_ns2__GetCertificate *CMDServices::get_GetCertificateRequest(soap *sp
                                                , char *endpoint
                                                , std::string in_applicationID
                                                , std::string *in_userId) {
    SOAP_ENV__Header *soapHeader = soap_new_SOAP_ENV__Header( sp );
    soapHeader->wsa__To = endpoint;

    soapHeader->wsa__Action = CC_MOVEL_SERVICE_GET_CERTIFICATE;

    //Set the created header in our soap structure
    sp->header = soapHeader;

    _ns2__GetCertificate *send = soap_new__ns2__GetCertificate( sp );
    if ( NULL == send ) return send;

    send->applicationId = encode_base64( sp, in_applicationID );
    send->userId        = in_userId;

    return send;
}

/*  *********************************************************
    ***    CMDServices::checkGetCertificateResponse()     ***
    ********************************************************* */
int CMDServices::checkGetCertificateResponse(
                                    _ns2__GetCertificateResponse *response ){
    if ( response == NULL ){
        MWLOG_ERR( logBuf, "Null response" );
        return ERR_NULL_HANDLER;
    }

    if ( response->GetCertificateResult == NULL ){
        MWLOG_ERR( logBuf, "Null GetCertificateResult" );
        return ERR_NULL_DATA;
    }

    return ERR_NONE;
}

/*  *********************************************************
    ***    CMDServices::GetCertificate()                  ***
    ********************************************************* */
int CMDServices::GetCertificate( std::string in_userId
                                , char **out_certificate
                                , int *out_certificateLen ){
    soap *sp = getSoap();
    if ( sp == NULL ){
        MWLOG_ERR( logBuf, "Null soap" );
        return ERR_NULL_HANDLER;
    }

    if ( in_userId.empty() ){
        MWLOG_ERR( logBuf, "Empty userId" );
        return ERR_INV_USERID;
    }

    const char *endPoint = getEndPoint();
    WSHttpBinding_USCORECCMovelSignatureProxy proxy
                            = WSHttpBinding_USCORECCMovelSignatureProxy( sp );
    proxy.soap_endpoint = endPoint;

    /*
        Get GetCertificate request
    */
    _ns2__GetCertificate *send = get_GetCertificateRequest( sp
                                                        , (char*)endPoint
                                                        , getApplicationID()
                                                        , &in_userId );
    if ( send == NULL ) {
        MWLOG_ERR( logBuf, "NULL send parameters" );
        return ERR_NULL_HANDLER;
    }

    QByteArray msg_id = generateMsgID().toUtf8();
    sp->header->wsa__MessageID = (char *) msg_id.constData();

    /*
        Call GetCertificate service
    */
    _ns2__GetCertificateResponse response;
    int ret;

    ret = proxy.GetCertificate( send, response );

    /* Clean pointers before exit */
    if ( send->applicationId != NULL ) {
        if ( send->applicationId->__ptr != NULL )
            free( send->applicationId->__ptr );
    }

    /* Handling errors */
    if ( handleError( proxy, ret ) != ERR_NONE ) return ret;

    /* Validate response */
    ret = checkGetCertificateResponse( &response );
    if ( ret != ERR_NONE ) return ret;

    /* Process X509Certificate */
    if ( out_certificate != NULL ){
        *out_certificate = getCPtr( *response.GetCertificateResult
                                    , out_certificateLen );
    }

    return ERR_NONE;
}

/*  *******************************************************************************************************************
    ****
    **** CCMovelSign
    ****
    ******************************************************************************************************************* */

/*  *********************************************************
    ***    CMDServices::get_CCMovelSignRequest()          ***
    ********************************************************* */
_ns2__CCMovelSign *CMDServices::get_CCMovelSignRequest(
                                                soap *sp
                                              , char *endpoint
                                              , std::string in_applicationID
                                              , std::string in_hash
                                              , std::string in_pin
                                              , std::string *in_userId ){
    SOAP_ENV__Header *soapHeader = soap_new_SOAP_ENV__Header( sp );
    soapHeader->wsa__To = endpoint;

    soapHeader->wsa__Action = CC_MOVEL_SERVICE_SIGN;

    //Set the created header in our soap structure
    sp->header = soapHeader;

    _ns3__SignRequest *soapBody = soap_new_ns3__SignRequest( sp );

    soapBody->ApplicationId = encode_base64( sp, in_applicationID );
    soapBody->Hash          = encode_base64( sp, in_hash );
    soapBody->Pin           = encode_base64( sp, in_pin );
    soapBody->UserId        = in_userId;

    _ns2__CCMovelSign *send = soap_new_set__ns2__CCMovelSign( sp, soapBody );
    return send;
}

/*  *********************************************************
    ***    CMDServices::checkCCMovelSignResponse()        ***
    ********************************************************* */
int CMDServices::checkCCMovelSignResponse( _ns2__CCMovelSignResponse *response ){
    if ( response == NULL ){
        MWLOG_ERR( logBuf, "Null response" );
        return ERR_NULL_HANDLER;
    }

    if ( response->CCMovelSignResult == NULL ){
        MWLOG_ERR( logBuf, "Null CCMovelSignResult" );
        return ERR_NULL_DATA;
    }

    return ERR_NONE;
}

/*  *********************************************************
    ***    CMDServices::CCMovelSign()                     ***
    ********************************************************* */
int CMDServices::CCMovelSign( std::string in_hash, std::string in_pin ){

    soap *sp = getSoap();
    if ( sp == NULL ){
        MWLOG_ERR( logBuf, "Null soap" );
        return ERR_NULL_HANDLER;
    }

    if ( in_hash.empty() ){
        MWLOG_ERR( logBuf, "Empty hash" );
        return ERR_INV_HASH;
    }

    if ( in_pin.empty() ){
        MWLOG_ERR( logBuf, "Empty pin" );
        return ERR_INV_USERPIN;
    }

    std::string in_userId = getUserId();
    if ( in_userId.empty() ){
        MWLOG_ERR( logBuf, "Empty userId" );
        return ERR_INV_USERID;
    }

    /*
        ProcessID initialization
    */
    setProcessID( STR_EMPTY );

    const char *endPoint = getEndPoint();
    WSHttpBinding_USCORECCMovelSignatureProxy proxy
                            = WSHttpBinding_USCORECCMovelSignatureProxy( sp );
    proxy.soap_endpoint = endPoint;

    QByteArray msg_id = generateMsgID().toUtf8();
    sp->header->wsa__MessageID = (char *) msg_id.constData();

    /*
        Get CCMovelSign request
    */
    _ns2__CCMovelSign *send = get_CCMovelSignRequest( sp
                                                    , (char*)endPoint
                                                    , getApplicationID()
                                                    , in_hash, in_pin
                                                    , &in_userId );
    if ( send == NULL ){
        MWLOG_ERR( logBuf, "NULL send parameters" );
        return ERR_NULL_HANDLER;
    }

    /*
        Call CCMovelSign service
    */
    _ns2__CCMovelSignResponse response;
    int ret;
    ret = proxy.CCMovelSign( NULL, NULL, send, response );

    /* Clean pointers before exit */
    if ( send->request != NULL ){
        /* Clean pointers before leaving function */
        if ( send->request->Pin != NULL ){
            if ( send->request->Pin->__ptr != NULL )
                free( send->request->Pin->__ptr );
        }

        if ( send->request->Hash != NULL ){
            if ( send->request->Hash->__ptr != NULL )
                free( send->request->Hash->__ptr );
        }

        if ( send->request->ApplicationId != NULL ){
            if ( send->request->ApplicationId->__ptr != NULL )
                free( send->request->ApplicationId->__ptr );
        }
    }

    /* Handling errors */
    if ( handleError( proxy, ret ) != ERR_NONE ) return ret;

    /* Validate response */
    ret = checkCCMovelSignResponse( &response );
    if ( ret != ERR_NONE ) return ret;

    /* Save ProcessId */
    cout << "ProcessId: " << *response.CCMovelSignResult->ProcessId << endl;
    setProcessID( *response.CCMovelSignResult->ProcessId );

    return ERR_NONE;
}

/*  *******************************************************************************************************************
    ****
    **** ValidateOtp
    ****
    ******************************************************************************************************************* */

/*  *********************************************************
    ***    CMDServices::get_ValidateOtpRequest()          ***
    ********************************************************* */
_ns2__ValidateOtp *CMDServices::get_ValidateOtpRequest(  soap *sp
                                                      , char *endpoint
                                                      , std::string in_applicationID
                                                      , std::string *in_code
                                                      , std::string *in_processId ){
    SOAP_ENV__Header *soapHeader = soap_new_SOAP_ENV__Header( sp );
    soapHeader->wsa__To = endpoint;

    soapHeader->wsa__Action = CC_MOVEL_SERVICE_VALIDATE_OTP;

    //Set the created header in our soap structure
    sp->header = soapHeader;

    _ns2__ValidateOtp *send = soap_new__ns2__ValidateOtp( sp );
    if ( send == NULL ) return NULL;

    send->code          = in_code;
    send->processId     = in_processId;
    send->applicationId = encode_base64( sp, in_applicationID );

    return send;
}

/*  *********************************************************
    ***    CMDServices::checkValidateOtpResponse()        ***
    ********************************************************* */
int CMDServices::checkValidateOtpResponse( _ns2__ValidateOtpResponse *response ){
    if ( response == NULL ) {
        MWLOG_ERR( logBuf, "Null response" );
        return ERR_NULL_HANDLER;
    }

    if ( response->ValidateOtpResult == NULL ) {
        MWLOG_ERR( logBuf, "Null ValidateOtpResult" );
        return ERR_NULL_HANDLER;
    }

    if ( response->ValidateOtpResult->Signature == NULL ) {
        MWLOG_ERR( logBuf, "Null Signature" );
        return ERR_NULL_HANDLER;
    }

    if ( response->ValidateOtpResult->Signature->__ptr == NULL ) {
        MWLOG_ERR( logBuf, "Null Signature pointer" );
        return ERR_NULL_DATA;
    }

    if ( response->ValidateOtpResult->Signature->__size < 1 ) {
        MWLOG_ERR( logBuf, "Invalide Signature pointer size: %d",
                  response->ValidateOtpResult->Signature->__size);
        return ERR_SIZE;
    }

    return ERR_NONE;
}

/*  *********************************************************
    ***    CMDServices::ValidateOtp()                     ***
    ********************************************************* */
int CMDServices::ValidateOtp( std::string in_code
                            , unsigned char **outSignature
                            , unsigned int *outSignatureLen) {
    soap *sp = getSoap();
    if ( sp == NULL ){
        MWLOG_ERR( logBuf, "Null soap" );
        return ERR_NULL_HANDLER;
    }

    if ( in_code.empty() ){
        MWLOG_ERR( logBuf, "Empty code" );
        return ERR_INV_CODE;
    }

    std::string code = in_code;
    std::string processId = getProcessID();
    const char *endPoint = getEndPoint();

    WSHttpBinding_USCORECCMovelSignatureProxy proxy
                            = WSHttpBinding_USCORECCMovelSignatureProxy( sp );
    proxy.soap_endpoint = endPoint;

    QByteArray msg_id = generateMsgID().toUtf8();
    sp->header->wsa__MessageID = (char *) msg_id.constData();

    /*
        Get ValidateOtp request
    */
    _ns2__ValidateOtp *send = get_ValidateOtpRequest(sp
                                                     , (char*)endPoint
                                                     , getApplicationID()
                                                     , &code
                                                     , &processId );

    if ( send == NULL ){
        MWLOG_ERR( logBuf, "Null send parameters" );
        return ERR_NULL_HANDLER;
    }

    /*
        Call ValidateOtp service
    */
    _ns2__ValidateOtpResponse response;
    int ret;
    ret = proxy.ValidateOtp( NULL, NULL, send, response );


    /* Clean pointers before exit */
    if ( send->applicationId != NULL ){
        if ( send->applicationId->__ptr != NULL )
            free( send->applicationId->__ptr );
    }

    /* Handling errors */
    if ( handleError( proxy, ret ) != ERR_NONE ) return ret;

    /* Validate response */
    ret = checkValidateOtpResponse( &response );
    if ( ret != ERR_NONE ) return ret;

    /* Set signature */
    if ( ( outSignature != NULL ) && ( outSignatureLen != NULL ) ) {
        *outSignature =
            (unsigned char*)malloc(
                            response.ValidateOtpResult->Signature->__size );

        if ( outSignature == NULL ) {
            MWLOG_ERR( logBuf, "Malloc fail!" );
            return ERR_NULL_HANDLER;
        }

        memcpy( *outSignature
                , response.ValidateOtpResult->Signature->__ptr
                , response.ValidateOtpResult->Signature->__size );

        *outSignatureLen = response.ValidateOtpResult->Signature->__size;
    }

    return ERR_NONE;
}

/*  *******************************************************************************************************************
    ****
    **** Functions visible to the outside
    ****
    ******************************************************************************************************************* */

/*  *********************************************************
    ***    CMDServices::getCertificate()                  ***
    ********************************************************* */
int CMDServices::getCertificate(std::string in_userId,
                                 std::vector<CByteArray> &out_cb)   {
    CByteArray empty_certificate;

    if ( in_userId.empty() ) {
        MWLOG_ERR( logBuf, "Empty userId" );
        return ERR_INV_USERID;
    }

    char *p_certificate = NULL;
    int certificateLen = 0;

    int ret = GetCertificate( in_userId, &p_certificate, &certificateLen );
    if (ret != ERR_NONE)
        return ret;

    std::vector<std::string> certs = toPEM(p_certificate, certificateLen );
    free(p_certificate);

    for (int i=0; i != certs.size(); i++)
    {
        CByteArray ba;
        unsigned char *der = NULL;
        int derLen = PEM_to_DER((char *)certs.at(i).c_str(), &der);

       if ( derLen < 0 ) {
         MWLOG_ERR( logBuf, "PEM -> DER conversion failed - len: %d", derLen );
         return ERR_INV_CERTIFICATE;

       }
       ba.Append( (const unsigned char *)der, (unsigned long)derLen );
       out_cb.push_back(ba);
    }

    
    /* Set variables */
    setUserId( in_userId );

    return ERR_NONE;
}

/*  *********************************************************
    ***    CMDServices::sendDataToSign()                  ***
    ********************************************************* */
int CMDServices::sendDataToSign( std::string in_hash, std::string in_pin ){
    return CCMovelSign( in_hash, in_pin );
}

/*  *********************************************************
    ***    CMDServices::getSignature()                    ***
    ********************************************************* */
int CMDServices::getSignature( std::string in_code, CByteArray& out_cb ){
    unsigned int signLen = 0;
    unsigned char *sign = NULL;

    int ret = ValidateOtp( in_code, &sign, &signLen );
    if ( ret != ERR_NONE ){
        MWLOG_ERR( logBuf, "ValidateOtp failed" );
        return ret;
    }

    if ( NULL == sign ){
        MWLOG_ERR( logBuf, "Null signature" );
        return ERR_NULL_HANDLER;
    }

    if ( signLen <= 0 ){
        free( sign );

        MWLOG_ERR( logBuf, "Invalid signature length: %d", signLen );
        return ERR_SIZE;
    }

    out_cb.ClearContents();
    out_cb.Append( (const unsigned char *)sign, (unsigned long)signLen );

    free( sign );

    return ERR_NONE;
}


}
