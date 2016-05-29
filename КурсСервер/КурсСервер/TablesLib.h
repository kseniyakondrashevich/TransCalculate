#pragma once


// TablesLib

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "sqlite3.h"

using namespace std;

struct TableNames {
	const char* full_title;
	char short_title;
};

struct Matrix {
	int id;
	int user_id;
};

struct Users {
	int id;
	string login;
	string password;
};

struct Cells {
	int id;
	int matrix_id;
	int cell;
};

class TablesLib : public CWnd
{
	DECLARE_DYNAMIC(TablesLib)

public:
	TablesLib();
	~TablesLib();
	list<Matrix> GetMatrixs();
	list<Cells> GetCells();
	list<Users> GetUsers();
	char TablesLib::GetShortCommand(const char*);

protected:
	list<TableNames> table_names;
	list<Matrix> matrixs;
	list<Cells> cells;
	list<Users> users;

	DECLARE_MESSAGE_MAP()
};


