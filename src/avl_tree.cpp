#include "avl_tree.h"

template<typename T>
template<typename... Args>
void avl_tree<T>::emplace(Args&&... args)
{
    auto node = std::make_unique<::node<T>>(T(std::forward<Args>(args)...));

    if (!root_) {
        root_ = std::move(node);
    } else {
        insert_node(root_, node);
    }
}

template<typename T>
void avl_tree<T>::insert(const T& value)
{
    emplace(std::move(value));
}

template<typename T>
void avl_tree<T>::insert(T&& value)
{
    emplace(value);
}

template<typename T>
std::shared_ptr<node<T>>& avl_tree<T>::balance()
{
    return nullptr;
}

template<typename T>
unsigned avl_tree<T>::height() const
{
    return 0;
}

template<typename T>
void avl_tree<T>::insert_node(
    const std::shared_ptr<node<T>>& parent, std::unique_ptr<node<T>>& node)
{ }

template<typename T>
std::shared_ptr<node<T>>& avl_tree<T>::rotate_left(std::shared_ptr<node<T>>& node)
{
    auto& right = node->right();
    auto& right_left = right->left();

    right->set_left(node);
    node->set_right(right_left);

    return right;
}

template<typename T>
std::shared_ptr<node<T>>& avl_tree<T>::rotate_left_right(std::shared_ptr<node<T>>& node)
{
    node->set_left(rotate_left(node->left()));

    return rotate_right(node);
}

template<typename T>
std::shared_ptr<node<T>>& avl_tree<T>::rotate_right(std::shared_ptr<node<T>>& node)
{
    auto& left = node->left();
    auto& left_right = left->right();

    left->set_right(node);
    node->set_left(left_right);

    return left;
}

template<typename T>
std::shared_ptr<node<T>>& avl_tree<T>::rotate_right_left(std::shared_ptr<node<T>>& node)
{
    node->set_right(rotate_right(node->right()));

    return rotate_left(node);
}
