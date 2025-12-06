#include "ConfigParser.hpp"
#include <map>
#include <string>
class ini_parser : public ConfigParser {
public:
  bool parser(const std::string &filepath);
  std::string getstring(const std::string &section, const std::string &key);

private:
  using key = std::map<std::string, std::string>;
  using section = std::map<std::string, key>;
  section _date;
};