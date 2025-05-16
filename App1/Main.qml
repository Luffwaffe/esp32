import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Window {
    id:mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("HQ")
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

    Popup {
       id: endPopup
       width: 350
       height: 150
       modal: true
       focus: true
       closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
       anchors.centerIn: parent
       background: Rectangle {
           color: "#528AA2"
           radius: 10
           border.color: "white"

       }
       Label {
           id:l
           text: "BẠN CÓ CHẮC CHẮN TẮT PHÒNG?"
           color: "white"
           font.pixelSize: 20
           Layout.alignment: Qt.AlignHCenter
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.top:parent.top
           anchors.topMargin: 20
       }


       Rectangle {
           id: ok
           width: 100
           height: 40
           radius: 8
           color: "red"
           anchors.bottom: parent.bottom
           anchors.bottomMargin: 10
           anchors.left: parent.left
           anchors.leftMargin: 50

           Text {
               anchors.centerIn: parent
               text: "Ok Tắt"
               font.pixelSize: 20
               color: "white"
           }

           MouseArea {
               anchors.fill: parent
               onClicked: {
                   roomInforRec.timeChoice = -1;
                   roomInforRec.roomModel.startEnd();
                   endPopup.close();
               }
               cursorShape: Qt.PointingHandCursor
           }
       }
       Rectangle {
           id: huy
           width: 100
           height: 40
           radius: 8
           color: "Green"
           anchors.bottom: parent.bottom
           anchors.bottomMargin: 10
           anchors.left: ok.right
           anchors.leftMargin: 40

           Text {
               anchors.centerIn: parent
               text: "Không Tắt"
               font.pixelSize: 20
               color: "white"
           }

           MouseArea {
               anchors.fill: parent
               onClicked: {
                   endPopup.close();
               }
               cursorShape: Qt.PointingHandCursor
           }
       }

    }
    Popup {
       id: numberPopup
       width: 350
       height: 150
       modal: true
       focus: true
       closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
       anchors.centerIn: parent
       background: Rectangle {
           color: "#528AA2"
           radius: 10
           border.color: "white"

       }

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Label {
                text: "Nhập thời gian"
                color: "white"
                font.pixelSize: 34
                Layout.alignment: Qt.AlignHCenter
            }

            RowLayout {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter

                TextField {
                    id: hourField
                    background: Rectangle {
                       color: "white"
                       radius: 3
                       width: 50
                       height: 30
                    }
                    placeholderText: "Giờ"

                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator { bottom: 0; top: 99 }
                }

                TextField {
                    id: minuteField
                    placeholderText: "Phút"
                    background: Rectangle {
                       color: "white"
                       radius: 3
                       width: 50
                       height: 30
                    }
                    width: 100
                    height: 40
                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator { bottom: 0; top: 59 }
                }
            }

            Button {
                text: "Xác nhận"

                font.pixelSize: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                background: Rectangle {
                   color: "#C5CFD3"
                   radius: 8
                }
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    var hour = parseInt(hourField.text)
                    var minute = parseInt(minuteField.text)
                    var time = hour * 100 + minute
                    roomInforRec.roomModel.setTimeBtnClick(time);
                    numberPopup.close();
                }
            }
        }
    }
    //top rec
    Rectangle {
        id: topRec
        width: parent.width
        height: 50
        color: "#5894AE"
        anchors.top: parent.top
        anchors.left: parent.left

        Text {
            id: roomLable
            text: qsTr("Room")
            color: "White"
            font.bold: true
            font.pixelSize: 35
            anchors.left:  parent.left
            anchors.leftMargin: 85
        }
        Text {
            id: roomInforLable
            text: qsTr(" Detail information")
            color: "White"
            font.bold: true
            font.pixelSize: 35
            anchors.left:  parent.left
            anchors.leftMargin: 370
        }
    }
    //bottom rec
    Rectangle {
        id: bottomRec
        width: parent.width
        height: 50
        color: "#5894AE"
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Rectangle {
            id: refreshBtn
            width:270
            height: parent.height
            color: "#5894AE"
            radius: 5
            anchors.bottom: parent.bottom
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: onOffBtnLabel
                text: qsTr("Design by Thanh Hải")
                color: "White"
                font.bold: true
                font.pixelSize: 20
                anchors.centerIn: parent
            }

            // MouseArea{
            //     id: onOffBtnMouseArea
            //     anchors.fill: parent
            //     hoverEnabled: true
            //     onEntered: {
            //         parent.color = "green"
            //     }
            //     onExited: {
            //         parent.color = "#808080"
            //     }
            //     onClicked:{
            //         room1model.refreshBtnClick()
            //     }
            // }
        }
    }
    //room rec
    Rectangle {
        id: roomRec
        width: 270
        height: parent.height - topRec.height - bottomRec.height
        anchors.top: topRec.bottom
        anchors.left: parent.left

        Rectangle {
            id: room1
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room1Name
                text: qsTr("Room 1")
                color: room1model.runningStatus === "started" ? "green" :
                       room1model.runningStatus === "ended" ? "red" : "grey"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
            MouseArea{
                id:room1MouseArea
                anchors.fill: parent
                onClicked: {
                    startEndBtn.mRoom = "room1"
                    room1model.roomBtnClick();
                    roomInforRec.roomModel = room1model;
                }
            }
        }
        Rectangle {
            id: room2
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room1.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room2Name
                text: qsTr("Room 2")
                color: room2model.runningStatus === "started" ? "green" :
                       room2model.runningStatus === "ended" ? "red" : "grey"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
            MouseArea{
                id:room2MouseArea
                anchors.fill: parent
                onClicked: {
                    startEndBtn.mRoom = "room2"
                    room2model.roomBtnClick();
                    roomInforRec.roomModel = room2model;
                }
            }
        }
        Rectangle {
            id: room3
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room2.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room3Name
                text: qsTr("Room 3")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: room4
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room3.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room4Name
                text: qsTr("Room 4")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: room5
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room4.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room5Name
                text: qsTr("Room 5")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: room6
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room5.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room6Name
                text: qsTr("Room 6")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: room7
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room6.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room7Name
                text: qsTr("Room 7")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: room8
            width: parent.width
            height: 57
            color: "#5894AE"     // Background color
            radius: 5
            anchors.top: room7.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            anchors.rightMargin: 5

            Text {
                id: room8Name
                text: qsTr("Room 8")
                color: "White"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }
    }
    //room infor rec
    Rectangle {
        id: roomInforRec
        width: parent.width - roomRec.width
        height: parent.height - topRec.height - bottomRec.height
        color: "#ACCEDC"
        anchors.top: topRec.bottom
        anchors.right: parent.right
        property var roomModel
        property int timeChoice: -1

        Rectangle {
            id: startEndBtn
            width: 130
            height: 130
            color:  !roomInforRec.roomModel ? "grey" :
                    roomInforRec.roomModel.runningStatus === "started" ? "green" :
                    roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            radius:40
            property string mRoom:""

            Text {
                id: startEndLable
                text:   !roomInforRec.roomModel ? "NA" :
                        roomInforRec.roomModel.runningStatus === "started" ? "TẮT" :
                        roomInforRec.roomModel.runningStatus === "ended" ? "BẬT" : "NA"
                font.pixelSize: 30
                font.bold: true
                anchors.centerIn: parent
                color:"white"
            }

            MouseArea{
                id: startEndArea
                anchors.fill: parent
                onClicked: {
                    if(roomInforRec.roomModel.runningStatus === "started"){
                        endPopup.open();
                    }
                    else{
                        roomInforRec.timeChoice = -1;
                        roomInforRec.roomModel.startEnd();
                    }
                }
            }
        }
        Loader {
            id: roomInforLoader
            anchors.fill: parent
            active: true
            Rectangle {
                id: roomInforMain
                width: parent.width - 40
                height: parent.height - 200
                color: "#D4DFE3"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                radius:12
                Text {
                    id: roomName
                    text: roomInforRec.roomModel ? roomInforRec.roomModel.getRoomInfor("name") : "Chưa chọn Phòng"
                    font.pixelSize: 30
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                }

                Text {
                    id: roomAddress
                    text: (roomInforRec.roomModel &&
                           (roomInforRec.roomModel.runningStatus === "started" || roomInforRec.roomModel.runningStatus === "ended"))?
                              "Address: " + roomInforRec.roomModel.getRoomInfor("address"): "Address: No connection"
                    font.pixelSize: 25
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: roomName.top
                    anchors.topMargin: 50
                }

                Text {
                    id: roomRunningStatus
                    text: roomInforRec.roomModel ? "Status: " +roomInforRec.roomModel.runningStatus : "Status: Chưa chọn phòng"
                    font.pixelSize: 25
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: roomAddress.top
                    anchors.topMargin: 50
                }

                Text {
                    id: timeStart
                    text: (roomInforRec.roomModel && roomInforRec.roomModel.runningStatus === "started")?
                              "Start time: " + roomInforRec.roomModel.timeStart : "Start time: 00:00:00"
                    font.pixelSize: 25
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: roomRunningStatus.top
                    anchors.topMargin: 50
                }

                Text {
                    id: timeEnd
                    text: (roomInforRec.roomModel && roomInforRec.roomModel.runningStatus === "started")?
                              "End time: " + roomInforRec.roomModel.timeEnd: "End time: 00:00:00"
                    font.pixelSize: 25
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: timeStart.top
                    anchors.topMargin: 50
                }

                Text {
                    id: timeRemain
                    text: (roomInforRec.roomModel && roomInforRec.roomModel.runningStatus === "started")?
                              "Used time: " + roomInforRec.roomModel.timeRemainning: "Used time: 00:00:00"
                    font.pixelSize: 25
                    font.bold: true
                    color:  !roomInforRec.roomModel ? "grey" :
                            roomInforRec.roomModel.runningStatus === "started" ? "green" :
                            roomInforRec.roomModel.runningStatus === "ended" ? "red" : "grey"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: timeEnd.top
                    anchors.topMargin: 50
                }
            }
        }
    }
}
