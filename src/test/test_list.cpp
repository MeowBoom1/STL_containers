#include <gtest/gtest.h>

#include "../s21_containers.h"

class ListTest : public ::testing::Test {
 protected:
  s21::list<int> test_list;

  void SetUp() override {
    test_list.push_back(1);
    test_list.push_back(2);
    test_list.push_back(3);
  }
};

// Test Default Constructor
TEST_F(ListTest, DefaultConstructor) {
  s21::list<int> empty_list;
  EXPECT_TRUE(empty_list.empty());
  EXPECT_EQ(empty_list.size(), 0);
}

// Test Parameterized Constructor
TEST_F(ListTest, ParameterizedConstructor) {
  s21::list<int> list_with_n_elements(5);
  EXPECT_EQ(list_with_n_elements.size(), 5);
  EXPECT_FALSE(list_with_n_elements.empty());
}

// Test Initializer List Constructor
TEST_F(ListTest, InitializerListConstructor) {
  s21::list<int> list_from_initializer = {1, 2, 3, 4, 5};
  EXPECT_EQ(list_from_initializer.size(), 5);
  EXPECT_EQ(list_from_initializer.front(), 1);
  EXPECT_EQ(list_from_initializer.back(), 5);
}

// Test Copy Constructor
TEST_F(ListTest, CopyConstructor) {
  s21::list<int> copy_list(test_list);
  EXPECT_EQ(copy_list.size(), test_list.size());
  EXPECT_EQ(copy_list.front(), test_list.front());
  EXPECT_EQ(copy_list.back(), test_list.back());
}

// Test Move Constructor
TEST_F(ListTest, MoveConstructor) {
  s21::list<int> moved_list(std::move(test_list));
  EXPECT_EQ(moved_list.size(), 3);
  EXPECT_TRUE(
      test_list.empty());  // After move, the original list should be empty.
}

// Test Assignment Operator (Move)
TEST_F(ListTest, MoveAssignmentOperator) {
  s21::list<int> another_list;
  another_list = std::move(test_list);
  EXPECT_EQ(another_list.size(), 3);
  EXPECT_TRUE(test_list.empty());
}

// Test front() and back()
TEST_F(ListTest, ElementAccess) {
  EXPECT_EQ(test_list.front(), 1);
  EXPECT_EQ(test_list.back(), 3);
}

// Test Iterators
TEST_F(ListTest, Iterators) {
  auto it = test_list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it,
            test_list.end());  // Should reach the end after the last element
}

// Test empty() and size()
TEST_F(ListTest, Capacity) {
  EXPECT_FALSE(test_list.empty());
  EXPECT_EQ(test_list.size(), 3);
}

// Test push_back(), push_front(), pop_back(), and pop_front()
TEST_F(ListTest, Modifiers) {
  test_list.push_back(4);
  EXPECT_EQ(test_list.back(), 4);
  test_list.pop_back();
  EXPECT_EQ(test_list.back(), 3);

  test_list.push_front(0);
  EXPECT_EQ(test_list.front(), 0);
  test_list.pop_front();
  EXPECT_EQ(test_list.front(), 1);
}
