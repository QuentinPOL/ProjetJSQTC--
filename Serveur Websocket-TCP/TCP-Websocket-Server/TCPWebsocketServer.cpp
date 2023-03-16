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

    // [BDD]
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("192.168.64.174");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("chatdatabase");

    if (db.open())
    {
        ui.label_database->setText("Connexion reussie  a " + QString::fromStdString(db.hostName().toStdString()));
    }
    else
    {
        ui.label_status->setText("Probleme de connexion a " + QString::fromStdString(db.hostName().toStdString()));
    }

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

	clients[clientWeb] = new ClientState();
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
    bool isConnected  = false;

    if (obj != nullptr ) // Si c'est un objet Socket
    {
        if (obj->state() == QTcpSocket::ConnectedState)
        {
            obj->write("\n" + messageReceived.toUtf8());
        }
    }
    else if (objWeb !=  nullptr) // Si c'est un objet Websocket
    {
		ClientState * clientState = clients[objWeb];
		if (!clientState->authenticated)
		{
			// Ne peut que inscription ou connexion
		}
		else
		{
			// Peut envoyer des messages ...
		}

        if (objWeb->state() == QAbstractSocket::ConnectedState)
        {    
			QJsonObject jsonMessage = QJsonDocument::fromJson(messageReceived.toUtf8()).object(); // On décode en objet JSON      
			QJsonObject reponse; //  On créer la réponse en objet JSON

            if (jsonMessage["type"].toString() == "inscription")
            {
                QString usernameEnter = jsonMessage["username"].toString();
                QString passwordEnter = jsonMessage["password"].toString();
                QString isExist = "ilExistePas";

                // On va faire quelque chose selon l'entete de cette réponse
                if (jsonMessage["type"].toString() == "inscription") // Si  c'est  une inscription
                {
                    // Requête SQL :
                    QSqlQuery selectUsername("SELECT username FROM account");

                    while (selectUsername.next()) // Tant que y'a des tuples
                    {
                        //ui.label_user->setText("Username = " + usernameSelect);
                        if (selectUsername.value(0).toString() == usernameEnter) // Si on trouve que l'username existe déjà
                        {
                            isExist = "ilExiste"; // On met la QString à vrai
                            break;
                        }
                    }

                    if (isExist == "ilExistePas") // Si on trouve pas l'username
                    {
                        QSqlQuery insert("INSERT INTO account (username, password) VALUES (?, ?)");
                        insert.addBindValue(usernameEnter);
                        insert.addBindValue(passwordEnter);

                        if (insert.exec())
                        {
                            isExist = "ilEstInscrit";
                            //isConnected = true;
                            //ui.label_message->setText("Inscription = " + messageReceived); // Réception Message du client Web
                        }
                    }

                    reponse.insert("Inscription", QJsonValue::fromVariant(isExist));
                }
                else  if (jsonMessage["type"].toString() == "connexion") // Si  c'est  une connexion
                {
                    // Requête SQL :
                    QSqlQuery selectUserPass("SELECT username, password FROM account WHERE username = '"+usernameEnter+"'");

                    if (selectUserPass.next()) // Si il y a > 0 tuples
                    {
                        QString userSelect = selectUserPass.value("username").toString();
                        QString passwordSelect = selectUserPass.value("password").toString();

                        if (usernameEnter == userSelect && passwordEnter == passwordSelect) // Si il à rentrer les bons identifiants
                        {
                            isExist = "ilEstConnecter";
                            //isConnected = true;
                            //ui.label_message->setText("Connexion = " + messageReceived); // Réception Message du client Web
                        }
                        else if (passwordEnter != passwordSelect) // Si il c'est tromper de mdp
                        {
                            isExist = "mdpPasBon";
                        }
                    }

                    reponse.insert("Connexion", QJsonValue::fromVariant(isExist));
                }
				else if (jsonMessage["type"].toString() == "message") // Si c'est un message
				{
					// On va vérifier qu'il est authentifier

					// On va insérer en base
					QSqlQuery insertMessage("INSERT INTO account (username, password) VALUES(?, ?)");
					insertMessage.addBindValue(jsonMessage["type"].toString());
					insertMessage.addBindValue(jsonMessage["type"].toString());


					// Et on va préparer la réponse en json

				}
            }

            QJsonDocument messageDoc(reponse);  // On transforme en document json
            QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible
            objWeb->sendTextMessage(QString::fromUtf8(messageBytes)); // Ensuite on envoie une chaine

			/*
			// Parcourir l'ensemble des clients présent dans le tableau associatif :
			for (auto it = clients.keyBegin(); it != clients.keyEnd(); it++)
			{
				(*it)->sendTextMessage("Test");
			}
			*/
            //objWeb->sendTextMessage(messageReceived + '\n');
        }
    }
}