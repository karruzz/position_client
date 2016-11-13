import QtQuick 2.0

Item {
     id: container

     property variant sa
     property variant orientation: Qt.Horizontal

     function position()
     {
         var ny = 0;
         if (container.orientation == Qt.Vertical)
             ny = sa.visibleArea.yPosition * container.height;
         else
             ny = sa.visibleArea.yPosition * container.width;
         if (ny > 2) return ny; else return 2;
     }

     function size()
     {
         var nh, ny;

         if (container.orientation == Qt.Vertical)
             nh = sa.visibleArea.heightRatio * container.height;
         else
             nh = sa.visibleArea.heightRatio * container.width;

         if (container.orientation == Qt.Vertical)
             ny = sa.visibleArea.yPosition * container.height;
         else
             ny = sa.visibleArea.yPosition * container.width;

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
//             drag.axis: Drag.YAxis
//             drag.minimumY: 0
//             drag.maximumY: (container.height-slider.height)

             drag.axis: Drag.XAxis
             drag.minimumX: 0
             drag.maximumX: (container.width-slider.width)

             onPositionChanged: {
                 if (pressedButtons == Qt.LeftButton) {
                     if (container.orientation == Qt.Vertical)
                         sa.contentY = (slider.y * sa.contentHeight / container.height);
                     else
                         sa.contentY = (slider.x * sa.contentHeight / container.width);
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
