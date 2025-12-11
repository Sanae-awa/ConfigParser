#include "json_parser.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
std::string trim(const std::string &line) {
  std::string whiteplace = " \t\n\r";
  size_t start = line.find_first_not_of(whiteplace);
  if (start == std::string::npos) {
    return "";
  }
  size_t end = line.find_last_not_of(whiteplace);
  return line.substr(start, end - start + 1);
}
bool json_parser::parser(const std::string &filepath) {
  std::ifstream fileopen(filepath);
  if (fileopen.is_open()) {

  } else {
    std::cout << "false" << std::endl;
    return false;
  }
  std::string line;
  std::string section;
  while (std::getline(fileopen, line)) {
    std::string line_trim = trim(line);
    if (line_trim.empty() || line_trim.front() == '{') {
      continue;
    }
    if (line_trim.back() == '}') {
      section = line_trim.substr(1, line_trim.length() - 4);
      _date[section] = {};
    }
    if (section.empty() || _date.find(section) == _date.end()) {
      continue;
    }
    size_t pos = line_trim.find(':');
    if (pos != std::string::npos) {
      std::string key = line_trim.substr(1, pos - 2);
      std::string value = line_trim.substr(pos + 2, line_trim.length() - 2);
      _date[section][key] = value;
    }
  }
  fileopen.close();
  return true;
}
std::string json_parser::getstring(const std::string &section,
                                   const std::string &key) {
  auto it_section = _date.find(section);
  if (it_section != _date.end()) {
    auto it_key = it_section->second.find(key);
    if (it_key != it_section->second.end()) {
      return it_key->second;
    }
  }
  return "";
}