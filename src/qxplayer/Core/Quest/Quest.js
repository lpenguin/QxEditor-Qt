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
    this.actions = mkFunc( jsonObject["actions"] );
    this.initActions = mkFunc( jsonObject["init"] );
    this.libraries = jsonObject["libraries"];
}


Quest.prototype.loadLocations = function( locationsArray ) {
    for ( var i in locationsArray ) {
        this.locations.push( this.loadLocation( locationsArray[i] ) );
    }
}

Quest.prototype.loadLocation = function( jsonObject ){
    return new Location( jsonObject['id'],
                        jsonObject['question'],
                        jsonObject['text'],
                        jsonObject['type'],
                        mkFunc( jsonObject['actions'] ),
                        mkFunc( jsonObject['init'] ) );
}

Quest.prototype.loadPaths = function( locationsArray ){
    var loc;
    for( var i in locationsArray ){
        loc = this.locations[i];
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
    return new Path(jsonObject["id"],
                    jsonObject["question"],
                    jsonObject['text'],
                    mkFunc( jsonObject['actions'] ),
                    mkFunc( jsonObject['init'] ),
                    mkFunc( jsonObject['conditions'] ),
                    loc);
}

Quest.prototype.reset = function() {
    locations = [];
}

Quest.prototype.findLocation = function( id ){
    for( var i in this.locations ){
        if( this.locations[i].id == id )
            return this.locations[i];
    }
    return null;
}

Quest.prototype.findStartLocation = function(){
    for( var i in this.locations ){
        if( this.locations[i].type == 'start' )
            return this.locations[i];
    }
    return null;
}    
