/**
 * @file cantor_set.cc
 * @brief Cantor set implementation with nested sets support
 * @author Dmitry Burbas
 * @date 19/10/2025
 */
#include "cantor_set.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <stack>

CantorSet::CantorSet(const std::string& set) {
    elements_ = ParseElements(set);
    NormalizeNestedSets(elements_);
    SortElements(elements_);
    RemoveDuplicates(elements_);
}

CantorSet::CantorSet(const char* set) {
    elements_ = ParseElements(std::string(set));
    NormalizeNestedSets(elements_);
    SortElements(elements_);
    RemoveDuplicates(elements_);
}
CantorSet& CantorSet::operator=(const CantorSet& other) {
    if (this != &other) {
        elements_ = other.elements_;
    }
    return *this;
}

std::string CantorSet::ToString() const {
    return ToStringHelper(elements_);
}

bool CantorSet::AddElement(const std::string& elem_to_add) {
    std::string normalized;
    if (IsSet(elem_to_add)) {
        try {
            CantorSet temp_set(elem_to_add);
            normalized = temp_set.ToString();
        } catch (const std::invalid_argument&) {
            return false;
        }
    }else {
        normalized = NormalizeString(elem_to_add);
        if (normalized.size()!=1 || !std::isalnum(normalized[0])) {
            return false;
        }
    }
    auto it = std::find(elements_.begin(), elements_.end(), normalized);
    if (it == elements_.end()){
        elements_.push_back(normalized);
        SortElements(elements_);
        return true;
    }
    return false;
}

bool CantorSet::EraseElement(const std::string& elem_to_erase) {
    std::string normalized;
    if (IsSet(elem_to_erase)) {
        try {
            CantorSet temp_set(elem_to_erase);
            normalized = temp_set.ToString();
        } catch (const std::invalid_argument&) {
            return false;
        }
    } else {
        normalized = NormalizeString(elem_to_erase);
        if (normalized.size()!=1 || !std::isalnum(normalized[0])) {
            return false;
        }
    }
    auto it = std::find(elements_.begin(), elements_.end(), normalized);
    if (it != elements_.end() && *it == normalized){
        elements_.erase(it);
        return true;
    }
    return false;
}

bool CantorSet::Contains(const std::string& elem) {
    return (*this)[elem];
}
bool CantorSet::operator[](const std::string& elem) const {
    if (IsSet(elem)) {
        try {
            CantorSet temp_set(elem);
            return std::binary_search(elements_.begin(), elements_.end(), temp_set.ToString(),[] (const std::string& str1,const std::string& str2) {
                return (str1.size() < str2.size()) ||
                (str1.size() == str2.size() && str1 < str2);});
        } catch (const std::invalid_argument&) {
            return false;
        }
    } else {
        std::string normalized = NormalizeString(elem);
        if (normalized.size()!=1 || !std::isalnum(normalized[0])) {
            return false;
        }
        return std::binary_search(elements_.begin(), elements_.end(), normalized,
                                  [] (const std::string& str1,const std::string& str2) {
            return (str1.size() < str2.size()) ||
            (str1.size() == str2.size() && str1 < str2);});
    }
}
CantorSet CantorSet::operator+(const CantorSet& other) const {
    CantorSet union_set(*this);
    union_set += other;
    return union_set;
}

CantorSet& CantorSet::operator+=(const CantorSet& other) {
    for (const auto& elem : other.elements_) {
        AddElement(elem);
    }
    return *this;
}

CantorSet CantorSet::operator*(const CantorSet& other) const {
    CantorSet intersection_set(*this);
    intersection_set *= other;
    return intersection_set;
}

CantorSet& CantorSet::operator*=(const CantorSet& other) {
    std::vector<std::string> elements_to_keep;
    for (const auto& elem : elements_) {
        if (other[elem]) elements_to_keep.push_back(elem);
    }
    elements_ = elements_to_keep;
    return *this;
}

CantorSet CantorSet::operator-(const CantorSet& other) const {
    CantorSet difference_set(*this);
    difference_set -= other;
    return difference_set;
}

CantorSet& CantorSet::operator-=(const CantorSet& other) {
    std::vector<std::string> elements_to_keep;
    for (const auto& elem : elements_) {
        if (!other[elem]) elements_to_keep.push_back(elem);
    }
    elements_ = elements_to_keep;
    return *this;
}
std::ostream& operator<<(std::ostream& out_stream, const CantorSet& set) {
    out_stream << set.ToString();
    return out_stream;
}

std::istream& operator>>(std::istream& in_stream, CantorSet& set) {
    std::string input;
    std::getline(in_stream, input);
    set = CantorSet(input);
    return in_stream;
}
CantorSet CantorSet::PowerSetBitMaskHelper() const {
    size_t set_size = elements_.size();
    if (set_size > 20) throw std::length_error("Set size is too big: >20");
    CantorSet power_set;
    size_t power_set_size = 1 << set_size; // 2^n
    for (size_t mask = 0; mask < power_set_size; mask++) {
        std::vector<std::string> subset;
        
        for (size_t element_index = 0; element_index < set_size; element_index++) {
            if (mask & (1 << element_index)) {
                subset.push_back(elements_[element_index]);
            }
        }
        std::string subset_str = ToStringHelper(subset);
        power_set.elements_.push_back(subset_str);
    }
    SortElements(power_set.elements_);
    RemoveDuplicates(power_set.elements_);
    return power_set;
}

bool CantorSet::IsSet(const std::string& str) const {
    if (str.empty()) return false;
    
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return false;
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str[first] == '{' && str[last] == '}';
}

void CantorSet::ValidateString(const std::string& str) const {
    if (str.empty()) {
        throw std::invalid_argument("Argument must not be empty");
    }
    if (!IsSet(str)) {
        throw std::invalid_argument("Argument must be set");
    }
    std::stack<char> stack_of_brackets;
    for (size_t i=0; i<str.size(); i++) {
        if (std::isspace(str[i])) {
            continue;
        } else if (str[i] == '{') {
            stack_of_brackets.push('{');
        } else if (str[i] == '}') {
            if (stack_of_brackets.empty()) {
                throw std::invalid_argument("Invalid set nesting");
            }
            if (i >= 2 && str[i-2] == ',') {
                throw std::invalid_argument("Extraneous: \",\" ");
            }
            stack_of_brackets.pop();
        } else if ( str[i] != ',' && !std::isalnum(str[i]) && !std::isspace(str[i]) ) {
            throw std::invalid_argument("Invalid symbols");
        } else if (i > 0 && std::isalpha(str[i]) && std::isalpha(str[i-1])) {
            throw std::invalid_argument("Invalid element syntax");
        }
    }
    if (!stack_of_brackets.empty()) {
        throw std::invalid_argument("Invalid set nesting");
    }
    
}

std::string CantorSet::NormalizeString(const std::string& str) const {
    std::string normalized;
    for (size_t i = 0; i < str.size(); i++) {
        if (std::isspace(str[i])) {
            continue;
        }
        if (str[i] ==',') {
            if (normalized.size() > 2 && normalized[normalized.size()-2] == ',') continue;
            normalized += ", ";
        } else {
            normalized += str[i];
        }
    }
    return normalized;
}

std::vector<std::string> CantorSet::ParseElements(const std::string& str) const {
    std::string normalized = NormalizeString(str);
    ValidateString(normalized);
    
    std::string content = normalized.substr(1, normalized.size()-2);
    std::vector<std::string> parsed;
    std::string element;
    size_t level = 0;
    for (size_t i = 0; i<content.size(); i++) {
        char symbol = content[i];
        element += symbol;
        if (symbol == '{') level++;
        if (symbol == '}') level--;
        
        if (symbol == ',' && level == 0) {
            element.pop_back();
            if (!element.empty()) {
                parsed.push_back(element);
                element.clear();
            }
            i++;
        }
    }
    if (!element.empty()) {
        parsed.push_back(element);
    }
    
    return parsed;
}
void CantorSet::NormalizeNestedSets(std::vector<std::string>& elements) const {
    for (size_t i=0; i<elements.size(); i++) {
        if (IsSet(elements[i])) {
            std::vector<std::string> temp = ParseElements(elements[i]);
            NormalizeNestedSets(temp);
            SortElements(temp);
            RemoveDuplicates(temp);
            elements[i] = ToStringHelper(temp);
        }
    }
}
void CantorSet::SortElements(std::vector<std::string>& elements) const {
    std::sort(elements.begin(), elements.end(), [] (const std::string& str1,
                                                   const std::string& str2) {
        return (str1.size() < str2.size()) ||
                (str1.size() == str2.size() && str1 < str2);
    });
}
void CantorSet::RemoveDuplicates(std::vector<std::string>& elements) const{
    auto new_end = std::unique(elements.begin(), elements.end());
    elements.erase(new_end,elements.end());
}

std::string CantorSet::ToStringHelper(const std::vector<std::string>& set) const {
    if (set.empty()) return "{}";
    std::string result = "{";
    for (size_t i = 0; i < set.size(); i++) {
        result += set[i];
        if (i != set.size() - 1) result += ", ";
    }
    result += "}";
    return result;
}

