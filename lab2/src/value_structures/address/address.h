/**
 * @file address.h
 * @brief
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

/*! @class Address
 *  @brief Represents a structured postal address.
 *  @details Stores country, region (oblast), city, street, house and apartment
 *  numbers, as well as a postal code. Provides validation, normalization and
 *  conversion of the address to a string representation.
 */
class Address {
 public:
  /*!
   *  @brief Constructs an Address from individual components.
   *  @param oblast Name of the region (oblast).
   *  @param city Name of the city.
   *  @param street Name of the street.
   *  @param house House number.
   *  @param country Country name
   *  @param postal_code Postal code (can be empty).
   *  @param apartment Apartment number (optional, defaults to 0).
   *  @throws AddressException, если любой из элементов не корректен
   */
  // TODO: перевести на русский документацию
  Address(const std::string& country, const std::string& oblast,
          const std::string& city, const std::string& street, int house,
          int apartment = 0, const std::string& postal_code = "");

  /*!
   *  @brief Constructs an Address from a full address string.
   *  @details Parses the given string and initializes all address components
   *  (country, region, city, street, house, apartment and postal code).
   *  @param full_address Full address string to be parsed.
   */
  explicit Address(const std::string& full_address) {
    *this = ParseFromString(full_address);
  }

  /*!
   *  @brief Sets the postal code.
   *  @param postal_code New postal code value.
   */
  void SetPostalCode(const std::string& postal_code);

  /*!
   *  @brief Sets the country.
   *  @param country New country name.
   */
  void SetCountry(const std::string& country);

  /*!
   *  @brief Sets the region (oblast).
   *  @param oblast New region (oblast) name.
   */
  void SetOblast(const std::string& oblast);

  /*!
   *  @brief Sets the city.
   *  @param city New city name.
   */
  void SetCity(const std::string& city);

  /*!
   *  @brief Sets the street.
   *  @param street New street name.
   */
  void SetStreet(const std::string& street);

  /*!
   *  @brief Sets the house number.
   *  @param house New house number.
   */
  void SetHouse(int house);

  /*!
   *  @brief Sets the apartment number.
   *  @param apartment New apartment number.
   */
  void SetApartment(int apartment);

  /*!
   *  @brief Converts the address to a human-readable string.
   *  @return String representation of the address.
   */
  [[nodiscard]] std::string ToString() const;

  /*!
   *  @brief Returns the postal code.
   *  @return Current postal code string.
   */
  [[nodiscard]] std::string GetPostalCode() const;

  /*!
   *  @brief Returns the country.
   *  @return Current country name.
   */
  [[nodiscard]] std::string GetCountry() const;

  /*!
   *  @brief Returns the region (oblast).
   *  @return Current region (oblast) name.
   */
  [[nodiscard]] std::string GetOblast() const;

  /*!
   *  @brief Returns the city.
   *  @return Current city name.
   */
  [[nodiscard]] std::string GetCity() const;

  /*!
   *  @brief Returns the street.
   *  @return Current street name.
   */
  [[nodiscard]] std::string GetStreet() const;

  /*!
   *  @brief Returns the house number.
   *  @return Current house number.
   */
  [[nodiscard]] int GetHouseNumber() const;

  /*!
   *  @brief Returns the apartment number.
   *  @return Current apartment number.
   */
  [[nodiscard]] int GetApartmentNumber() const;

 private:
  std::string postal_code_;  ///< Postal code of the address.
  std::string country_;      ///< Country name.
  std::string oblast_;       ///< Region (oblast) name.
  std::string city_;         ///< City name.
  std::string street_;       ///< Street name.
  int house_;                ///< House number.
  int apartment_ = 0;        ///< Apartment number.

  static const Address& ParseFromString(const std::string& full_address);

  /*!
   *  @brief Normalizes a postal code string.
   *  @details Trims whitespaces.
   *  @param postal_code Original postal code string (can be empty).
   *  @return Normalized postal code string.
   */
  static std::string NormalizePostalCode(const std::string& postal_code = "");

  /*!
   *  @brief Normalizes a country name
   *  @details Trims whitespaces (can be expanded)
   *  @param country Original country name
   *  @return Normalized country name
   */
  static std::string NormalizeCountry(const std::string& country);

  /*!
   *  @brief Normalizes a region (oblast) name.
   *  @details Trims whitespaces (can be expanded).
   *  @param oblast Original region (oblast) name.
   *  @return Normalized region (oblast) name.
   */
  static std::string NormalizeOblast(const std::string& oblast);

  /*!
   *  @brief Normalizes a city name.
   *  @details Trims whitespaces (can be expanded).
   *  @param city Original city name.
   *  @return Normalized city name.
   */
  static std::string NormalizeCity(const std::string& city);

  /*!
   *  @brief Normalizes a street name.
   *  @details Trims whitespaces (can be expanded).
   *  @param street Original street name.
   *  @return Normalized street name.
   */
  static std::string NormalizeStreet(const std::string& street);

  /*!
   *  @brief Validates the postal code.
   *  @details Checks that the postal code matches the expected format for
   *  the given country and throws an exception on invalid input(detailed
   * validation for belarusian codes).
   *  @param postal_code Postal code to validate (can be empty).
   *  @param country Country for which the postal code is validated.
   */
  static void ValidatePostalCode(const std::string& country,
                                 const std::string& postal_code = "");

  static void ValidateCountry(const std::string& country);

  /*!
   *  @brief Validates the region (oblast) name.
   *  @details Checks that the oblast is not empty (can be expanded)
   *  @param oblast Region (oblast) name to validate.
   */
  static void ValidateOblast(const std::string& oblast);

  /*!
   *  @brief Validates the city name.
   *  @details Checks that the city is not empty (can be expanded)
   *  @param city City name to validate.
   */
  static void ValidateCity(const std::string& city);

  /*!
   *  @brief Validates the street name.
   *  @details Checks that the street is not empty (can be expanded)
   *  @param street Street name to validate.
   */
  static void ValidateStreet(const std::string& street);

  /*!
   *  @brief Validates the house number.
   *  @details Checks that the house is positive number (can be expanded)
   *  @param house House number to validate.
   */
  static void ValidateHouse(int house);

  /*!
   *  @brief Validates the apartment number.
   *  @details Checks that the apartment is not a negative number (can be
   * expanded)
   *  @param apartment Apartment number to validate.
   */
  static void ValidateApartment(int apartment);
};

#endif  // ADDRESS_H
