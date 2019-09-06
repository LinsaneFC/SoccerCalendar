import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: root
    x:170
    y:280
    height: width*.65
    width: 325
    anchors.centerIn: parent
//    anchors.fill: parent
    color: "green"

    Text {
        id: title
//        width: root * 10
//        height: root.height * 15
        font.pixelSize: 25
        color: "white"
        y: root + 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Comic Sans"
        text: "Premier League Calendar"
    }

     Button {
         id: openCalendar
         anchors.centerIn: parent
         width: root * .5
         height: 22
         text: "Enter"
         font.pixelSize: 20
         onClicked: Calendarlayout

         background: Rectangle {
             implicitWidth: openCalendar
             implicitHeight: openCalendar
             color: "green"
             border.color: "black"

         }

     }

}
