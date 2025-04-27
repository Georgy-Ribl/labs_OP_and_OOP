#ifndef SET_HPP
#define SET_HPP

#include <stdexcept>
#include <initializer_list>
#include <cstddef>

template <typename T>
class Iterator;

template <typename T>
class Set
{
private:
    T* data;
    std::size_t length;
    std::size_t capacity;

    void reallocate(std::size_t newCapacity)
    {
        bool need = newCapacity > capacity;
        if (need)
        {
            T* newData = new T[newCapacity];
            for (std::size_t i = 0; i < length; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

    bool contains(const T& value) const
    {
        bool found = false;
        for (std::size_t i = 0; i < length; ++i)
        {
            if (data[i] == value)
            {
                found = true;
                break;
            }
        }
        return found;
    }

public:
    friend class Iterator<T>;

    Set()
        : data(nullptr)
        , length(0)
        , capacity(0)
    {
        reallocate(1);
    }

    Set(std::initializer_list<T> initList)
        : data(nullptr)
        , length(0)
        , capacity(0)
    {
        reallocate(initList.size());
        for (const auto& elem : initList)
            insert(elem);
    }

    Set(const Set<T>& other)
        : data(new T[other.capacity])
        , length(other.length)
        , capacity(other.capacity)
    {
        for (std::size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    Set<T>& operator=(const Set<T>& other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            length   = other.length;
            data     = new T[capacity];
            for (std::size_t i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~Set()
    {
        delete[] data;
    }

    void insert(const T& value)
    {
        if (!contains(value))
        {
            if (length >= capacity)
                reallocate(capacity * 2);
            data[length++] = value;
        }
    }

    void pushBack(const T& value)
    {
        insert(value);
    }

    std::size_t getLength() const
    {
        return length;
    }

    T& at(std::size_t index)
    {
        bool ok = index < length;
        if (!ok)
            throw std::out_of_range("Set::at - index out of range");
        return data[index];
    }

    T& operator[](std::size_t index)
    {
        return at(index);
    }

    void clear()
    {
        length = 0;
    }

    friend Set<T> operator+(const Set<T>& s1, const Set<T>& s2)
    {
        Set<T> result(s1);
        for (std::size_t i = 0; i < s2.length; ++i)
            result.insert(s2.data[i]);
        return result;
    }

    friend Set<T> operator-(const Set<T>& s1, const Set<T>& s2)
    {
        Set<T> result;
        result.reallocate(s1.length);
        for (std::size_t i = 0; i < s1.length; ++i)
        {
            if (!s2.contains(s1.data[i]))
                result.insert(s1.data[i]);
        }
        return result;
    }

    friend Set<T> operator*(const Set<T>& s1, const Set<T>& s2)
    {
        Set<T> result;
        std::size_t minCap = (s1.length < s2.length ? s1.length : s2.length);
        result.reallocate(minCap);
        for (std::size_t i = 0; i < s1.length; ++i)
            if (s2.contains(s1.data[i]))
                result.insert(s1.data[i]);
        return result;
    }

    friend bool operator==(const Set<T>& s1, const Set<T>& s2)
    {
        bool equal = true;
        if (s1.length != s2.length)
            equal = false;
        else
            for (std::size_t i = 0; i < s1.length; ++i)
                if (!s2.contains(s1.data[i]))
                {
                    equal = false;
                    break;
                }
        return equal;
    }

    friend bool operator!=(const Set<T>& s1, const Set<T>& s2)
    {
        bool notEqual = !(s1 == s2);
        return notEqual;
    }
};

#endif // SET_HPP
