#include "mysqlmanager.h"

int MySQLManager::registerUser(const std::string& username, const std::string& email, const std::string& password) {
    int ret = dao_->registerUser(username, email, password);
    return ret; 
}