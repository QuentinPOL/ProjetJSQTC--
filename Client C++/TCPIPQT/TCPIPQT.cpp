#include "TCPIPQT.h"
#include <qdebug.h>

TCPIPQT::TCPIPQT(QWidget *parent) // Constructeur
    : QMainWindow(parent)
{
    ui.setupUi(this);


	// [Rendre invisible bouton et saisi message et zone]
	ui.MessageEdit->setVisible(false);
	ui.pushMessageButton->setVisible(false);
	ui.plainTextEdit->setVisible(false);

	ui.PasswordEdit->setEchoMode(QLineEdit::Password); // Cache le mdp

	socket = new QTcpSocket(this); // Creation du socket
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));

	socket->connectToHost("192.168.64.101", 4321); // Connexion au serveur
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
		}
	}
	else
	{
		// le champ est vide -> Message d'erreur
		ui.label_error->setText("<font color='red'>Veuillez remplir le champ message</font>");
	}
}

void TCPIPQT::onClientReadyRead()
{
	// Lire les données reçues
	QByteArray data = socket->read(socket->bytesAvailable());
	QString str(data);
	std::string stdstr = str.toStdString();
	for (int i = 0; i < str.length(); i++)
	{
		buffer.push_back(stdstr[i]);
	}

	bool hasCompleteMessage = false;
	int messageEndIdx = -1;
	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] == 0x01)
		{
			hasCompleteMessage = true;
			messageEndIdx = i;
			break;
		}
	}

	if (hasCompleteMessage)
	{
		str = "";
		for (int i = 0; i < messageEndIdx; i++)
		{
			str += buffer.front();
			buffer.pop_front();
		}
		buffer.pop_front();

		QJsonObject jsonMessage = QJsonDocument::fromJson(str.toUtf8()).object(); // On décode en objet JSON

		// Si c'est une inscription
		if (jsonMessage["Type"].toString() == "Inscription")
		{
			if (jsonMessage["Etat"].toString() == "ilExiste") // Si il existe déjà
			{
				// Message d'erreur
				ui.label_error->setText("<font color='red'>Ce nom d'utilisateur existe deja !</font>");
			}
			else if (jsonMessage["Etat"].toString() == "ilEstInscrit") // Si il est inscrit
			{
				userUsername = jsonMessage["Username"].toString(); // On stocke l'username

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

				// Activer la chatbox
				ui.plainTextEdit->setEnabled(true);
				ui.plainTextEdit->setVisible(true);

				onMessageReceived(jsonMessage, 1);
			}
		}
		else if (jsonMessage["Type"].toString() == "Connexion") // Si c'est une connexion
		{
			if (jsonMessage["Etat"].toString() == "ilExistePas") // Si il existe pas
			{
				// Message d'erreur
				ui.label_error->setText("<font color='red'>Ce nom d'utilisateur n'existe pas !</font>");
			}
			else if (jsonMessage["Etat"].toString() == "mdpPasBon") // Si mdp pas bon
			{
				// Message d'erreur
				ui.label_error->setText("<font color='red'>Mot de passe incorrect !</font>");
			}
			else if (jsonMessage["Etat"].toString() == "ilEstConnecter") // Si il est connecter
			{
				userUsername = jsonMessage["Username"].toString(); // On stocke l'username

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

				// Activer la chatbox
				ui.plainTextEdit->setEnabled(true);
				ui.plainTextEdit->setVisible(true);

				onMessageReceived(jsonMessage, 1);
			}
		}
		else if (jsonMessage["Type"].toString() == "message") // Si c'est un message
		{
			onMessageReceived(jsonMessage, 0);
		}
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

void TCPIPQT::onMessageReceived(QJsonObject message, int arrayMessage)
{
	QString Message;

	if (arrayMessage == 1) // Si c'est le tableau des derniers messages
	{
		QJsonArray messagesArray = message.value("Messages").toArray();

		for (int i = messagesArray.size() - 1; i >= 0; --i) {
			QJsonValue value = messagesArray.at(i);

			QString contentMessage = value["content"].toString();
			QString dateMessage = value["date"].toString();
			QString HeureMessage = value["heure"].toString();

			if (value["username"].toString() == userUsername) // Si c'est lui même
			{
				Message = "<font color='red'>(Moi même) : " + userUsername + " : " + contentMessage + ", Date : " + dateMessage + ", Heure : " + HeureMessage + "</font>";
				ui.plainTextEdit->appendHtml(Message);
			}
			else
			{
				QString usernameMessage = value["username"].toString();

				Message = "<font color='blue'>" + usernameMessage + " : " + contentMessage + ", Date : " + dateMessage + ", Heure : " + HeureMessage + "</font>";
				ui.plainTextEdit->appendHtml(Message);
			}
		}
	}
	else
	{
		QString contentMessage = message["Content"].toString();
		QString dateMessage = message["Date"].toString();
		QString HeureMessage = message["Heure"].toString();

		if (message["Username"].toString() == userUsername) // Si c'est lui même
		{
			Message = "<font color='red'>(Moi même) : " + userUsername + " : " + contentMessage + ", Date : " + dateMessage + ", Heure : " + HeureMessage + "</font>";
			ui.plainTextEdit->appendHtml(Message);
		}
		else
		{
			QString usernameMessage = message["Username"].toString();

			Message = "<font color='blue'>" + usernameMessage + " : " + contentMessage + ", Date : " + dateMessage + ", Heure : " + HeureMessage + "</font>";
			ui.plainTextEdit->appendHtml(Message);
		}
	}
}