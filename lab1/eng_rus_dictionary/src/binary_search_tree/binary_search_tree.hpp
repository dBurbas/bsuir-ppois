/**
 * @file binary_search_tree.hpp
 * @brief Binary Search Tree template implementation
 * @author Dmitry Burbas
 * @date 10/10/2025
 */

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <iostream>

/**
 * @brief Template class implementing a binary search tree data structure.
 *
 * This class provides a key-value storage with O(log n) average time complexity
 * for insertion, deletion, and lookup operations. Keys must support comparison
 * operators (< and ==).
 *
 * @tparam KeyType Type of keys stored in the tree
 * @tparam ValueType Type of values associated with keys and stored in the tree
 */
template <typename KeyType, typename ValueType>
class BinarySearchTree {
public:
  /**
   * @brief Default constructor. Creates an empty tree
   */
  BinarySearchTree() = default;

  /**
   * @brief Copy constructor. Performs deep copy of another tree.
   * @param other Tree to copy from
   */
  BinarySearchTree(const BinarySearchTree &other)
      : root_(CopyHelper(other.root_)), size_(other.size_) {}

  /**
   * @brief Copy assignment operator. Replaces current tree with a copy of
   * another.
   * @param other Tree to copy from
   * @return Reference to this tree
   */
  BinarySearchTree &operator=(const BinarySearchTree &other) {
    if (this == &other) {
      return *this;
    }
    Node *copied = CopyHelper(other.root_);
    ClearHelper(root_);
    root_ = copied;
    size_ = other.size_;
    return *this;
  }

  /**
   * @brief Destructor. Deallocates all nodes in the tree.
   */
  ~BinarySearchTree() { ClearHelper(root_); }

  /**
   * @brief Access or insert element by key (non-const version).
   *
   * If key exists, returns reference to its value. If key doesn't exist,
   * creates new entry with default-constructed value.
   *
   * @param key Key to find, change or insert
   * @return Reference to the value associated with the key
   */
  ValueType &operator[](const KeyType &key) {
    Node *node = FindNode(key);
    if (!node) {
      ValueType default_value{};
      node = InsertHelper(key, default_value);
    }
    return node->value;
  }

  /**
   * @brief Access element by key (const version).
   *
   * @param key Key to find
   * @return Const reference to the value
   * @throw std::out_of_range if key not found
   */
  const ValueType &operator[](const KeyType &key) const {
    Node *found = FindNode(key);
    if (!found) {
      throw std::out_of_range("Key not found");
    }
    return found->value;
  }

  /**
   * @brief Equality comparison operator.
   *
   * Two trees are equal if they have the same structure and all
   * corresponding nodes have equal keys and values.
   *
   * @param other Tree to compare with
   * @return true if trees are equal, false otherwise
   */
  bool operator==(const BinarySearchTree &other) const {
    if (size_ != other.size_)
      return false;
    return EqualsHelper(root_, other.root_);
  }

  /**
   * @brief Inequality comparison operator.
   * @param other Tree to compare with
   * @return true if trees are not equal, false otherwise
   */
  bool operator!=(const BinarySearchTree &other) const {
    return !(*this == other);
  }

  /**
   * @brief Inserts a key-value pair into the tree.
   *
   * If key already exists, updates its value. Otherwise creates new node.
   *
   * @param key Key to insert
   * @param value Value to associate with the key
   * @return true if new element was inserted, false if existing was updated
   */
  bool Insert(const KeyType &key, const ValueType &value) {
    size_t old_size = size_;
    InsertHelper(key, value);
    return size_ > old_size;
  }

  /**
   * @brief Searches for a key in the tree.
   * @param key Key to find
   * @return Pointer to value if found, nullptr otherwise
   */
  const ValueType *Find(const KeyType &key) const {
    Node *found = FindNode(key);
    if (found)
      return &found->value;
    return nullptr;
  }

  /**
   * @brief Removes element with specified key from the tree.
   * @param key Key to remove
   * @return true if element was removed, false if key not found
   */
  bool Erase(const KeyType &key) {
    bool erased = false;
    root_ = EraseHelper(root_, key, erased);
    if (erased)
      --size_;
    return erased;
  }

  /**
   * @brief Removes all elements from the tree.
   */
  void Clear() {
    ClearHelper(root_);
    root_ = nullptr;
    size_ = 0;
  }

  /**
   * @brief Checks if the tree is empty.
   * @return true if tree contains no elements, false otherwise
   */
  bool IsEmpty() const { return root_ == nullptr; }

  /**
   * @brief Returns the number of elements in the tree.
   * @return Size of the tree
   */
  size_t GetSize() const { return size_; }

  /**
   * @brief Performs in-order traversal of the tree.
   *
   * Calls the provided function for each node in ascending key order.
   *
   * @tparam Func Function type with signature void(const KeyType&, const
   * ValueType&)
   * @param func Callback function to apply to each node
   */
  template <typename Func> void InOrderTraversal(Func func) const {
    InOrderHelper(root_, func);
  }

private:
  /**
   * @brief Internal node structure.
   */
  struct Node {
    KeyType key;           ///< Node key
    ValueType value;       ///< Node value
    Node *left = nullptr;  ///< Pointer to left child
    Node *right = nullptr; ///< Pointer to right child
  };
  Node *root_ = nullptr; ///< Root node of the tree
  size_t size_ = 0;      ///< Number of elements in the tree

  /**
   * @brief Recursively copies a subtree
   * @param other root of the subtree to copy
   * @return Pointer to the copied subtree root
   */
  Node *CopyHelper(const Node *other) {
    if (!other)
      return nullptr;
    Node *copied = new Node;
    copied->key = other->key;
    copied->value = other->value;
    copied->left = CopyHelper(other->left);
    copied->right = CopyHelper(other->right);
    return copied;
  }

  /**
   * @brief Recursively compares two subtrees for equality.
   * @param node1 Root of first subtree
   * @param node2 Root of second subtree
   * @return true if subtrees are equal, false otherwise
   */
  bool EqualsHelper(const Node *node1, const Node *node2) const {
    if (!node1 && !node2)
      return true;
    if (!node1 || !node2)
      return false;
    return node1->key == node2->key && node1->value == node2->value &&
           EqualsHelper(node1->left, node2->left) &&
           EqualsHelper(node1->right, node2->right);
  }

  /**
   * @brief Helper function to insert a node.
   * @param key Key to insert
   * @param value Value to insert
   * @return Pointer to inserted or updated node
   */
  Node *InsertHelper(const KeyType &key, const ValueType &value);

  /**
   * @brief Helper function to find a node by key.
   * @param key Key to search for
   * @return Pointer to found node or nullptr
   */
  Node *FindNode(const KeyType &key) const;

  /**
   * @brief Helper function to recursively erase a node.
   * @param node Current node in recursion
   * @param key Key to erase
   * @param erased Output parameter indicating if erasure occurred
   * @return Pointer to new root of subtree after deletion
   */
  Node *EraseHelper(Node *node, const KeyType &key, bool &erased);

  /**
   * @brief Helper function for in-order traversal.
   * @tparam Func Function type
   * @param node Current node
   * @param func Callback function
   */
  template <typename Func> void InOrderHelper(Node *node, Func func) const {
    if (node) {
      InOrderHelper(node->left, func);
      func(node->key, node->value);
      InOrderHelper(node->right, func);
    }
  }

  /**
   * @brief Recursively deallocates a subtree.
   * @param node Root of subtree to clear
   */
  void ClearHelper(Node *node) {
    if (node == nullptr)
      return;
    ClearHelper(node->left);
    ClearHelper(node->right);
    delete node;
  }
};

// Template method implementations

template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node *
BinarySearchTree<KeyType, ValueType>::InsertHelper(const KeyType &key,
                                                   const ValueType &value) {
  if (!root_) {
    root_ = new Node{key, value};
    ++size_;
    return root_;
  }
  Node *current = root_;
  Node *parent = nullptr;
  while (current) {
    if (key == current->key) {
      current->value = value;
      return current;
    } else if (key < current->key) {
      parent = current;
      current = current->left;
    } else {
      parent = current;
      current = current->right;
    }
  }
  Node *added_node = new Node{key, value};
  if (key < parent->key) {
    parent->left = added_node;
  } else {
    parent->right = added_node;
  }
  ++size_;
  return added_node;
}
template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node *
BinarySearchTree<KeyType, ValueType>::FindNode(const KeyType &key) const {
  Node *current = root_;
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
typename BinarySearchTree<KeyType, ValueType>::Node *
BinarySearchTree<KeyType, ValueType>::EraseHelper(Node *node,
                                                  const KeyType &key,
                                                  bool &erased) {
  if (node == nullptr)
    return nullptr;
  if (key < node->key) {
    node->left = EraseHelper(node->left, key, erased);
  } else if (key > node->key) {
    node->right = EraseHelper(node->right, key, erased);
  } else {
    erased = true;
    Node *swap_node = node->right;
    if (!node->left) {
      delete node;
      return swap_node;
    }
    if (!node->right) {
      swap_node = node->left;
      delete node;
      return swap_node;
    }
    Node *swap_node_parent = node;
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
