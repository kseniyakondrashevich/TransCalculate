// SQLiteDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "КурсСервер.h"
#include "SQLiteDatabase.h"


// SQLiteDatabase

IMPLEMENT_DYNAMIC(SQLiteDatabase, CWnd)

SQLiteDatabase::SQLiteDatabase(const char* db_name)
{

	if (sqlite3_open(db_name, &(this->db)) != SQLITE_OK) {
		this->Error("SQL", sqlite3_errmsg(db));
	}
	else {
		this->Init();
	}
}

SQLiteDatabase::~SQLiteDatabase()
{
	sqlite3_close(this->db);
}

void SQLiteDatabase::Error(const char* type, const char* err_msg) {

	MessageBox(err_msg,
		type, MB_OK | MB_ICONERROR);
}

/**
* Initialize columns in database.
*/
void SQLiteDatabase::Init() {

	const char* colMatrixs = "id INTEGER PRIMARY KEY AUTOINCREMENT," \
		"user_id INTEGER NOT NULL," \
		"FOREIGN KEY(user_id) REFERENCES users(id)";
	this->CreateTable("matrixs", colMatrixs);

	const char* colValues = "id INTEGER PRIMARY KEY AUTOINCREMENT," \
		"matrix_id INTEGER NOT NULL," \
		"cell INTEGER NOT NULL," \
		"FOREIGN KEY(matrix_id) REFERENCES matrixs(id)";
	this->CreateTable("cells", colValues);


	const char* colUsers = "id INTEGER PRIMARY KEY AUTOINCREMENT," \
		"login TEXT NOT NULL," \
		"password TEXT NOT NULL";	
	this->CreateTable("users", colUsers);

	/*this->Delete("users", "admin", "admin");
	this->Delete("users", "111", "111");
	this->Delete("users", "login, password", "admin, admin");
	this->Delete("users", "login, password", "111, 111");*/
	//this->Insert("users", "login, password", "'admin', 'admin'");
	//this->Insert("users", "login, password", "'111', '111'");
}

/**
* Create table in database if it not exists.
*
* @param table new table name.
* @param columns list of new columns.
*/
void SQLiteDatabase::CreateTable(const char* table, const char* columns) {

	string sql = (string)"CREATE TABLE IF NOT EXISTS "
		+ table
		+ '(' + columns + ')';

	this->Execute(sql.c_str());
}

/**
* Send query to database and, if it possibly, return result.
*
* @param sql sql query, contains one or more instructions.
* @return query status true|false.
*/
bool SQLiteDatabase::Execute(const char* sql) {

	if (sqlite3_exec(this->db, sql, 0, 0, &(this->err)) != SQLITE_OK) {
		this->Error("SQL", err);
		sqlite3_free(this->err);
		return false;
	}

	return true;
}

/**
* Insert values in database.
*
* @param table that contains current columns.
* @param columns for values.
* @param values data, that'll be added to database.
* @return insert status true|false.
*/
bool SQLiteDatabase::Insert(const char* table, const char* columns, const char* values) {

	string sql = (string)"INSERT INTO "
		+ table
		+ '(' + columns + ')'
		+ " VALUES"
		+ '(' + values + ')';

	return this->Execute(sql.c_str());
}

bool SQLiteDatabase::Delete(const char* table, const char* columns, const char* values) {

	string sql = (string)"DELETE FROM "
		+ table
		+ " WHERE "
		+ columns
		+ "='"
		+ values
		+ "'";

	return this->Execute(sql.c_str());
}


/**
* Select all values from table.
*
* @param table type of table.
*/
sqlite3_stmt* SQLiteDatabase::Select(const char* table, const string _where) {


	string sql = (string)"SELECT * "
		+ " FROM "
		+ table;

	if (!_where.empty()) {
		sql += " WHERE " + _where;
	}

	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

	char short_command = this->GetShortCommand(table);

	switch (short_command) {
		case 'm': {
			return stmt;
			break;
		}
		case 'u': {
			return stmt;
			break;
		}
		case 'c': {
			return stmt;
			break;
		}
		default: {
			this->Error("SQL", "Table not found");
		}
	}
}

BEGIN_MESSAGE_MAP(SQLiteDatabase, CWnd)
END_MESSAGE_MAP()



// SQLiteDatabase message handlers


