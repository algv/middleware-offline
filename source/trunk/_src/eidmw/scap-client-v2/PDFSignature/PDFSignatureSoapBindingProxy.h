/* PDFSignaturePDFSignatureSoapBindingProxy.h
   Generated by gSOAP 2.8.28 from SCAP-PDFSignature.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef PDFSignaturePDFSignatureSoapBindingProxy_H
#define PDFSignaturePDFSignatureSoapBindingProxy_H
#include "PDFSignatureH.h"

namespace PDFSignature {

class SOAP_CMAC PDFSignatureSoapBindingProxy
{ public:
	struct soap *soap;
	bool soap_own;
	/// Endpoint URL of service 'PDFSignatureSoapBindingProxy' (change as needed)
	const char *soap_endpoint;
	/// Variables globally declared in SCAP-PDFSignature.h (non-static)
	/// Constructor
	PDFSignatureSoapBindingProxy();
	/// Copy constructor
	PDFSignatureSoapBindingProxy(const PDFSignatureSoapBindingProxy& rhs);
	/// Constructor to use/share an engine state
	PDFSignatureSoapBindingProxy(struct soap*);
	/// Constructor with endpoint URL
	PDFSignatureSoapBindingProxy(const char *url);
	/// Constructor with engine input+output mode control
	PDFSignatureSoapBindingProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	PDFSignatureSoapBindingProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	PDFSignatureSoapBindingProxy(soap_mode imode, soap_mode omode);
	/// Destructor deletes non-shared engine context only (use destroy() to delete deserialized data)
	virtual	~PDFSignatureSoapBindingProxy();
	/// Initializer used by constructors
	virtual	void PDFSignatureSoapBindingProxy_init(soap_mode imode, soap_mode omode);
	/// Create a new copy
	virtual	PDFSignatureSoapBindingProxy *copy() SOAP_PURE_VIRTUAL;
	/// Copy assignment
	PDFSignatureSoapBindingProxy& operator=(const PDFSignatureSoapBindingProxy&);
	/// Delete all deserialized data (with soap_destroy and soap_end)
	virtual	void destroy();
	/// Delete all deserialized data and reset to default
	virtual	void reset();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif

	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'Sign' (returns error code or SOAP_OK)
	virtual	int Sign(ns1__SignRequest *ns1__SignRequest_, ns1__SignResponse &ns1__SignResponse_) { return this->Sign(NULL, NULL, ns1__SignRequest_, ns1__SignResponse_); }
	virtual	int Sign(const char *endpoint, const char *soap_action, ns1__SignRequest *ns1__SignRequest_, ns1__SignResponse &ns1__SignResponse_);
};

} // namespace PDFSignature

#endif
