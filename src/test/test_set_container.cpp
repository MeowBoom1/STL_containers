#include <gtest/gtest.h>

#include "../s21_containers.h"  // Adjust the include path as necessary

class SetContainerTest : public ::testing::Test {
 protected:
  s21::set_container<int> set;

  void SetUp() override {
    set.insert(10);
    set.insert(20);
    set.insert(30);
  }
};

TEST_F(SetContainerTest, DefaultConstructor) {
  s21::set_container<int> empty_set;
  EXPECT_TRUE(empty_set.empty());
}

TEST_F(SetContainerTest, CopyConstructor) {
  s21::set_container<int> copied_set(set);
  EXPECT_EQ(copied_set.size(), set.size());
  EXPECT_EQ(*copied_set.find(10), *set.find(10));
}

TEST_F(SetContainerTest, AssignmentOperator) {
  s21::set_container<int> assigned_set;
  assigned_set = set;
  EXPECT_EQ(assigned_set.size(), set.size());
  EXPECT_EQ(*assigned_set.find(20), *set.find(20));
}

TEST_F(SetContainerTest, BeginEndIterator) {
  auto it = set.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
}

TEST_F(SetContainerTest, ReverseBeginEndIterator) {
  auto rit = set.rbegin();
  EXPECT_EQ(*rit, 30);
  ++rit;
  EXPECT_EQ(*rit, 20);
  ++rit;
  EXPECT_EQ(*rit, 10);
}

TEST_F(SetContainerTest, Insert) {
  set.insert(40);
  EXPECT_EQ(set.size(), 4);
  EXPECT_EQ(*set.find(40), 40);
}

TEST_F(SetContainerTest, EraseByIterator) {
  auto it = set.find(30);
  set.erase(it);
  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(*set.find(20), *set.end());
}

TEST_F(SetContainerTest, EraseByValue) {
  int x = 30;
  set.erase(x);
  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(*set.find(20), *set.end());
}

TEST_F(SetContainerTest, Find) {
  auto it = set.find(20);
  EXPECT_EQ(*it, 20);
}

TEST_F(SetContainerTest, LowerBound) {
  int x = 20;
  auto it = set.lower_bound(x);
  EXPECT_EQ(*it, 10);
}

TEST_F(SetContainerTest, UpperBound) {
  int x = 20;
  auto it = set.upper_bound(x);
  EXPECT_EQ(*it, 30);
}

TEST_F(SetContainerTest, EqualRange) {
  int x = 20;
  auto range = set.equal_range(x);
  EXPECT_EQ(*range.first, 10);
  EXPECT_EQ(*range.second, 30);
}

TEST_F(SetContainerTest, InsertMany) {
  set.insert_many(40, 50, 60);
  auto it = set.rbegin();
  EXPECT_EQ(*it, 60);
  ++it;
  EXPECT_EQ(*it, 50);
  ++it;
  EXPECT_EQ(*it, 40);
  ++it;
  EXPECT_EQ(*it, 30);
}
