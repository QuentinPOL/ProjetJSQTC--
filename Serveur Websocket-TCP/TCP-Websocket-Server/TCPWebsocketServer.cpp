#include "TCPWebsocketServer.h"

// [Constructeur]
TCPWebsocketServer::TCPWebsocketServer(QWidget *parent)
    : QMainWindow(parent)
	, TCPserver(new QTcpServer(this))
	, webSocketServer(new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this))
{
    ui.setupUi(this);

	// [TCP]
	if (TCPserver->listen(QHostAddress::AnyIPv4, 4321))
	{
		qDebug() << "Socket server listening on adress " << TCPserver->serverAddress();
		qDebug() << "Socket server listening on port" << TCPserver->serverPort();

		connect(TCPserver, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
	}

	// [Websocket]
	if (webSocketServer->listen(QHostAddress::AnyIPv4, 1236))
	{
		qDebug() << "WebSocket server listening on adress " << webSocketServer->serverAddress();
		qDebug() << "WebSocket server listening on port" << webSocketServer->serverPort();

		connect(webSocketServer, &QWebSocketServer::newConnection, this, &TCPWebsocketServer::onServerNewConnection);
	}

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
    if (sender() == TCPserver) // Si c'est un objet TCP
    {
        ui.label_status->setText("Un client application viens de se connecter ! ");

        // [TCP]
        QTcpSocket* client = TCPserver->nextPendingConnection();
        cltsTCP[client] = new ClientState(); // on créer un nouveau client tcp

        // [TCP]
        QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
        QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    }
    else if (sender() == webSocketServer) // Si c'est un objet webSocket
    {
        ui.label_status->setText("Un client Web viens de se connecter ! ");

        // [WebSocket]
        QWebSocket* clientWeb = webSocketServer->nextPendingConnection();
        cltsWeb[clientWeb] = new ClientState(); // on créer un nouveau client web

        // [WebSocket]
        QObject::connect(clientWeb, &QWebSocket::textMessageReceived, this, &TCPWebsocketServer::onWebClientReadyRead);
        QObject::connect(clientWeb, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    }
}

// [Deconnexion client]
void TCPWebsocketServer::onClientDisconnected()
{
    if (sender() == TCPserver) // Si c'est un objet TCP
    {
        // [TCP]
        QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());

        // [TCP]
        QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
        QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

        // [TCP]
        obj->deleteLater();
		delete cltsTCP[obj];
		cltsTCP.remove(obj);
    }
    else if (sender() == webSocketServer) // Si c'est un objet webSocket
    {
        // [WebSocket]
        QWebSocket* objWeb = qobject_cast<QWebSocket*>(sender());

        // [WebSocket]
        QObject::disconnect(objWeb, &QWebSocket::textMessageReceived, this, &TCPWebsocketServer::onWebClientReadyRead);
        QObject::disconnect(objWeb, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

        // [WebSocket]
        objWeb->deleteLater();
		delete cltsWeb[objWeb];
		cltsWeb.remove(objWeb);
    }
}

// [Reception message client TCP]
void TCPWebsocketServer::onClientReadyRead()
{
    QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());

    QByteArray data = obj->read(obj->bytesAvailable());
    QString str(data);
    
	qDebug() << "Status de connexion : Message client TCP = " << str;
    ui.label_message->setText("Status de connexion : Message client TCP = " + str); // Réception Message du client TCP
    onSendMessageButtonClicked(obj, nullptr, str); // Envoie du message au client TCP
}

// [Reception message client Web]
void TCPWebsocketServer::onWebClientReadyRead(const QString& message)
{
    QWebSocket* objWeb = qobject_cast<QWebSocket*>(sender());

	qDebug() << "Status de connexion : Message client TCP = " << message;
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
				// Conversion du tableau JSON en objet JSON complet
				QJsonObject result;

				// Création d'un tableau JSON pour stocker les résultats
				QJsonArray messagesArray;

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
							reponse.insert("Username", QJsonValue::fromVariant(usernameEnter));

							// Requête SQL :
							QSqlQuery selectUserPass("SELECT * FROM message ORDER BY idMessage DESC LIMIT 100");

							// Récupération des résultats et ajout à l'objet JSON
							while (selectUserPass.next())
							{
								QJsonObject message;

								message["id"] = selectUserPass.value("idMessage").toInt();
								message["username"] = selectUserPass.value("username").toString();
								message["content"] = selectUserPass.value("contentMessage").toString();
								message["date"] = selectUserPass.value("date").toString();
								message["heure"] = selectUserPass.value("heure").toString();

								messagesArray.append(message);
							}

							result["messages"] = messagesArray;
							reponse.insert("Messages", result["messages"]);
						}
					}
					reponse.insert("Type", QJsonValue::fromVariant("Inscription"));
					reponse.insert("Etat", QJsonValue::fromVariant(isExist));
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
							reponse.insert("Username", QJsonValue::fromVariant(usernameEnter));

							// Requête SQL :
							QSqlQuery selectUserPass("SELECT * FROM message ORDER BY idMessage DESC LIMIT 100");

							// Récupération des résultats et ajout à l'objet JSON
							while (selectUserPass.next())
							{
								QJsonObject message;
								qDebug() << "requete 100 objet";
								message["id"] = selectUserPass.value("idMessage").toInt();
								message["username"] = selectUserPass.value("username").toString();
								message["content"] = selectUserPass.value("contentMessage").toString();
								message["date"] = selectUserPass.value("date").toString();
								message["heure"] = selectUserPass.value("heure").toString();

								messagesArray.append(message);
							}

							result["messages"] = messagesArray;
							reponse.insert("Messages", result["messages"]);
						}
						else if (passwordEnter != passwordSelect) // Si il c'est tromper de mdp
						{
							isExist = "mdpPasBon";
						}

						reponse.insert("Type", "Connexion");
						reponse.insert("Etat", isExist);
					}
				}

				QJsonDocument messageDoc(reponse);  // On transforme en document json
				QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible

				messageBytes.append(0x01);
				obj->write(messageBytes);
			}
			else if (jsonMessage["type"].toString() == "message" && cltsTCP[obj]->isAuthenticated()) // si le client est authentifier et si c'est un message
			{
				type = 3;
				qDebug() << "fdgjfngfjn";
				// On va insérer en base
				QSqlQuery insertMessage("INSERT INTO message (username, contentMessage, date, heure) VALUES (?, ?, ?, ?)");

				insertMessage.addBindValue(usernameEnter);
				insertMessage.addBindValue(jsonMessage["content"].toString());
				insertMessage.addBindValue(jsonMessage["date"].toString());
				insertMessage.addBindValue(jsonMessage["heure"].toString());

				if (insertMessage.exec()) // Si requete réussi
				{
					// Et on va préparer la réponse en json
					reponse.insert("Type", QJsonValue::fromVariant("message"));
					reponse.insert("Username", QJsonValue::fromVariant(usernameEnter));
					reponse.insert("Content", QJsonValue::fromVariant(jsonMessage["content"].toString()));
					reponse.insert("Date", QJsonValue::fromVariant(jsonMessage["date"].toString()));
					reponse.insert("Heure", QJsonValue::fromVariant(jsonMessage["heure"].toString()));
				}
			}
		}
	}
	else if (objWeb != nullptr) // Si c'est un objet Websocket
	{
		if (objWeb->state() == QAbstractSocket::ConnectedState)
		{
			if (!cltsWeb[objWeb]->isAuthenticated()) // Si il n'est pas authentifier
			{
				// On va faire quelque chose selon l'entete de cette réponse
				if (jsonMessage["type"].toString() == "authentification" && jsonMessage["path"].toString() == "/client.php") // Si c'est une authentification
				{
					// Conversion du tableau JSON en objet JSON complet
					QJsonObject result;

					// Création d'un tableau JSON pour stocker les résultats
					QJsonArray messagesArray;

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

							// Requête SQL :
							QSqlQuery selectUserPass("SELECT * FROM message ORDER BY idMessage ASC LIMIT 100");

							// Récupération des résultats et ajout à l'objet JSON
							while (selectUserPass.next())
							{
								QJsonObject message;

								message["id"] = selectUserPass.value("idMessage").toInt();
								message["Username"] = selectUserPass.value("username").toString();
								message["Content"] = selectUserPass.value("contentMessage").toString();
								message["Date"] = selectUserPass.value("date").toString();
								message["Heure"] = selectUserPass.value("heure").toString();

								messagesArray.append(message);
							}

							result["messages"] = messagesArray;
							reponse.insert("Messages", result["messages"]);
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

				QJsonDocument messageDoc(reponse);  // On transforme en document json
				QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible

				objWeb->sendTextMessage(QString::fromUtf8(messageBytes));
			}
			else if (jsonMessage["type"].toString() == "message" && cltsWeb[objWeb]->isAuthenticated() && jsonMessage["path"].toString() == "/client.php") // Si c'est un message et que le client est authentifier et que c'est  la bonne page
			{
				type = 3;

				// On va insérer en base
				QSqlQuery insertWebMessage("INSERT INTO message (username, contentMessage, date, heure) VALUES(?, ?, ?, ?)");
				insertWebMessage.addBindValue(usernameEnter);
				insertWebMessage.addBindValue(jsonMessage["content"].toString());
				insertWebMessage.addBindValue(jsonMessage["date"].toString());
				insertWebMessage.addBindValue(jsonMessage["heure"].toString());

				if (insertWebMessage.exec())
				{
					// Et on va préparer la réponse en json
					reponse.insert("Type", QJsonValue::fromVariant("message"));
					reponse.insert("Username", QJsonValue::fromVariant(usernameEnter));
					reponse.insert("Content", QJsonValue::fromVariant(jsonMessage["content"].toString()));
					reponse.insert("Date", QJsonValue::fromVariant(jsonMessage["date"].toString()));
					reponse.insert("Heure", QJsonValue::fromVariant(jsonMessage["heure"].toString()));
				}
			}
		}
	}

    if (type == 3) // Si client
    {
        QJsonDocument messageDoc(reponse);  // On transforme en document json
        QByteArray messageBytes = messageDoc.toJson(); // On le converti en donnée compréhensible

		QByteArray tcpMessageBytes = messageDoc.toJson(); // Pour tcp
		tcpMessageBytes.append(0x01); // On va rajouter une fin de message

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
}