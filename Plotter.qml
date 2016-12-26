import QtQuick 2.0
import QtQuick.Layouts 1.0
import Client.Components 1.0

Item {
    property alias objectN: chart.objectName
    property alias color: chart.color
    property alias text: chartName.text

    GridLayout
    {
        anchors.fill: parent
        anchors.margins: 8
        columnSpacing: 3
        rowSpacing: 2
        columns: 2

        Rectangle
        {
            color: "black"
            Layout.fillHeight: true
            width: 60

            function step()
            {
                return height / 3;
            }

            Repeater
            {
                model: 3

                Rectangle
                {
                    x: 5
                    y: index * parent.step() + parent.step() / 2 - height / 2
                    height: 15
                    width: 50
                    color: "black"


                    Text
                    {
                        anchors.right: parent.right
                        text: (chart.maxY - (chart.maxY - chart.minY) / 3.0 * (index+0.5)).toFixed(4)
                        color: "gray"
                    }
                }
            }
        }

        Rectangle
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"

            Chart
            {
                id: chart
                anchors.fill: parent
            }

            Text
            {
                id: chartName
                anchors.margins: 3
                anchors.right: parent.right
                anchors.top: parent.top
                color: "gray"
            }
        }

        Rectangle
        {
            color: "black"
            height: 20
            width: 60
        }

        Rectangle
        {
            color: "black"
            Layout.fillWidth: true
            height: 20

            function step()
            {
                return width / 5;
            }

            Repeater
            {
                model: 5

                Rectangle
                {
                    y: 2
                    x: index * parent.step() + parent.step() / 2 - width / 2
                    height: 15
                    width: 50
                    color: "black"


                    Text
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: ((chart.maxX - (chart.maxX - chart.minX) / 5.0 * (index+0.5))/1000000000).toFixed(1)
                        color: "gray"
                    }
                }
            }
        }
    }
}

