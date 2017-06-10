import QtQuick 2.6

/* Constants imports */
import "../../scripts/Constants.js" as Constants

PageServicesSignAdvancedForm {

    propertyDropArea {

        onEntered: {
            console.log("You chose file(s): " + drag.urls.toString());
            filesArray = drag.urls
            console.log("Num files: "+filesArray.length);
        }
        onDropped: {
            for(var i = 0; i < filesArray.length; i++){
                console.log("Adding file: " + filesArray[i])
                filesModel.append({
                                      "fileUrl": filesArray[i]
                                  })
            }
            // Force scroll and focus to the last item addded
            forceScrollandFocus()
        }
        onExited: {
            console.log ("onExited");
            filesArray = []
        }
    }
    propertyFileDialog {

        onAccepted: {
            console.log("You chose file(s): " + propertyFileDialog.fileUrls)
            console.log("Num files: " + propertyFileDialog.fileUrls.length)

            for(var i = 0; i < propertyFileDialog.fileUrls.length; i++){
                console.log("Adding file: " + propertyFileDialog.fileUrls[i])
                filesModel.append({
                                      "fileUrl": propertyFileDialog.fileUrls[i]
                                  })
            }

            // Force scroll and focus to the last item addded
            forceScrollandFocus()
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    propertyMouseAreaRectMainRigh {
        onClicked: {
            console.log("propertyMouseAreaRectMainRigh clicked")
            propertyFileDialog.visible = true
        }
    }
    propertyMouseAreaItemOptionsFiles {
        onClicked: {
            console.log("propertyMouseAreaItemOptionsFiles clicked")
            propertyFileDialog.visible = true
        }
    }
    propertyButtonAdd {
        onClicked: {
            console.log("propertyButtonAdd clicked")
            propertyFileDialog.visible = true
        }
    }
    propertyButtonRemoveAll {
        onClicked: {
            console.log("Removing all files")
            propertyListViewFiles.model.clear()
        }
    }

    Component {
        id: listViewFilesDelegate
        Rectangle{
            width: parent.width - propertyFilesListViewScroll.width
                   - Constants.SIZE_LISTVIEW_SPACING
            height: Constants.SIZE_V_COMPONENTS
            color: Constants.COLOR_MAIN_SOFT_GRAY
            Item {
                width: parent.width

                Text {
                    id: fileName
                    text: fileUrl
                    width: parent.width - Constants.SIZE_V_COMPONENTS
                    font.pixelSize: Constants.SIZE_TEXT_FIELD
                    verticalAlignment: Text.AlignVCenter
                    color: Constants.COLOR_TEXT_BODY
                    wrapMode: Text.WrapAnywhere
                }
                Image {
                    id: iconRemove
                    anchors.left: fileName.right
                    width: Constants.SIZE_V_COMPONENTS
                    height: Constants.SIZE_V_COMPONENTS
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit
                    source:  mouseAreaIconDelete.containsMouse ?
                                 "../../images/ic_highlight_on_black_24dp.png" :
                                 "../../images/ic_highlight_off_black_24dp.png"
                    MouseArea {
                        id: mouseAreaIconDelete
                        anchors.fill: parent
                        hoverEnabled : true
                        onClicked: {
                            console.log("Delete file index:" + index);
                            filesModel.remove(index)

                        }
                    }
                }
            }
        }
    }
    ListModel {
        id: filesModel

        onCountChanged: {
            console.log("filesModel onCountChanged")
            if(filesModel.count === 0){
                fileLoaded = false
            }else{
                fileLoaded = true
            }
        }
    }
    function forceScrollandFocus() {
        // Force scroll and focus to the last item addded
        propertyListViewFiles.positionViewAtEnd()
        propertyListViewFiles.forceActiveFocus()
        propertyListViewFiles.currentIndex = propertyListViewFiles.count -1
        if(propertyFilesListViewScroll.position > 0)
            propertyFilesListViewScroll.active = true
    }
}
