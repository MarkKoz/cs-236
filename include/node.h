#ifndef CS_236_03_NODE_H
#define CS_236_03_NODE_H

#include <memory>

template<typename T>
class node
{
public:
    explicit node(const T& value);

    explicit node(T&& value);

    [[nodiscard]] T* value();

    [[nodiscard]] const T* value() const;

    [[nodiscard]] const std::shared_ptr<node<T>>& left() const;

    void set_left(std::unique_ptr<node<T>>&& child);

    [[nodiscard]] const std::shared_ptr<node<T>>& right() const;

    void set_right(std::unique_ptr<node<T>>&& child);

private:
    T data_;
    std::shared_ptr<node<T>> left_ = nullptr;
    std::shared_ptr<node<T>> right_ = nullptr;
};

#include "node.cpp"

#endif
