import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import Client.Components 1.0

Item {
        visible: true
        width: 640
        height: 80

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
                        dispatcher.open(fileDialog.fileUrl.toString().replace("file://",""))
                        console.log("File selected: " + fileUrl)
                    }
                }

                onClicked: fileDialog.open();
            }

            Button{
                anchors.right: parent.right
                text: "следить"

                Timer {
                    id: timer
                    interval: 10; running: false; repeat: true
                    onTriggered: dispatcher.seek(dispatcher.endCounter)
                }

                onClicked: timer.running = true;
            }
        }     

        Scroll{ visible: dispatcher.isOpened
                height: 15
                width: parent.width
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                minimum: dispatcher.startCounter
                maximum: dispatcher.endCounter

                onSeek: {
                    dispatcher.seek(counter)
                }
        }


    Window {
        visible: true
        width: 800
        height: 400

        GyroChartView
        {
            anchors.fill: parent
        }
    }

    Window {
        visible: true
        width: 800
        height: 400

        Projection
        {
            objectName: "gyro3D"
            anchors.fill: parent

            RowLayout {
                anchors.left: parent.left
                anchors.top: parent.top
                height: 60
                width: 500
                anchors.margins: 8
                spacing: 8

                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "roll:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "pitch:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "yaw:"
                        color: "gray"
                    }
                }

                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "wx:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "wy:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "wz:"
                        color: "gray"
                    }
                }

                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "ax:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "ay:"
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "az:"
                        color: "gray"
                    }
                }
            }

        }
    }
}

