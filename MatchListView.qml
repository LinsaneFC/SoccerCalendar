import QtQuick 2.12

ListView {
    id: eventsListView
    width: root.width * 0.4
    height: calendar.height
    header: MatchListHeader{ }
    headerPositioning: ListView.OverlayHeader
    spacing: 4
    clip: true


    Rectangle{
        id: eventsBorder
        anchors.fill: parent
        border.color: "black"
        color: "transparent"
    }

//    delegate: Rectangle {
//        width: eventsListView.width
//        height: eventItemColumn.height
//        anchors.horizontalCenter: parent.horizontalCenter
//    }

}


