#include <gtest/gtest.h>

#include "../s21_containers.h"

class AssociativeContainerTest : public ::testing::Test {
 protected:
  s21::associative_container<int, int> container;

  void SetUp() override {
    container.insert(std::make_pair(1, 10));
    container.insert(std::make_pair(2, 20));
    container.insert(std::make_pair(3, 30));
  }
};

TEST_F(AssociativeContainerTest, DefaultConstructor) {
  s21::associative_container<int, int> empty_container;
  EXPECT_TRUE(empty_container.empty());
}

TEST_F(AssociativeContainerTest, CopyConstructor) {
  int x = 2;
  s21::associative_container<int, int> copied_container(container);
  EXPECT_EQ(copied_container.size(), container.size());
  EXPECT_EQ(copied_container.find(x).iter_node_->value_.second,
            container.find(x).iter_node_->value_.second);
}

TEST_F(AssociativeContainerTest, AssignmentOperator) {
  s21::associative_container<int, int> assigned_container;
  assigned_container = container;
  EXPECT_EQ(assigned_container.size(), container.size());
  EXPECT_EQ(assigned_container.find(3).iter_node_->value_.second,
            container.find(3).iter_node_->value_.second);
}

TEST_F(AssociativeContainerTest, BeginEndIterator) {
  auto it = container.begin();
  EXPECT_EQ(it.iter_node_->value_.first, 1);
  EXPECT_EQ(it.iter_node_->value_.second, 10);
  ++it;
  EXPECT_EQ(it.iter_node_->value_.first, 2);
  EXPECT_EQ(it.iter_node_->value_.second, 20);
  ++it;
  EXPECT_EQ(it.iter_node_->value_.first, 3);
  EXPECT_EQ(it.iter_node_->value_.second, 30);
}

TEST_F(AssociativeContainerTest, ReverseBeginEndIterator) {
  auto rit = container.rbegin();
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 3);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 30);
  ++rit;
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 2);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 20);
  ++rit;
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 1);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 10);
  ;
}

TEST_F(AssociativeContainerTest, Size) { EXPECT_EQ(container.size(), 3); }

TEST_F(AssociativeContainerTest, Empty) {
  s21::associative_container<int, int> empty_container;
  EXPECT_TRUE(empty_container.empty());
  empty_container.insert(std::make_pair(4, 40));
  EXPECT_FALSE(empty_container.empty());
}

TEST_F(AssociativeContainerTest, Insert) {
  container.insert(std::make_pair(4, 40));
  EXPECT_EQ(container.size(), 4);
  EXPECT_EQ(container.find(4).iter_node_->value_.second, 40);
}

TEST_F(AssociativeContainerTest, InsertMany) {
  s21::associative_container<int, int> associative_container_map;
  s21::associative_container<int, int> associative_container;
  associative_container_map.insert_many(
      std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3),
      std::make_pair(4, 4));
  associative_container.insert({1, 1});
  associative_container.insert({2, 2});
  associative_container.insert({3, 3});
  associative_container.insert({4, 4});
  EXPECT_EQ(associative_container_map.size(), associative_container.size());
  EXPECT_EQ(associative_container_map.find(4).iter_node_->value_.second, 4);
  EXPECT_EQ(associative_container.find(4).iter_node_->value_.second, 4);
}

TEST_F(AssociativeContainerTest, EraseByIterator) {
  auto it = container.find(2);
  container.erase(it);
  EXPECT_EQ(container.size(), 2);
}

TEST_F(AssociativeContainerTest, EraseByKey) {
  int x = 3;
  container.erase(x);
  EXPECT_EQ(container.size(), 2);
}

TEST_F(AssociativeContainerTest, Find) {
  auto it = container.find(2);
  EXPECT_EQ(it.iter_node_->value_.first, 2);
  EXPECT_EQ(it.iter_node_->value_.second, 20);
}

TEST_F(AssociativeContainerTest, UpperBound) {
  int x = 2;
  auto it = container.upper_bound(x);
  EXPECT_EQ(it.iter_node_->value_.first, 3);
}

TEST_F(AssociativeContainerTest, EqualRange) {
  int x = 2;
  auto range = container.equal_range(x);
  EXPECT_EQ(range.first.iter_node_->value_.first, 1);
  EXPECT_EQ(range.second.iter_node_->value_.first, 3);
}

TEST_F(AssociativeContainerTest, LowerBound) {
  int x = 2;
  auto it = container.lower_bound(x);
  EXPECT_EQ(it.iter_node_->value_.first, 1);
}
