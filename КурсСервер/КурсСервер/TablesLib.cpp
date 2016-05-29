// TablesLib.cpp : implementation file
//

#include "stdafx.h"
#include "КурсСервер.h"
#include "TablesLib.h"


// TablesLib

IMPLEMENT_DYNAMIC(TablesLib, CWnd)

TablesLib::TablesLib()
{
	TableNames table;
	table.full_title = "matrixs";
	table.short_title = 'm';
	table_names.push_back(table);

	table.full_title = "cells";
	table.short_title = 'c';
	table_names.push_back(table);

	table.full_title = "users";
	table.short_title = 'u';
	table_names.push_back(table);
}

TablesLib::~TablesLib()
{
	this->matrixs.clear();
	this->cells.clear();
	this->users.clear();
}

list<Matrix> TablesLib::GetMatrixs()
{
	return this->matrixs;
}

list<Cells> TablesLib::GetCells()
{
	return this->cells;
}

list<Users> TablesLib::GetUsers()
{
	return this->users;
}

char TablesLib::GetShortCommand(const char *long_command)
{
	char short_command = 'z';
	list<TableNames>::iterator it;
	for (it = this->table_names.begin(); it != this->table_names.end(); it++) {
		if (!strcmp(long_command, it->full_title)) {
			short_command = it->short_title;
			break;
		}
	}

	return short_command;
}


BEGIN_MESSAGE_MAP(TablesLib, CWnd)
END_MESSAGE_MAP()



// TablesLib message handlers


