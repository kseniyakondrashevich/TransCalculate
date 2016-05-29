#pragma once

#include "SQLiteDatabase.h"

// dbUsers

class dbUsers : public SQLiteDatabase
{
	DECLARE_DYNAMIC(dbUsers)

public:
	dbUsers();
	virtual ~dbUsers();
	bool addUser(const string login, const string password);
	bool removeUser(const string login);
	void SelectUsers(const string _where = "");

protected:
	DECLARE_MESSAGE_MAP()
};


