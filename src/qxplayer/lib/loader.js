function get( url, handler, format ) {
    if( ! format )
        format = "text"
    var loader = new XMLHttpRequest()
    loader.open("GET", url, true);
    console.log("loading: "+url)
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
