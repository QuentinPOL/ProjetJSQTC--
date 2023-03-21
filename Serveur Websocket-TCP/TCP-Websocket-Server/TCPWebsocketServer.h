#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCPWebsocketServer.h"
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <qmap.h>
#include "ClientState.h"

class TCPWebsocketServer : public QMainWindow
{
    Q_OBJECT

public:
    TCPWebsocketServer(QWidget *parent = nullptr);
    ~TCPWebsocketServer();

private:
    Ui::TCPWebsocketServerClass ui;
    QTcpServer* TCPserver; // TCP Server
    QWebSocketServer* webSocketServer; // WebSocket Server
    QSqlDatabase db; // Base de donnée
	QMap<QTcpSocket*, ClientState*> cltsTCP; // Listes des clients TCP
	QMap<QWebSocket*, ClientState*> cltsWeb; // Listes des clients Web

public slots:
    void onServerNewConnection(); // Connexion client
    void onClientDisconnected(); // Deconnexion client
    void onClientReadyRead(); // Reception message client application
    void onWebClientReadyRead(const QString& message); // Reception message client web
    void onSendMessageButtonClicked(QTcpSocket* obj, QWebSocket* objWeb, QString messageReceived); // Envoie message client
};
