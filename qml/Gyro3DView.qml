import QtQuick 2.0
import QtQuick.Layouts 1.0
import Client.Components 1.0


Item
{
    id: container
    width: parent.width
    height: parent.height
    anchors.fill: parent

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
            text: "counter: " + project.frame.Counter
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
                width: 200
                spacing: 8

                Text
                {
                    anchors.margins: 8
                    width: parent.width
                    Layout.fillHeight: true
                    text: "roll: " + project.frame.Roll.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    width: parent.width
                    Layout.fillHeight: true
                    text: "pitch: " + project.frame.Pitch.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    width: parent.width
                    Layout.fillHeight: true
                    text: "yaw: " + project.frame.Yaw.toFixed(7)
                    color: "gray"
                }
            }

            ColumnLayout {
                width: 200
                spacing: 8

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "wx: " + project.frame.wx.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "wy: " + project.frame.wy.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "wz: " + project.frame.wz.toFixed(7)
                    color: "gray"
                }
            }

            ColumnLayout {
                width: 200
                spacing: 8

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "ax: " + project.frame.ax.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "ay: " + project.frame.ay.toFixed(7)
                    color: "gray"
                }

                Text
                {
                    anchors.margins: 8
                    Layout.fillHeight: true
                    text: "az: " + project.frame.az.toFixed(7)
                    color: "gray"
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            property variant previousPosition
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed: {
                previousPosition = Qt.point(mouseX, mouseY)
            }
            onPositionChanged: {
                if (pressedButtons == Qt.LeftButton || pressedButtons == Qt.RightButton) {
                    var dx = mouseX - previousPosition.x
                    var dy = mouseY - previousPosition.y
                    previousPosition.x = mouseX
                    previousPosition.y = mouseY
                    project.mouse_dragged(pressedButtons, dx, dy)
                }
            }
        }
    }
}

