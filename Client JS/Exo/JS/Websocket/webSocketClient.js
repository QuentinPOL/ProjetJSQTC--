const webSocketClient = new WebSocket('ws://localhost:5000');

exampleSocket.onopen = (event) => {
    exampleSocket.send("Here's some text that the server is urgently awaiting!");
};