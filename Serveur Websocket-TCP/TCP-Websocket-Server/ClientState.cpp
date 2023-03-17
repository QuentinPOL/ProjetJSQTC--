#include "ClientState.h"

// [Constructeur]
ClientState::ClientState(QString newUsername)
{
	authenticated = false;
	username = newUsername;
}

// [M�thode pour savoir si le client est connecter]
bool ClientState::isAuthenticated()
{
	return authenticated;
}

// [M�thode pour changer l'authentification et l'username]
void ClientState::setAuthenticated(bool newAuthenticated, QString newUsername)
{
	this->authenticated = newAuthenticated;
	this->username = newUsername;
}
