import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import GyroData 1.0

ApplicationWindow {
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

                onRejected: {
                    console.log("Canceled")
                }
                onAccepted: {
                    dataEntry.apen(fileDialog.fileUrl.toString().replace("file://",""))
                    console.log("File selected: " + fileUrl)
                }
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
                    text: dataEntry.angle.Roll
                }
            }

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.angle.Pitch
                }
            }

            Rectangle {
                width: 100
                height: parent.height
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.angle.Yaw
                }
            }
        }
    }

    Rectangle
    {
        id: graphPanel
        width: parent.width
        anchors.top: framePanel.bottom
        anchors.bottom: parent.bottom

        Scroll{ height: 8; width: graphPanel.width
                       anchors.left: graphPanel.left; anchors.bottom: graphPanel.bottom }
    }
}

