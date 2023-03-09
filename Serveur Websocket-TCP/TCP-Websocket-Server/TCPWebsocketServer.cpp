#include "TCPWebsocketServer.h"

// [Constructeur]
TCPWebsocketServer::TCPWebsocketServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    // [TCP]
    TCPserver = new QTcpServer(this);
    QObject::connect(TCPserver, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
    
    webSocketServer = new QWebSocketServer("", QWebSocketServer::SslMode::NonSecureMode, this);
    QObject::connect(webSocketServer, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));

    // [TCP]
    webSocketServer->listen(QHostAddress::AnyIPv4, 81);
    TCPserver->listen(QHostAddress::AnyIPv4, 1234);
}

// [Desctructeur]
TCPWebsocketServer::~TCPWebsocketServer()
{
    TCPserver->close();
    webSocketServer->close();

    delete TCPserver, webSocketServer;
}

// [Connexion client]
void TCPWebsocketServer::onServerNewConnection()
{

    ui.label_status->setText("Un client viens de se connecter ! ");

    // [TCP]
    QTcpSocket * client = TCPserver->nextPendingConnection();

    // [WebSocket]
    QWebSocket * clientWeb = webSocketServer->nextPendingConnection();

    // [TCP]
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

    // [WebSocket]
    QObject::connect(clientWeb, &QWebSocket::textMessageReceived, this, &TCPWebsocketServer::onWebClientReadyRead);
    QObject::connect(clientWeb, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

// [Deconnexion client]
void TCPWebsocketServer::onClientDisconnected()
{
    // [TCP]
    QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());

    // [WebSocket]
    QWebSocket * objWeb = qobject_cast<QWebSocket*>(sender());

    // [TCP]
    QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

    // [WebSocket]
    QObject::disconnect(objWeb, &QWebSocket::textMessageReceived, this, &TCPWebsocketServer::onWebClientReadyRead);
    QObject::disconnect(objWeb, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

    // [TCP]
    obj->deleteLater();

    // [WebSocket]
    objWeb->deleteLater();
}

// [Reception message client TCP]
void TCPWebsocketServer::onClientReadyRead()
{
    // [TCP]
    QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());

    // [TCP]
    QByteArray data = obj->read(obj->bytesAvailable());
    QString str(data);
    
    // [TCP]
    ui.label_status->setText("Status de connexion : Message client TCP = " + str); // Réception Message du client TCP

    // [TCP]
    onSendMessageButtonClicked(obj, nullptr, str); // Envoie du message au client TCP
}

// [Reception message client Web]
void TCPWebsocketServer::onWebClientReadyRead(const QString& message)
{
    // [WebSocket]
    QWebSocket* objWeb = qobject_cast<QWebSocket*>(sender());

    // [WebSocket]
    ui.label_status->setText("Status de connexion : Message client WebSocket = " + message); // Réception Message du client Web

    // [WebSocket]
    onSendMessageButtonClicked(nullptr, objWeb, message); // Envoie du message au Client Web
}

// [Envoie message client]
void TCPWebsocketServer::onSendMessageButtonClicked(QTcpSocket * obj, QWebSocket* objWeb, QString messageReceived) 
{
    if (obj != nullptr ) // Si c'est un objet Socket
    {
        if (obj->state() == QTcpSocket::ConnectedState)
        {
            obj->write("\n" + messageReceived.toUtf8());
            objWeb->sendTextMessage(messageReceived + "\n");
        }
    }
    else if (objWeb !=  nullptr) // Si c'est un objet Websocket
    {
        if (objWeb->state() == QAbstractSocket::ConnectedState)
        {
            objWeb->sendTextMessage(messageReceived + "\n");
            obj->write("\n" + messageReceived.toUtf8());
        }
    }
}