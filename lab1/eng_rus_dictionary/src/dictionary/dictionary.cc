/**
 * @file dictionary.cc
 * @brief Implementation of Dictionary class methods
 * @author Dmitry Burbas
 * @date 17/10/2025
 */

#include "../dictionary_utils/dictionary_utils.h"
#include "dictionary.h"
#include <fstream>
#include <stdexcept>

Dictionary::Dictionary(const Dictionary &other)
    : container_(other.container_) {}
Dictionary &Dictionary::operator=(const Dictionary &other) {
  if (this == &other)
    return *this;
  container_ = other.container_;
  return *this;
}

Dictionary &
Dictionary::operator+=(const std::pair<std::string, std::string> &word_pair) {
  if (!utils::IsEnglishWord(word_pair.first)) {
    throw std::invalid_argument(
        "Invalid argument format: first word must be english");
  }
  if (!utils::IsRussianWord(word_pair.second)) {
    throw std::invalid_argument(
        "Invalid argument format: second word must be russian");
  }
  container_.Insert(word_pair.first, word_pair.second);
  return *this;
}
Dictionary &Dictionary::operator+=(const std::string &word_pair) {
  std::string english_word, russian_word;
  utils::ParseWordPair(english_word, russian_word, word_pair);
  if (!utils::IsEnglishWord(english_word)) {
    throw std::invalid_argument(
        "Invalid argument format: first word must be english");
  }
  if (!utils::IsRussianWord(russian_word)) {
    throw std::invalid_argument(
        "Invalid argument format: second word must be russian");
  }
  container_.Insert(english_word, russian_word);
  return *this;
}
Dictionary &Dictionary::operator+=(const char *word_pair) {
  return *this += std::string(word_pair);
}

Dictionary &Dictionary::operator-=(const std::string &english_word) {
  if (!utils::IsEnglishWord(english_word)) {
    throw std::invalid_argument(
        "Invalid argument format: word must be english");
  }
  if (!container_.Erase(english_word)) {
    throw std::out_of_range("Word not found: " + english_word);
  }
  return *this;
}
Dictionary &Dictionary::operator-=(const char *english_word) {
  return *this -= std::string(english_word);
}

const std::string &
Dictionary::operator[](const std::string &english_word) const {
  if (!utils::IsEnglishWord(english_word)) {
    throw std::invalid_argument(
        "Invalid argument format: word must be english");
  }
  return container_[english_word];
}
std::string &Dictionary::operator[](const std::string &english_word) {
  if (!utils::IsEnglishWord(english_word)) {
    throw std::invalid_argument(
        "Invalid argument format: word must be english");
  }
  return container_[english_word];
}
std::ostream &operator<<(std::ostream &out_stream, const Dictionary &dict) {
  dict.container_.InOrderTraversal(
      [&out_stream](const std::string &english_word,
                    const std::string &russian_word) {
        out_stream << english_word << ":" << russian_word << "\n";
      });
  return out_stream;
}

std::istream &operator>>(std::istream &in_stream, Dictionary &dict) {
  std::string line;
  while (std::getline(in_stream, line)) {
    if (line.empty())
      continue;

    try {
      dict += line;
    } catch (const std::exception &exception) {
      continue;
    }
  }
  return in_stream;
}
bool Dictionary::LoadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }
  Clear();
  file >> *this;
  bool success = file.eof() || file.good();
  file.close();
  return success;
}
