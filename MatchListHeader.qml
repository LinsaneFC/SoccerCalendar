import QtQuick 2.0
import QtQuick.Controls 2.5

Component {
    id: matchListheader
    Rectangle{
        id: headerBackground
        width: matchListView.width
        height: matchListView.height / 12
        z: 3
        Row {
            spacing: 0.01 * root.width
            Rectangle{
                id: spacing
                width: parent.width * 0.01
                height: 1
                color: "transparent"
            }

            Label {
                id: matchDayLabel
                text: calendar.selectedDate.getDate()
                font.pointSize: 0.08 * headerBackground.width
            }
            Column {
                height: matchDayLabel.height

                Rectangle{
                    id: spacing2
                    width: 1
                    height: parent.height * 0.1
                    color: "transparent"
                }

                Label {
                    text: Qt.locale().standaloneDayName(calendar.selectedDate.getDay(), Locale.LongFormat)
                    font.pointSize: 0.5 * matchDayLabel.font.pointSize
                }
                Label {
                    text: Qt.locale().standaloneMonthName(calendar.selectedDate.getMonth())
                          + " " + calendar.selectedDate.toLocaleDateString(Qt.locale(), "yyyy")
                    font.pointSize: 0.33 * matchDayLabel.font.pointSize
                }
            }
        }
    }
}
