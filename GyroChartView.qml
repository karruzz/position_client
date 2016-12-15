import QtQuick 2.0
import QtQuick.Layouts 1.0
import Client.Components 1.0


Rectangle{
    id: container
    width: parent.width
    height: parent.height
    anchors.fill: parent
    color: "black"

    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 1

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.color: "lightsteelblue"
            border.width: 1
            anchors.margins: 2
            color: "black"

            Chart
            {
                anchors.fill: parent
                objectName: "gyroChartAngleX"
                color: "green"
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.color: "lightsteelblue"
            border.width: 1
            anchors.margins: 2
            color: "black"

            Chart
            {
                anchors.fill: parent
                objectName: "gyroChartAngleY"
                color: "blue"
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.color: "lightsteelblue"
            border.width: 1
            anchors.margins: 2
            color: "black"

            Chart
            {
                anchors.fill: parent
                objectName: "gyroChartAngleZ"
                color: "red"
            }
        }
    }
}

