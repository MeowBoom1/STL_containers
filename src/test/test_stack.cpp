#include <gtest/gtest.h>
// #include "stack.h"  // Include your Stack class header
#include "../s21_containers.h"

class StackTest : public ::testing::Test {
 protected:
  s21::stack<int> test_stack;

  void SetUp() override {
    test_stack.push(1);
    test_stack.push(2);
    test_stack.push(3);
  }
};

TEST_F(StackTest, Push) {
  test_stack.push(4);
  EXPECT_EQ(test_stack.top(), 4);
  EXPECT_EQ(test_stack.size(), 4);
}

TEST_F(StackTest, Pop) {
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 2);
  EXPECT_EQ(test_stack.size(), 2);
}

TEST_F(StackTest, Top) { EXPECT_EQ(test_stack.top(), 3); }

TEST_F(StackTest, Empty) {
  s21::stack<int> empty_stack;
  EXPECT_TRUE(empty_stack.empty());

  empty_stack.push(1);
  EXPECT_FALSE(empty_stack.empty());
}

TEST_F(StackTest, Size) {
  EXPECT_EQ(test_stack.size(), 3);

  test_stack.push(4);
  EXPECT_EQ(test_stack.size(), 4);
}

TEST_F(StackTest, InsertManyFront) {
  test_stack.insert_many_front(10, 20, 30);
  EXPECT_EQ(test_stack.size(), 6);

  EXPECT_EQ(test_stack.top(), 30);
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 20);
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 10);
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 3);
}

TEST_F(StackTest, MultiplePop) {
  test_stack.pop();
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 1);
  EXPECT_EQ(test_stack.size(), 1);
}

TEST_F(StackTest, PushPopCombo) {
  test_stack.push(4);
  test_stack.pop();
  EXPECT_EQ(test_stack.top(), 3);
  EXPECT_EQ(test_stack.size(), 3);
}

TEST_F(StackTest, InsertManyFrontEmptyStack) {
  s21::stack<int> empty_stack;
  empty_stack.insert_many_front(10, 20, 30);
  EXPECT_EQ(empty_stack.size(), 3);
  EXPECT_EQ(empty_stack.top(), 30);
  empty_stack.pop();
  EXPECT_EQ(empty_stack.top(), 20);
  empty_stack.pop();
  EXPECT_EQ(empty_stack.top(), 10);
}
