#include "ini_parser.hpp"
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
} // 去除空格
bool ini_parser::parser(const std::string &filepath) {
  std::ifstream fileopen(filepath); // 打开文件
  if (fileopen.is_open()) {

  } else {
    std::cout << "false" << std::endl;
    return false;
  } // 检查
  std::string line;
  std::string section;
  while (std::getline(fileopen, line)) {
    std::string line_trim = trim(line);
    if (line_trim.empty()) {
      continue;
    } // 空行跳过
    if (line_trim.front() == '[' && line_trim.back() == ']') {
      section = line_trim.substr(1, line_trim.length() - 1);
      _date[section] = {};
    } // 初始化section(map第一层)
    if (section.empty() || _date.find(section) == _date.end()) {
      continue;
    } // 检查section是否为空
    size_t pos = line_trim.find(':'); // 检查是否有':'
    if (pos != std::string::npos) {
      std::string key = line_trim.substr(0, pos);
      std::string value = line_trim.substr(pos + 1);
      _date[section][key] = value; // 赋值
    }
  }
  fileopen.close(); // 关闭文件
  return true;
}
std::string ini_parser::getstring(const std::string &section,
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
// 后续增加注释检查