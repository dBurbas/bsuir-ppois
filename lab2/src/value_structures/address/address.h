/**
 * @file address.h
 * @brief Заголовочный файл класса Address
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

/*! @class Address
 *  @brief Представляет структурированный почтовый адрес
 *  @details Хранит страну, область, город, улицу, номера дома и квартиры, а
 *  также почтовый индекс. Предоставляет валидацию, нормализацию и конвертацию
 *  адреса в строковое представление.
 */
class Address {
 public:
  /*!
   *  @brief Конструктор Address из отдельных компонентов
   *  *  @param country Название страны
   *  @param oblast Название области
   *  @param city Название города
   *  @param street Название улицы
   *  @param house Номер дома
   *  @param postal_code Почтовый индекс (может быть пустым)
   *  @param apartment Номер квартиры (опционально, по умолчанию 0)
   *  @throws AddressException, если любой из элементов некорректен
   */
  Address(const std::string& country, const std::string& oblast,
          const std::string& city, const std::string& street, int house,
          int apartment = 0, const std::string& postal_code = "");

  /*!
   *  @brief Конструктор Address из полной строки адреса
   *  @details Парсит переданную строку и делегирует основному конструктору.
   *  @param full_address Полная строка адреса для парсинга
   */
  explicit Address(const std::string& full_address)
      : Address(ParseFromString(full_address)) {}

  /*!
   *  @brief Устанавливает почтовый индекс
   *  @param postal_code Новое значение почтового индекса
   *  @details Нормализует, валидирует и устанавливает почтовый индекс.
   *  @throw AddressException, если данный почтовый индекс не валиден
   */
  void SetPostalCode(const std::string& postal_code);

  /*!
   *  @brief Устанавливает страну
   *  @param country Новое название страны
   *  @details Нормализует, валидирует и устанавливает страну.
   *  @throw AddressException, если данная строка пустая
   */
  void SetCountry(const std::string& country);

  /*!
   *  @brief Устанавливает область
   *  @param oblast Новое название области
   *  @details Нормализует, валидирует и устанавливает область.
   *  @throw AddressException, если данная строка пустая
   */
  void SetOblast(const std::string& oblast);

  /*!
   *  @brief Устанавливает город
   *  @param city Новое название города
   *  @details Нормализует, валидирует и устанавливает город.
   *  @throw AddressException, если данная строка пустая
   */
  void SetCity(const std::string& city);

  /*!
   *  @brief Устанавливает улицу
   *  @param street Новое название улицы
   *  @details Нормализует, валидирует и устанавливает улицу.
   *  @throw AddressException, если данная строка пустая
   */
  void SetStreet(const std::string& street);

  /*!
   *  @brief Устанавливает номер дома
   *  @param house Новый номер дома
   *  @details Нормализует, валидирует и устанавливает дом.
   *  @throw AddressException, если данная строка пустая
   */
  void SetHouse(int house);

  /*!
   *  @brief Устанавливает номер квартиры
   *  @param apartment Новый номер квартиры
   *  @details Нормализует, валидирует и устанавливает квартиру.
   *  @throw AddressException, если данный номер меньше либо равен 0
   */
  void SetApartment(int apartment);

  /*!
   *  @brief Преобразует адрес в человеко-читаемую строку
   *  @return Строковое представление адреса
   */
  [[nodiscard]] std::string ToString() const;

  /*!
   *  @brief Возвращает почтовый индекс
   *  @return Текущий почтовый индекс
   */
  [[nodiscard]] std::string GetPostalCode() const;

  /*!
   *  @brief Возвращает страну
   *  @return Текущее название страны
   */
  [[nodiscard]] std::string GetCountry() const;

  /*!
   *  @brief Возвращает область
   *  @return Текущее название региона
   */
  [[nodiscard]] std::string GetOblast() const;

  /*!
   *  @brief Возвращает город
   *  @return Текущее название города
   */
  [[nodiscard]] std::string GetCity() const;

  /*!
   *  @brief Возвращает улицу
   *  @return Текущее название улицы
   */
  [[nodiscard]] std::string GetStreet() const;

  /*!
   *  @brief Возвращает номер дома
   *  @return Текущий номер дома
   */
  [[nodiscard]] int GetHouseNumber() const;

  /*!
   *  @brief Возвращает номер квартиры
   *  @return Текущий номер квартиры
   */
  [[nodiscard]] int GetApartmentNumber() const;

 private:
  std::string postal_code_;  ///< Почтовый индекс адреса
  std::string country_;      ///< Название страны
  std::string oblast_;       ///< Название области
  std::string city_;         ///< Название города
  std::string street_;       ///< Название улицы
  int house_;                ///< Номер дома
  int apartment_ = 0;        ///< Номер квартиры

  /*!
   *  @brief Парсит адрес из строки
   *  @details Разделяет строку на элементы адреса по разделителю ';'
   *  @param full_address Строковое представление адреса
   *  @return Полученный объект Address
   *  @throw AddressException, если формат данной строки некорректен(не хватает
   * элементов)
   */
  static const Address& ParseFromString(const std::string& full_address);

  /*!
   *  @brief Нормализует строку почтового индекса
   *  @details Удаляет пробельные символы.
   *  @param postal_code Исходная строка почтового индекса (может быть пустой)
   *  @return Нормализованная строка почтового индекса
   */
  static std::string NormalizePostalCode(const std::string& postal_code = "");

  /*!
   *  @brief Нормализует название страны
   *  @details Удаляет пробельные символы (функционал может быть расширен).
   *  @param country Исходное название страны
   *  @return Нормализованное название страны
   */
  static std::string NormalizeCountry(const std::string& country);

  /*!
   *  @brief Нормализует название области
   *  @details Удаляет пробельные символы (функционал может быть расширен).
   *  @param oblast Исходное название области
   *  @return Нормализованное название области
   */
  static std::string NormalizeOblast(const std::string& oblast);

  /*!
   *  @brief Нормализует название города
   *  @details Удаляет пробельные символы (функционал может быть расширен).
   *  @param city Исходное название города
   *  @return Нормализованное название города
   */
  static std::string NormalizeCity(const std::string& city);

  /*!
   *  @brief Нормализует название улицы
   *  @details Удаляет пробельные символы (функционал может быть расширен).
   *  @param street Исходное название улицы
   *  @return Нормализованное название улицы
   */
  static std::string NormalizeStreet(const std::string& street);

  /*!
   *  @brief Валидирует почтовый индекс
   *  @details Проверяет, что почтовый индекс соответствует ожидаемому формату
   * для указанной страны, и выбрасывает исключение при некорректном вводе
   * (детальная валидация для белорусских индексов).
   *  @param postal_code Почтовый индекс для валидации (может быть пустым)
   *  @param country Страна, для которой выполняется валидация индекса
   */
  static void ValidatePostalCode(const std::string& country,
                                 const std::string& postal_code = "");

  static void ValidateCountry(const std::string& country);

  /*!
   *  @brief Валидирует название области
   *  @details Проверяет, что область не пуста (функционал может быть расширен).
   *  @param oblast Название области для валидации
   */
  static void ValidateOblast(const std::string& oblast);

  /*!
   *  @brief Валидирует название города
   *  @details Проверяет, что город не пуст (функционал может быть расширен).
   *  @param city Название города для валидации
   */
  static void ValidateCity(const std::string& city);

  /*!
   *  @brief Валидирует название улицы
   *  @details Проверяет, что улица не пуста (функционал может быть расширен).
   *  @param street Название улицы для валидации
   */
  static void ValidateStreet(const std::string& street);

  /*!
   *  @brief Валидирует номер дома
   *  @details Проверяет, что номер дома положительный (функционал может быть
   * расширен).
   *  @param house Номер дома для валидации
   */
  static void ValidateHouse(int house);

  /*!
   *  @brief Валидирует номер квартиры
   *  @details Проверяет, что номер квартиры неотрицательный (функционал может
   * быть расширен).
   *  @param apartment Номер квартиры для валидации
   */
  static void ValidateApartment(int apartment);
};

#endif  // ADDRESS_H
