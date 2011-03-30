import QtQuick 1.0

import "Core/Quest/Location.js" as LocationUnit
import "Core/Quest/Path.js" as PathUnit
import "Core/Quest/Quest.js" as QuestUnit
import "Core/Player.js" as PlayerUnit
import "lib/loader.js" as Ajax
import "lib/PlayerLoader.js" as PlayerLoader
import "main.js" as Main

Rectangle{
    property string questPath: ""
    function init(){
        Main.init(questPath);
        return 0;
    }
    property int initRes: init();
    Text{
        text:"QxPlayer - qml version"
        font.family: "Comic Sans MS"
        font.pointSize: 12
    }

    PlayerView{
        id:playerView
//        Component.onCompleted: {

//            console.log("ok");
//            Main.init();

//        }
    }
}
