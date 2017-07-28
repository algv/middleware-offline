######################################################################
# Automatically generated by qmake (2.01a) Fri Dec 21 11:11:18 2007
######################################################################


include(../_Builds/eidcommon.mak)

TEMPLATE = lib
TARGET = $${APPLAYERLIB}
VERSION = $${APPLAYERLIB_MAJ}.$${APPLAYERLIB_MIN}.$${APPLAYERLIB_REV}

message("Compile $$TARGET")

###
### Installation setup
###
target.path = $${INSTALL_DIR_LIB}
INSTALLS += target


###
### Compiler setup
###

CONFIG -= warn_on qt

## destination directory for the compiler
DESTDIR = ../lib 
DEFINED += APPLAYER_EXPORTS

LIBS += -L../lib \
	     -L/usr/local/Cellar/openssl/1.0.1i/lib \
	    -l$${COMMONLIB} \
	    -lcrypto -lssl \
	    -lxerces-c \
	    -lfreeimagePTEiD \
	    -lcurl

!macx: LIBS += -Wl,-R,'../lib' -lxml-security-c
!macx: LIBS += ../lib/libpteid-poppler.a
!macx: LIBS += -Wl,--exclude-libs,ALL 

macx: LIBS += -lxml-security-c
macx: LIBS += -Wl,-framework -Wl,CoreFoundation
macx: LIBS += -Wl,-framework -Wl,SystemConfiguration
macx: LIBS += -Wl,-framework -Wl,CoreServices
macx: INCLUDEPATH += /usr/local/Cellar/openssl/1.0.1i/include/ /usr/local/include/
macx: INCLUDEPATH += /System/Library/Frameworks/CFNetwork.framework/Headers

isEmpty(EMULATE_CARDLAYER) {

  LIBS += -l$${CARDLAYERLIB} 
  isEmpty(USE_PRIVACYFB){
    macx: LIBS += -Wl,-framework -Wl,PCSC
  }
} else {
  LIBS += -l$${CARDLAYEREMULIB} 
}

DEPENDPATH += .
INCLUDEPATH += . ../common ../cardlayer ../eidlib ../dialogs ../FreeImagePTEiD/Source
INCLUDEPATH += $${PCSC_INCLUDE_DIR}
INCLUDEPATH += ../pteid-poppler/
DEFINES += APPLAYER_EXPORTS
# Input
HEADERS += \
	APLCardFile.h \
	APLCard.h \
	APLCertif.h \
	APLCrypto.h \
	APLDoc.h \
	APLReader.h \
	APLConfig.h \
	CardFile.h \
	CertStatusCache.h \
	cryptoFramework.h \
	eidmw_EIDTagHandler.h \
	eidmw_EIDTag_processors.h \
	eidmw_EIDXmlParser.h \
	eidmw_TagProcessor.h \
	eidmw_XML_datastorage.h \
	eidmw_XML_DefHandler.h \
	eidmw_XMLParser.h \
	MiscUtil.h \
	CardPteid.h	    \
	CardPteidDef.h   \
	cryptoFwkPteid.h \
	APLCardPteid.h   \
	PhotoPteid.h \
	SecurityContext.h  \
	APLPublicKey.h \
    SigContainer.h \
	ScapSSLConnection.h \
	XadesSignature.h \
	TSAClient.h \
	SODParser.h \ 
	cJSON.h \
 	SSLConnection.h \	 


SOURCES += \
	APLCertif.cpp        \
	APLCrypto.cpp        \
	APLDoc.cpp	        \
	APLCardPteid.cpp     \
	APLConfig.cpp	\
	APLReader.cpp        \
	CardFile.cpp	        \
	CardPteid.cpp        \
	CertStatusCache.cpp  \
	cryptoFramework.cpp  \
	cryptoFwkPteid.cpp   \
	APLCard.cpp          \ 
	XMLParser.cpp   	\
	MiscUtil.cpp \
	PhotoPteid.cpp \
	APLPublicKey.cpp \
	SigContainer.cpp \
	ScapSSLConnection.cpp \
	XadesSignature.cpp \
	SODParser.cpp \
	SSLConnection.cpp \
	TSAClient.cpp \
	SecurityContext.cpp \
	sign-pkcs7.cpp \
	cJSON.c \
	CRLFetcher.cpp \
	PDFSignature.cpp \
	SAM.cpp \
	OCSP.cpp

# Disable annoying and mostly useless gcc warning
QMAKE_CXXFLAGS += -Wno-write-strings