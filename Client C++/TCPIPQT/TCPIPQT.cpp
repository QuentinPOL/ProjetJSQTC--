#include "TCPIPQT.h"

TCPIPQT::TCPIPQT(QWidget *parent) // Constructeur
    : QMainWindow(parent)
{
    ui.setupUi(this);

	// [Rendre invisible bouton et saisi message]
	ui.MessageEdit->setVisible(false);
	ui.pushMessageButton->setVisible(false);

	socket = new QTcpSocket(this); // Creation du socket
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));

	socket->connectToHost("127.0.0.1", 1234); // Connexion au serveur
}

TCPIPQT::~TCPIPQT() // Destructeur
{
	delete socket;
}

void TCPIPQT::onSignUpButtonClicked() // Bouton d'inscription
{
	QString username = ui.UsernameEdit->text(); // Recup l'username
	QString password = ui.PasswordEdit->text(); // Recup le password

	// Vérifier si les champs ne sont pas pas vide
	if (!username.isEmpty() && !password.isEmpty())
	{
		// Création de l'objet JSON
		QJsonObject jsonObject;
		jsonObject["type"] = "inscription";
		jsonObject["username"] = username;

		// On hash le password
		QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
		jsonObject["password"] = QString(hash.toHex());

		// Création du document JSON
		QJsonDocument jsonDoc(jsonObject);

		// Conversion du document JSON en QString
		QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Compact);

		if (socket->state() == QTcpSocket::ConnectedState) // Si le websocket est connecter
		{
			socket->write(jsonString); // Envoie du message au serveur

			// Attendre que des données soient disponibles
			if (socket->waitForReadyRead())
			{
				// Lire les données reçues
				QByteArray data = socket->read(socket->bytesAvailable());
				QString str(data);

				QJsonObject jsonMessage = QJsonDocument::fromJson(str.toUtf8()).object(); // On décode en objet JSON

				if (jsonMessage["Inscription"].toString() == "ilExiste") // Si il existe déjà
				{
					// Message d'erreur
					ui.label_error->setText("<font color='red'>Ce nom d'utilisateur existe deja !</font>");
				}
				else if (jsonMessage["Inscription"].toString() == "ilEstInscrit") // Si il est inscrit
				{
					userUsername = username; // On stocke l'username

					// désactiver et cacher bouton connexion et inscription
					ui.pushConnectButton->setEnabled(false);
					ui.pushConnectButton->setVisible(false);
					ui.pushSignUptButton->setEnabled(false);
					ui.pushSignUptButton->setVisible(false);

					// désactiver et cacher label username et password
					ui.label_username->setEnabled(false);
					ui.label_username->setVisible(false);
					ui.label_password->setEnabled(false);
					ui.label_password->setVisible(false);
					ui.label_error->setText("");

					// désactiver et cacher champSaisi username et password
					ui.UsernameEdit->setEnabled(false);
					ui.UsernameEdit->setVisible(false);
					ui.PasswordEdit->setEnabled(false);
					ui.PasswordEdit->setVisible(false);

					// Activer et afficher champSaisiMessage et boutonEnvoieMessage
					ui.MessageEdit->setEnabled(true);
					ui.MessageEdit->setVisible(true);
					ui.pushMessageButton->setEnabled(true);
					ui.pushMessageButton->setVisible(true);
				}
			}
		}
	}
	else
	{
		// le champ est vide -> Message d'erreur
		ui.label_error->setText("<font color='red'>Veuillez remplir les champs</font>");
	}
}

void TCPIPQT::onConnectButtonClicked() // Bouton de connexion
{
	QString username = ui.UsernameEdit->text(); // Recup l'username
	QString password = ui.PasswordEdit->text(); // Recup le password

	// Vérifier si les champs ne sont pas pas vide
	if (!username.isEmpty() && !password.isEmpty())
	{
		// Création de l'objet JSON
		QJsonObject jsonObject;
		jsonObject["type"] = "connexion";
		jsonObject["username"] = username;

		// On hash le password
		QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
		jsonObject["password"] = QString(hash.toHex());

		// Création du document JSON
		QJsonDocument jsonDoc(jsonObject);

		// Conversion du document JSON en QString
		QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Compact);

		if (socket->state() == QTcpSocket::ConnectedState) // Si le websocket est connecter
		{
			socket->write(jsonString); // Envoie du message au serveur

			// Attendre que des données soient disponibles
			if (socket->waitForReadyRead())
			{
				// Lire les données reçues
				QByteArray data = socket->read(socket->bytesAvailable());
				QString str(data);

				QJsonObject jsonMessage = QJsonDocument::fromJson(str.toUtf8()).object(); // On décode en objet JSON

				if (jsonMessage["Connexion"].toString() == "ilExistePas") // Si il existe pas
				{
					// Message d'erreur
					ui.label_error->setText("<font color='red'>Ce nom d'utilisateur n'existe pas !</font>");
				}
				else if (jsonMessage["Connexion"].toString() == "mdpPasBon") // Si mdp pas bon
				{
					// Message d'erreur
					ui.label_error->setText("<font color='red'>Mot de passe incorrect !</font>");
				}
				else if (jsonMessage["Connexion"].toString() == "ilEstConnecter") // Si il est connecter
				{
					userUsername = username; // On stocke l'username

					// désactiver et cacher bouton connexion et inscription
					ui.pushConnectButton->setEnabled(false);
					ui.pushConnectButton->setVisible(false);
					ui.pushSignUptButton->setEnabled(false);
					ui.pushSignUptButton->setVisible(false);

					// désactiver et cacher label username et password et error
					ui.label_username->setEnabled(false);
					ui.label_username->setVisible(false);
					ui.label_password->setEnabled(false);
					ui.label_password->setVisible(false);
					ui.label_error->setText("");

					// désactiver et cacher champSaisi username et password
					ui.UsernameEdit->setEnabled(false);
					ui.UsernameEdit->setVisible(false);
					ui.PasswordEdit->setEnabled(false);
					ui.PasswordEdit->setVisible(false);

					// Activer et afficher champSaisiMessage et boutonEnvoieMessage
					ui.MessageEdit->setEnabled(true);
					ui.MessageEdit->setVisible(true);
					ui.pushMessageButton->setEnabled(true);
					ui.pushMessageButton->setVisible(true);
				}
			}
		}
	}
	else
	{
		// le champ est vide -> Message d'erreur
		ui.label_error->setText("<font color='red'>Veuillez remplir les champs</font>");
	}
}

void TCPIPQT::onSendMessageButtonClicked()
{
	QString contentMessage = ui.MessageEdit->text(); // Recup le message

	// vérifier si le champ n'est pas vide
	if (!contentMessage.isEmpty())
	{
		// Création de l'objet JSON
		QJsonObject jsonObject;
		jsonObject["type"] = "message";
		jsonObject["username"] = userUsername;
		jsonObject["content"] = contentMessage;

		// Obtenir la date et l'heure actuelles
		QDateTime currentDateTime = QDateTime::currentDateTime();
		// Obtenir la date actuelle
		QDate currentDate = currentDateTime.date();

		jsonObject["date"] = currentDate.toString(Qt::ISODate);

		// Obtenir l'heure actuelle
		QTime currentTime = currentDateTime.time();
		jsonObject["heure"] = currentTime.toString(Qt::ISODate);

		// Création du document JSON
		QJsonDocument jsonDoc(jsonObject);

		// Conversion du document JSON en QString
		QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Compact);

		if (socket->state() == QTcpSocket::ConnectedState)
		{
			socket->write(jsonString); // Envoie du message au serveur

			// Attendre que des données soient disponibles
			if (socket->waitForReadyRead()) 
			{
				// Lire les données reçues
				QByteArray data = socket->read(socket->bytesAvailable());
				QString str(data);

				//ui.label_message->setText(str); 

				QJsonObject jsonMessage = QJsonDocument::fromJson(str.toUtf8()).object(); // On décode en objet JSON

				if (jsonMessage["Type"].toString() == "message") // Si c'est  un message
				{
					QString contentMessage = jsonMessage["Content"].toString();
					QString dateMessage = jsonMessage["Date"].toString();
					QString HeureMessage = jsonMessage["Heure"].toString();

					if (jsonMessage["Username"].toString() == userUsername) // Si c'est lui même
					{
						ui.label_message->setText("C moi !!! " + userUsername + " : " + contentMessage + ", Date : " + dateMessage  + ", Heure : " + HeureMessage);
					}
					else
					{
						QString usernameMessage = jsonMessage["Username"].toString();

						ui.label_message->setText(usernameMessage + " : " + contentMessage + ", Date : " + dateMessage + ", Heure : " + HeureMessage);
					}
				}
			}
		}
	}
	else
	{
		// le champ est vide -> Message d'erreur
		ui.label_error->setText("<font color='red'>Veuillez remplir le champ message</font>");
	}
}

void TCPIPQT::onSocketConnected()
{
	ui.label_status->setText("Status connexion : Connecter");
}

void TCPIPQT::onSocketDisconnected()
{
	ui.label_status->setText("Status connexion : Deconnecter");
}