import QtQuick 2.12

ListView {
    id: matchListView
    width: root.width * 0.4
    height: calendar.height
    header: MatchListHeader{ }
    headerPositioning: ListView.OverlayHeader
    spacing: 4
    clip: true


    Rectangle{
        id: matchListViewBorder
        anchors.fill: parent
        border.color: "black"
        color: "transparent"
    }

    delegate: MatchListDelegate{ }

}


