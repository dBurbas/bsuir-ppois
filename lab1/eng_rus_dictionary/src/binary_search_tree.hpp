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

    
    const ValueType* Find(const KeyType& key) const;
    
    bool Erase(const KeyType& key);
    
    void Clear();
    
    void PrintInOrder() const;
    
    bool IsEmpty() const;
    
    size_t GetSize() const;
    
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root_;
    size_t size_;
    
    void ClearHelper(Node* node);
    
    Node* CopyHelper(const Node* node);
    
    void PrintInOrderHelper(const Node* node) const;
    
    Node* EraseHelper(Node* node, const KeyType& key, bool& erased);
    
    bool EqualsHelper(const Node* node1, const Node* node2) const;
};

#endif // BINARY_SEARCH_TREE_HPP
