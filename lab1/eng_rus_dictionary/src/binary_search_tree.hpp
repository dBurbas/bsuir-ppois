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
    BinarySearchTree(){};
    
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    
    ~BinarySearchTree();
    
    bool operator==(const BinarySearchTree& other) const;
    
    bool operator!=(const BinarySearchTree& other) const;
    
    bool Insert(const KeyType& key, const ValueType& value);
    
    friend std::ostream& operator<<(std::ostream& out_stream, const BinarySearchTree& tree);
    
    friend std::istream& operator>>(std::ostream& in_stream, BinarySearchTree& tree);
    
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
        Node* left_child = nullptr;
        Node* right_child = nullptr;
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
