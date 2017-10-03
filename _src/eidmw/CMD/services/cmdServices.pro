
include(../../_Builds/eidcommon.mak)

TEMPLATE = lib
TARGET = $${CMDSERVICESLIB}
VERSION = $${CMDSERVICESLIB_MAJ}.$${CMDSERVICESLIB_MIN}.$${CMDSERVICESLIB_REV}

message("Compile $$TARGET")
message("Version $$VERSION")

###
### Installation setup
###
target.path = $${INSTALL_DIR_LIB}
INSTALLS += target

QT -= gui

## destination directory
DESTDIR = ./../../lib
DEPENDPATH += .

LIBS += -L./../../lib -l$${COMMONLIB} -l$${APPLAYERLIB} -l$${CARDLAYERLIB}
INCLUDEPATH += . ../../common ../../applayer ../../cardlayer

unix: DEFINES += __UNIX__ DEBUG WITH_OPENSSL
#Support Fat binaries on Mac with both x86 and x86_64 architectures

# Input
HEADERS += \
            CCMovelSignature.h \
            soapH.h \
            soapStub.h \
            soapWSHttpBinding_USCORECCMovelSignatureProxy.h \
            stdsoap2.h \
            cmdServices.h \
            CMDSignature.h

SOURCES += \
            soapC.cpp \
            soapWSHttpBinding_USCORECCMovelSignatureProxy.cpp \
            stdsoap2.cpp \
            cmdServices.cpp \
            CMDSignature.cpp
