import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: container

     property variant orientation: Qt.Horizontal

     property int value: 0
     property double minimum: 0
     property double maximum: 10

     signal seek(double counter)

     function position()
     {
         var delta = maximum - minimum;
         if (delta == 0) return 0;
         var ny = 0;
         if (container.orientation == Qt.Vertical)
             ny = value * container.height / delta;
         else
             ny = value * container.width / delta;
         if (ny > 2) return ny; else return 2;
     }

     function size()
     {
         var nh, ny;

         if (container.orientation == Qt.Vertical)
             nh = container.height / 20;
         else
             nh = container.width / 20;

         ny = position();

         if (ny > 3) {
             var t;
             if (container.orientation == Qt.Vertical)
                 t = Math.ceil(container.height - 3 - ny);
             else
                 t = Math.ceil(container.width - 3 - ny);
             if (nh > t) return t; else return nh;
         } else return nh + ny;
     }

     Rectangle { anchors.fill: parent; color: "Black"; opacity: 0.3 }

     Rectangle {
         id: slider
         color: "blue"; radius: 10
         x: container.orientation == Qt.Vertical ? 2 : position()
         width: container.orientation == Qt.Vertical ? container.width - 4 : size()
         y: container.orientation == Qt.Vertical ? position() : 2
         height: container.orientation == Qt.Vertical ? size() : container.height - 4

         MouseArea {
             anchors.fill: parent
             drag.target: parent
             drag.axis: Drag.XAxis
             drag.minimumX: 0
             drag.maximumX: (container.width-slider.width)

             onPositionChanged: {
                 var delta = maximum - minimum;
                 if (pressedButtons == Qt.LeftButton) {
                     if (container.orientation == Qt.Vertical)
                         container.seek(minimum + slider.y * delta / container.height);
                     else
                         container.seek(minimum + slider.x * delta / container.width);
                 }
             }
         }
     }

     states: State {
         name: "visible"
         when: container.orientation == Qt.Vertical ? sa.movingVertically : sa.movingHorizontally
         PropertyChanges { target: container; opacity: 1.0 }
     }

     transitions: Transition {
         from: "visible"; to: ""
         NumberAnimation { properties: "opacity"; duration: 600 }
     }
}
