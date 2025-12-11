#include "ConfigParser.hpp"
#include <map>
#include <string>
class json_parser : public ConfigParser {
public:
  bool parser(const std::string &filepath);
  std::string getstring(const std::string &section, const std::string &key);
  json_parser();

private:
  using key = std::map<std::string, std::string>;
  using section = std::map<std::string, key>;
  section _date;
};