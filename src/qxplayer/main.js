var questPlayer = {};

function init(path){
    if( !path )
        return;
    questPlayer = new PlayerUnit.Player( playerView );
    PlayerLoader.load(path, function(data){
        console.log("loaded")
    });
}
