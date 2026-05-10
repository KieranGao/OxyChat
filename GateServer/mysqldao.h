#ifndef MYSQLDAO_H
#define MYSQLDAO_H

#include "mysqlconnectpool.h"

class MySQLDao {
public:
    MySQLDao();
    ~MySQLDao();
    bool userResetpass(const std::string& username, const std::string& email, const std::string& new_password);
    int registerUser(const std::string& username, const std::string& email, const std::string& password);
private:
    std::unique_ptr<MySQLConnectPool> pool_;
};

#endif /* MYSQLDAO_H */
