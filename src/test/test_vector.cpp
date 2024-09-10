#include <gtest/gtest.h>

#include "../s21_containers.h"

// Test default constructor and size method
TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

// Test constructor with size
TEST(VectorTest, ConstructorWithSize) {
  s21::vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);

  // Check that the default value is zero-initialized
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

// Test copy constructor
TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1(5);
  for (int i = 0; i < 5; ++i) {
    v1[i] = i + 1;
  }
  s21::vector<int> v2(v1);

  EXPECT_EQ(v2.size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

// Test move constructor
TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1(5);
  for (int i = 0; i < 5; ++i) {
    v1[i] = i + 1;
  }
  s21::vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }

  // v1 should be empty after the move
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
}

// Test assignment operator
TEST(VectorTest, AssignmentOperator) {
  s21::vector<int> v1(5);
  for (int i = 0; i < 5; ++i) {
    v1[i] = i + 1;
  }
  s21::vector<int> v2 = v1;

  EXPECT_EQ(v2.size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

// Test reserve method
TEST(VectorTest, Reserve) {
  s21::vector<int> v(5);
  v.reserve(10);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 10);
}

// Test push_back method
TEST(VectorTest, PushBack) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

// Test pop_back method
TEST(VectorTest, PopBack) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.pop_back();

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

// Test clear method
TEST(VectorTest, Clear) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(),
            2);  // The capacity should remain the same after clear
}

// Test at method with valid index
TEST(VectorTest, AtValidIndex) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

// Test at method with invalid index (out_of_range)
TEST(VectorTest, AtInvalidIndex) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_THROW(v.at(3), std::out_of_range);
}

// Test size and empty methods
TEST(VectorTest, SizeAndEmpty) {
  s21::vector<int> v;

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);

  v.push_back(1);

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 1);
}

// Test shrink_to_fit method
TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> v(5);
  v.reserve(10);
  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), 5);
}

// Test data method
TEST(VectorTest, DataMethod) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  int* data = v.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
}
