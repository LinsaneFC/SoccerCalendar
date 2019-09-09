import QtQuick 2.2
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.4

import HttpRequestAndParse 1.0
import Database 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Calendar")
//    Rectangle {
//        anchors.fill: parent
//        color: "red"
//    }

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


    Homepage{ }

    Calendar {
        id: calendar
        width: parent.width
        height: parent.height
        frameVisible: true
        weekNumbersVisible: true
        focus: true

        style: CalendarStyle {


                Rectangle {
                    anchors.fill: parent
                    border.color: "White"
                    color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "transparent"
                    anchors.margins: styleData.selected ? -1 : 0
                }

                Image {
                    visible: eventModel.eventsForDate(styleData.date).length > 0
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: -1
                    width: 12
                    height: width
//                    source: "qrc:/images/eventindicator.png"
                }

                Label {
                    id: dayDelegateText
                    text: styleData.date.getDate()
                    anchors.centerIn: parent
                    color: "Black"
                    }
                }
            }

    Component {
        id: eventListHeader

        Row {
            id: eventDateRow
            width: parent.width
            height: eventDayLabel.height
            spacing: 10

            Label {
                id: eventDayLabel
                text: calendar.selectedDate.getDate()
                font.pointSize: 35
            }
            Column {
                height: eventDayLabel.height

                Label {
                    text: Qt.locale().standaloneDayName(calendar.selectedDate.getDay(), Locale.LongFormat)
                    font.pointSize: 18
                }
                Label {
                    text: Qt.locale().standaloneMonthName(calendar.selectedDate.getMonth())
                        + calendar.selectedDate.toLocaleDateString(Qt.locale(), "yyyy")
                    font.pointSize: 12
                }
            }
        }
    }
    Rectangle {
        width: (parent.width - parent.spacing)
        height: (parent.height - parent.spacing)
        border.color: Qt.darker(color, 1.2)

        ListView {
            id: eventsListView
            spacing: 4
            clip: true
            header: eventListHeader
            anchors.fill: parent
            anchors.margins: 10
            model: eventModel.eventsForDate(calendar.selectedDate)

            delegate: Rectangle {
                width: eventsListView.width
                height: eventItemColumn.height
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    width: 12
                    height: width
                    source: "qrc:/images/eventindicator.png"
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "blue"
                }

                Column {
                    id: eventItemColumn
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.right: parent.right
                    height: timeLabel.height + nameLabel.height + 8

                    Label {
                        id: nameLabel
                        width: parent.width
                        wrapMode: Teext.Wrap
                        text: modelData.name
                    }
                    Label {
                        id: timeLabel
                        width: parent.width
                        wrapMode: Text.Wrap
                        text: model.Data.startDate.toLocaleTimeString(calendar.locale, Locale.ShortFormat)
                        color: "orange"
                    }
                }
            }
        }
    }
}

