#include "Isconnected.h"

Isconnected::Isconnected()
{
    authenticated = false;
    username = nullptr; // nullptr
}

bool Isconnected::isAuthenticated()
{
    return authenticated;
}

void Isconnected::setAuthenticated(bool newAuthenticated, QString newUsername)
{
}
