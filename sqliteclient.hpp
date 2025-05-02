#ifndef SQLITE_CLIENT_HPP
#define SQLITE_CLIENT_HPP

#include <sqlite3.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

class SqliteClient
{
	public:
		SqliteClient(const char *fileName);
		void connect();
		//void executeQuery(const char* query, std::vector<std::string> &resVec);
		std::optional<std::vector<std::string>> *executeQuery(const char* query);

		void executeQuery(const char *query, std::vector<std::unordered_map<std::string, std::string>> *queryResult);
		void closeConnection();
		~SqliteClient();
	private:
		sqlite3 *db;
		const char* fileName;
		bool connected=false;
};

#endif
