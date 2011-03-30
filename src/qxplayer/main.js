var questPlayer = {};
var loader = {};
var global = this;

var libs = [
        "Core/Quest/Location.js",
        "Core/Quest/Path.js",
        "Core/Quest/Quest.js",
        "Core/Player.js",
        "lib/loader.js",
        "lib/PlayerLoader.js"
    ];

function loadLibraries( libs, onCompleteHandler ){
    var lib = libs.shift();
    if( ! lib ){
        onCompleteHandler.call( null );
        return;
    }

    console.log("loading core library: "+lib)
    Qt.include( lib );
    loadLibraries( libs, onCompleteHandler);
}

function init(path){
    if( !path )
        return;

    loadLibraries( libs, function(){
        questPlayer = new Player( playerView );
        loader = new PlayerLoader();
        loader.load(path, function(data){
            questPlayer.load( data );
            questPlayer.play();
        });
    });
}

function mkFunc( actions ){
   //return eval("function(){"+actions+"}");
    return actions;
}

function extend( obj1 , obj2 ){
    for( var i in obj2 )
        obj1[i] = obj2[i];
}

function trace( str ){
    console.log( ">> " + str );
}

function dump(arr,level) {
    var dumped_text = "";
    if(!level) level = 0;

    //The padding given at the beginning of the line.
    var level_padding = "";
    for(var j=0;j<level+1;j++) level_padding += "    ";

    if(typeof(arr) == 'object') { //Array/Hashes/Objects
        for(var item in arr) {
            var value = arr[item];

            if(typeof(value) == 'object') { //If it is an array,
                dumped_text += level_padding + "'" + item + "' ...\n";
                dumped_text += dump(value,level+1);
            } else {
                dumped_text += level_padding + "'" + item + "' => \"" + value + "\"\n";
            }
        }
    } else { //Stings/Chars/Numbers etc.
        dumped_text = "===>"+arr+"<===("+typeof(arr)+")";
    }
    return dumped_text;
}

