import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0


import Client.Components 1.0


GridLayout {
    id: grid
    anchors.fill: parent
    rows: 2
    columns: 2

//    Component.onCompleted: {
//       Qt.quit()
//    }

    Rectangle
    {
        Layout.fillWidth: true
        height: 60
        Layout.columnSpan: 2
        Layout.row: 1
        Layout.column: 1
        anchors.top: parent.top

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
                    opacity: dispatcher.is_opened ? 1.0 : 0.5
                    enabled: dispatcher.is_opened

                    Image
                    {
                        source: parent.checked ?  "../ui/pics/stop.png" : "../ui/pics/play.png"
                        anchors.fill: parent
                    }

                    Timer {
                        id: timer
                        interval: 10; running: false; repeat: true
                        onTriggered: dispatcher.seek(dispatcher.end_counter)
                    }

                    onClicked: {
                        timer.running = checked;
                        if (!checked) dispatcher.count_changed();
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

                ToolButton{

                    height: 40
                    width: 40

                    Image
                    {
                        source: "../ui/pics/exit.png"
                        anchors.fill: parent
                    }

                    onClicked: Qt.quit();
                }
            }

    }

    Scroll{ visible: dispatcher.is_opened
            opacity: playButton.checked ? 0.5 : 1.0
            enabled: !playButton.checked
            height: 15
            width: parent.width
            anchors.bottom: parent.bottom
            minimum: dispatcher.start_counter
            maximum: dispatcher.end_counter

            onSeek: {
                dispatcher.seek(counter)
            }
    }
}

    Rectangle
    {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.row: 2
        Layout.column: 1

        color: "transparent"
        border.color: "gray"

        Gyro3DView
        {
            anchors.fill: parent
        }
    }

    Rectangle
    {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.row: 2
        Layout.column: 2

        GyroChartView
        {
            anchors.fill: parent
        }
    }
}

