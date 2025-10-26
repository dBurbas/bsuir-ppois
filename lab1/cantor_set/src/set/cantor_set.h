/**
 * @file cantor_set.h
 * @brief Cantor set header file with nested sets support
 * @author Dmitry Burbas
 * @date 19/10/2025
 */
#ifndef CANTOR_SET_H
#define CANTOR_SET_H

#include <iostream>
#include <vector>
#include <string>

class CantorSet {
public:
    
    CantorSet() = default;
    
    CantorSet(const CantorSet& other): elements_(other.elements_) {}
    
    explicit CantorSet(const std::string& set);
    
    explicit CantorSet(const char* set);
    
    ~CantorSet() = default;
    
    CantorSet& operator=(const CantorSet& other);
    
    bool operator==(const CantorSet& other) const {
        return elements_ == other.elements_;
    }

    bool operator!=(const CantorSet& other) const {
        return !(*this == other);
    }
    
    bool Equals(const CantorSet& other) const {
        return *this == other;
    }
    
    std::string ToString() const;
    
    bool IsEmpty() const { return elements_.empty(); }
    
    bool AddElement(const std::string& elem_to_add);
    
    bool EraseElement(const std::string& elem_to_erase);
    
    bool Contains(const std::string& elem);
    
    size_t Cardinality() const { return elements_.size(); }
    
    bool operator[](const std::string& elem) const;
    
    CantorSet operator+(const CantorSet& other) const;
    
    CantorSet& operator+=(const CantorSet& other);
    
    CantorSet operator*(const CantorSet& other) const;
    
    CantorSet& operator*=(const CantorSet& other);
    
    CantorSet operator-(const CantorSet& other) const;
    
    CantorSet& operator-=(const CantorSet& other);
    
    CantorSet PowerSet() const { return PowerSetBitMaskHelper(); }
    
    friend std::ostream& operator<<(std::ostream& out_stream, const CantorSet& set);
    
    friend std::istream& operator>>(std::istream& in_stream, CantorSet& set);
    
    void Clear() { elements_.clear(); }
private:
    std::vector<std::string> elements_; ///< Container storing string representation of elements
    
    bool IsSet(const std::string& str) const;
    
    void ValidateString(const std::string& str) const;
    
    std::string NormalizeString(const std::string& str) const;
    
    std::vector<std::string> ParseElements(const std::string& str) const;
    
    void SortElements(std::vector<std::string>& elements) const;
    
    void RemoveDuplicates(std::vector<std::string>& elements) const;
    
    void NormalizeNestedSets(std::vector<std::string>& elements) const;
    
    std::string ToStringHelper(const std::vector<std::string>& set) const;
    
    CantorSet PowerSetBitMaskHelper() const;
};

#endif // CANTOR_SET_H
