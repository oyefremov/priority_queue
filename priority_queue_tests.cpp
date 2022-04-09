#include <gtest/gtest.h>

#include "priority_queue.h"

TEST(priority_queue, empty_queue_is_empty) {
    priority_queue<int> queue(10);
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, empty_queue_has_no_items) {
    priority_queue<int> queue(10);
    ASSERT_FALSE(queue.has_items());
}

TEST(priority_queue, empty_queue_has_capacity) {
    priority_queue<int> queue(10);
    ASSERT_EQ(10, queue.capacity());
}

TEST(priority_queue, empty_queue_has_size_0) {
    priority_queue<int> queue(10);
    ASSERT_EQ(0, queue.size());
}

TEST(priority_queue, push_one_item_increases_size) {
    priority_queue<int> queue(10);
    queue.push(1);
    ASSERT_EQ(1, queue.size());
}

TEST(priority_queue, push_one_item_keep_capacity) {
    priority_queue<int> queue(10);
    queue.push(1);
    ASSERT_EQ(10, queue.capacity());
}

TEST(priority_queue, push_one_item) {
    priority_queue<int> queue(10);
    queue.push(1);
    ASSERT_FALSE(queue.empty());
    EXPECT_TRUE(queue.has_items());
    EXPECT_EQ(1, queue.top());
}

TEST(priority_queue, push_two_items_1_2) {
    priority_queue<int> queue(10);
    queue.push(1);
    queue.push(2);
    ASSERT_EQ(2, queue.size());
    ASSERT_EQ(1, queue.top()) << "top item is smallest of 1 and 2";
}

TEST(priority_queue, push_two_items_2_1) {
    priority_queue<int> queue(10);
    queue.push(2);
    queue.push(1);
    ASSERT_EQ(2, queue.size());
    ASSERT_EQ(1, queue.top()) << "top item is smallest of 1 and 2";
}

TEST(priority_queue, push_pop_one_item) {
    priority_queue<int> queue(10);
    queue.push(1);
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, push_pop_two_items) {
    priority_queue<int> queue(10);
    queue.push(1);
    queue.push(2);
    ASSERT_EQ(1, queue.top()) << "top item is smallest of 1 and 2";
    queue.pop();
    ASSERT_EQ(2, queue.top()) << "top item is the only remaining item";
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, push_pop_replace_top_item) {
    priority_queue<int> queue(10);
    queue.push(1);
    queue.push(2);
    ASSERT_EQ(1, queue.top()) << "top item is smallest of 1 and 2";
    queue.replace_top(3);
    ASSERT_EQ(2, queue.top()) << "top item is smallest of 2 and 3";
    queue.pop();
    ASSERT_EQ(3, queue.top()) << "the only remaining item is 3";
    queue.pop();
    ASSERT_TRUE(queue.empty());
}