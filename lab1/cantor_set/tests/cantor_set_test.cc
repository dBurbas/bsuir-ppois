//
//  cantor_set_test.cc
//  cantor_set
//
//  Created by Dmitry Burbas on 24/10/2025.
//
#include "../src/set/cantor_set.h"
#include <gtest/gtest.h>
#include <sstream>

class CantorSetFixture : public ::testing::Test {
protected:
  void SetUp() override {
    test_set = CantorSet("{a, b, c}");
    nested_set = CantorSet("{a, {b, c}, d}");
    empty_set = CantorSet("{}");
  }

  void TearDown() override {
    test_set.Clear();
    nested_set.Clear();
    empty_set.Clear();
  }

  CantorSet test_set;
  CantorSet nested_set;
  CantorSet empty_set;
};

TEST(CantorSetNonFixture, DefaultConstructor) {
  CantorSet set;
  ASSERT_TRUE(set.IsEmpty());
  ASSERT_EQ(set.Cardinality(), 0);
}

TEST(CantorSetNonFixture, StringConstructorSimple) {
  CantorSet set("{a, b, c}");
  ASSERT_FALSE(set.IsEmpty());
  ASSERT_EQ(set.Cardinality(), 3);
  ASSERT_EQ(set.ToString(), "{a, b, c}");
}

TEST(CantorSetNonFixture, StringConstructorWithSpaces) {
  CantorSet set("{  a ,  b  ,   c  }");
  ASSERT_EQ(set.ToString(), "{a, b, c}");
}

TEST(CantorSetNonFixture, StringConstructorNested) {
  CantorSet set("{a, {b, c}, d}");
  ASSERT_EQ(set.Cardinality(), 3);
  ASSERT_TRUE(set.Contains("{b, c}"));
}

TEST(CantorSetNonFixture, StringConstructorEmpty) {
  CantorSet set("{}");
  ASSERT_TRUE(set.IsEmpty());
  ASSERT_EQ(set.ToString(), "{}");
}

TEST(CantorSetNonFixture, CStringConstructor) {
  CantorSet set("{a, b, c}");
  ASSERT_EQ(set.ToString(), "{a, b, c}");
}

TEST(CantorSetNonFixture, CopyConstructor) {
  CantorSet original("{a, b, c}");
  CantorSet copy(original);
  ASSERT_TRUE(copy == original);
  ASSERT_EQ(copy.ToString(), "{a, b, c}");
}

TEST(CantorSetNonFixture, InvalidStringEmpty) {
  ASSERT_THROW(CantorSet(""), std::invalid_argument);
}

TEST(CantorSetNonFixture, InvalidStringNoBraces) {
  ASSERT_THROW(CantorSet("a, b, c"), std::invalid_argument);
}

TEST(CantorSetNonFixture, InvalidStringUnbalancedBraces) {
  ASSERT_THROW(CantorSet("{a, b, c"), std::invalid_argument);
  ASSERT_THROW(CantorSet("a, b, c}"), std::invalid_argument);
  ASSERT_THROW(CantorSet("{a, {b, c}, d"), std::invalid_argument);
}

TEST(CantorSetNonFixture, InvalidStringInvalidCharacters) {
  ASSERT_THROW(CantorSet("{a, b, @}"), std::invalid_argument);
  ASSERT_THROW(CantorSet("{a, b#c}"), std::invalid_argument);
}

TEST(CantorSetNonFixture, InvalidStringMultiCharElement) {
  ASSERT_THROW(CantorSet("{a, bc, d}"), std::invalid_argument);
  ASSERT_THROW(CantorSet("{ab}"), std::invalid_argument);
}

TEST_F(CantorSetFixture, IsEmptyOnEmptySet) {
  ASSERT_TRUE(empty_set.IsEmpty());
}

TEST_F(CantorSetFixture, IsEmptyOnNonEmptySet) {
  ASSERT_FALSE(test_set.IsEmpty());
  ASSERT_FALSE(nested_set.IsEmpty());
}

TEST_F(CantorSetFixture, CardinalitySimpleSet) {
  ASSERT_EQ(test_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, CardinalityNestedSet) {
  ASSERT_EQ(nested_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, CardinalityEmptySet) {
  ASSERT_EQ(empty_set.Cardinality(), 0);
}

TEST_F(CantorSetFixture, ClearNonEmptySet) {
  test_set.Clear();
  ASSERT_TRUE(test_set.IsEmpty());
  ASSERT_EQ(test_set.Cardinality(), 0);
}

TEST_F(CantorSetFixture, ClearEmptySet) {
  empty_set.Clear();
  ASSERT_TRUE(empty_set.IsEmpty());
}

TEST_F(CantorSetFixture, AddElementNewAtomic) {
  ASSERT_TRUE(test_set.AddElement("d"));
  ASSERT_EQ(test_set.Cardinality(), 4);
  ASSERT_TRUE(test_set.Contains("d"));
}

TEST_F(CantorSetFixture, AddElementExistingAtomic) {
  ASSERT_FALSE(test_set.AddElement("a"));
  ASSERT_EQ(test_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, AddElementNewNestedSet) {
  ASSERT_TRUE(test_set.AddElement("{x, y}"));
  ASSERT_TRUE(test_set.Contains("{x, y}"));
}

TEST_F(CantorSetFixture, AddElementExistingNestedSet) {
  ASSERT_FALSE(nested_set.AddElement("{b, c}"));
}

TEST_F(CantorSetFixture, AddElementInvalidAtomic) {
  ASSERT_THROW(test_set.AddElement("ab"), std::invalid_argument);
  ASSERT_THROW(test_set.AddElement("@"), std::invalid_argument);
}

TEST_F(CantorSetFixture, AddElementToEmptySet) {
  ASSERT_TRUE(empty_set.AddElement("a"));
  ASSERT_EQ(empty_set.Cardinality(), 1);
  ASSERT_FALSE(empty_set.IsEmpty());
}

TEST_F(CantorSetFixture, EraseElementExistingAtomic) {
  ASSERT_TRUE(test_set.EraseElement("a"));
  ASSERT_EQ(test_set.Cardinality(), 2);
  ASSERT_FALSE(test_set.Contains("a"));
}

TEST_F(CantorSetFixture, EraseElementNonExistingAtomic) {
  ASSERT_FALSE(test_set.EraseElement("x"));
  ASSERT_EQ(test_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, EraseElementExistingNestedSet) {
  ASSERT_TRUE(nested_set.EraseElement("{b, c}"));
  ASSERT_EQ(nested_set.Cardinality(), 2);
  ASSERT_FALSE(nested_set.Contains("{b, c}"));
}

TEST_F(CantorSetFixture, EraseElementNonExistingNestedSet) {
  ASSERT_FALSE(nested_set.EraseElement("{x, y}"));
  ASSERT_EQ(nested_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, EraseElementInvalid) {
  ASSERT_THROW(test_set.EraseElement("ab"), std::invalid_argument);
  ASSERT_THROW(test_set.EraseElement("@"), std::invalid_argument);
}

TEST_F(CantorSetFixture, ContainsExistingElement) {
  ASSERT_TRUE(test_set.Contains("a"));
  ASSERT_TRUE(test_set.Contains("b"));
  ASSERT_TRUE(test_set.Contains("c"));
}

TEST_F(CantorSetFixture, ContainsNonExistingElement) {
  ASSERT_FALSE(test_set.Contains("d"));
  ASSERT_FALSE(test_set.Contains("x"));
}

TEST_F(CantorSetFixture, OperatorBracketExistingElement) {
  ASSERT_TRUE(test_set["a"]);
  ASSERT_TRUE(test_set["b"]);
}

TEST_F(CantorSetFixture, OperatorBracketNonExistingElement) {
  ASSERT_FALSE(test_set["x"]);
  ASSERT_FALSE(test_set["z"]);
}

TEST_F(CantorSetFixture, ContainsNestedSet) {
  ASSERT_TRUE(nested_set.Contains("{b, c}"));
  ASSERT_FALSE(nested_set.Contains("{x, y}"));
}

TEST_F(CantorSetFixture, ContainsInvalidElement) {
  ASSERT_FALSE(test_set.Contains("ab"));
  ASSERT_FALSE(test_set.Contains("@"));
}

TEST_F(CantorSetFixture, EqualityOperatorEqualSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{a, b, c}");
  ASSERT_TRUE(set1 == set2);
}

TEST_F(CantorSetFixture, EqualityOperatorDifferentSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{a, b, d}");
  ASSERT_FALSE(set1 == set2);
}

TEST_F(CantorSetFixture, EqualityOperatorDifferentOrder) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{c, b, a}");
  ASSERT_TRUE(set1 == set2);
}

TEST_F(CantorSetFixture, InequalityOperatorEqualSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{a, b, c}");
  ASSERT_FALSE(set1 != set2);
}

TEST_F(CantorSetFixture, InequalityOperatorDifferentSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{a, b, d}");
  ASSERT_TRUE(set1 != set2);
}

TEST_F(CantorSetFixture, EqualsMethodEqualSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{a, b, c}");
  ASSERT_TRUE(set1.Equals(set2));
}

TEST_F(CantorSetFixture, EqualsMethodDifferentSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{x, y, z}");
  ASSERT_FALSE(set1.Equals(set2));
}

TEST_F(CantorSetFixture, AssignmentOperatorNonEmpty) {
  CantorSet new_set;
  new_set = test_set;
  ASSERT_TRUE(new_set == test_set);
  ASSERT_EQ(new_set.ToString(), "{a, b, c}");
}

TEST_F(CantorSetFixture, AssignmentOperatorEmpty) {
  CantorSet new_set("{x, y, z}");
  new_set = empty_set;
  ASSERT_TRUE(new_set == empty_set);
  ASSERT_TRUE(new_set.IsEmpty());
}

TEST_F(CantorSetFixture, AssignmentOperatorSelfAssignment) {
  test_set = test_set;
  ASSERT_EQ(test_set.ToString(), "{a, b, c}");
  ASSERT_EQ(test_set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, UnionOperatorDisjointSets) {
  CantorSet set1("{a, b}");
  CantorSet set2("{c, d}");
  CantorSet result = set1 + set2;
  ASSERT_EQ(result.ToString(), "{a, b, c, d}");
  ASSERT_EQ(result.Cardinality(), 4);
}

TEST_F(CantorSetFixture, UnionOperatorOverlappingSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{b, c, d}");
  CantorSet result = set1 + set2;
  ASSERT_EQ(result.Cardinality(), 4);
  ASSERT_TRUE(result.Contains("a"));
  ASSERT_TRUE(result.Contains("d"));
}

TEST_F(CantorSetFixture, UnionOperatorWithEmptySet) {
  CantorSet result = test_set + empty_set;
  ASSERT_TRUE(result == test_set);
}

TEST_F(CantorSetFixture, UnionAssignmentOperator) {
  CantorSet set1("{a, b}");
  CantorSet set2("{c, d}");
  set1 += set2;
  ASSERT_EQ(set1.Cardinality(), 4);
  ASSERT_TRUE(set1.Contains("c"));
  ASSERT_TRUE(set1.Contains("d"));
}

TEST_F(CantorSetFixture, UnionOperatorNestedSets) {
  CantorSet set1("{a, {b, c}}");
  CantorSet set2("{{b, c}, d}");
  CantorSet result = set1 + set2;
  ASSERT_EQ(result.Cardinality(), 3);
  ASSERT_TRUE(result.Contains("a"));
  ASSERT_TRUE(result.Contains("d"));
  ASSERT_TRUE(result.Contains("{b, c}"));
}

TEST_F(CantorSetFixture, IntersectionOperatorOverlappingSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{b, c, d}");
  CantorSet result = set1 * set2;
  ASSERT_EQ(result.Cardinality(), 2);
  ASSERT_TRUE(result.Contains("b"));
  ASSERT_TRUE(result.Contains("c"));
  ASSERT_FALSE(result.Contains("a"));
  ASSERT_FALSE(result.Contains("d"));
}

TEST_F(CantorSetFixture, IntersectionOperatorDisjointSets) {
  CantorSet set1("{a, b}");
  CantorSet set2("{c, d}");
  CantorSet result = set1 * set2;
  ASSERT_TRUE(result.IsEmpty());
}

TEST_F(CantorSetFixture, IntersectionOperatorWithEmptySet) {
  CantorSet result = test_set * empty_set;
  ASSERT_TRUE(result.IsEmpty());
}

TEST_F(CantorSetFixture, IntersectionAssignmentOperator) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{b, c, d}");
  set1 *= set2;
  ASSERT_EQ(set1.Cardinality(), 2);
  ASSERT_TRUE(set1.Contains("b"));
  ASSERT_TRUE(set1.Contains("c"));
}

TEST_F(CantorSetFixture, IntersectionOperatorIdenticalSets) {
  CantorSet result = test_set * test_set;
  ASSERT_TRUE(result == test_set);
}

TEST_F(CantorSetFixture, DifferenceOperatorOverlappingSets) {
  CantorSet set1("{a, b, c}");
  CantorSet set2("{b, c, d}");
  CantorSet result = set1 - set2;
  ASSERT_EQ(result.Cardinality(), 1);
  ASSERT_TRUE(result.Contains("a"));
  ASSERT_FALSE(result.Contains("b"));
  ASSERT_FALSE(result.Contains("c"));
}

TEST_F(CantorSetFixture, DifferenceOperatorDisjointSets) {
  CantorSet set1("{a, b}");
  CantorSet set2("{c, d}");
  CantorSet result = set1 - set2;
  ASSERT_TRUE(result == set1);
}

TEST_F(CantorSetFixture, DifferenceOperatorWithEmptySet) {
  CantorSet result = test_set - empty_set;
  ASSERT_TRUE(result == test_set);
}

TEST_F(CantorSetFixture, DifferenceAssignmentOperator) {
  CantorSet set1("{a, b, c, d}");
  CantorSet set2("{b, d}");
  set1 -= set2;
  ASSERT_EQ(set1.Cardinality(), 2);
  ASSERT_TRUE(set1.Contains("a"));
  ASSERT_TRUE(set1.Contains("c"));
}

TEST_F(CantorSetFixture, DifferenceOperatorIdenticalSets) {
  CantorSet result = test_set - test_set;
  ASSERT_TRUE(result.IsEmpty());
}

TEST(CantorSetNonFixture, PowerSetEmptySet) {
  CantorSet set("{}");
  CantorSet power = set.PowerSet();
  ASSERT_EQ(power.Cardinality(), 1);
  ASSERT_TRUE(power.Contains("{}"));
}

TEST(CantorSetNonFixture, PowerSetOneElement) {
  CantorSet set("{a}");
  CantorSet power = set.PowerSet();
  ASSERT_EQ(power.Cardinality(), 2);
  ASSERT_TRUE(power["{}"]);
  ASSERT_TRUE(power["{a}"]);
}

TEST(CantorSetNonFixture, PowerSetTwoElements) {
  CantorSet set("{a, b}");
  CantorSet power = set.PowerSet();
  ASSERT_EQ(power.Cardinality(), 4);
  ASSERT_TRUE(power.Contains("{}"));
  ASSERT_TRUE(power.Contains("{a}"));
  ASSERT_TRUE(power.Contains("{b}"));
  ASSERT_TRUE(power.Contains("{a, b}"));
}

TEST(CantorSetNonFixture, PowerSetThreeElements) {
  CantorSet set("{a, b, c}");
  CantorSet power = set.PowerSet();
  ASSERT_EQ(power.Cardinality(), 8);
}

TEST(CantorSetNonFixture, PowerSetTooLarge) {
  CantorSet set(
      "{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u}");
  ASSERT_THROW(set.PowerSet(), std::length_error);
}

TEST_F(CantorSetFixture, OutputStreamOperator) {
  std::ostringstream oss;
  oss << test_set;
  ASSERT_EQ(oss.str(), "{a, b, c}");
}

TEST_F(CantorSetFixture, InputStreamOperator) {
  std::istringstream iss("{x, y, z}");
  CantorSet set;
  iss >> set;
  ASSERT_EQ(set.ToString(), "{x, y, z}");
  ASSERT_EQ(set.Cardinality(), 3);
}

TEST_F(CantorSetFixture, InputStreamOperatorNested) {
  std::istringstream iss("{a, {b, c}, d}");
  CantorSet set;
  iss >> set;
  ASSERT_TRUE(set.Contains("{b, c}"));
}

TEST(CantorSetNonFixture, RemoveDuplicates) {
  CantorSet set("{a, b, a, c, b}");
  ASSERT_EQ(set.Cardinality(), 3);
  ASSERT_EQ(set.ToString(), "{a, b, c}");
}

TEST(CantorSetNonFixture, NormalizeNestedSets) {
  CantorSet set("{a, {c, b}, {b, c}}");
  ASSERT_EQ(set.Cardinality(), 2);
  ASSERT_TRUE(set.Contains("a"));
  ASSERT_TRUE(set.Contains("{b, c}"));
}

TEST(CantorSetNonFixture, SortElementsByLengthAndLexicographic) {
  CantorSet set("{c, a, {b, c}, b}");
  std::string result = set.ToString();
  ASSERT_EQ(result, "{a, b, c, {b, c}}");
}

TEST_F(CantorSetFixture, ToStringSimpleSet) {
  ASSERT_EQ(test_set.ToString(), "{a, b, c}");
}

TEST_F(CantorSetFixture, ToStringNestedSet) {
  ASSERT_EQ(nested_set.ToString(), "{a, d, {b, c}}");
}

TEST_F(CantorSetFixture, ToStringEmptySet) {
  ASSERT_EQ(empty_set.ToString(), "{}");
}

TEST(CantorSetNonFixture, NestedEmptySet) {
  CantorSet set("{a, {}}");
  ASSERT_EQ(set.Cardinality(), 2);
  ASSERT_TRUE(set.Contains("a"));
  ASSERT_TRUE(set.Contains("{}"));
}

TEST(CantorSetNonFixture, DeeplyNestedSets) {
  CantorSet set("{a, {b, {c, d}}}");
  ASSERT_TRUE(set.Contains("{b, {c, d}}"));
}

TEST(CantorSetNonFixture, NumericElements) {
  CantorSet set("{1, 2, 3}");
  ASSERT_EQ(set.Cardinality(), 3);
  ASSERT_TRUE(set.Contains("1"));
}

TEST(CantorSetNonFixture, MixedAlphanumeric) {
  CantorSet set("{a, 1, b, 2}");
  ASSERT_EQ(set.Cardinality(), 4);
}
