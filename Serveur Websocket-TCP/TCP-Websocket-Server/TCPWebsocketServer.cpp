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
	cltsTCP[client] = new ClientState(); // on créer un nouveau client tcp

    // [WebSocket]
    QWebSocket * clientWeb = webSocketServer->nextPendingConnection();
	cltsWeb[clientWeb] = new ClientState(); // on créer un nouveau client web

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
    QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());

    QByteArray data = obj->read(obj->bytesAvailable());
    QString str(data);
    
    ui.label_message->setText("Status de connexion : Message client TCP = " + str); // Réception Message du client TCP
    onSendMessageButtonClicked(obj, nullptr, str); // Envoie du message au client TCP
}

// [Reception message client Web]
void TCPWebsocketServer::onWebClientReadyRead(const QString& message)
{
    QWebSocket* objWeb = qobject_cast<QWebSocket*>(sender());

    ui.label_message->setText("Status de connexion : Message client WebSocket = " + message); // Réception Message du client Web
    onSendMessageButtonClicked(nullptr, objWeb, message); // Envoie du message au Client Web
}

// [Envoie message client]
void TCPWebsocketServer::onSendMessageButtonClicked(QTcpSocket * obj, QWebSocket* objWeb, QString messageReceived) 
{
	QJsonObject jsonMessage = QJsonDocument::fromJson(messageReceived.toUtf8()).object(); // On décode en objet JSON      
	QJsonObject reponse; //  On créer la réponse en objet JSON
    int type = 0; // Variable  de type (connexion, inscription, message)

    QString usernameEnter = jsonMessage["username"].toString();
    QString passwordEnter, isExist;

    if (jsonMessage["type"].toString() == "inscription" || jsonMessage["type"].toString() == "connexion" || jsonMessage["type"].toString() == "authentification") // Si c'est connexion ou inscription ou authentification
    {
        passwordEnter = jsonMessage["password"].toString();
        isExist = "ilExistePas";
    }

    if (obj != nullptr) // Si c'est un objet Socket
    {
        if (obj->state() == QTcpSocket::ConnectedState)
        {
            if (!cltsTCP[obj]->isAuthenticated()) // Si il n'est pas authentifier
            {
                if (jsonMessage["type"].toString() == "inscription") // Si c'est  une inscription
                {
					type = 1;

                    // Requête SQL :
                    QSqlQuery selectUsername("SELECT username FROM account");

                    while (selectUsername.next()) // Tant que y'a des tuples
                    {
                        if (selectUsername.value(0).toString() == usernameEnter) // Si on trouve que l'username existe déjà
                        {
                            isExist = "ilExiste"; // On met la QString à ilExiste
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
							cltsTCP[obj]->setAuthenticated(true, usernameEnter); // on va authentifié notre client
                        }
                    }
                    reponse.insert("Inscription", QJsonValue::fromVariant(isExist));
                }
                else if (jsonMessage["type"].toString() == "connexion") // Si c'est une connexion
                {
					type = 2;

                    // Requête SQL :
                    QSqlQuery selectUserPass("SELECT username, password FROM account WHERE username = '" + usernameEnter + "'");

                    if (selectUserPass.next()) // Si il y a > 0 tuples
                    {
                        QString userSelect = selectUserPass.value("username").toString();
                        QString passwordSelect = selectUserPass.value("password").toString();

                        if (usernameEnter == userSelect && passwordEnter == passwordSelect) // Si il à rentrer les bons identifiants
                        {
                            isExist = "ilEstConnecter";
							cltsTCP[obj]->setAuthenticated(true, usernameEnter); // on va authentifié notre client
                        }
                        else if (passwordEnter != passwordSelect) // Si il c'est tromper de mdp
                        {
                            isExist = "mdpPasBon";
                        }
                    }
                    reponse.insert("Connexion", QJsonValue::fromVariant(isExist));
                }
            }
            else if (jsonMessage["type"].toString() == "message" && cltsWeb[objWeb]->isAuthenticated()) // si le client est authentifier et si c'est un message
            {
				type = 3;

                // On va insérer en base
                QSqlQuery insertMessage("INSERT INTO message (username, contentMessage, date, heure) VALUES (?, ?, ?, ?)");

                insertMessage.addBindValue(usernameEnter);
                insertMessage.addBindValue(jsonMessage["content"].toString());
                insertMessage.addBindValue(jsonMessage["date"].toString());
                insertMessage.addBindValue(jsonMessage["heure"].toString());

                if (insertMessage.exec()) // Si requete réussi
                {
                    // Et on va préparer la réponse en json
                    reponse.insert("username", QJsonValue::fromVariant(usernameEnter));
                    reponse.insert("content", QJsonValue::fromVariant(jsonMessage["content"].toString()));
                    reponse.insert("date", QJsonValue::fromVariant(jsonMessage["date"].toString()));
                    reponse.insert("heure", QJsonValue::fromVariant(jsonMessage["heure"].toString()));
                }
            }

            QJsonDocument messageDoc(reponse);  // On transforme en document json
            QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible

            obj->write(messageBytes); // On envoie le message
            //obj->write("\n" + messageReceived.toUtf8());
        }
    }
    else if (objWeb !=  nullptr) // Si c'est un objet Websocket
    {
        if (objWeb->state() == QAbstractSocket::ConnectedState)
        {
			if (!cltsWeb[objWeb]->isAuthenticated()) // Si il n'est pas authentifier
			{
				// On va faire quelque chose selon l'entete de cette réponse
				if (jsonMessage["type"].toString() == "authentification" && jsonMessage["path"].toString() == "/client.php") // Si c'est une authentification
				{
					// On va faire une requête pour vérifier qu'il existe bien
					QSqlQuery selectUserPass("SELECT username, password FROM account WHERE username = '" + usernameEnter + "'");

					if (selectUserPass.next()) // Si il y a > 0 tuples
					{
						QString userSelect = selectUserPass.value("username").toString();
						QString passwordSelect = selectUserPass.value("password").toString();

						if (usernameEnter == userSelect && passwordEnter == passwordSelect) // Si il à rentrer les bons identifiants
						{
							isExist = "ilEstConnecter";
							cltsWeb[objWeb]->setAuthenticated(true, usernameEnter); // on va authentifié notre client
						}
						else if (passwordEnter != passwordSelect) // Si il c'est tromper de mdp
						{
							isExist = "mdpPasBon";
						}
					}
					reponse.insert("Authentification", QJsonValue::fromVariant(isExist));
				}
				else if (jsonMessage["type"].toString() == "inscription" && jsonMessage["page"].toString() == "inscription.php") // Si  c'est  une inscription que c'est bien la page
				{
                    type = 1;

					// Requête SQL :
					QSqlQuery selectUsername("SELECT username FROM account");

					while (selectUsername.next()) // Tant que y'a des tuples
					{
						if (selectUsername.value(0).toString() == usernameEnter) // Si on trouve que l'username existe déjà
						{
							isExist = "ilExiste"; // On met la QString à ilExiste
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
							cltsWeb[objWeb]->setAuthenticated(true, usernameEnter); // on va authentifié notre client
                            reponse.insert("Username", QJsonValue::fromVariant(usernameEnter)); // On va renvoyer l'username
							reponse.insert("Password", QJsonValue::fromVariant(passwordEnter)); // On va renvoyer le password
						}
					}
					reponse.insert("Inscription", QJsonValue::fromVariant(isExist));
				}
				else  if (jsonMessage["type"].toString() == "connexion" && jsonMessage["path"].toString() == "/" || jsonMessage["page"].toString() == "index.php") // Si  c'est  une connexion et la bonne page
				{
                    type = 2;

					// Requête SQL :
					QSqlQuery selectUserPass("SELECT username, password FROM account WHERE username = '" + usernameEnter + "'");

					if (selectUserPass.next()) // Si il y a > 0 tuples
					{
						QString userSelect = selectUserPass.value("username").toString();
						QString passwordSelect = selectUserPass.value("password").toString();

						if (usernameEnter == userSelect && passwordEnter == passwordSelect) // Si il à rentrer les bons identifiants
						{
							isExist = "ilEstConnecter";
							cltsWeb[objWeb]->setAuthenticated(true, usernameEnter); // on va authentifié notre client
                            reponse.insert("Username", QJsonValue::fromVariant(usernameEnter)); // On va renvoyer l'username
							reponse.insert("Password", QJsonValue::fromVariant(passwordEnter)); // On va renvoyer le password
						}
						else if (passwordEnter != passwordSelect) // Si il c'est tromper de mdp
						{
							isExist = "mdpPasBon";
						}
					}
					reponse.insert("Connexion", QJsonValue::fromVariant(isExist));
				}
			}
			else
			{
                if (jsonMessage["type"].toString() == "message" && cltsWeb[objWeb]->isAuthenticated() && jsonMessage["path"].toString() == "/client.php") // Si c'est un message et que le client est authentifier et que c'est  la bonne page
				{
					type = 3;

					// On va insérer en base
					QSqlQuery insertMessage("INSERT INTO message (username, content, date, heure) VALUES(?, ?, ?, ?)");
					insertMessage.addBindValue(usernameEnter);
					insertMessage.addBindValue(jsonMessage["content"].toString());
					insertMessage.addBindValue(jsonMessage["date"].toString());
					insertMessage.addBindValue(jsonMessage["heure"].toString());

					// Et on va préparer la réponse en json
					reponse.insert("Type", QJsonValue::fromVariant("message"));
					reponse.insert("Username", QJsonValue::fromVariant(usernameEnter));
					reponse.insert("Content", QJsonValue::fromVariant(jsonMessage["content"].toString()));
					reponse.insert("Date", QJsonValue::fromVariant(jsonMessage["date"].toString()));
					reponse.insert("Heure", QJsonValue::fromVariant(jsonMessage["heure"].toString()));
				}
			}

            QJsonDocument messageDoc(reponse);  // On transforme en document json
            QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible

            if (type == 3) // Si client
            {
                // Parcourir l'ensemble des clients Webs présent dans le tableau associatif :
                for (auto it = cltsTCP.keyBegin(); it != cltsTCP.keyEnd(); it++)
                {
                    (*it)->write(messageBytes);
                }

				// Parcourir l'ensemble des clients TCPs présent dans le tableau associatif :
				for (auto it = cltsWeb.keyBegin(); it != cltsWeb.keyEnd(); it++)
				{
					(*it)->sendTextMessage(QString::fromUtf8(messageBytes));
				}
            }
            else // Si c'est une inscription ou connexion
            {
                objWeb->sendTextMessage(QString::fromUtf8(messageBytes)); // Ensuite on envoie une chaine
            }
        }
    }
}