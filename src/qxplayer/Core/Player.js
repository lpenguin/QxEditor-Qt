var checkConditions = function( path ){
    if( !path.conditions )
        return true;
    this.evalActions( path.conditions, {"path" : path} );
}

var onStartExecActions = function(){};
var onStopExecActions = function(){};
var locationPaths = function( location ){
    return location.paths;
}

var Player = function( playerView ){
    this.playerView = playerView;
    this.reset();
}
Player.prototype.playerView = {};

Player.prototype.resetQuest = function(){
    this.context = { text:"", stateText:"" }
    this.quest = new Quest();
}

Player.prototype.updateContext = function( text, stateText ){
    if( text != null && text != undefined)
        this.context.text = text;
    if( stateText != null && stateText != undefined)
        this.context.stateText = stateText;
}

Player.prototype.readContext = function(){
    playerView.text = this.context.text;
    playerView.stateText = this.context.stateText;
}

Player.prototype.onPathSelected = function( path ){
    this.showPath( path )
}

Player.prototype.reset = function( path ){
    this.context = {}
//    this.context.checkConditions = function( path ){
//        if( !path.conditions )
//            return true;
//        this.evalActions( path.conditions, {"path" : path} );
//    }

    //this.context.onStartExecActions = function(){};
    //this.context.onStopExecActions = function(){};
}

Player.prototype.load = function( jsonObject ){
    this.resetQuest();
    this.libraries = jsonObject.libraries;
    this.quest = new Quest( jsonObject );
}

Player.prototype.play = function() {
    var loc = this.quest.findStartLocation();
    if( !loc )
        throw Error("Cannot find start location");
    console.log("exec libraries");
    for( var i in this.libraries ){
        this.playGlobalActions( this.libraries[i] );
    }
    return;
    console.log("exec init sections");
    this.initQuest();
    console.log("exec quest actions");
    this.playGlobalActions( this.quest.actions );
    this.showLocation( loc );
    
}

// Player.prototype.exposeDefinitions = function() {
//     D.importFunction("trace", myTrace);
//     D.importFunction("typeof", function(v){
//         return typeof(v);
//     });
// //          _context.exposeDefinition(_local, "local");
// //          _context.exposeDefinition(myTrace, "trace");
// //          _context.exposeDefinition(_playerView.text, "text");
// //          _context.exposeDefinition(_playerView.stateText, "state");
// }
    
Player.prototype.initQuest = function(){
    this.playGlobalActions( this.quest.initActions );
    for( var i in this.quest.locations ){
        var loc = this.quest.locations[i];
        this.playLocalActions( loc.initActions, {"location":loc});
        for( var j in loc.paths ){
            var path = loc.paths[i];
            this.playLocalActions( loc.initActions, {"path":path});
        }
    }
}

//Player.prototype.execInContext = function( thisObject, actionsFunc ){
//    with( this.context ){
//        return actionsFunc.call( thisObject );
//    }
//}

//Player.prototype.evalActions = function( actions, thisObject ){
//    var that = this;
//    return this.execInContext(  thisObject, function(){
//        try{
//            with( that.context ){
//                var r = eval( actions );
//             trace( dump( this ));
//            }
//            return 0;
//        }catch(e) {
//          trace( "Eval error: " + e.message+"\n"+actions );
//        }
//    } );
//}

Player.prototype.playGlobalActions = function(actions) {
//    this.execInContext( actions, this.context )

}

Player.prototype.playLocalActions = function( actions, thisObject ) {
    onStartExecActions();
//    this.execInContext( thisObject, this.context.onStartExecActions  );
    with( thisObject ){
        eval( actions );
    }

//    this.execInContext( thisObject, actions );
//    this.execInContext( thisObject, this.context.onStopExecActions );
    onStopExecActions();
}

Player.prototype.clearView = function() {
    this.playerView.text = "";
    this.playerView.stateText = "";
    this.playerView.clearActions();
}

//Player.prototype.clearPaths = function( ){
//    this.playerView.clearPaths();
//}

Player.prototype.showLocation = function( loc ){
    this.playerView.clearPaths();
    this.updateContext( loc.text );
    var paths = locationPaths( loc );
//    try{
//        with( this.context ){
//            with( { "location":loc } ){
//                paths = locationPaths( location )
//            }
//        }
//    }catch(e){
//        this.trace(e.message);
//    }
    
    for( var i in paths ){
        this.playerView.addPath( loc.paths[i] );
    }
    this.playLocalActions( loc.actions, { "location":loc } );
    this.readContext();
}
    
Player.prototype.showPath = function( path ) {
    this.clearView();
    this.updateContext(path.text);
    this.playLocalActions( path.actions, { "path":path } );
    this.readContext();
    if ( this.context.text ) {
        this.playerView.addAction( new PlayerAction( new Path( "tmp", "next>>", "", "", "", "", path.nextLocation ) ) );
    }else
        this.showLocation( path.nextLocation );
}

