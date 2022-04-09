#include <vector>
#include <cassert>

template <typename T>

class priority_queue {
    size_t size = 0;
    size_t top_index = 0;
    size_t new_element_index = 0;
    std::vector<T> data;

public:
    priority_queue(size_t capacity) {
        data.reserve(capacity);
    }

    void push(T value) {
        assert(!is_full());
    }

    T pop() {
        assert(has_items());
    }

    const T& top() const {
        assert(has_items());
        return data[top_index];
    }

    void replace_top(T value) {
        assert(has_items());
    }

    bool empty() const {
        return size == 0;
    }

    bool has_items() const {
        return size > 0;
    }

    bool is_full() const {
        return size == data.capacity();
    }

    size_t size() const {
        return size;
    }

    size_t capacity() const {
        return data.capacity();
    }
};
