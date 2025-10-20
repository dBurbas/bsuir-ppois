/**
 * @file dictionary_utils.cc
 * @brief Utility functions implementation
 * @author Dmitry Burbas
 * @date 20/10/2025
 */

#include "dictionary_utils.h"
#include <sstream>
#include <cctype>

bool utils::IsEnglishWord(const std::string& word) {
    if (word.empty()) {
        return false;
    }
    for (unsigned char c : word) {
        if(c == '-') continue;
        if (!std::isalpha(c) || c > ASCII_BORDER) {
            return false;
        }
    }
    return true;
}
bool utils::IsRussianWord(const std::string& word) {
    if (word.empty()) {
        return false;
    }
    for (unsigned char c : word) {
        if (c == '-') continue;
        if (c <= ASCII_BORDER) return false;
    }
    return true;
}
void utils::ParseWordPair(std::string& english, std::string& russian, const std::string& pair) {
    if (pair.empty() || pair == std::string(1,WORD_PAIR_DELIMETER)) {
        throw std::invalid_argument("ParseWordPair: pair cannot be empty");
    }
    std::stringstream sstream(pair);
    std::getline(sstream, english, WORD_PAIR_DELIMETER);
    std::getline(sstream, russian, WORD_PAIR_DELIMETER);
}
