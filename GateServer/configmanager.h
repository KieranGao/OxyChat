#include "global.h"
#include "boost/filesystem.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

struct SectionInfo {
    SectionInfo() = default;
    ~SectionInfo(){_section_datas.clear();}
    SectionInfo(const SectionInfo& src) {
        _section_datas = src._section_datas;
    }
    SectionInfo& operator=(const SectionInfo& src) {
        if (&src == this) {
            return *this;
        }
        this->_section_datas = src._section_datas;
        return *this;
    }
    std::map<std::string, std::string> _section_datas;
    std::string operator[](const std::string  &key) {
        if (_section_datas.find(key) == _section_datas.end()) {
            return "";
        }
        return _section_datas[key];
    }
};

class ConfigManager
{
public:
    ConfigManager();
    ~ConfigManager() {conf_map_.clear();};
    SectionInfo operator[](const std::string& section) {
        if (conf_map_.find(section) == conf_map_.end()) {
            return SectionInfo();
        }
        return conf_map_[section];
    }
    ConfigManager& operator=(const ConfigManager& src) {
        if (&src == this) {
            return *this;
        }
        this->conf_map_ = src.conf_map_;
    };
    ConfigManager(const ConfigManager& src) {
        this->conf_map_ = src.conf_map_;
    }
private:
    // 存储section和key-value对的map  
    std::map<std::string, SectionInfo> conf_map_;
};