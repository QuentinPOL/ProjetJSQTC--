#pragma once
#include <qstring.h>

class ClientState
{
public :
	ClientState(QString username); // Constructeur
	bool isAuthenticated(); // Méthode d'authentification
	void setAuthenticated(bool newAuthenticated, QString newUsername); // Changer l'authentification

private:
	bool authenticated;
	QString username;
};

