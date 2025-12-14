//
// Created by Dmitry Burbas on 13/12/2025.
//

#ifndef SCHOLARSHIP_H
#define SCHOLARSHIP_H
#include <cmath>
#include <string>

#include "../exceptions/dean_office_exceptions.h"
class Scholarship {
 public:
  explicit Scholarship(const int base = kMinBase,
                       const double rate = kMinRate) {
    SetBase(base);
    SetRate(rate);
  }
  void SetBase(const int base) {
    if (base < kMinBase)
      throw ScholarshipException("Scholarship base cannot be <" +
                                 std::to_string(kMinBase));
    base_ = base;
  }
  void SetRate(const double rate) {
    if (rate <= 0 || rate > kMaxRate)
      throw ScholarshipException("Scholarship rate must be > 0 and <= " +
                                 std::to_string(kMaxRate));
    rate_ = rate;
  }
  [[nodiscard]] int GetValue() const {
    return static_cast<int>(std::lround(base_ * rate_));
  }
  [[nodiscard]] double GetRate() const { return rate_; }
  [[nodiscard]] int GetBase() const { return base_; }

 private:
  static constexpr int kMinBase = 100;
  static constexpr double kMinRate = 1.0;
  static constexpr double kMaxRate = 10.0;

  int base_ = kMinBase;
  double rate_ = kMinRate;
};

#endif  // SCHOLARSHIP_H
