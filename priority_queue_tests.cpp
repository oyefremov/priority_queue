#include "priority_queue.h"
#include <gtest/gtest.h>

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
    ASSERT_EQ(2, queue.top()) << "top item is largest of 1 and 2";
}

TEST(priority_queue, push_two_items_2_1) {
    priority_queue<int> queue(10);
    queue.push(2);
    queue.push(1);
    ASSERT_EQ(2, queue.size());
    ASSERT_EQ(2, queue.top()) << "top item is largest of 1 and 2";
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
    ASSERT_EQ(2, queue.top()) << "top item is largest of 1 and 2";
    queue.pop();
    ASSERT_EQ(1, queue.top()) << "top item is the only remaining item";
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, push_pop_replace_top_item) {
    priority_queue<int> queue(10);
    queue.push(1);
    queue.push(2);
    ASSERT_EQ(2, queue.top()) << "top item is largest of 1 and 2";
    queue.replace_top(0);
    ASSERT_EQ(1, queue.top()) << "top item is largest of 1 and 0";
    queue.pop();
    ASSERT_EQ(0, queue.top()) << "the only remaining item is 0";
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, populate_queue_from_collection) {
    priority_queue<int> queue(10);
    // shuffle the collection
    std::vector<int> collection = {1, 7, 3, 10, 5, 6, 2, 8, 9, 4};
    queue.populate_from_collection(collection.begin(), collection.end());
    ASSERT_EQ(10, queue.size());
    ASSERT_EQ(10, queue.top()) << "top item is largest";
}

TEST(priority_queue, populate_queue_from_large_collection) {
    priority_queue<int> queue(5); // keep 5 smallest elements
    // shuffle the collection
    std::vector<int> collection = {1, 7, 3, 9, 5, 6, 2, 8, 10, 4};
    queue.populate_from_collection(collection.begin(), collection.end());
    ASSERT_EQ(5, queue.size());
    ASSERT_EQ(5, queue.top()) << "keep 5 smallest elements, largest of them is 5";
    queue.pop();
    ASSERT_EQ(4, queue.size());
    ASSERT_EQ(4, queue.top()) << "second largest item is 4";
}

TEST(priority_queue, pop_randomized){
    priority_queue<int> queue(10);
    // shuffle the collection
    for (int x: {1, 7, 3, 10, 5, 6, 2, 8, 9, 4}) {
        queue.push(x);
    }
    ASSERT_EQ(10, queue.size());
    ASSERT_EQ(10, queue.top()) << "top item is largest";
    queue.pop();
    ASSERT_EQ(9, queue.size());
    ASSERT_EQ(9, queue.top()) << "second largest item is 9";
    queue.pop();
    ASSERT_EQ(8, queue.size());
    ASSERT_EQ(8, queue.top()) << "third largest item is 8";
    queue.pop();
    ASSERT_EQ(7, queue.size());
    ASSERT_EQ(7, queue.top()) << "fourth largest item is 7";
    queue.pop();
    ASSERT_EQ(6, queue.size());
    ASSERT_EQ(6, queue.top()) << "fifth largest item is 6";
    queue.pop();
    ASSERT_EQ(5, queue.size());
    ASSERT_EQ(5, queue.top()) << "sixth largest item is 5";
    queue.pop();
    ASSERT_EQ(4, queue.size());
    ASSERT_EQ(4, queue.top()) << "seventh largest item is 4";
    queue.pop();
    ASSERT_EQ(3, queue.size());
    ASSERT_EQ(3, queue.top()) << "eighth largest item is 3";
    queue.pop();
    ASSERT_EQ(2, queue.size());
    ASSERT_EQ(2, queue.top()) << "ninth largest item is 2";
    queue.pop();
    ASSERT_EQ(1, queue.size());
    ASSERT_EQ(1, queue.top()) << "tenth largest item is 1";
    queue.pop();
}

TEST(priority_queue, pop){
    priority_queue<int> queue(10);
    for (int i=1; i<=10; i++) {
        queue.push(i);
    }
    ASSERT_EQ(10, queue.size());
    ASSERT_EQ(10, queue.top()) << "top item is largest";
    queue.pop();
    ASSERT_EQ(9, queue.size());
    ASSERT_EQ(9, queue.top()) << "second largest item is 9";
    queue.pop();
    ASSERT_EQ(8, queue.size());
    ASSERT_EQ(8, queue.top()) << "third largest item is 8";
    queue.pop();
    ASSERT_EQ(7, queue.size());
    ASSERT_EQ(7, queue.top()) << "fourth largest item is 7";
    queue.pop();
    ASSERT_EQ(6, queue.size());
    ASSERT_EQ(6, queue.top()) << "fifth largest item is 6";
    queue.pop();
    ASSERT_EQ(5, queue.size());
    ASSERT_EQ(5, queue.top()) << "sixth largest item is 5";
    queue.pop();
    ASSERT_EQ(4, queue.size());
    ASSERT_EQ(4, queue.top()) << "seventh largest item is 4";
    queue.pop();
    ASSERT_EQ(3, queue.size());
    ASSERT_EQ(3, queue.top()) << "eighth largest item is 3";
    queue.pop();
    ASSERT_EQ(2, queue.size());
    ASSERT_EQ(2, queue.top()) << "ninth largest item is 2";
    queue.pop();
    ASSERT_EQ(1, queue.size());
    ASSERT_EQ(1, queue.top()) << "tenth largest item is 1";
}

TEST(priority_queue, populate_queue_from_empty_collection) {
    priority_queue<int> queue(10);
    // shuffle the collection
    std::vector<int> collection;
    queue.populate_from_collection(collection.begin(), collection.end());
    ASSERT_TRUE(queue.empty());
}

TEST(priority_queue, populate_queue_from_collection_with_duplicates) {
    priority_queue<int> queue(10);
    // shuffle the collection
    std::vector<int> collection = {1, 3, 10, 5, 6, 2, 8, 9, 4, 10};
    queue.populate_from_collection(collection.begin(), collection.end());
    ASSERT_EQ(10, queue.size());
    ASSERT_EQ(10, queue.top()) << "top item is largest";
    queue.pop();
    ASSERT_EQ(9, queue.size());
    ASSERT_EQ(10, queue.top()) << "second largest item is 10 too";
    queue.pop();
    ASSERT_EQ(8, queue.size());
    ASSERT_EQ(9, queue.top()) << "third largest item is 9";
}

TEST(priority_queue, try_push_one_item_to_empty_queue) {
    priority_queue<int> queue(10);
    queue.try_push(1);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), 1);
}

TEST(priority_queue, try_push_one_item_to_full_queue) {
    priority_queue<int> queue(1);
    queue.push(1);
    queue.try_push(2);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), 1);
}

TEST(priority_queue, try_push_one_item_to_full_queue_item_is_replaced) {
    priority_queue<int> queue(1);
    queue.push(2);
    queue.try_push(1);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), 1);
}

TEST(priority_queue, try_push_multiple_items) {
    // keep track of 3three smallest elements
    priority_queue<int> queue(3);
    queue.try_push(10);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), 10);
    queue.try_push(12);
    ASSERT_EQ(queue.size(), 2);
    ASSERT_EQ(queue.top(), 12);
    queue.try_push(14);
    ASSERT_EQ(queue.size(), 3);
    ASSERT_EQ(queue.top(), 14);

    queue.try_push(16);
    ASSERT_EQ(queue.size(), 3); // element 16 is ignored
    ASSERT_EQ(queue.top(), 14);

    queue.try_push(11);
    ASSERT_EQ(queue.size(), 3); // element 11 replace 14
    ASSERT_EQ(queue.top(), 12);

    queue.pop();
    ASSERT_EQ(queue.size(), 2);
    ASSERT_EQ(queue.top(), 11);

    queue.pop();
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), 10);
}