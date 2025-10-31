/**
 * @mainpage Cantor Set Documentation
 *
 * @section intro_sec Introduction
 *
 * This project implements a Cantor Set class for mathematical set operations.
 * The implementation supports nested sets as elements and provides complete
 * functionality for set theory operations.
 *
 * @section features_sec Key Features
 * - Support for atomic elements (single alphanumeric characters)
 * - Support for nested sets as elements
 * - Set operations: union, intersection, difference
 * - Power set computation using bitmask algorithm
 * - String-based representation and parsing
 * - Automatic normalization and sorting of elements
 *
 * @section usage_sec Usage Example
 *
 * @code
 * CantorSet set1("{a, b, c}");
 * CantorSet set2("{b, c, d}");
 *
 * // Union
 * CantorSet union_set = set1 + set2;  // {a, b, c, d}
 * @endcode
 *
 * @section classes_sec Main Classes
 * - CantorSet: Main class implementing set operations
 *
 * @author Dmitry Burbas
 * @date October 2025
 */

/**
 * @file cantor_set.h
 * @brief Cantor set header file with nested sets support
 * @author Dmitry Burbas
 * @date 19/10/2025
 */
#ifndef CANTOR_SET_H
#define CANTOR_SET_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Represents a Cantor set that can contain atomic elements and nested
 * sets The CantorSet class provides a complete implementation of mathematical
 * set operations including union, intersection, and difference. It supports
 * nested sets as elements.
 */
class CantorSet {
public:
  /**
   * @brief Default constructor
   * Creates an empty set with no elements
   */
  CantorSet() = default;

  /**
   * @brief Copy constructor
   * Performs deep copy of all elements from another set
   * @param other The set to copy from
   */
  CantorSet(const CantorSet &other) : elements_(other.elements_) {}

  /**
   * @brief Constructs set from string representation
   *
   * Parses string in format "{a, {b, c}, d}" and creates corresponding set.
   * The string must have valid syntax with balanced braces.
   *
   * @param set String representation of the set
   * @throw std::invalid_argument if string has invalid syntax
   *
   * @code
   * CantorSet s1("{a, b, c}");
   * CantorSet s2("{a, {b, c}, d}");  // nested set
   * @endcode
   */
  explicit CantorSet(const std::string &set);

  /**
   * @brief Constructs set from C-string representation
   *
   * Parses string in format "{a, {b, c}, d}" and creates corresponding set.
   * The string must have valid syntax with balanced braces.
   *
   * @param set C-string representation of the set
   * @throw std::invalid_argument if string has invalid syntax
   */
  explicit CantorSet(const char *set);

  /**
   * @brief Default destructor
   * Automatically frees all resources. Uses default implementation
   * as std::vector handles memory management.
   */
  ~CantorSet() = default;

  /**
   * @brief Assignment operator
   * Makes deep copy with proper cleanup of existing elements.
   * Handles self-assignment correctly.
   *
   * @param other The set to assign from
   * @return Reference to this set
   */
  CantorSet &operator=(const CantorSet &other);

  /**
   * @brief Equality comparison operator
   *
   * Two sets are equal if they contain exactly the same elements.
   *
   * @param other Set to compare with
   * @return true if sets are equal, false otherwise
   */
  bool operator==(const CantorSet &other) const {
    return elements_ == other.elements_;
  }

  /**
   * @brief Inequality comparison operator.
   * @param other Set to compare with
   * @return true if sets differ, false otherwise
   */
  bool operator!=(const CantorSet &other) const { return !(*this == other); }

  /**
   * @brief Compares sets for equality
   *
   * Convenience method that delegates to operator==.
   *
   * @param other Set to compare
   * @return true if all elements of sets are equal, false otherwise
   */
  bool Equals(const CantorSet &other) const { return *this == other; }

  /**
   * @brief Converts this set to string representation
   *
   * @return String representation in format "{a, b, c}"
   * @code
   * CantorSet s("{a, b}");
   * std::cout << s.ToString();  // Output: "{a, b}"
   * @endcode
   */
  std::string ToString() const;

  /**
   * @brief Checks if set is empty
   * @return true if set has no elements, false otherwise
   */
  bool IsEmpty() const { return elements_.empty(); }

  /**
   *@brief Adds element to the set
   *
   * Element can be either single alphanumeric character
   * or a nested set. If element already exists, set is not modified.
   *
   * @param elem_to_add String representation of element to add
   * @return true if element was added, false if it already exists or is invalid
   *
   * @code
   * CantorSet s;
   * s.AddElement("a");           // atomic element
   * s.AddElement("{b, c}");      // nested set
   * @endcode
   */
  bool AddElement(const std::string &elem_to_add);

  /**
   *@brief Removes element from the set
   *
   * @param elem_to_erase String representation of element to erase
   * @return true if element was found and removed, false otherwise
   */
  bool EraseElement(const std::string &elem_to_erase);

  /**
   * @brief Checks if element belongs to the set
   *
   * Convenience method that delegates to operator[].
   *
   * @param elem Element to check
   * @return true if element is in the set, false otherwise
   */
  bool Contains(const std::string &elem);

  /**
   * @brief Returns the number of elements in the set
   * @return Number of elements
   */
  size_t Cardinality() const { return elements_.size(); }

  /**
   * @brief Checks if element belongs to the set using [] operator
   *
   * Uses binary search for efficient lookup (O(log n)).
   *
   * @param elem Element to check
   * @return true if element is in the set, false otherwise
   *
   */
  bool operator[](const std::string &elem) const;

  /**
   * @brief Union operator
   *
   * Returns new set containing all elements from both sets.
   *
   * @param other Second set for union
   * @return New set representing union of this and other
   *
   * @code
   * CantorSet s1("{a, b}");
   * CantorSet s2("{b, c}");
   * CantorSet result = s1 + s2;  // {a, b, c}
   * @endcode
   */
  CantorSet operator+(const CantorSet &other) const;

  /**
   * @brief Union assignment operator
   *
   * Adds all elements from other set that are not already present.
   *
   * @param other Set to unite with
   * @return Reference to this set
   */
  CantorSet &operator+=(const CantorSet &other);

  /**
   * @brief Intersection operator
   *
   * Returns new set containing only elements present in both sets.
   *
   * @param other Second set for intersection
   * @return New set representing intersection
   *
   * @code
   * CantorSet s1("{a, b, c}");
   * CantorSet s2("{b, c, d}");
   * CantorSet result = s1 * s2;  // {b, c}
   * @endcode
   */
  CantorSet operator*(const CantorSet &other) const;

  /**
   * @brief Intersection assignment operator
   *
   * Keeps only elements that are present in both sets.
   *
   * @param other Set to intersect with
   * @return Reference to this set
   */
  CantorSet &operator*=(const CantorSet &other);

  /**
   * @brief Difference operator
   *
   * Returns new set with elements from this set not present in other.
   *
   * @param other Set to subtract
   * @return New set representing difference
   *
   * @code
   * CantorSet s1("{a, b, c}");
   * CantorSet s2("{b, c, d}");
   * CantorSet result = s1 - s2;  // {a}
   * @endcode
   */
  CantorSet operator-(const CantorSet &other) const;

  /**
   * @brief Difference assignment operator
   *
   * Removes all elements that are present in the other set.
   *
   * @param other Set to subtract
   * @return Reference to this set
   */
  CantorSet &operator-=(const CantorSet &other);

  /**
   * @brief Computes power set
   * For a set with n elements, creates set of all subsets with 2^n elements,
   * containing all possible subsets, including empty set and the set itself
   * @throw std::length\_error if set size > 20 (to prevent memory overflow)
   * @return Power set
   *
   * @code
   * CantorSet s("{a, b}");
   * CantorSet power = s.PowerSet();  // {{}, {a}, {b}, {a, b}}
   * @endcode
   */
  CantorSet PowerSet() const { return PowerSetBitMaskHelper(); }

  /**
   * @brief Stream output operator
   *
   * Outputs set in format "{a, b, c}" to output stream.
   *
   * @param out_stream Output stream
   * @param set Set to output
   * @return Reference to the output stream for chaining
   *
   * @code
   * CantorSet s("{a, b, c}");
   * std::cout << s << std::endl;  // Output: {a, b, c}
   * @endcode
   */
  friend std::ostream &operator<<(std::ostream &out_stream,
                                  const CantorSet &set);

  /**
   * @brief Stream input operator
   *
   * Reads set from input stream in format "{a, b, c}".
   * Reads until end of line.
   *
   * @param in_stream Input stream
   * @param set Set to read into
   * @return Reference to the input stream for chaining
   * @throw std::invalid_argument if input has invalid syntax
   *
   * @code
   * CantorSet s;
   * std::cin >> s;  // User enters: {a, b, c}
   * @endcode
   */
  friend std::istream &operator>>(std::istream &in_stream, CantorSet &set);

  /**
   * @brief Removes all elements from the set
   * Frees memory for all elements and makes set empty
   */
  void Clear() { elements_.clear(); }

private:
  std::vector<std::string>
      elements_; ///< Container storing string representation of elements

  /**
   * @brief Checks if string represents a set
   *
   * Determines if string has set syntax (begins with '{' and ends with '}').
   * Ignores whitespace.
   *
   * @param str String to check
   * @return true if string begins with '{' and ends with '}', false otherwise
   */
  bool IsSet(const std::string &str) const;

  /**
   * @brief Validates string has correct set syntax
   *
   * Checks for balanced braces, valid characters, proper comma placement,
   * and correct element syntax.
   *
   * @param str String to validate
   * @throw std::invalid\_argument if syntax is incorrect with descriptive
   * message
   */
  void ValidateString(const std::string &str) const;

  /**
   * @brief Normalizes string by removing extra whitespace
   *
   * Removes all whitespace and ensures consistent formatting with
   * single space after each comma.
   *
   * @param str String to normalize
   * @return Normalized string without extra whitespace
   *
   * @code
   * // Input:  "{a,  b ,   c}"
   * // Output: "{a, b, c}"
   * @endcode
   */
  std::string NormalizeString(const std::string &str) const;

  /**
   * @brief Parses elements from string representation
   *
   * Extracts individual elements from set string, handling nested sets
   * by tracking brace nesting level.
   *
   * @param str String to parse in format "{a, b, {c, d}}"
   * @return Vector of string representations of elements
   * @throw std::invalid\_argument if string has invalid syntax
   */
  std::vector<std::string> ParseElements(const std::string &str) const;

  /**
   * @brief Sorts elements by length then lexicographically
   *
   * Uses custom comparator: shorter strings come first,
   * equal length strings are sorted alphabetically.
   * Required for binary_search correctness.
   *
   * @param elements Vector to sort (modified in place)
   */
  void SortElements(std::vector<std::string> &elements) const;

  /**
   * @brief Removes consecutive duplicate elements
   *
   * Uses std::unique and vector erase. Assumes elements are already sorted.
   *
   * @param elements Vector to deduplicate (modified in place)
   */
  void RemoveDuplicates(std::vector<std::string> &elements) const;

  /**
   * @brief Normalizes all nested sets in element vector
   *
   * Recursively parses, normalizes, sorts and deduplicates nested sets
   * to ensure canonical representation.
   *
   * @param elements Vector of elements to normalize (modified in place)
   */
  void NormalizeNestedSets(std::vector<std::string> &elements) const;

  /**
   * @brief Helper function to convert vector of elements to string
   *
   * @param set Vector of element strings
   * @return String representation in format "{a, b, c}"
   */
  std::string ToStringHelper(const std::vector<std::string> &set) const;

  /**
   * @brief Helper function to compute power set using bitmask algorithm
   *
   * Uses bitmasking to generate all 2^n subsets efficiently.
   * Each bit position represents inclusion/exclusion of an element.
   *
   * @return Power set of this set
   * @throw std::length_error if set size > 20
   */
  CantorSet PowerSetBitMaskHelper() const;
};

#endif // CANTOR_SET_H
