#include <gtest/gtest.h>

#include "../s21_containers.h"

class MapTest : public ::testing::Test {
 protected:
  s21::map<int, int> test_map;

  void SetUp() override {
    test_map.insert(std::make_pair(1, 10));
    test_map.insert(std::make_pair(2, 20));
    test_map.insert(std::make_pair(3, 30));
  }
};

TEST_F(MapTest, DefaultConstructor) {
  s21::map<int, int> empty_map;
  EXPECT_TRUE(empty_map.empty());
}

TEST_F(MapTest, CopyConstructor) {
  s21::map<int, int> copied_map(test_map);
  EXPECT_EQ(copied_map.size(), test_map.size());
  EXPECT_EQ(copied_map[2], test_map[2]);
}

TEST_F(MapTest, BeginEndIterator) {
  auto it = test_map.begin();
  EXPECT_EQ(it.iter_node_->value_.first, 1);
  EXPECT_EQ(it.iter_node_->value_.second, 10);
  ++it;
  EXPECT_EQ(it.iter_node_->value_.first, 2);
  EXPECT_EQ(it.iter_node_->value_.second, 20);
  ++it;
  EXPECT_EQ(it.iter_node_->value_.first, 3);
  EXPECT_EQ(it.iter_node_->value_.second, 30);
}

TEST_F(MapTest, ReverseBeginEndIterator) {
  auto rit = test_map.rbegin();
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 3);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 30);
  ++rit;
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 2);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 20);
  ++rit;
  EXPECT_EQ(rit.reverse_iter_node_->value_.first, 1);
  EXPECT_EQ(rit.reverse_iter_node_->value_.second, 10);
}

TEST_F(MapTest, Size) { EXPECT_EQ(test_map.size(), 3); }

TEST_F(MapTest, Empty) {
  s21::map<int, int> empty_map;
  EXPECT_TRUE(empty_map.empty());
  empty_map.insert({1, 1});
  EXPECT_FALSE(empty_map.empty());
}

TEST_F(MapTest, Insert) {
  test_map.insert(std::make_pair(4, 40));
  EXPECT_EQ(test_map.size(), 4);
  EXPECT_EQ(test_map.find(4).iter_node_->value_.second, 40);
}

TEST_F(MapTest, InsertMany) {
  s21::map<int, int> many_map;
  s21::map<int, int> map;
  many_map.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                       std::make_pair(3, 3), std::make_pair(4, 4));
  map.insert({1, 1});
  map.insert({2, 2});
  map.insert({3, 3});
  map.insert({4, 4});
  EXPECT_EQ(many_map.size(), map.size());
  EXPECT_EQ(many_map.find(4).iter_node_->value_.second, 4);
  EXPECT_EQ(map.find(4).iter_node_->value_.second, 4);
}

TEST_F(MapTest, EraseByIterator) {
  auto it = test_map.find(2);
  test_map.erase(it);
  EXPECT_EQ(test_map.size(), 2);
}

TEST_F(MapTest, EraseByKey) {
  int x = 3;
  test_map.erase(x);
  EXPECT_EQ(test_map.size(), 2);
}

TEST_F(MapTest, Find) {
  auto it = test_map.find(2);
  EXPECT_EQ(it.iter_node_->value_.first, 2);
  EXPECT_EQ(it.iter_node_->value_.second, 20);
}

TEST_F(MapTest, LowerBound) {
  int x = 2;
  auto it = test_map.lower_bound(x);
  EXPECT_EQ(it.iter_node_->value_.first, 1);
}

TEST_F(MapTest, UpperBound) {
  int x = 2;
  auto it = test_map.upper_bound(x);
  EXPECT_EQ(it.iter_node_->value_.first, 3);
}

TEST_F(MapTest, EqualRange) {
  int x = 2;
  auto range = test_map.equal_range(x);
  EXPECT_EQ(range.first.iter_node_->value_.first, 1);
  EXPECT_EQ(range.second.iter_node_->value_.first, 3);
}
