#ifndef MYSQLMANAGER_H
#define MYSQLMANAGER_H

#include "mysqldao.h"
#include "singleton.h"

class MySQLManager : public Singleton<MySQLManager> {
    friend class Singleton<MySQLManager>;
public:
    ~MySQLManager() = default;
    int registerUser(const std::string& username, const std::string& email, const std::string& password);
private:
    MySQLManager();
    std::unique_ptr<MySQLDao> dao_;
};


#endif /* MYSQLMANAGER_H */
