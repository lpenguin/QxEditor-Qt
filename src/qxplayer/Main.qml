import QtQuick 1.0
import "main.js" as Main
import "Core/Player.js" as PlayerUnit
import "Core/Quest/Location.js" as LocationUnit
import "Core/Quest/Path.js" as PathUnit
import "Core/Quest/Quest.js" as QuestUnit

Rectangle{
    Text{
        text:"QxPlayer - qml version"
        font.family: "Comic Sans MS"
        font.pointSize: 12
    }
    PlayerView{
        id:playerView
        onCompleted: Main.init();
    }
}
