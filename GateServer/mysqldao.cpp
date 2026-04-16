#include "mysqldao.h"
#include "configmanager.h"
MySQLDao::MySQLDao() {
    ConfigManager& config = ConfigManager::getInstance();
    std::string host = config["MySQL"]["host"];
    std::string port = config["MySQL"]["port"];
    std::string user = config["MySQL"]["user"];
    std::string dbName = config["MySQL"]["dbName"];
    std::string password = config["MySQL"]["password"];
    pool_ = std::make_unique<MySQLConnectPool>(5, host + ":" + port, user, password, dbName);
}

MySQLDao::~MySQLDao() {
    pool_->stop();
}

int MySQLDao::registerUser(std::string username, std::string email, std::string password) {
    auto connection = ConnectionGuard(*pool_, pool_->getConnection());
    try {
        auto& sql_conn = connection.get()->getConn();
        std::unique_ptr<sql::PreparedStatement> stmt(sql_conn->prepareStatement("CALL reg_user(?,?,?,@result)"));
        stmt->setString(1, username);
        stmt->setString(2, email);
        stmt->setString(3, password);
        stmt->execute();

        std::unique_ptr<sql::Statement> stmtResult(sql_conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
        if (res and res->next()) {
            return res->getInt("result");
        }
        return -1;
    } catch(sql::SQLException& exp) {
        std::cerr << "SQLException: " << exp.what();
        std::cerr << " (MySQL error code: " << exp.getErrorCode();
        std::cerr << ", SQLState: " << exp.getSQLState() << " )" << std::endl;
        return -1;
    }
}