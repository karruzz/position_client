import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0


import Client.Components 1.0


Item {
        visible: true
        width: 640
        height: 65

        Rectangle
        {
            anchors.fill: parent
            color: "black"

            ToolBar
            {
                id: buttonPanel
                width: parent.width
                anchors.top: parent.top

                Row{
                    anchors.fill: parent
                    spacing:4

                    ToolButton{

                        height: 40
                        width: 40
                        opacity: playButton.checked ? 0.5 : 1.0
                        enabled: !playButton.checked

                        Image
                        {
                            source: "../ui/pics/open.png"
                            anchors.fill: parent
                        }

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

                    ToolButton{
                        id: playButton
                        height: 40
                        width: 40
                        checkable: true
                        opacity: dispatcher.isOpened ? 1.0 : 0.5
                        enabled: dispatcher.isOpened

                        Image
                        {
                            source: parent.checked ?  "../ui/pics/stop.png" : "../ui/pics/play.png"
                            anchors.fill: parent
                        }

                        Timer {
                            id: timer
                            interval: 10; running: false; repeat: true
                            onTriggered: dispatcher.seek(dispatcher.endCounter)
                        }

                        onClicked: {
                            timer.running = checked;
                            if (!checked) dispatcher.countChanged();
                        }
                    }

                    ToolButton{

                        height: 40
                        width: 40

                        Image
                        {
                            source: "../ui/pics/settings.png"
                            anchors.fill: parent
                        }

                        onClicked: {
                            chartWindow.visible = true;
                            projectionWindow.visible = true;
                        }
                    }
                }

        }     

        Scroll{ visible: dispatcher.isOpened
                opacity: playButton.checked ? 0.5 : 1.0
                enabled: !playButton.checked
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
        id: chartWindow
        visible: true
        width: 800
        height: 400
        title: "Charts"

        GyroChartView
        {
            anchors.fill: parent
        }
    }

    Window {
        id: projectionWindow
        visible: true
        width: 800
        height: 400
        title: "3D view"

        Gyro3DView
        {
            anchors.fill: parent
        }
    }
}

