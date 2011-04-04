import QtQuick 1.0

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
