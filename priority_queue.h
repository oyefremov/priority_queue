
#pragma once

#include <vector>
#include <cassert>
#include <algorithm>

template <typename T>
class priority_queue {
    size_t m_size = 0;
    size_t m_top_index = 0;
    size_t m_new_element_index = 0;
    std::vector<T> m_data;

public:
    priority_queue(size_t capacity) {
        m_data.resize(capacity);
    }

    template<typename U>
    void push(U&& value) {
        assert(!is_full());
        m_data[m_new_element_index] = std::forward<U>(value);
        m_new_element_index++;
        m_size++;
        std::make_heap(m_data.data(), m_data.data() + m_size);
    }

    T pop() {
        assert(has_items());
        std::swap(m_data[0], m_data[m_size - 1]);
        m_size--;
        std::make_heap(m_data.data(), m_data.data() + m_size);
        return std::move( m_data[m_size] );
    }

    const T& top() const {
        assert(has_items());
        return m_data[m_top_index];
    }

    template<typename U>
    void replace_top(U&& value) {
        assert(has_items());
        m_data[m_top_index] = std::forward<U>(value);
        std::make_heap(m_data.data(), m_data.data() + m_size);
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
        std::make_heap(m_data.data(), m_data.data() + m_size);

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
