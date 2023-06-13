#pragma once

#define ITERABLE_ENUM_BEGIN(name) enum class name : int {
#define ITERABLE_ENUM_END ,end, begin = 0 }

template <class T>
class Iterable
{
public:
    Iterable(T value = T::begin) : mValue(value) {}
    Iterable(const Iterable& other) : mValue(other.mValue) {}

    Iterable& operator++()
    {
        assert(mValue >= T::begin && mValue < T::end);
        mValue = static_cast<T>(static_cast<int>(mValue) + 1);
        return *this;
    }

    Iterable operator++(int)
    {
        Iterable prev = *this;
        mValue = static_cast<T>(static_cast<int>(mValue) + 1);
        return prev;
    }

    Iterable& operator--()
    {
        assert(mValue >= T::end && mValue < T::begin);
        mValue = static_cast<T>(static_cast<int>(mValue) - 1);
        return *this;
    }

    Iterable operator--(int)
    {
        Iterable prev = *this;
        mValue = static_cast<T>(static_cast<int>(mValue) - 1);
        return prev;
    }

    Iterable operator+(int i)
    {
        return static_cast<T>(static_cast<int>(mValue) + i);
    }

    Iterable operator+(T i)
    {
        return static_cast<T>(static_cast<int>(mValue) + static_cast<int>(i));
    }

    Iterable operator-(int i)
    {
        return static_cast<T>(static_cast<int>(mValue) - i);
    }

    Iterable operator-(T i)
    {
        return static_cast<T>(static_cast<int>(mValue) - static_cast<int>(i));
    }


    bool operator >(const T& other) const
    {
        return static_cast<int>(mValue) > static_cast<int>(other);
    }

    bool operator >=(const T& other) const
    {
        return static_cast<int>(mValue) >= static_cast<int>(other);
    }

    bool operator <(const T& other) const
    {
        return static_cast<int>(mValue) < static_cast<int>(other);
    }

    bool operator <=(const T& other) const
    {
        return static_cast<int>(mValue) <= static_cast<int>(other);
    }

    bool operator ==(const T& other) const
    {
        return static_cast<int>(mValue) == static_cast<int>(other);
    }

    bool valid() const { return mValue != T::end; }

    operator T() const { return mValue; }
    operator T&() { return mValue; }
    T val() const { return mValue; }

private:
    T mValue;
};