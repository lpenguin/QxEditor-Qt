import QtQuick 1.0
import "main.js" as Main
import "Core/Player.js"
import "Core/Quest/"

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
