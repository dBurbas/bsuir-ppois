/**
 * @mainpage English-Russian Dictionary Documentation
 *
 * @section intro_sec Introduction
 *
 * This project implements an English-Russian dictionary using a binary
 * search tree data structure for efficient word lookup and storage.
 *
 * @section features_sec Key Features
 *
 * - Fast O(log n) average lookup time
 * - Alphabetically sorted word pairs
 * - Support for adding and removing translations
 * - File I/O operations for loading dictionaries
 *
 * @section usage_sec Usage Example
 *
 * @code
 * Dictionary dict;
 * dict += "hello:привет";
 * dict += "world:мир";
 * std::cout << dict["hello"]; // Outputs: привет
 * @endcode
 *
 * @section classes_sec Main Classes
 *
 * - BinarySearchTree: Template class for key-value storage
 * - Dictionary: English-Russian dictionary implementation
 *
 * @author Dmitry Burbas
 * @date October 2025
 */

/**
 * @file dictionary.h
 * @brief English-Russian dictionary implementation
 * @author Dmitry Burbas
 * @date 17/10/2025
 */
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include "../binary_search_tree/binary_search_tree.hpp"

/**
 * @brief English-Russian dictionary class.
 * 
 * This class provides a dictionary that maps English words to their Russian
 * translations. It uses a binary search tree internally for efficient lookup
 * and maintains alphabetical ordering.
 */
class Dictionary {
public:
    /**
     * @brief Default constructor. Creates an empty dictionary.
     */
    Dictionary() = default;

    /**
     * @brief Copy constructor. Creates a deep copy of another dictionary.
     * @param other Dictionary to copy from
     */
    Dictionary(const Dictionary& other);

    /**
     * @brief Copy assignment operator.
     * @param other Dictionary to copy from
     * @return Reference to this dictionary
     */
    Dictionary& operator=(const Dictionary& other);
    
    /**
     * @brief Destructor. Automatically cleans up all resources.
     */
    ~Dictionary() = default;
    
    /**
     * @brief Adds a word pair to the dictionary.
     * 
     * The first element must be an English word,
     * and the second must be a Russian word.
     * 
     * @param word_pair Pair of English word, Russian translation
     * @return Reference to this dictionary for chaining
     * @throw std::invalid_argument if word format is invalid
     */
    Dictionary& operator+=(const std::pair<std::string, std::string>& word_pair);

    /**
     * @brief Adds a word pair from a string in format "english:russian".
     * @param word_pair String containing colon-separated word pair
     * @return Reference to this dictionary for chaining
     * @throw std::invalid_argument if word format is invalid
     */
    Dictionary& operator+=(const std::string& word_pair);

    /**
     * @brief Adds a word pair from a C-string in format "english:russian".
     * @param word_pair C-string containing colon-separated word pair
     * @return Reference to this dictionary for chaining
     * @throw std::invalid_argument if word format is invalid
     */
    Dictionary& operator+=(const char* word_pair);
    
    /**
     * @brief Removes a word pair from the dictionary.
     * @param english_word English word to remove
     * @return Reference to this dictionary for chaining
     * @throw std::invalid_argument if word is not valid English
     * @throw std::out_of_range if word not found
     */
    Dictionary& operator-=(const std::string& english_word);

    /**
     * @brief Removes a word pair from the dictionary (C-string version).
     * @param english_word English word to remove
     * @return Reference to this dictionary for chaining
     * @throw std::invalid_argument if word is not valid English
     * @throw std::out_of_range if word not found
     */
    Dictionary& operator-=(const char* english_word);
    
    /**
     * @brief Accesses translation of an English word (const version).
     * @param english_word English word to look up
     * @return Const reference to Russian translation
     * @throw std::invalid_argument if word is not valid English
     * @throw std::out_of_range if word not found
     */
    const std::string& operator[](const std::string& english_word) const;

    /**
     * @brief Accesses or creates translation of an English word.
     * 
     * If word doesn't exist, creates an entry with empty translation.
     * 
     * @param english_word English word to look up or create
     * @return Reference to Russian translation
     * @throw std::invalid_argument if word is not valid English
     */
    std::string& operator[](const std::string& english_word);
    
    /**
     * @brief Equality comparison operator.
     * @param other Dictionary to compare with
     * @return true if dictionaries contain identical entries
     */
    bool operator==(const Dictionary& other) const {
        return container_ == other.container_;
    }

    /**
     * @brief Inequality comparison operator.
     * @param other Dictionary to compare with
     * @return true if dictionaries differ
     */
    bool operator!=(const Dictionary& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Output stream operator. Prints all word pairs in format "english:russian".
     * @param out_stream Output stream
     * @param dict Dictionary to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& out_stream, const Dictionary& dict);

    /**
     * @brief Input stream operator. Reads word pairs line by line.
     * 
     * Each line should be in format "english:russian". Invalid lines are skipped.
     * 
     * @param in_stream Input stream
     * @param dict Dictionary to populate
     * @return Reference to input stream
     */
    friend std::istream& operator>>(std::istream& in_stream, Dictionary& dict);
    
    /**
     * @brief Removes all entries from the dictionary.
     */
    void Clear() {
        container_.Clear();
    }

    /**
     * @brief Returns the number of word pairs in the dictionary.
     * @return Size of dictionary
     */
    size_t GetSize() const {
        return container_.GetSize();
    }

    /**
     * @brief Checks if dictionary is empty.
     * @return true if dictionary contains no entries
     */
    bool IsEmpty() const {
        return container_.IsEmpty();
    }

    /**
     * @brief Loads dictionary from a text file.
     * 
     * File should contain one word pair per line in format "english:russian".
     * Clears current dictionary before loading.
     * 
     * @param filename Path to file to load
     * @return true if file was successfully loaded, false if file couldn't be opened
     */
    bool LoadFromFile(const std::string& filename);
private:
    BinarySearchTree<std::string, std::string> container_;  ///< Internal storage of the pairs
};

#endif // DICTIONARY_H
