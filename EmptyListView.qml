import QtQuick 2.12

ListView{
    visible: false
    model: emptyModel
    width: root.width * 0.4
    height: calendar.height
    header: MatchListHeader{ }
    headerPositioning: ListView.OverlayHeader
    spacing: 4
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    Rectangle{
        id: matchListViewBorder
        anchors.fill: parent
        border.color: "black"
        color: "transparent"
    }

    delegate: Rectangle{
        width: matchListView.width
        height: matchListView.height / 10
        Rectangle{
            anchors.fill: parent
            color: "#b50c00";
            Text{
                text: "No matches today"
                font.pixelSize: parent.height * 0.4
                font.family: "Rockwell"
                font.weight: Font.ExtraBold
                anchors.centerIn: parent
            }
        }
    }
}
