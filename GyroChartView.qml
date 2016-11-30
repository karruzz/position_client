import QtQuick 2.0
import QtQuick.Layouts 1.0
import Client.Components 1.0


Item{
    id: container
    width: parent.width
    height: parent.height
    anchors.fill: parent

    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 2

        Chart
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "gyroChartAngleX"
            color: "red"
        }

        Chart
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "gyroChartAngleY"
            color: "blue"
        }

        Chart
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            objectName: "gyroChartAngleZ"
            color: "green"
        }
    }
}

