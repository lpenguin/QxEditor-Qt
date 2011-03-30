var PlayerLoader = function( path, handler ){
    if( path  )
        this.load( path, handler );
}

PlayerLoader.prototype.libraries = [];
PlayerLoader.prototype.loader = new URLLoader();

PlayerLoader.prototype.loadLibs = function( libs, handler ){
    var that = this;

    var lib = libs.shift();
    if(! lib ){
        handler.call( null );
        return;
    }
    console.log("loading library: "+lib)
    this.loader.get( lib, function( data ){
        that.libraries.push( data );
        that.loadLibs( libs, handler )
    })
}

PlayerLoader.prototype.load = function( path, handler ){
    var that = this;

    //var t = function(){ function a(){ return ''; } };
    this.libraries = [];
    this.loader.get(path, function( data ){
        var libs = data["libraries"];
        if( libs )
            that.loadLibs( libs, function(){
                data["libraries"] = that.libraries;
                handler.call( null, data );
            });
        else
            handler.call( null, data );
    }, "json" );
}


