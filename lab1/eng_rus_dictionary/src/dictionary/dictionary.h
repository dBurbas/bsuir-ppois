//
//  dictionary.h
//  eng_rus_dictionary
//
//  Created by Dmitry Burbas on 17/10/2025.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstddef>
#include <iostream>
#include <string>
#include "../binary_search_tree/binary_search_tree.hpp"

class Dictionary {
public:
    Dictionary() = default;
    
    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    
    ~Dictionary() = default;
    
    Dictionary& operator+=(const std::pair<std::string, std::string>& word_pair);
    Dictionary& operator+=(const std::string& word_pair);
    Dictionary& operator+=(const char* word_pair);
    
    Dictionary& operator-=(const std::string& english_word);
    Dictionary& operator-=(const char* english_word);
    
    const std::string& operator[](const std::string& english_word) const;
    std::string& operator[](const std::string& english_word);
    
    bool operator==(const Dictionary& other) const {
        return container_ == other.container_;
    }
    bool operator!=(const Dictionary& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& out_stream, const Dictionary& dict);
    friend std::istream& operator>>(std::istream& in_stream, Dictionary& dict);
    
    void Clear() {
        container_.Clear();
    }
    size_t GetSize() const {
        return container_.GetSize();
    }
    bool IsEmpty() const {
        return container_.IsEmpty();
    }
    bool LoadFromFile(const std::string& filename);
private:
    BinarySearchTree<std::string, std::string> container_;
};

#endif // DICTIONARY_H
