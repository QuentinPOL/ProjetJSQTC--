#pragma once
#include <qstring.h>

class Isconnected
{
public:
	Isconnected();
	bool isAuthenticated(); // M�thode d'authentification
	void setAuthenticated(bool newAuthenticated, QString newUsername); // Changer l'authentification

private:
	bool authenticated;
	QString username;
};

