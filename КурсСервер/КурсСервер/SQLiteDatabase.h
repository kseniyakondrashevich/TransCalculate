#pragma once

#include "TablesLib.h"

#define DB_NAME "../lib/database.sqlite3"

// SQLiteDatabase

class SQLiteDatabase : public TablesLib
{
	DECLARE_DYNAMIC(SQLiteDatabase)

	/**
	* @var db database descriptor
	*/
	sqlite3 *db = nullptr;
	/**
	* @var err database error message
	*/
	char *err = nullptr;

public:
	SQLiteDatabase(const char* = DB_NAME);
	~SQLiteDatabase();
	void Error(const char*, const char*);
	void Init();
	void CreateTable(const char*, const char*);
	bool Execute(const char*);
	bool Insert(const char*, const char*, const char*);
	bool Delete(const char * table, const char * columns, const char * values);
	sqlite3_stmt* Select(const char* table, const string _where="");

protected:
	DECLARE_MESSAGE_MAP()
};


