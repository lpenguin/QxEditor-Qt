var Quest = function ( jsonObject ) {
    if( jsonObject )
        this.load( jsonObject );
}

Quest.prototype.name = [];
Quest.prototype.description = "";
Quest.prototype.initActions = "";
Quest.prototype.actions = "";
Quest.prototype.libraries = [];

Quest.prototype.locations = [];

Quest.prototype.load = function( jsonObject ) {
    var locationsArray = jsonObject["vers"];
    this.loadLocations( locationsArray );
    this.loadPaths( locationsArray );
    
    this.name = jsonObject["name"];
    this.description = jsonObject["description"];
    this.actions = jsonObject["actions"];
    this.initActions = jsonObject["init"];
    this.libraries = jsonObject["libraries"];
}


Quest.prototype.loadLocations = function( locationsArray ) {
    for ( var i in locationsArray ) {
        this.locations.push( this.loadLocation( locationsArray[i] ) );
    }
}

Quest.prototype.loadLocation = function( jsonObject ){
    return new Location( jsonObject['id'], jsonObject['question'], jsonObject['text'], jsonObject['type'], jsonObject['actions'], jsonObject['init'] );
}

Quest.prototype.loadPaths = function( locationsArray ){
    var loc;
    for( var i in locationsArray ){
        loc = locations[i];
        var pathsArray = locationsArray[i]["edges"];
        for( var j in pathsArray ){
            loc.addPath( this.loadPath( pathsArray[j] ) );
        }
    }
}
Quest.prototype.loadPath = function( jsonObject) {
    var locId = jsonObject["nextVer"];
    var loc = this.findLocation( locId );
    if( loc == null)
        throw Error("Location '"+locId+"' not found");
    return new Path(jsonObject["id"], jsonObject["question"], jsonObject['text'], jsonObject['actions'], jsonObject['init'], jsonObject['conditions'], loc);
}

Quest.prototype.reset = function() {
    locations = [];
}

Quest.prototype.findLocation = function( id ){
    var loc;
    for( var i in _locations ){
        if( locations[i].id == id )
            return loc;
    }
    return null;
}

Quest.prototype.findStartLocation = function(){
    var loc;
    for( var i in _locations ){
        if( locations[i].type == 'start' )
            return loc;
    }
    return null;
}    
