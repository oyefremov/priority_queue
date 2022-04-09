
#pragma once

#include <vector>
#include <cassert>

template <typename T>
class priority_queue {
    std::vector<T> m_data;

    void make_heap_impl(){
        for (int i=size() / 2 - 1; i>=0; i--) {
            int largest_index = i;
            int left_child_index = 2*i + 1;
            int right_child_index = 2*i + 2;
            if (left_child_index < size() && m_data[left_child_index] > m_data[largest_index]) {
                largest_index = left_child_index;
            }
            if (right_child_index < size() && m_data[right_child_index] > m_data[largest_index]) {
                largest_index = right_child_index;
            }
            if (largest_index != i) {
                using std::swap;
                swap(m_data[i], m_data[largest_index]);
                propagate_heap_down(largest_index);
            }
        }
    }

    void propagate_heap_up(int i){
        while (i > 0) {
            int parent_index = (i - 1) / 2;
            if (m_data[i] > m_data[parent_index]) {
                using std::swap;
                swap(m_data[i], m_data[parent_index]);
                i = parent_index;
            } else {
                break;
            }
        }
    }

    void propagate_heap_down(int i){
        while (i < size()) {
            int largest_index = i;
            int left_child_index = 2*i + 1;
            int right_child_index = 2*i + 2;
            if (left_child_index < size() && m_data[left_child_index] > m_data[largest_index]) {
                largest_index = left_child_index;
            }
            if (right_child_index < size() && m_data[right_child_index] > m_data[largest_index]) {
                largest_index = right_child_index;
            }
            if (largest_index != i) {
                using std::swap;
                swap(m_data[i], m_data[largest_index]);
                i = largest_index;
            } else {
                break;
            }
        }
    }

public:
    priority_queue(size_t capacity) {
        m_data.reserve(capacity);
    }

    template<typename U>
    void push(U&& value) {
        assert(!is_full());
        m_data.push_back( std::forward<U>(value) );
        propagate_heap_up(size() - 1);
    }

    void pop() {
        assert(has_items());
        m_data.front() = std::move(m_data.back());
        m_data.pop_back();
        propagate_heap_down(0);
    }

    const T& top() const {
        assert(has_items());
        return m_data.front();
    }

    template<typename U>
    void replace_top(U&& value) {
        assert(has_items());
        m_data.front() = std::forward<U>(value);
        propagate_heap_down(0);
    }

    // Push new item is capacity allows it
    // When queue is full the new item will replace worst item in the collection
    // Worst item is the largest one
    template<typename U>
    void try_push(U&& value) {
        if (is_full()) {
            if (top() > value) {
                replace_top(std::forward<U>(value));
            }
        }else{
            push(std::forward<U>(value));
        }
    }

    // queue must be empty
    template<typename Iter>
    void populate_from_collection(Iter begin, Iter end) {
        assert(empty());
        size_t input_size = std::distance(begin, end);

        // First chunk of the input can fit in the queue
        auto first_chunk_size = std::min(input_size, capacity());
        m_data.assign(begin, begin + first_chunk_size);
        make_heap_impl();

        // Process the rest of the input
        // Keep only the largest items
        for (auto i = first_chunk_size; i < input_size; i++) {
            try_push(*(begin + i));
        }
    }

    bool empty() const {
        return m_data.empty();
    }

    bool has_items() const {
        return !empty();
    }

    bool is_full() const {
        return size() == capacity();
    }

    size_t size() const {
        return m_data.size();
    }

    size_t capacity() const {
        return m_data.capacity();
    }
};
