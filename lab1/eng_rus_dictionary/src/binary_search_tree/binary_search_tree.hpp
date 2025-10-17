//
//  binary_search_tree.hpp
//  eng_rus_dictionary
//
//  Created by Dmitry Burbas on 10/10/2025.
//

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <iostream>

template <typename KeyType, typename ValueType>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    
    BinarySearchTree(const BinarySearchTree& other) : root_(CopyHelper(other.root_)), size_(other.size_) {}
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this;
        }
        ClearHelper(root_);
        root_ = CopyHelper(other.root_);
        size_ = other.size_;
        
        return *this;
    }
    ~BinarySearchTree() {
        ClearHelper(root_);
    }

    bool operator==(const BinarySearchTree& other) const {
        if (size_ != other.size_) return false;
        return EqualsHelper(root_, other.root_);
    }
    bool operator!=(const BinarySearchTree& other) const {
        return !(*this == other);
    }
    bool Insert(const KeyType& key, const ValueType& value) {
        return InsertHelper(key, value);
    }
    const ValueType* Find(const KeyType& key) const {
        Node* found = FindNode(key);
        if (found) return &found->value;
        return nullptr;
    }
    bool Erase(const KeyType& key) {
        bool erased = false;
        root_ = EraseHelper(root_, key, erased);
        if (erased) --size_;
        return erased;
    }
    void Clear() {
        ClearHelper(root_);
        root_ = nullptr;
        size_ = 0;
    }
    bool IsEmpty() const { return root_ == nullptr; }
    
    size_t GetSize() const { return size_; }
    
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root_ = nullptr;
    size_t size_ = 0;
    
    Node* CopyHelper(const Node* other);
    bool EqualsHelper(const Node* node1, const Node* node2) const;
    bool InsertHelper(const KeyType& key, const ValueType& value);
    Node* FindNode(const KeyType& key) const;
    Node* EraseHelper(Node* node, const KeyType& key, bool& erased);
    std::ostream& InOrderHelper(std::ostream& out, const Node* node) const;
    void ClearHelper(Node* node);
};

#endif // BINARY_SEARCH_TREE_HPP
