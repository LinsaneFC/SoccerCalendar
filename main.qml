import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import HttpRequestAndParse 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    HttpRequestAndParse{
        id: httpRequestAndParse
    }

    Button{
        id: button
        width: 100
        height: width
        text: "Get Premier League Results"
        onClicked: {
            httpRequestAndParse.getPremierLeagueResults();
        }
    }

}
