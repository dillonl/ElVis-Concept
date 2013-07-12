ElVis.MessageTypes = {
    LOAD_PLUGIN: 0,
    LOAD_MODEL: 1
}

var connection = null;

$(function () {
    connection = new WebSocket("ws://localhost:4849/")
});

/*
 * A messageObject should contain at least
 * a message type so the server knows how
 * to deal with it.
 */
function sendMessage(messageObject) {
    
}
