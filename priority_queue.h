
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

    void push(T&& value) {
        assert(!is_full());
        m_data[m_new_element_index] = std::forward<T>(value);
        m_new_element_index++;
        m_size++;
        std::make_heap(m_data.data(), m_data.data() + m_size);
    }

    T pop() {
        assert(has_items());
        std::swap(m_data[0], m_data[m_size - 1]);
        m_size--;
        return std::move( m_data[m_size] );
    }

    const T& top() const {
        assert(has_items());
        return m_data[m_top_index];
    }

    void replace_top(T value) {
        assert(has_items());
        m_data[m_top_index] = std::move(value);
        std::make_heap(m_data.data(), m_data.data() + m_size);
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
