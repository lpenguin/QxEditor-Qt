var URLLoader = function( url, handler, format ){
    if( url )
        this.get( url, handler, format );
}

URLLoader.prototype.get = function( url, handler, format ) {
    if( ! format )
        format = "text"
    var loader = new XMLHttpRequest()
    loader.open("GET", url, true);
    loader.onreadystatechange = function() {
        if (loader.readyState == loader.DONE) {
            var data = loader.responseText;
            if( format == "json")
                data = eval("("+data+")");
            handler.call( null, data );
        }/*else
            handler.call( null, {} );*/
    }
    loader.send(null);
}
