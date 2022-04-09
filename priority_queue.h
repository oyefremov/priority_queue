
#pragma once

#include <vector>
#include <cassert>

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

    void push(T value) {
        assert(!is_full());
        m_data[m_new_element_index] = value;
        m_new_element_index++;
        m_size++;
    }

    T pop() {
        assert(has_items());
    }

    const T& top() const {
        assert(has_items());
        return m_data[m_top_index];
    }

    void replace_top(T value) {
        assert(has_items());
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
