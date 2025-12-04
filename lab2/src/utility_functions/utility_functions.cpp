//
// Created by Dmitry Burbas on 15/11/2025.
//
#include "utility_functions.h"

#include <algorithm>
#include <string>

std::string Utility::Trim(const std::string& str) {
  const auto start = str.find_first_not_of(" \t\n\r");
  if (start == std::string::npos) return "";
  const auto end = str.find_last_not_of(" \t\n\r");
  return str.substr(start, end - start + 1);
}
std::string Utility::DeleteWhitespaces(std::string str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](const char c) { return std::isspace(c); }),
            str.end());
  return str;
}
std::vector<std::string> Utility::Split(const std::string& str,
                                        char delimiter) {
  std::vector<std::string> result;
  std::size_t start = 0;
  while (true) {
    std::size_t pos = str.find(delimiter, start);
    if (pos == std::string::npos) {
      std::string token = Trim(str.substr(start));
      if (!token.empty()) {
        result.push_back(token);
      }
      break;
    }
    std::string token = Trim(str.substr(start, pos - start));
    if (!token.empty()) {
      result.push_back(token);
    }
    start = pos + 1;
  }
  return result;
}