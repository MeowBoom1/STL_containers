#include <gtest/gtest.h>

#include "../s21_containers.h"

class QueueTest : public ::testing::Test {
 protected:
  s21::queue<int> test_queue;

  void SetUp() override {
    test_queue.push(1);
    test_queue.push(2);
    test_queue.push(3);
  }
};

TEST_F(QueueTest, DefaultConstructor) {
  s21::queue<int> empty_queue;
  EXPECT_TRUE(empty_queue.empty());
  EXPECT_EQ(empty_queue.size(), 0);
}

TEST_F(QueueTest, Push) {
  test_queue.push(4);
  EXPECT_EQ(test_queue.back(), 4);
  EXPECT_EQ(test_queue.size(), 4);
}

TEST_F(QueueTest, Pop) {
  test_queue.pop();
  EXPECT_EQ(test_queue.front(), 2);
  EXPECT_EQ(test_queue.size(), 2);
}

TEST_F(QueueTest, Front) { EXPECT_EQ(test_queue.front(), 1); }

TEST_F(QueueTest, Back) { EXPECT_EQ(test_queue.back(), 3); }

TEST_F(QueueTest, SizeAndEmpty) {
  EXPECT_EQ(test_queue.size(), 3);
  EXPECT_FALSE(test_queue.empty());

  test_queue.pop();
  test_queue.pop();
  test_queue.pop();

  EXPECT_TRUE(test_queue.empty());
}

TEST_F(QueueTest, InsertManyBack) {
  test_queue.insert_many_back(4, 5, 6);
  EXPECT_EQ(test_queue.front(), 1);
  EXPECT_EQ(test_queue.back(), 6);
}
