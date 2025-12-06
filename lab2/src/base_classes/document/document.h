/**
 * @file document.h
 * @brief Base class for documents
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>

#include "../../base_classes/person/person.h"
#include "../../date/date.h"
/*! @class Document
 *  @brief Abstract base class for all documents.
 *  @details Describes the common interface of a document: number, issue date,
 *  owner, and signature state. Intended to be inherited by concrete document
 *  types.
 */
class Document {
 public:
  /*!
   *  @brief Document constructor.
   *  @param number Unique document number.
   *  @param issue_date Document issue date.
   *  @param owner Reference to the document owner.
   */
  Document(std::string number, const Date& issue_date, Person& owner)
      : number_(std::move(number)), issue_date_(issue_date), owner_(owner) {}
  /*!
   *  @brief Virtual destructor.
   *  @details Ensures proper destruction of derived class objects when deleted
   *  through a pointer to the base class Document.
   */
  virtual ~Document() = default;
  /*!
   *  @brief Returns the document number.
   *  @return A string containing the unique document number.
   */
  [[nodiscard]] std::string GetNumber() const { return number_; }
  /*!
   *  @brief Returns the document issue date.
   *  @return Date object representing the document issue date.
   */
  [[nodiscard]] Date GetIssueDate() const { return issue_date_; }
  /*!
   *  @brief Returns the document owner.
   *  @return Constant reference to a Person object representing the owner.
   */
  [[nodiscard]] const Person& GetOwner() const { return owner_; }
  /*!
   *  @brief Checks whether the document is signed.
   *  @return True if the document is signed, otherwise false.
   */
  [[nodiscard]] bool IsSigned() const { return is_signed_; }

  /*!
   *  @brief Signs the document.
   *  @details Pure virtual function that must be implemented in derived
   *  classes. The signing logic may include role checks, permission checks,
   *  and modifications of the internal document state.
   *  @param signer Reference to a Person object acting as the signer.
   */
  virtual void SignDocument(Person& signer) = 0;

 protected:
  bool is_signed_ = false;  ///< Flag indicating the document is signed.
  std::string number_;      ///< Unique document number.
  Date issue_date_;         ///< Document issue date.
  Person& owner_;           ///< Reference to the document owner.
};

#endif  // DOCUMENT_H
