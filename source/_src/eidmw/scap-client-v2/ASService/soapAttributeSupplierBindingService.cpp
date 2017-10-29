/* soapAttributeSupplierBindingService.cpp
   Generated by gSOAP 2.8.28 from SCAP-ASService.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapAttributeSupplierBindingService.h"

AttributeSupplierBindingService::AttributeSupplierBindingService()
{	this->soap = soap_new();
	this->soap_own = true;
	AttributeSupplierBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

AttributeSupplierBindingService::AttributeSupplierBindingService(const AttributeSupplierBindingService& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
}

AttributeSupplierBindingService::AttributeSupplierBindingService(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	AttributeSupplierBindingService_init(_soap->imode, _soap->omode);
}

AttributeSupplierBindingService::AttributeSupplierBindingService(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	AttributeSupplierBindingService_init(iomode, iomode);
}

AttributeSupplierBindingService::AttributeSupplierBindingService(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	AttributeSupplierBindingService_init(imode, omode);
}

AttributeSupplierBindingService::~AttributeSupplierBindingService()
{	if (this->soap_own)
		soap_free(this->soap);
}

void AttributeSupplierBindingService::AttributeSupplierBindingService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"c14n", "http://www.w3.org/2001/10/xml-exc-c14n#", NULL, NULL},
	{"wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd", NULL, NULL},
	{"xenc", "http://www.w3.org/2001/04/xmlenc#", NULL, NULL},
	{"wsc", "http://docs.oasis-open.org/ws-sx/ws-secureconversation/200512", NULL, NULL},
	{"ds", "http://www.w3.org/2000/09/xmldsig#", NULL, NULL},
	{"wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd", "http://docs.oasis-open.org/wss/oasis-wss-wssecurity-secext-1.1.xsd", NULL},
	{"ns3", "http://www.cartaodecidadao.pt/ccc/commons/messages/Attribute", NULL, NULL},
	{"ns4", "http://www.cartaodecidadao.pt/ccc/commons/messages/Types", NULL, NULL},
	{"ns1", "http://www.cartaodecidadao.pt/ccc/sccc/services/AttributeSupplierService", NULL, NULL},
	{"ns2", "http://www.cartaodecidadao.pt/ccc/sccc/messages/AttributeSupplierService", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this->soap, namespaces);
}

void AttributeSupplierBindingService::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void AttributeSupplierBindingService::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	AttributeSupplierBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
AttributeSupplierBindingService *AttributeSupplierBindingService::copy()
{	AttributeSupplierBindingService *dup = SOAP_NEW_COPY(AttributeSupplierBindingService);
	if (dup)
		soap_copy_context(dup->soap, this->soap);
	return dup;
}
#endif

AttributeSupplierBindingService& AttributeSupplierBindingService::operator=(const AttributeSupplierBindingService& rhs)
{	if (this->soap_own)
		soap_free(this->soap);
	this->soap = rhs.soap;
	this->soap_own = false;
	return *this;
}

int AttributeSupplierBindingService::soap_close_socket()
{	return soap_closesock(this->soap);
}

int AttributeSupplierBindingService::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

int AttributeSupplierBindingService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this->soap, string, detailXML);
}

int AttributeSupplierBindingService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

int AttributeSupplierBindingService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this->soap, string, detailXML);
}

int AttributeSupplierBindingService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

void AttributeSupplierBindingService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void AttributeSupplierBindingService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *AttributeSupplierBindingService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

void AttributeSupplierBindingService::soap_noheader()
{	this->soap->header = NULL;
}

void AttributeSupplierBindingService::soap_header(struct _wsse__Security *wsse__Security)
{	::soap_header(this->soap);
	this->soap->header->wsse__Security = wsse__Security;
}

const SOAP_ENV__Header *AttributeSupplierBindingService::soap_header()
{	return this->soap->header;
}

int AttributeSupplierBindingService::run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int AttributeSupplierBindingService::ssl_run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->ssl_accept() || this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}
#endif

SOAP_SOCKET AttributeSupplierBindingService::bind(const char *host, int port, int backlog)
{	return soap_bind(this->soap, host, port, backlog);
}

SOAP_SOCKET AttributeSupplierBindingService::accept()
{	return soap_accept(this->soap);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int AttributeSupplierBindingService::ssl_accept()
{	return soap_ssl_accept(this->soap);
}
#endif

int AttributeSupplierBindingService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->soap->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->soap->max_keep_alive > 0 && !--k)
			this->soap->keep_alive = 0;
#endif

		if (soap_begin_serve(this->soap))
		{	if (this->soap->error >= SOAP_STOP)
				continue;
			return this->soap->error;
		}
		if (dispatch() || (this->soap->fserveloop && this->soap->fserveloop(this->soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this->soap);
#else
			return soap_send_fault(this->soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this->soap);
		soap_end(this->soap);
	} while (1);
#else
	} while (this->soap->keep_alive);
#endif
	return SOAP_OK;
}

static int serve___ns1__AttributeSuppliers(struct soap*, AttributeSupplierBindingService*);

int AttributeSupplierBindingService::dispatch()
{	return dispatch(this->soap);
}

int AttributeSupplierBindingService::dispatch(struct soap* soap)
{
	AttributeSupplierBindingService_init(soap->imode, soap->omode);

	soap_peek_element(soap);
    return serve___ns1__AttributeSuppliers(this);
}

static int serve___ns1__AttributeSuppliers(struct soap *soap, AttributeSupplierBindingService *service)
{	struct __ns1__AttributeSuppliers soap_tmp___ns1__AttributeSuppliers;
	ns2__AttributeSupplierResponseType ns2__AttributeSupplierResponse;
	ns2__AttributeSupplierResponse.soap_default(soap);
	soap_default___ns1__AttributeSuppliers(soap, &soap_tmp___ns1__AttributeSuppliers);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->AttributeSuppliers(ns2__AttributeSupplierResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	ns2__AttributeSupplierResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns2__AttributeSupplierResponse.soap_put(soap, "ns2:AttributeSupplierResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns2__AttributeSupplierResponse.soap_put(soap, "ns2:AttributeSupplierResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
