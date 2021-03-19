#ifndef CS_236_03_AVL_TREE_H
#define CS_236_03_AVL_TREE_H

#include <memory>

template<typename T>
class avl_tree
{
public:
    template<typename... Args>
    void emplace(Args&&... args);

    void insert(const T& value);

    void insert(T&& value);

private:
    struct node_t;
    typedef typename std::unique_ptr<node_t> node_ptr;

    struct node_t
    {
        explicit node_t(const T& value_) : value {value_} { }

        explicit node_t(T&& value_) : value {std::move(value_)} { }

        T value;
        node_ptr left;
        node_ptr right;
    };

    node_ptr& balance(node_ptr& node);

    [[nodiscard]] std::size_t height(const node_ptr& node) const;

    void insert_node(node_ptr& parent, node_ptr&& node);

    node_ptr& rotate_left(node_ptr& node);

    node_ptr& rotate_left_right(node_ptr& node);

    node_ptr& rotate_right(node_ptr& node);

    node_ptr& rotate_right_left(node_ptr& node);

    node_ptr root_ = nullptr;
};

#include "avl_tree.cpp"

#endif
