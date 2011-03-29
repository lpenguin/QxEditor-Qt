var Player = function( playerView ){
    this.playerView = playerView;
    this.reset();
}
Player.prototype.playerView = {};

Player.prototype.reset = function(){
    this.context = {}
    this.quest = new Quest();
}

Player.prototype.updateContext = function( text, stateText ){
    if( text != null )
        context.text = text;
    if( stateText != null)
        context.stateText = stateText;
}

Player.prototype.readContext = function(){
    playerView.text = context.text;
    playerView.stateText = context.stateText;
}

Player.prototype.onPathSelected = function( path ){
    this.showPath( path )
}

Player.prototype.reset = function( path ){
    this.context = {}
    this.context.checkConditions = function( path ){
        if( !path.conditions )
            return true;
        this.evalActions( path.conditions, {"path" : path} );
    }
}

Player.prototype.load = function( jsonObject ){
    this.reset();
    this.quest = new Quest( jsonObject );
}

Player.prototype.play = function() {
    var locn = this.quest.findStartLocation();
    if( !loc )
        throw Error("Cannot find start location");
        
    for( var i in this.libraries )
        this.playGlobalActions( this.libraries[i] );
    this.initQuest();
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
    
Player.prototype.trace = function( str ) {
    //s.controls.Alert.show( str );
//     _playerView.showMsg( str );
//     trace( str );
}
Player.prototype.evalActions = function( actions, thisObject ){
    try{
        var contextFunc = function( actions ){
            var thisFunc = function( actions ){
                return eval( actions );
            }
            return thisFunc.call( thisObject, actions );
        }
        return contextFunc.call(context, actions );
    }catch(e) {
        trace( "Error: " + e.message+"\n"+actions );
    }
}
Player.prototype.playGlobalActions = function(actions) {
    this.evalActions( actions, _context );
}

Player.prototype.playLocalActions = function( actions, thisObject ) {
    this.evalActions( "onStartExecActions();", thisObject );
    this.evalActions( actions, thisObject );
    this.evalActions( "onStopExecActions();", thisObject );
}

Player.prototype.clearView = function() {
    this.playerView.text = "";
    this.playerView.stateText = "";
    this.playerView.clearActions();
}
Player.prototype.showLocation = function( loc ){
    this.clearPaths();
    this.updateContext( loc.text );
    var paths;
    try{
        paths = this.evalActions( "locationPaths( location );", { "location":loc });
    }catch(e){
        this.trace(e.message);
    }
    
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
    if ( context.text ) {
        this.playerView.addAction( new PlayerAction( new Path( "tmp", "next>>", "", "", "", "", path.nextLocation ) ) );
    }else
        this.showLocation( path.nextLocation );
}

