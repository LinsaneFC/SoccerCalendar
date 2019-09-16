import QtQuick 2.0
import QtQuick.Controls 2.5

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
                      + " " + calendar.selectedDate.toLocaleDateString(Qt.locale(), "yyyy")
                font.pointSize: 12
            }
        }
    }
}
