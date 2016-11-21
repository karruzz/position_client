import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import Client.Components 1.0

ApplicationWindow {
    visible: true
    width: 840
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
                    dataEntry.open(fileDialog.fileUrl.toString().replace("file://",""))
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
            spacing: 4


            Rectangle {
                width: 70
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: "Time:"
                }
            }

            Rectangle {
                width: 120
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.frame.Time
                }
            }


            Rectangle {
                width: 70
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: "Angle:"
                }
            }

            Rectangle {
                width: 70
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.frame.Roll.toFixed(7)
                }
            }

            Rectangle {
                width: 70
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.frame.Pitch.toFixed(7)
                }
            }

            Rectangle {
                width: 70
                height: parent.height
                color: "transparent"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: dataEntry.frame.Yaw.toFixed(7)
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

        Chart
        {
            anchors.fill: graphPanel
        }

        Scroll{ visible: dataEntry.count
                height: 8
                width: graphPanel.width
                anchors.left: graphPanel.left
                anchors.bottom: graphPanel.bottom
                maximum: dataEntry.count

                onSeek: {
                    dataEntry.seek(index)
                }

        }
    }
}

