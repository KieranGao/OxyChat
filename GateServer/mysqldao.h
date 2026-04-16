#ifndef MYSQLDAO_H
#define MYSQLDAO_H

#include "mysqlconnectpool.h"

class ConnectionGuard {
public:
    ConnectionGuard(MySQLConnectPool& pool, std::unique_ptr<SqlConnection> conn)
        : pool_(pool), conn_(std::move(conn)) {}
    ~ConnectionGuard() {
        if (conn_) {
            pool_.returnConnection(std::move(conn_));
        }
    }
    ConnectionGuard(const ConnectionGuard&) = delete;
    ConnectionGuard& operator=(const ConnectionGuard&) = delete;
    ConnectionGuard(ConnectionGuard&&) = default;
    ConnectionGuard& operator=(ConnectionGuard&&) = default;

    std::unique_ptr<SqlConnection>& get() { return conn_; }
    explicit operator bool() const { return conn_ != nullptr; }
private:
    MySQLConnectPool& pool_;
    std::unique_ptr<SqlConnection> conn_;
};

class MySQLDao {
public:
    MySQLDao();
    ~MySQLDao();
    int registerUser(std::string username, std::string email, std::string password);
private:
    std::unique_ptr<MySQLConnectPool> pool_;
};

#endif /* MYSQLDAO_H */
