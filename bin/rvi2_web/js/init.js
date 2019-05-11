var resizeTimeout;

function send_resize()
{
    if(resizeTimeout != undefined)
    {
        clearTimeout(resizeTimeout);
    }    
    resizeTimeout = setTimeout(function() {
        Wt.emit('_COZY_WIDGET_', 'resize_signal', window.innerWidth, window.innerHeight);
    }, 500);
}

window.onresize = send_resize;