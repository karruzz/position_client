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
            anchors.fill: parent
            color: "black"

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
            id: project
            objectName: "gyro3D"
            anchors.fill: parent

            Text
            {
                anchors.margins: 8
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                text: "counter: " + project.Frame.Counter
                color: "gray"
            }

            Row {
                anchors.left: parent.left
                anchors.top: parent.top
                height: 60
                width: parent.width
                anchors.margins: 8
                spacing: 8

                ColumnLayout {
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        width: parent.width
                        Layout.fillHeight: true
                        text: "roll: " + project.Frame.Roll.toFixed(7)
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        width: parent.width
                        Layout.fillHeight: true
                        text: "pitch: " + project.Frame.Pitch.toFixed(7)
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        width: parent.width
                        Layout.fillHeight: true
                        text: "yaw: " + project.Frame.Yaw.toFixed(7)
                        color: "gray"
                    }
                }

                ColumnLayout {
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        text: "wx: " + project.Frame.wx.toFixed(7)
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        text: "wy: " + project.Frame.wy.toFixed(7)
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        text: "wz: " + project.Frame.wz.toFixed(7)
                        color: "gray"
                    }
                }

                ColumnLayout {
                    width: 150
                    spacing: 8

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        text: "ax: " + project.Frame.ax
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        text: "ay: " + project.Frame.ay
                        color: "gray"
                    }

                    Text
                    {
                        anchors.margins: 8
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "az: " + project.Frame.az
                        color: "gray"
                    }
                }
            }

        }
    }
}

