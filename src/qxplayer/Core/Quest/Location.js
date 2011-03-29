function Location(id, question, text, type, actions, initActions, paths) 
{
    this.actions = actions;
    this.text = text;
    this.id = id;
    if( paths )
        this.paths = paths;
    else    
        this.paths = new Array;
    this.type = type;
    this.initActions = initActions;
}
Location.prototype.actions = "";
Location.prototype.text = "";
Location.prototype.type = "";
Location.prototype.id = "";
Location.prototype.paths = [];
Location.prototype.initActions = "";

Location.prototype.addPath = function( path ) {
    paths.push( path );
}

