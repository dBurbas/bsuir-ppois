/**
 * @file utility_functions.h
 * @brief Вспомогательные функции для обработки строк.
 * @author Dmitry Burbas
 * @date 15/11/2025
 */
#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#include <string>
#include <vector>

/**
 * @namespace Utility
 * @brief Пространство имен для общих вспомогательных функций
 */
namespace Utility {

/**
 * @brief Удаляет пробельные символы с начала и конца строки
 * @details Если строка состоит только из пробельных символов,
 * возвращается пустая строка.
 * @param str Исходная строка
 * @return Новая строка без ведущих и завершающих пробелов, табуляций и
 * переносов строк
 */
std::string Trim(const std::string& str);

/**
 * @brief Удаляет все пробельные символы из строки.
 * @param str Исходная строка (передается по значению для модификации).
 * @return Строка, из которой удалены все пробелы, табуляции и символы переноса
 * строк.
 */
std::string DeleteWhitespaces(std::string str);

/**
 * @brief Разбивает строку на части по заданному разделителю
 * @details Функция автоматически удаляет пробелы (Trim) у каждого токена.
 * Пустые токены (например, между двумя подряд идущими разделителями)
 * игнорируются и не попадают в результирующий вектор.
 * @param str Строка для разбиения
 * @param delimiter Символ-разделитель
 * @return Вектор строк, содержащий непустые части исходной строки
 */
std::vector<std::string> Split(const std::string& str, char delimiter);
}  // namespace Utility
#endif  // UTILITY_FUNCTIONS_H
