import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

import GyroData 1.0

//Window {
//    visible: true
//    id: root

//    width: 500
//    height: 200

//    ListView {
//        id: view
//        anchors.fill: parent
//        model: DataEntryModel {}
//        delegate: Text {
//            font.pixelSize: 10
//            // use the defined model role "display"
//            text: model.display
//        }
////        highlight: Rectangle {
////            width: 120
////            height: 300
////            color:"blue"
////        }
//    }

//    ScrollBar{ scrollArea: view; height: view.height; width: 8
//               anchors.right: view.right; anchors.top: view.top }
//}


ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Gyro test")

    Rectangle
    {
        id: buttonPanel
        width: parent.width
        height: 50
        anchors.top: parent.top
        color: "gray"

        Button{
            text: "выбрать файл"

            FileDialogs {
                id: fileDialog
            }


            onClicked: fileDialog.open();
        }

    }


    Rectangle
    {
        id: framePanel
        width: parent.width
        height: 50
        anchors.top: buttonPanel.bottom
        color: "lightgray"

        RowLayout {
            id: layout
            anchors.fill: parent
            spacing: 6

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: "Angle:"
                }
            }

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.Angle.Roll
                }
            }

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.Angle.Pitch
                }
            }

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.Angle.Yaw
                }
            }
        }
    }



//    ListView {
//        id: list
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.top: framePanel.bottom
//        anchors.bottom: parent.bottom
//     //   model: RoleEntryModel {}
//        model: model1
//        focus: true
//        delegate: Text {
//            text: 'hsv(' +
//                  Number(model.hue).toFixed(2) + ',' +
//                  Number(model.saturation).toFixed() + ',' +
//                  Number(model.brightness).toFixed() + ')'
//            color: model.name
//        }
//    }

//    ScrollView{ sa: framePanel; height: 8; width: framePanel.width
//               anchors.left: framePanel.left; anchors.bottom: framePanel.bottom }

}

