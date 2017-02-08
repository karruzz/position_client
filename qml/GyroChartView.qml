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

        Plotter
        {
            Layout.fillHeight: true
            Layout.fillWidth: true

            objectN:"gyroChartAngleX"
            color: "green"
            text: "roll"
        }

        Plotter
        {
            Layout.fillHeight: true
            Layout.fillWidth: true

            objectN:"gyroChartAngleY"
            color: "blue"
            text: "pitch"
        }

        Plotter
        {
            Layout.fillHeight: true
            Layout.fillWidth: true

            objectN:"gyroChartAngleZ"
            color: "red"
            text: "yaw"
        }
    }
}

