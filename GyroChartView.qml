import QtQuick 2.0
import Client.Components 1.0


Item{
    id: container
    width: parent.width
    height: parent.height
    anchors.fill: parent

    Chart
    {
        id: chartControl
        objectName: "chartObj"
        anchors.fill: parent
    }
}

