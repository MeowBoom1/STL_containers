#include <gtest/gtest.h>

// #include "../s21_containers.h" // Adjust the include path as necessary

#include "../s21_containers.h"

class MultiSetContainerTest : public ::testing::Test {
 protected:
  s21::multiset<int> multiset;

  void SetUp() override {
    multiset.insert(10);
    multiset.insert(20);
    multiset.insert(20);
    multiset.insert(30);
    multiset.insert(30);
    multiset.insert(30);
  }
};

TEST_F(MultiSetContainerTest, DefaultConstructor) {
  s21::multiset<int> empty_multiset;
  EXPECT_TRUE(empty_multiset.empty());
}

TEST_F(MultiSetContainerTest, CopyConstructor) {
  s21::multiset<int> copied_multiset(multiset);
  EXPECT_EQ(copied_multiset.size(), multiset.size());
  EXPECT_EQ(*copied_multiset.find(20), *multiset.find(20));
}

TEST_F(MultiSetContainerTest, AssignmentOperator) {
  s21::multiset<int> assigned_multiset;
  assigned_multiset = multiset;
  EXPECT_EQ(assigned_multiset.size(), multiset.size());
  EXPECT_EQ(*assigned_multiset.find(30), *multiset.find(30));
}

TEST_F(MultiSetContainerTest, BeginEndIterator) {
  auto it = multiset.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 30);
  EXPECT_EQ(*it, *multiset.end());
}

TEST_F(MultiSetContainerTest, ReverseBeginEndIterator) {
  auto rit = multiset.rbegin();
  EXPECT_EQ(*rit, 30);
  ++rit;
  EXPECT_EQ(*rit, 30);
  ++rit;
  EXPECT_EQ(*rit, 30);
  ++rit;
  EXPECT_EQ(*rit, 20);
  ++rit;
  EXPECT_EQ(*rit, 20);
  ++rit;
  EXPECT_EQ(*rit, 10);
  EXPECT_EQ(*rit, *multiset.rend());
}

TEST_F(MultiSetContainerTest, Size) { EXPECT_EQ(multiset.size(), 6); }

TEST_F(MultiSetContainerTest, Empty) {
  s21::multiset<int> empty_multiset;
  EXPECT_TRUE(empty_multiset.empty());
  empty_multiset.insert(40);
  EXPECT_FALSE(empty_multiset.empty());
}

TEST_F(MultiSetContainerTest, Insert) {
  multiset.insert(40);
  EXPECT_EQ(multiset.size(), 7);
  EXPECT_EQ(40, *multiset.end());
}

TEST_F(MultiSetContainerTest, EraseByIterator) {
  auto it = multiset.find(20);
  multiset.erase(it);
  EXPECT_EQ(multiset.size(), 5);
}

TEST_F(MultiSetContainerTest, Find) {
  auto it = multiset.find(20);
  EXPECT_EQ(*it, 20);
}

TEST_F(MultiSetContainerTest, LowerBound) {
  int x = 20;
  auto it = multiset.lower_bound(x);
  EXPECT_EQ(*it, 20);
}

TEST_F(MultiSetContainerTest, UpperBound) {
  int x = 20;
  auto it = multiset.upper_bound(x);
  EXPECT_EQ(*it, 30);
}

TEST_F(MultiSetContainerTest, EqualRange) {
  int x = 20;
  auto range = multiset.equal_range(x);
  EXPECT_EQ(*range.first, 20);
  EXPECT_EQ(*range.second, 30);
}

TEST_F(MultiSetContainerTest, InsertMany) {
  multiset.insert_many(40, 50, 60);
  auto it = multiset.end();
  EXPECT_EQ(*it, 60);
  --it;
  EXPECT_EQ(*it, 50);
  --it;
  EXPECT_EQ(*it, 40);
  --it;
  EXPECT_EQ(*it, 30);
}