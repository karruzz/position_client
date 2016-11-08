import QtQuick 2.3
import QtQuick.Window 2.2
//import org.example 1.0


/*Window {
    visible: true
    id: root

    width: 500
    height: 200

 /*   ListView {
        id: view
        anchors.fill: parent
        model: DataEntryModel {}
        delegate: Text {
            font.pixelSize: 10
            // use the defined model role "display"
            text: model.display
        }
        highlight: Rectangle {
            width: 120
            height: 300
            color:"blue"
        }
    }*/


    ListView {
        id: view
        anchors.fill: parent
     //   model: RoleEntryModel {}
        model: model1
        focus: true
        delegate: Text {
            text: 'hsv(' +
                  Number(model.hue).toFixed(2) + ',' +
                  Number(model.saturation).toFixed() + ',' +
                  Number(model.brightness).toFixed() + ')'
            color: model.name
        }
    }
//}

