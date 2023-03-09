#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCPIPQT.h"
#include "qtcpsocket.h"

class TCPIPQT : public QMainWindow
{
    Q_OBJECT

public:
    TCPIPQT(QWidget *parent = nullptr);
    ~TCPIPQT();

private:
    Ui::TCPIPQTClass ui;
	QTcpSocket * socket; // Socket pour la connexion TCP/IP

public slots:
	void onConnectButtonClicked(); // Bouton de connexion
	void onSocketConnected(); // Connexion Status
	void onSocketDisconnected(); // Déconnexion Status
	void onSendMessageButtonClicked(); // Envoie Message Serveur
	void onSocketReadyRead(); // Reception Message Serveur
};
