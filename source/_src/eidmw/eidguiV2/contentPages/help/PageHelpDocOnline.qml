import QtQuick 2.6

PageHelpDocOnlineForm {
    propertyTextLinkCC.onLinkActivated: {
        Qt.openUrlExternally(link)
    }
}

