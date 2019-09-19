import QtQuick 2.0

Rectangle{
    id: delegateBackground
    width: matchListView.width
    height: matchListView.height / 8
    color: "transparent"
    Rectangle{
        anchors.fill: parent
//        border.color: "black"
//        border.width: 2
        color: "transparent"
    }

    Image{
        id: homeTeamImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0.025 * delegateBackground.width
        height: 0.7 * delegateBackground.height
        width: height
        source: hCrest
    }

    Rectangle{
        id: homeTeamName
        anchors.left: homeTeamImage.right
        anchors.leftMargin: 0.01 * delegateBackground.width
        anchors.verticalCenter: parent.verticalCenter
        width: 0.24 * delegateBackground.width
        height: 0.6 * delegateBackground.height
        color: "transparent"
        Text{
            anchors.centerIn: parent
            text: hTeam
            font.pixelSize: 0.035 * delegateBackground.width
            font.bold: winner ? true : false
        }
    }

    Rectangle{
        id: score
        height: 0.6 * delegateBackground.height
        anchors.left: homeTeamName.right
        anchors.leftMargin: 0.01 * delegateBackground.width
        anchors.right: awayTeamName.left
        anchors.rightMargin: 0.01 * delegateBackground.width
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"
        Text{
            anchors.centerIn: parent
            text: hScore + " - " + aScore
            font.pixelSize: 0.05 * delegateBackground.width
        }
    }

    Rectangle{
        id: awayTeamName
        anchors.right: awayTeamImage.left
        anchors.rightMargin: 0.01 * delegateBackground.width
        anchors.verticalCenter: parent.verticalCenter
        width: 0.24 * delegateBackground.width
        height: 0.6 * delegateBackground.height
        color: "transparent"
        Text{
            anchors.centerIn: parent
            text: aTeam
            font.pixelSize: 0.035 * delegateBackground.width
            font.bold: winner ? false : true
        }
    }


    Image{
        id: awayTeamImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0.025 * delegateBackground.width
        height: 0.7 * delegateBackground.height
        width: height
        source: aCrest
    }

}
