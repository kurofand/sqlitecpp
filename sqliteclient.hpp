#include <sqlite3.h>
#include <vector>
#include <string>
class SqliteClient
{
	public:
		SqliteClient(const char *fileName);
		void connect();
		void executeQuery(const char* query, std::vector<std::string> &resVec);
		void returnResult(std::vector<std::string> &resVec);
		void closeConnection();
		~SqliteClient();
	private:
		sqlite3 *db;
		const char* fileName;
		bool connected=false;
};
