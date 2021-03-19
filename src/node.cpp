#include "node.h"

template<typename T>
node<T>::node(const T& value) : data_ {value} { }

template<typename T>
node<T>::node(T&& value) : data_ {std::move(value)} { }

template<typename T>
T* node<T>::value()
{
    return &data_;
}

template<typename T>
const T* node<T>::value() const
{
    return &data_;
}

template<typename T>
const std::shared_ptr<node<T>>& node<T>::left() const
{
    return left_;
}

template<typename T>
void node<T>::set_left(std::unique_ptr<node<T>>&& child)
{
    left_ = std::move(child);
}

template<typename T>
const std::shared_ptr<node<T>>& node<T>::right() const
{
    return right_;
}

template<typename T>
void node<T>::set_right(std::unique_ptr<node<T>>&& child)
{
    right_ = std::move(child);
}
