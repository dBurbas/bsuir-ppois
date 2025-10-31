/**
 * @file dictionary_utils.h
 * @brief Utility functions
 * @author Dmitry Burbas
 * @date 20/10/2025
 */

#include <string>

#define ASCII_BORDER 127 ///< Macros for border of ASCII symbols
#define WORD_PAIR_DELIMETER   \
  ':' ///< Macros for word delimete of pair: word <delimeter> translation
namespace utils {

/**
 * @brief Checks if a string contains only English letters.
 *
 * Allows hyphens within the word. Empty strings return false.
 *
 * @param word String to check
 * @return true if word contains only ASCII letters and hyphens
 */
bool IsEnglishWord(const std::string &word);

/**
 * @brief Checks if a string contains only Russian letters.
 *
 * Allows hyphens within the word. Empty strings return false.
 *
 * @param word String to check
 * @return true if word contains only non-ASCII letters and hyphens
 */
bool IsRussianWord(const std::string &word);

/**
 * @brief Parses a colon-separated word pair.
 * @param english Output parameter for English word
 * @param russian Output parameter for Russian word
 * @param pair String in format "english:russian"
 */
void ParseWordPair(std::string &english, std::string &russian,
                   const std::string &pair);
} // namespace utils
