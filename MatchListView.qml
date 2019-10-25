import QtQuick 2.12

ListView {
    id: matchListView
    width: root.width * 0.4
    height: calendar.height
    header: MatchListHeader{ }
    headerPositioning: ListView.OverlayHeader
    spacing: 4
    clip: true
    boundsBehavior: Flickable.StopAtBounds
    section.property: "mTime"
    section.criteria: ViewSection.FullString
    section.delegate: Rectangle{
        color: "#a8fffe"
        width: parent.width
        height: matchListView.height / 16
        border.color: "black"
        border.width: 2
        Text{
            anchors.centerIn: parent
            text: formatTime(section)
            font.pixelSize: parent.height * 0.5
            font.family: "Consolas"
            font.bold: true

            function formatTime(time){
                var hours = parseInt(time.substring(0,2));
                var suffix = hours >= 12 ? "PM" : "AM";
                hours = ((hours + 11) % 12 + 1);
                return hours.toString() + time.substring(2, 5) + " " + suffix;
            }
        }
    }
    section.labelPositioning: ViewSection.InlineLabels

    Rectangle{
        id: matchListViewBorder
        anchors.fill: parent
        border.color: "black"
        color: "transparent"
    }

    delegate: MatchListDelegate{ }

}


