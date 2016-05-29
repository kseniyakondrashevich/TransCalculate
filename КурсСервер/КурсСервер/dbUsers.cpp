// dbUsers.cpp : implementation file
//

#include "stdafx.h"
#include "КурсСервер.h"
#include "dbUsers.h"


// dbUsers

IMPLEMENT_DYNAMIC(dbUsers, CWnd)

dbUsers::dbUsers()
{

}

dbUsers::~dbUsers()
{
}

bool dbUsers::addUser(const string login, const string password) {

	if (!login.length() || !password.length()) {
		return false;
	}

	stringstream ss;
	ss << "'" << login << "', ";
	ss << "'" << password << "'";
	string values = ss.str();

	return this->Insert("users", "login, password", values.c_str());
}

bool dbUsers::removeUser(const string login) {

	if (!login.length()) {
		return false;
	}

	return this->Delete("users", "login", login.c_str());
}

void dbUsers::SelectUsers(const string _where) {

	sqlite3_stmt *stmt = this->Select("users", _where);

	int stat = sqlite3_step(stmt);
	stringstream buffer;
	this->users.clear();

	if (stat == SQLITE_ROW) {

		for (; sqlite3_column_text(stmt, 0); sqlite3_step(stmt)) {

			Users user;

			buffer.clear();
			buffer << sqlite3_column_text(stmt, 0);
			buffer >> user.id;

			buffer.clear();
			buffer << sqlite3_column_text(stmt, 1);
			buffer >> user.login;

			buffer.clear();
			buffer << sqlite3_column_text(stmt, 2);
			buffer >> user.password;

			this->users.push_back(user);
		}

		sqlite3_finalize(stmt);
	}
}


BEGIN_MESSAGE_MAP(dbUsers, CWnd)
END_MESSAGE_MAP()



// dbUsers message handlers


