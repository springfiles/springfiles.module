

function hidediv(pass) {
    var divs = document.getElementsByTagName('div');
    for(i=0;i<divs.length;i++){
        if(divs[i].id.match(pass)){//if they are 'see' divs
            if (document.getElementById) // DOM3 = IE5, NS6
            divs[i].style.visibility="hidden";// show/hide
            else
            if (document.layers) // Netscape 4
            document.layers[divs[i]].display = 'hidden';
            else // IE 4
            document.all.hideshow.divs[i].visibility = 'hidden';
        }
    }
}

function showdiv(pass) {
    var divs = document.getElementsByTagName('div');
    for(i=0;i<divs.length;i++){
        if(divs[i].id.match(pass)){
            if (document.getElementById)
            divs[i].style.visibility="visible";
            else
            if (document.layers) // Netscape 4
            document.layers[divs[i]].display = 'visible';
            else // IE 4
            document.all.hideshow.divs[i].visibility = 'visible';
        }
    }
}

function SetImage(id) {
    
    if (id == 0)
    {
        showdiv('spring-geomap');
        hidediv('spring-metalmap');
        hidediv('spring-heightmap');
    }
    if (id == 1)
    {
        showdiv('spring-metalmap');
        hidediv('spring-geomap');
        hidediv('spring-heightmap');
    }
    if (id == 2)
    {
        showdiv('spring-heightmap');
        hidediv('spring-geomap');
        hidediv('spring-metalmap');
       
    }

}
