#include "sqliteclient.hpp"

SqliteClient::SqliteClient(const char *fileName)
{
	this->fileName=fileName;
}

void SqliteClient::connect()
{
	uint8_t rc;
	rc=sqlite3_open(this->fileName, &db);
	if(rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else
		fprintf(stderr, "Opened db successfully\n");
	this->connected=true;
}

std::optional<std::vector<std::string>> *SqliteClient::executeQuery(const char* query)
{
	if(!this->connected)
		return nullptr;
	auto *res=new std::optional<std::vector<std::string>>();
	std::string queryType;
	uint8_t i=0;
	while(query[i]!=' ')
		queryType+=query[i++];
	if(queryType=="SELECT")
	{
		std::vector<std::string> selectRes;
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
		uint8_t colCount=sqlite3_column_count(stmt);
		sqlite3_step(stmt);
		std::string colNames;
		for(uint8_t i=0;i<colCount;i++)
			colNames.append(std::string((char *)sqlite3_column_name(stmt, i))+"|");
		colNames.pop_back();
		selectRes.push_back(colNames);
		while(sqlite3_column_text(stmt, 0))
		{
			std::string str;
			for(uint8_t i=0;i<colCount;i++)
				str.append(std::string((char *)sqlite3_column_text(stmt, i))+ "|");
			str.pop_back();
			selectRes.push_back(str);
			sqlite3_step(stmt);
		}
		res->emplace(selectRes);
		return res;
	}
	else
	{
		sqlite3_exec(db, query, NULL, 0, 0);
		return nullptr;
	}
}


void SqliteClient::closeConnection()
{
	if(this->connected)
		sqlite3_close(db);
}

SqliteClient::~SqliteClient()
{
	this->closeConnection();
}

