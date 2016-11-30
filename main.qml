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
        }


        Scroll{ visible: dispatcher.count
                height: 8
                width: parent.width
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                maximum: dispatcher.count

                onSeek: {
                    dispatcher.seek(index)
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
}

