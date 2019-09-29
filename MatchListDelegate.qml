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
        anchors.leftMargin: 0.0125 * delegateBackground.width
        height: 0.7 * delegateBackground.height
        fillMode: Image.PreserveAspectFit
        width: height
        source: hCrest
    }

    Rectangle{
        id: homeTeamName
        anchors.left: homeTeamImage.right
        anchors.leftMargin: 0.01 * delegateBackground.width
        anchors.right: score.left
        anchors.rightMargin: 0.01 * delegateBackground.width
        anchors.verticalCenter: parent.verticalCenter
        width: 0.24 * delegateBackground.width
        height: 0.6 * delegateBackground.height
        color: "transparent"
        Text{
            anchors.centerIn: parent
            text: hTeam.length > 13 ? hTeamShort : hTeam
            font.pixelSize: 0.05 * delegateBackground.width
//            font.bold: winner == 1 ? true : false
//            font.weight: winner == 1 ? Font.Black : Font.Normal
            style: winner == 1 ? Text.Outline  : Text.Normal
            styleColor: "#72da72"
            font.family: "Gill Sans MT Condensed"
        }
    }


    Rectangle{
        id: status
        width: 0.2 * delegateBackground.width
        height: 0.2 * delegateBackground.height
        color: "transparent"
        anchors.horizontalCenter: score.horizontalCenter
        anchors.bottom: score.top
        Text{
            anchors.centerIn: parent
            font.pixelSize: 0.9 * parent.height
            font.family: "Eras Demi ITC"
            text: {
                if(mStatus == "SCHEDULED"){
                    color = "gray";
                    return "SCHEDULED";
                }else if(mStatus == "LIVE" || mStatus == "IN_PLAY"){
                    color = "red";
                    return "LIVE";
                }else if(mStatus == "FINISHED"){
                    color = "blue";
                    return "FT";
                }else{
                    color = "yellow";
                    return mStatus;
                }
            }
        }
    }

    Rectangle{
        id: score
        width: 0.15 * delegateBackground.width
        height: 0.3 * delegateBackground.height
        anchors.centerIn: parent
        color: "transparent"
        Text{
            id: scoreText
            anchors.centerIn: parent
            text: hScore + " - " + aScore
            font.pixelSize: 0.05 * delegateBackground.width
        }
    }

    Rectangle{
        id: awayTeamName
        anchors.right: awayTeamImage.left
        anchors.rightMargin: 0.01 * delegateBackground.width
        anchors.left: score.right
        anchors.leftMargin: 0.01 * delegateBackground.width
        anchors.verticalCenter: parent.verticalCenter
        width: 0.24 * delegateBackground.width
        height: 0.6 * delegateBackground.height
        color: "transparent"
        Text{
            anchors.centerIn: parent
            text: aTeam.length > 13 ? aTeamShort : aTeam
            font.pixelSize: 0.05 * delegateBackground.width
//            font.bold: winner == 0 ? true : false
//            font.weight: winner == 0 ? Font.Black : Font.Normal
            style: winner == 0 ? Text.Outline  : Text.Normal
            styleColor: "#72da72"
            font.family: "Gill Sans MT Condensed"
        }
    }


    Image{
        id: awayTeamImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0.0125 * delegateBackground.width
        height: 0.7 * delegateBackground.height
        width: height
        fillMode: Image.PreserveAspectFit
        source: aCrest
    }


}
