#pragma once
#include <string>
class ConfigParser {
public:
  virtual ~ConfigParser();
  virtual bool parser() = 0;
  virtual std::string getstring() = 0;
};