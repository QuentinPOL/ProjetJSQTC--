#pragma once
#include <qstring.h>

class ClientState
{
public :
	ClientState(QString username); // Constructeur
	bool isAuthenticated(); // M�thode d'authentification
	void setAuthenticated(bool newAuthenticated, QString newUsername); // Changer l'authentification

private:
	bool authenticated;
	QString username;
};

