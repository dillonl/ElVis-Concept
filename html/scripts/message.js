// This enum maps to the enum in messagefactory.h
var ElVisMessageTypes = {
    LOAD_PLUGIN: 0,
    LOAD_MODEL: 1
}

var ConnectionState = {
    CONNECTING: 0,
    OPEN: 1,
    CLOSING: 2,
    CLOSED: 3,
    UNKNOWN: 4
}

var connection = null;

$(function () {

    connection = new WebSocket("ws://localhost:4849/");
    connection.onopen = function() { onOpen(); }
    connection.onerror = function(error) { onError(error); }
    connection.onmessage = function(e) { onMessage(e); }
});

/*
 * A callback for when connection is open.
 */
function onOpen() {
}

/*
 * A callback for when the connection errors.
 */
function onError(error) {
    alert('error');
}

/*
 * A callback for when connection receives a message.
 */
function onMessage(e) {
    console.log(e);
    var json_data = JSON.parse(e.data);
    alert('success = ' + json_data.success);
}

function checkSocket() {
    var state = ConnectionState.UNKNOWN;
    if ( connection != null ) {
        switch ( connection.readyState ) {
        case 0:
            state = ConnectionState.CONNECTING;
            break;
        case 1:
            state = ConnectionState.OPEN;
            break;
        case 2:
            state = ConnectionState.CLOSING;
            break;
        case 3:
            state = ConnectionState.CLOSED;
            break;
        default:
            break;
        }
    }
    return state;
}

/*
 * A messageObject should contain at least
 * a message type so the server knows how
 * to deal with it.
 */
function sendMessage(messageObject) {
    if (checkSocket() != ConnectionState.OPEN) {
        alert('You are not connected to the server');
    }
    connection.send(JSON.stringify(messageObject));

}

function sendTmpMessage() {
    sendMessage(ElVisMessageTypes);
}
