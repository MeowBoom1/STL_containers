#include <gtest/gtest.h>

#include "../s21_containers.h"

class ArrayTest : public ::testing::Test {
 protected:
  s21::array<int, 5> test_array;

  void SetUp() override {
    test_array.fill(0);
    test_array[0] = 1;
    test_array[1] = 2;
    test_array[2] = 3;
    test_array[3] = 4;
    test_array[4] = 5;
  }
};

// Test Construction and Initialization
TEST_F(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> empty_array;
  for (size_t i = 0; i < empty_array.size(); ++i) {
    EXPECT_EQ(empty_array[i], 0);  // Assuming default initialization to 0
  }
}

TEST_F(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST_F(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr_copy(test_array);
  for (size_t i = 0; i < arr_copy.size(); ++i) {
    EXPECT_EQ(arr_copy[i], test_array[i]);
  }
}

TEST_F(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr_moved(std::move(test_array));
  EXPECT_EQ(arr_moved[0], 1);
  EXPECT_EQ(arr_moved[4], 5);
  EXPECT_EQ(test_array[0],
            0);  // Moved-from object should be in a valid but unspecified state
}

TEST_F(ArrayTest, MoveAssignment) {
  s21::array<int, 5> arr;
  arr = std::move(test_array);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 5);
  EXPECT_EQ(test_array[0],
            0);  // Moved-from object should be in a valid but unspecified state
}

// Test Element Access
TEST_F(ArrayTest, AccessOperator) {
  EXPECT_EQ(test_array[0], 1);
  EXPECT_EQ(test_array[4], 5);
}

TEST_F(ArrayTest, AtWithBoundsCheck) {
  EXPECT_EQ(test_array.at(0), 1);
  EXPECT_EQ(test_array.at(4), 5);
  EXPECT_THROW(test_array.at(5),
               std::out_of_range);  // Should throw out_of_range exception
}

TEST_F(ArrayTest, FrontBack) {
  EXPECT_EQ(test_array.front(), 1);
  EXPECT_EQ(test_array.back(), 5);
}

TEST_F(ArrayTest, Data) {
  int* data_ptr = test_array.data();
  EXPECT_EQ(*data_ptr, 1);
  EXPECT_EQ(*(data_ptr + 4), 5);
}

// Test Iterators
TEST_F(ArrayTest, BeginEndIterator) {
  auto it = test_array.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, test_array.end());
}

// Test Capacity
TEST_F(ArrayTest, EmptyAndSize) {
  s21::array<int, 5> empty_array;
  EXPECT_FALSE(
      empty_array.empty());  // Should not be empty since it has 5 elements
  EXPECT_EQ(empty_array.size(), 5);
}

TEST_F(ArrayTest, MaxSize) { EXPECT_EQ(test_array.max_size(), 5); }

// Test Modifiers
TEST_F(ArrayTest, Fill) {
  test_array.fill(10);
  for (size_t i = 0; i < test_array.size(); ++i) {
    EXPECT_EQ(test_array[i], 10);
  }
}

TEST_F(ArrayTest, Swap) {
  s21::array<int, 5> other_array = {10, 20, 30, 40, 50};
  test_array.swap(other_array);
  EXPECT_EQ(test_array[0], 10);
  EXPECT_EQ(test_array[4], 50);
  EXPECT_EQ(other_array[0], 1);
  EXPECT_EQ(other_array[4], 5);
}
