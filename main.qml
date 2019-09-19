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

    Database{
        id: db
    }

    HttpRequestAndParse{
        id: httpRequest
    }

    ListModel{
        id: matchModel
    }

    Row {
        id: row
        anchors.fill: parent
        anchors.margins: parent.width > parent.height ? root.width * 0.02 : root.height * 0.02
        spacing: parent.width > parent.height ? root.width * 0.01 : root.height * 0.01

        MatchListView{
            model: matchModel
        }

        Calendar {
            id: calendar
            width: root.width * 0.56 - parent.spacing
            height: root.height * 0.95
            frameVisible: true
            weekNumbersVisible: true
            focus: true
            onSelectedDateChanged: {
                calendarDelayTimer.start();
            }

            Timer{
                id: calendarDelayTimer
                running: true
                interval: 1000
                onTriggered: {
                    //Function to populate model
                    populateMatchModel();
                }

                function populateMatchModel(){
                    console.log("ran");
                    matchModel.clear();
                    var date = Qt.formatDateTime(calendar.selectedDate, "yyyy-MM-dd");
                    var newQuery = replaceDate(date);
                    var records = db.query(newQuery);
                    for(var i = 0; i < records.length; ++i){
                        var record = records[i];
                        matchModel.append({winner : record.winner, hTeam : record.hTeam, aTeam : record.aTeam, hScore : record.hScore, aScore : record.aScore, hCrest : record.hCrest, aCrest : record.aCrest});
                    }
                }

                function replaceDate(newDate){
                    var oldQuery = "SELECT CASE match.winner
                                        WHEN 'HOME_TEAM' then 1
                                        WHEN 'AWAY_TEAM' then 0
                                        ELSE -1
                                        END 'winner', t1.name as hTeam, t2.name as aTeam, match.homeScore as hScore, match.awayScore as aScore, t1.crestUrl as hCrest, t2.crestUrl as aCrest
                                    FROM match, team as t1, team as t2
                                    WHERE match.utcDate = \"2019-08-10\"  and t1.id = homeTeam and t2.id = awayTeam"
                    return oldQuery.replace(/2019-08-10/g, newDate);
                }

            }

        }
    }


}
