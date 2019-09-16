import QtQuick 2.2
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.4

import HttpRequestAndParse 1.0
import Database 1.0

Window {
    id: root
    visible: true
    width: 1200
    height: 800
    title: qsTr("BPL Calendar")

    Timer{
        interval: 4000
        onTriggered: {
            db.query("")
        }
    }

    Database{
        id: db
    }

    HttpRequestAndParse{
        id: httpRequest
    }

    Row {
        id: row
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        MatchListView{ }

        Calendar {
            id: calendar
            width: (parent.width > parent.height ? parent.width * 0.6 - parent.spacing : parent.width)
            height: (parent.height > parent.width ? parent.height * 0.6 - parent.spacing : parent.height)
            frameVisible: true
            weekNumbersVisible: true
            focus: true

            style: CalendarStyle {

                Rectangle {
                    anchors.fill: parent
                    border.color: "White"
                    color: "transparent"
                    anchors.margins: 0
                }

                Image {
                    anchors.margins: -1
                    width: 12
                    height: width
                }

                Label {
                    id: dayDelegateText
                    anchors.centerIn: parent
                    color: "black"
                }
            }
        }

    }
}
