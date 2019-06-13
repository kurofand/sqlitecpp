#include <sqlite3.h>
#include <vector>
#include <string>
#include <optional>
class SqliteClient
{
	public:
		SqliteClient(const char *fileName);
		void connect();
		//void executeQuery(const char* query, std::vector<std::string> &resVec);
		std::optional<std::vector<std::string>> *executeQuery(const char* query);
		void closeConnection();
		~SqliteClient();
	private:
		sqlite3 *db;
		const char* fileName;
		bool connected=false;
};
