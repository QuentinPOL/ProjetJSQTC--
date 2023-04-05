#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCPIPQT.h"
#include "qtcpsocket.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QDateTime>
#include <deque>

class TCPIPQT : public QMainWindow
{
    Q_OBJECT

public:
    TCPIPQT(QWidget *parent = nullptr);
    ~TCPIPQT();

private:
    Ui::TCPIPQTClass ui;
	QTcpSocket * socket; // Socket pour la connexion TCP/IP
	QString userUsername;
	std::deque<char> buffer;

public slots:
	// [Bouton]
	void onSignUpButtonClicked(); // Bouton d'inscription
	void onConnectButtonClicked(); // Bouton de connexion
	void onSendMessageButtonClicked(); // Envoie Message Serveur

	// [Status]
	void onSocketConnected(); // Connexion Status
	void onSocketDisconnected(); // Déconnexion Status
	void onClientReadyRead(); // Recevoir Message Serveur
	void onMessageReceived(QJsonObject message, int arrayMessage); // Traitement message
};
