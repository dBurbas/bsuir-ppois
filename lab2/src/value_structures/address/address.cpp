//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "address.h"

#include <regex>

#include "../../exceptions/components_exceptions.h"
#include "../../utility_functions/utility_functions.h"

Address::Address(const std::string& country, const std::string& oblast,
                 const std::string& city, const std::string& street,
                 const int house, const int apartment,
                 const std::string& postal_code) {
  const std::string normalized_country = NormalizeCountry(country);
  ValidateCountry(normalized_country);
  const std::string normalized_oblast = NormalizeOblast(oblast);
  ValidateOblast(normalized_oblast);
  const std::string normalized_city = NormalizeCity(city);
  ValidateCity(normalized_city);
  const std::string normalized_street = NormalizeStreet(street);
  ValidateStreet(normalized_street);
  const std::string normalized_postal = NormalizePostalCode(postal_code);
  ValidatePostalCode(normalized_country, normalized_postal);

  ValidateHouse(house);
  ValidateApartment(apartment);
  country_ = normalized_country;
  oblast_ = normalized_oblast;
  city_ = normalized_city;
  street_ = normalized_street;
  house_ = house;
  postal_code_ = normalized_postal;
  apartment_ = apartment;
}

void Address::SetPostalCode(const std::string& postal_code) {
  const std::string normalized = NormalizePostalCode(postal_code);
  ValidatePostalCode(country_, normalized);
  postal_code_ = normalized;
}

void Address::SetCountry(const std::string& country) {
  country_ = NormalizeCountry(country);
}

void Address::SetOblast(const std::string& oblast) {
  const std::string normalized = NormalizeOblast(oblast);
  ValidateOblast(normalized);
  oblast_ = normalized;
}

void Address::SetCity(const std::string& city) {
  const std::string normalized = NormalizeCity(city);
  ValidateCity(normalized);
  city_ = normalized;
}

void Address::SetStreet(const std::string& street) {
  const std::string normalized = NormalizeStreet(street);
  ValidateStreet(normalized);
  street_ = normalized;
}

void Address::SetHouse(const int house) {
  ValidateHouse(house);
  house_ = house;
}

void Address::SetApartment(const int apartment) {
  ValidateApartment(apartment);
  apartment_ = apartment;
}
std::string Address::ToString() const {
  std::string result;
  result += country_;
  result += (result.empty() ? "" : ";") + oblast_;
  result += (result.empty() ? "" : ";") + city_;
  result += (result.empty() ? "" : ";") + street_;
  result += (result.empty() ? "" : ";") + std::to_string(house_);
  if (apartment_ > 0) {
    result += ";" + std::to_string(apartment_);
  }
  if (!postal_code_.empty()) {
    result += ";" + postal_code_;
  }
  return result;
}
std::string Address::GetPostalCode() const {
  if (postal_code_.empty())
    throw AddressException("No postal code in this address.");
  return postal_code_;
}
std::string Address::GetCountry() const { return country_; }
std::string Address::GetOblast() const { return oblast_; }
std::string Address::GetCity() const { return city_; }
std::string Address::GetStreet() const { return street_; }
int Address::GetHouseNumber() const { return house_; }
int Address::GetApartmentNumber() const {
  if (apartment_ == 0) throw AddressException("No apartment in this address.");
  return apartment_;
}
const Address& Address::ParseFromString(const std::string& full_address) {
  std::vector<std::string> parts = Utility::Split(full_address, ';');
  if (parts.size() < 5) {
    throw AddressException(
        "Address error: not enough parts in string. Expected format: "
        "Country;Oblast;City;Street;House;(optional->)Apartment;Postal Code");
  }
  const std::string& country = parts[0];
  const std::string& oblast = parts[1];
  const std::string& city = parts[2];
  const std::string& street = parts[3];
  const int house = std::stoi(parts[4]);
  const int apartment = parts.size() > 5 ? std::stoi(parts[5]) : 0;
  const std::string& postal_code = parts.size() > 6 ? parts[6] : "";
  return Address(country, oblast, city, street, house, apartment, postal_code);
}
std::string Address::NormalizePostalCode(const std::string& postal_code) {
  return Utility::DeleteWhitespaces(postal_code);
}
std::string Address::NormalizeCountry(const std::string& country) {
  return Utility::Trim(country);
}
std::string Address::NormalizeOblast(const std::string& oblast) {
  return Utility::Trim(oblast);
}
std::string Address::NormalizeCity(const std::string& city) {
  return Utility::Trim(city);
}
std::string Address::NormalizeStreet(const std::string& street) {
  return Utility::Trim(street);
}
void Address::ValidatePostalCode(const std::string& country,
                                 const std::string& postal_code) {
  if (postal_code.empty()) return;
  std::regex pattern(R"(^[A-Za-z0-9\- ]{2,10}$)");
  if (country == "Belarus" || country == "BY") {
    pattern = std::regex(R"(^(2\d{5})$)");
  }
  if (!std::regex_match(postal_code, pattern)) {
    throw AddressException("Address error: invalid postal code: " +
                           postal_code);
  }
}
void Address::ValidateCountry(const std::string& country) {
  if (country.empty())
    throw AddressException("Address error: country is required");
}
void Address::ValidateOblast(const std::string& oblast) {
  if (oblast.empty())
    throw AddressException("Address error: oblast is required");
}
void Address::ValidateCity(const std::string& city) {
  if (city.empty()) throw AddressException("Address error: city is required");
}
void Address::ValidateStreet(const std::string& street) {
  if (street.empty())
    throw AddressException("Address error: street is required");
}
void Address::ValidateHouse(const int house) {
  if (house <= 0)
    throw AddressException("Address error: house number must be positive");
}
void Address::ValidateApartment(int apartment) {
  if (apartment < 0)
    throw AddressException(
        "Address error: apartment number cannot be negative");
}