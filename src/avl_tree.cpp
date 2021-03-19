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
std::shared_ptr<node<T>>& avl_tree<T>::balance(std::shared_ptr<node<T>>& node)
{
    // Don't use the difference because that can lead to an overflow.
    auto left_height = height(node->left());
    auto right_height = height(node->right());

    if (left_height > right_height + 1) {
        // Left subtree is taller.
        auto left_left_height = height(node->left()->left());
        auto left_right_height = height(node->left()->right());

        if (left_left_height >= left_right_height) {
            return rotate_right(node);
        } else {
            return rotate_left_right(node);
        }
    } else if (right_height < left_height + 1) {
        // Right subtree is taller.
        auto right_left_height = height(node->right()->left());
        auto right_right_height = height(node->right()->right());

        if (right_right_height >= right_left_height) {
            return rotate_left(node);
        } else {
            return rotate_right_left(node);
        }
    } else {
        // Already balanced; heights don't differ by more than 1.
        return node;
    }
}

template<typename T>
std::size_t avl_tree<T>::height(const std::shared_ptr<node<T>>& node) const
{
    if (node == nullptr) {
        return 0;
    } else {
        std::size_t left_height = height(node->left());
        std::size_t right_height = height(node->right());

        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
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
