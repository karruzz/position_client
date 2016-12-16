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
        anchors.margins: 8
        spacing: 1

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"

            Chart
            {
                anchors.fill: parent
                anchors.margins: 8
                objectName: "gyroChartAngleX"
                color: "green"
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"

            Chart
            {
                anchors.fill: parent
                anchors.margins: 8
                objectName: "gyroChartAngleY"
                color: "blue"
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"

            Chart
            {
                anchors.fill: parent
                anchors.margins: 8
                objectName: "gyroChartAngleZ"
                color: "red"
            }
        }
    }
}

