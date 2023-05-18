#ifndef FIXEDQUEUE_H
#define FIXEDQUEUE_H

#include <deque>

template<typename T, size_t N>
class FixedQueue {
private:
    std::deque<T> m_elements;
    size_t m_maxLength;

public:
    FixedQueue(): m_maxLength(N) {}

    void push(const T& value) {
        if (m_elements.size() >= m_maxLength) {
            pop();
        }
        m_elements.push_front(value);
    }

    void clear() {
        m_elements.clear();
    }

    size_t size() const {
        return m_elements.size();
    }

    const T& at(size_t n) const {
        return m_elements.at(n);
    }

    // Iterator support
    typename std::deque<T>::iterator begin() {
        return m_elements.begin();
    }

    typename std::deque<T>::const_iterator begin() const {
        return m_elements.begin();
    }

    typename std::deque<T>::iterator end() {
        return m_elements.end();
    }

    typename std::deque<T>::const_iterator end() const {
        return m_elements.end();
    }

private:
    void pop() {
        if (!m_elements.empty()) {
            m_elements.pop_back();
        }
    }
};

#endif // FIXEDQUEUE_H
