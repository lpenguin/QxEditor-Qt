var libraries;

function load( path, handler ){
    libraries = [];
    Ajax.get(path, function( data ){
        var libs = data["libraries"];
        if( libs )
            loadLibs( libs, function(){
                data.libraries = libraries;
                handler.call( null, data );
            });
        else
            handler.call( null, data );
    }, "json" );
}

function loadLibs( libs, handler ){
    var lib = libs.shift();
    if(! lib )
        handler.call( null );
    Ajax.get( lib, function( data ){
        console.log("on libs load " + data);
        libraries.push( data );
        //loadLibs( libs, handler )
    } )
}
