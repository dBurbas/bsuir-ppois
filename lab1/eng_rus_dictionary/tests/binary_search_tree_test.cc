//
//  binary_search_tree_tests.cc
//  eng_rus_dictionary
//
//  Created by Dmitry Burbas on 17/10/2025.
//
#include <utility>
#include <gtest/gtest.h>
#include "../src/binary_search_tree/binary_search_tree.hpp"


class BinarySearchTreeFixture : public ::testing::Test {
protected:
    void SetUp() override {
        test_tree.Insert("five", 5);
        test_tree.Insert("four", 4);
        test_tree.Insert("nine", 9);
        test_tree.Insert("six", 6);
        test_tree.Insert("seven", 7);
        test_tree.Insert("three", 3);
    }
    void TearDown() override {
        test_tree.Clear();
    }
    
    BinarySearchTree<std::string, int> test_tree;
};
TEST(BinarySearchTreeNonFixture, IsEmptyEmptyTree) {
    BinarySearchTree<std::string, std::string> tree;
    ASSERT_TRUE(tree.IsEmpty());
}
TEST(BinarySearchTreeNonFixture, GetSizeEmptyTree) {
    BinarySearchTree<std::string, std::string> tree;
    ASSERT_EQ(0,tree.GetSize());
}
TEST_F(BinarySearchTreeFixture, FindExistingKey) {
    ASSERT_EQ(5,*test_tree.Find("five"));
    ASSERT_EQ(3,*test_tree.Find("three"));
    ASSERT_EQ(7,*test_tree.Find("seven"));
}
TEST_F(BinarySearchTreeFixture, OperatorFindExistingKey) {
    ASSERT_EQ(5,test_tree["five"]);
    ASSERT_EQ(3,test_tree["three"]);
    ASSERT_EQ(7,test_tree["seven"]);
}
TEST_F(BinarySearchTreeFixture, OperatorChangeExistingKey) {
    test_tree["five"] = 55;
    ASSERT_EQ(55,test_tree["five"]);
    test_tree["three"] = 33;
    ASSERT_EQ(33,test_tree["three"]);
    test_tree["seven"] = 77;
    ASSERT_EQ(77,test_tree["seven"]);
}
TEST_F(BinarySearchTreeFixture, FindNonExistingKey) {
    ASSERT_EQ(nullptr,test_tree.Find("forty two"));
    ASSERT_EQ(nullptr,test_tree.Find("fifty"));
    ASSERT_EQ(nullptr,test_tree.Find("sevenn"));
}
TEST_F(BinarySearchTreeFixture, OperatorFindNonExistingKey) {
    ASSERT_EQ(test_tree["five hundred"], 0);
    ASSERT_EQ(test_tree["three hundred"], 0);
    ASSERT_EQ(test_tree["seventy"], 0);
}
TEST_F(BinarySearchTreeFixture, OperatorChangeNonExistingKey) {
    test_tree["fifty five"] = 55;
    ASSERT_EQ(55,test_tree["fifty five"]);
    test_tree["thirty three"] = 33;
    ASSERT_EQ(33,test_tree["thirty three"]);
    test_tree["seventy seven"] = 77;
    ASSERT_EQ(77,test_tree["seventy seven"]);
}
TEST_F(BinarySearchTreeFixture, InsertNonExisting) {
    ASSERT_TRUE(test_tree.Insert("fifty five",55));
    ASSERT_EQ(55,test_tree["fifty five"]);
    ASSERT_TRUE(test_tree.Insert("twenty three",23));
    ASSERT_EQ(23,test_tree["twenty three"]);
}
TEST_F(BinarySearchTreeFixture, InsertExisting) {
    ASSERT_FALSE(test_tree.Insert("five",55));
    ASSERT_EQ(55,test_tree["five"]);
    ASSERT_FALSE(test_tree.Insert("three",33));
    ASSERT_EQ(33,test_tree["three"]);
}
TEST_F(BinarySearchTreeFixture, EraseNonExisting) {
    ASSERT_FALSE(test_tree.Erase("fifty five"));
    ASSERT_FALSE(test_tree.Erase("twenty five"));
    ASSERT_FALSE(test_tree.Erase("forty two"));
}
TEST_F(BinarySearchTreeFixture, EraseExisting) {
    ASSERT_TRUE(test_tree.Erase("five"));
    ASSERT_EQ(test_tree.Find("five"), nullptr);
    ASSERT_TRUE(test_tree.Erase("four"));
    ASSERT_EQ(test_tree.Find("four"), nullptr);
    ASSERT_TRUE(test_tree.Erase("nine"));
    ASSERT_EQ(test_tree.Find("nine"), nullptr);
}
TEST_F(BinarySearchTreeFixture, GetSizeNonEmpty) {
    ASSERT_EQ(6,test_tree.GetSize());
    test_tree.Erase("five");
    ASSERT_EQ(5,test_tree.GetSize());
}
TEST_F(BinarySearchTreeFixture, IsEmptyNonEmptyTree) {
    ASSERT_FALSE(test_tree.IsEmpty());
}
TEST_F(BinarySearchTreeFixture, ClearTree) {
    test_tree.Clear();
    test_tree.IsEmpty();
}
TEST_F(BinarySearchTreeFixture, EqualsOperatorEqualTrees) {
    BinarySearchTree<std::string, int> new_tree;
    new_tree.Insert("five", 5);
    new_tree.Insert("four", 4);
    new_tree.Insert("nine", 9);
    new_tree.Insert("six", 6);
    new_tree.Insert("seven", 7);
    new_tree.Insert("three", 3);
    EXPECT_TRUE(test_tree == new_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, EqualsOperatorNonEqualTrees) {
    BinarySearchTree<std::string, int> new_tree;
    EXPECT_FALSE(test_tree == new_tree);
    new_tree.Insert("five", 5);
    new_tree.Insert("four", 4);
    new_tree.Insert("nine", 9);
    EXPECT_FALSE(test_tree == new_tree);
    new_tree.Insert("six", 6);
    new_tree.Insert("seven", 7);
    new_tree.Insert("thirty three", 33);
    EXPECT_FALSE(test_tree == new_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, UnequalOperatorEqualTrees) {
    BinarySearchTree<std::string, int> new_tree;
    new_tree.Insert("five", 5);
    new_tree.Insert("four", 4);
    new_tree.Insert("nine", 9);
    new_tree.Insert("six", 6);
    new_tree.Insert("seven", 7);
    new_tree.Insert("three", 3);
    EXPECT_FALSE(test_tree != new_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, UnequalOperatorNonEqualTrees) {
    BinarySearchTree<std::string, int> new_tree;
    EXPECT_TRUE(test_tree != new_tree);
    new_tree.Insert("five", 5);
    new_tree.Insert("four", 4);
    new_tree.Insert("nine", 9);
    EXPECT_TRUE(test_tree != new_tree);
    new_tree.Insert("six", 6);
    new_tree.Insert("seven", 7);
    new_tree.Insert("thirty three", 33);
    EXPECT_TRUE(test_tree != new_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, CopyConstructor) {
    BinarySearchTree new_tree(test_tree);
    EXPECT_TRUE(test_tree == test_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, AssignmentOperator) {
    BinarySearchTree new_tree = test_tree;
    EXPECT_TRUE(test_tree == test_tree);
    new_tree.Clear();
}
TEST_F(BinarySearchTreeFixture, InOrderTraversalWorks) {
    std::vector<std::pair<std::string,int>> result;
    test_tree.InOrderTraversal([&](const std::string& key, const int& value) {
        result.push_back({key, value});
    });
    std::vector<std::pair<std::string, int>> expected = {
            {"five", 5}, {"four", 4}, {"nine", 9},
            {"seven", 7}, {"six", 6}, {"three", 3}
        };
    ASSERT_EQ(result, expected);
}
