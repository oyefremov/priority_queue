
#pragma once

#include <vector>
#include <cassert>

template <typename T>
class priority_queue {
    size_t m_size = 0;
    std::vector<T> m_data;

    void make_heap_impl(){
        
        for (int i=m_size / 2 - 1; i>=0; i--) {
            int largest_index = i;
            int left_child_index = 2*i + 1;
            int right_child_index = 2*i + 2;
            if (left_child_index < m_size && m_data[left_child_index] > m_data[largest_index]) {
                largest_index = left_child_index;
            }
            if (right_child_index < m_size && m_data[right_child_index] > m_data[largest_index]) {
                largest_index = right_child_index;
            }
            if (largest_index != i) {
                std::swap(m_data[i], m_data[largest_index]);
            }
        }
    }

public:
    priority_queue(size_t capacity) {
        m_data.resize(capacity);
    }

    template<typename U>
    void push(U&& value) {
        assert(!is_full());
        m_data[m_size] = std::forward<U>(value);
        m_size++;
        make_heap_impl();
    }

    T pop() {
        assert(has_items());
        std::swap(m_data[0], m_data[m_size - 1]);
        m_size--;
        make_heap_impl();
        return std::move( m_data[m_size] );
    }

    const T& top() const {
        assert(has_items());
        return m_data[0];
    }

    template<typename U>
    void replace_top(U&& value) {
        assert(has_items());
        m_data[0] = std::forward<U>(value);
        make_heap_impl();
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
        m_size = first_chunk_size;
        make_heap_impl();

        // Process the rest of the input
        // Keep only the largest items
        for (auto i = first_chunk_size; i < input_size; i++) {
            try_push(*(begin + i));
        }
    }

    bool empty() const {
        return m_size == 0;
    }

    bool has_items() const {
        return m_size > 0;
    }

    bool is_full() const {
        return m_size == m_data.capacity();
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_data.capacity();
    }
};
