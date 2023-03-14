#pragma once

#include <qstring.h>

struct ClientState
{

	bool authenticated;
	QString username;

	ClientState()
	{
		authenticated = false;
		username = "";
	}
};

