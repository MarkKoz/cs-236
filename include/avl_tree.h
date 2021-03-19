#ifndef CS_236_03_AVL_TREE_H
#define CS_236_03_AVL_TREE_H

#include "node.h"

template<typename T>
class avl_tree
{
public:
    template<typename... Args>
    void emplace(Args&&... args);

    void insert(const T& value);

    void insert(T&& value);

private:
    std::shared_ptr<node<T>>& balance();

    [[nodiscard]] std::size_t height(const std::shared_ptr<node<T>>& node) const;

    void insert_node(const std::shared_ptr<node<T>>& parent, std::unique_ptr<node<T>>& node);

    std::shared_ptr<node<T>>& rotate_left(std::shared_ptr<node<T>>& node);

    std::shared_ptr<node<T>>& rotate_left_right(std::shared_ptr<node<T>>& node);

    std::shared_ptr<node<T>>& rotate_right(std::shared_ptr<node<T>>& node);

    std::shared_ptr<node<T>>& rotate_right_left(std::shared_ptr<node<T>>& node);

    std::shared_ptr<node<T>> root_ = nullptr;
};

#include "avl_tree.cpp"

#endif
