//
// Created by Dmitry Burbas on 15/11/2025.
//

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#include <string>
#include <vector>
namespace Utility {
std::string Trim(const std::string& str);
std::string DeleteWhitespaces(std::string str);
std::vector<std::string> Split(const std::string& str, char delimiter);
}  // namespace Utility
#endif  // UTILITY_FUNCTIONS_H
