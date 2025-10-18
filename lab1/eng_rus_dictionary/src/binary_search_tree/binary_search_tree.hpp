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
    
    Node* CopyHelper(const Node* other) {
        if (!other) return nullptr;
        Node* copied = new Node;
        copied->key = other->key;
        copied->value = other->value;
        copied->left = CopyHelper(other->left);
        copied->right = CopyHelper(other->right);
        return copied;
    }
    bool EqualsHelper(const Node* node1, const Node* node2) const {
        if (!node1 && !node2) return true;
        if (!node1 || !node2) return false;
        return node1->key == node2->key &&
                node1->value == node2->value &&
                EqualsHelper(node1->left, node2->left) &&
                EqualsHelper(node1->right, node2->right);
    }
    bool InsertHelper(const KeyType& key, const ValueType& value);
    Node* FindNode(const KeyType& key) const;
    Node* EraseHelper(Node* node, const KeyType& key, bool& erased);
    std::ostream& InOrderHelper(std::ostream& out, const Node* node) const {
        if (node) {
            InOrderHelper(out, node->left);
            out << node->key << ":" << node->value;
            InOrderHelper(out, node->right);
        }
        return out;
    }
    void ClearHelper(Node* node) {
        if (node == nullptr) return;
        ClearHelper(node->left);
        ClearHelper(node->right);
        delete node;
    }
};

template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::InsertHelper(const KeyType& key, const ValueType& value){
    if (!root_) {
        root_ = new Node{key, value};
        ++size_;
        return true;
    }
    Node* current = root_;
    Node* parent = nullptr;
    while (current) {
        if (key == current->key) {
            current->value = value;
            return false;
        } else if (key < current->key) {
            parent = current;
            current = current->left;
        } else {
            parent = current;
            current = current->right;
        }
    }
    Node* added_node = new Node{key, value};
    if (key < parent->key) {
        parent->left = added_node;
    } else {
        parent->right = added_node;
    }
    ++size_;
    return true;
}
template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::FindNode(const KeyType& key) const {
    Node* current = root_;
    while (current) {
        if (key == current->key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}
template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::EraseHelper(Node* node, const KeyType& key, bool& erased) {
    if (node == nullptr) return nullptr;
    if (key < node->key) {
        node->left = EraseHelper(node->left, key, erased);
    } else if (key > node->key) {
        node->right = EraseHelper(node->right, key, erased);
    } else {
        erased = true;
        Node* swap_node = node->right;
        if (!node->left) {
            delete node;
            return swap_node;
        }
        if (!node->right) {
            swap_node = node->left;
            delete node;
            return swap_node;
        }
        Node* swap_node_parent = node;
        while (swap_node->left) {
            swap_node_parent = swap_node;
            swap_node = swap_node->left;
        }
        if (swap_node == node->right) {
            swap_node->left = node->left;
            delete node;
            return swap_node;
        }
        swap_node_parent->left = swap_node->right;
        swap_node->left = node->left;
        swap_node->right = node->right;
        delete node;
        return swap_node;
    }
    return node;
}

#endif // BINARY_SEARCH_TREE_HPP
