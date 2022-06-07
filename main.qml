import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import QmlFileItem 1.0

Window {
    width: 160
    height: 450
    Component.onCompleted: {
        x = Screen.width
        y = Screen.height / 2 - height / 2
    }

    visible: true
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint

    SystemPalette {
        id: palette
    }    
    
    color: palette.window
    
    
    
    ListView {
        id: itemsView
        anchors.margins: 10
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent
        orientation: ListView.Vertical
        spacing: 5
        model: QmlFileItemModel {
            id: fileList
        }
        
        delegate: Item {
            width: itemsView.width
            height: layout.height
            Drag.dragType: Drag.Automatic
            Drag.active: dragArea.drag.active
            Drag.hotSpot.x: 10
            Drag.hotSpot.y: 10
            Drag.mimeData:  {"text/uri-list": model.url}
            Drag.keys: model.keys

            Drag.onDragFinished: 
                (dropAction) => {
                    removeDelayTimer.start();
                }
            
            Timer {
                id: removeDelayTimer
                interval: 250
                onTriggered: {
                    fileList.removeItem(model.url);
                }
            }
            
            ToolTip.delay: 500
            ToolTip.visible: dragArea.containsMouse
            ToolTip.text: model.url
            
            ColumnLayout {
                width: parent.width
                id: layout
                z:0
                Image {
                    width: parent.width-10
                    height: width
                    source: model.icon
                    Layout.alignment: Qt.AlignHCenter
                }
                
                Label {
                    text: model.name
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width
                    
                    horizontalAlignment: Qt.AlignHCenter
                    
                    elide: Label.ElideMiddle
                    wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                }
            }
            MouseArea {
                z:2
                id: dragArea
                anchors.fill: parent
                hoverEnabled: true
                
                drag.target: parent
                
                onPressed: {
                    parent.grabToImage(function(result) {
                        parent.Drag.imageSource = result.url
                    })}
            }
        }
    }
    
    
    DropArea {
        anchors.fill: parent
        onDropped: (drop) => {
                       fileList.addItem(drop.urls[0], drop.keys)
                       drop.acceptProposedAction()                       
                   }
        
        Rectangle {
            anchors.fill: parent
            color: "green"
            
            visible: parent.containsDrag
        }
    }
}
