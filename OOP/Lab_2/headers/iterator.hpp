#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "set.hpp"
#include <stdexcept>
#include <cstddef>

template <typename T>
class Iterator
{
private:
    Set<T>* container;
    std::size_t currentIndex;

public:
    Iterator(Set<T>& cont, std::size_t startIndex = 0)
        : container(&cont)
        , currentIndex(startIndex)
    {
    }

    T value() const
    {
        bool inRange = (currentIndex < container->length);
        if (!inRange)
            throw std::out_of_range("Iterator::value - out of range");
        return container->data[currentIndex];
    }

    Iterator& next()
    {
        bool canAdvance = (currentIndex < container->length);
        if (canAdvance)
            ++currentIndex;
        return *this;
    }

    bool is_end() const
    {
        bool flag = (currentIndex >= container->length);
        return flag;
    }

    T& operator*()
    {
        bool inRange = (currentIndex < container->length);
        if (!inRange)
            throw std::out_of_range("Iterator::operator* - out of range");
        return container->data[currentIndex];
    }

    T* operator->()
    {
        bool inRange = (currentIndex < container->length);
        if (!inRange)
            throw std::out_of_range("Iterator::operator-> - out of range");
        return &container->data[currentIndex];
    }

    Iterator& operator++()
    {
        next();
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp = *this;
        next();
        return tmp;
    }

    bool operator==(const Iterator& other) const
    {
        bool equal = (container == other.container)
        && (currentIndex == other.currentIndex);
        return equal;
    }

    bool operator!=(const Iterator& other) const
    {
        bool notEqual = !(*this == other);
        return notEqual;
    }
};

#endif // ITERATOR_HPP
