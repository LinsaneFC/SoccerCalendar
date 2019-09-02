import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4

import HttpRequestAndParse 1.0
import Database 1.0

Window {
    id: root
    visible: true
    width: 1200
    height: 800
    title: qsTr("Hello World")

    Rectangle{
        id: background
        anchors.fill: parent
        color: "transparent"

        Database{

        }

        HttpRequestAndParse{
            id: httpRequestAndParse
        }

    }

}
