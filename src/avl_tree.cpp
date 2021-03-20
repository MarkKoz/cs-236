#include "avl_tree.h"

template<typename T>
template<typename... Args>
void avl_tree<T>::emplace(Args&&... args)
{
    auto node = std::make_unique<avl_tree<T>::node_t>(T(std::forward<Args>(args)...));

    if (!root_) {
        root_ = std::move(node);
    } else {
        insert_node(root_, std::move(node));
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
typename avl_tree<T>::node_ptr& avl_tree<T>::balance(node_ptr& node)
{
    // Don't use the difference because that can lead to an overflow.
    auto left_height = height(node->left);
    auto right_height = height(node->right);

    if (left_height > right_height + 1) {
        // Left subtree is taller.
        auto left_left_height = height(node->left->left);
        auto left_right_height = height(node->left->right);

        if (left_left_height >= left_right_height) {
            return rotate_right(node);
        } else {
            return rotate_left_right(node);
        }
    } else if (right_height > left_height + 1) {
        // Right subtree is taller.
        auto right_left_height = height(node->right->left);
        auto right_right_height = height(node->right->right);

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
std::size_t avl_tree<T>::height(const node_ptr& node) const
{
    if (node == nullptr) {
        return 0;
    } else {
        std::size_t left_height = height(node->left);
        std::size_t right_height = height(node->right);

        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

template<typename T>
void avl_tree<T>::insert_node(node_ptr& parent, node_ptr&& node)
{
    if (parent->value > node->value) {
        // Smaller values to the left.
        if (parent->left) {
            // The left node_t exists; start the search at the left node_t.
            insert_node(parent->left, std::move(node));
        } else {
            // The left node_t doesn't exist; found the free position.
            parent->left = std::move(node); // Inserts the node_t.
            parent = std::move(balance(parent));
        }
    } else if (parent->value < node->value) {
        // Larger go right.
        if (parent->right) {
            // The right node_t exists; start the search at the right node_t.
            insert_node(parent->right, std::move(node));
        } else {
            // The right node_t doesn't exist; found the free position.
            parent->right = std::move(node); // Inserts the node_t.
            parent = std::move(balance(parent));
        }
    } else {
        // Value is equal to the parent's value; no duplicates allowed.
        throw std::runtime_error("Cannot insert a duplicate value.");
    }
}

template<typename T>
typename avl_tree<T>::node_ptr& avl_tree<T>::rotate_left(node_ptr& node)
{
    auto& right = node->right;
    auto& right_left = right->left;

    right->left = std::move(node);
    node->right = std::move(right_left);

    return right;
}

template<typename T>
typename avl_tree<T>::node_ptr& avl_tree<T>::rotate_left_right(node_ptr& node)
{
    node->left = std::move(rotate_left(node->left));

    return rotate_right(node);
}

template<typename T>
typename avl_tree<T>::node_ptr& avl_tree<T>::rotate_right(node_ptr& node)
{
    auto& left = node->left;
    auto& left_right = left->right;

    left->right = std::move(node);
    node->left = std::move(left_right);

    return left;
}

template<typename T>
typename avl_tree<T>::node_ptr& avl_tree<T>::rotate_right_left(node_ptr& node)
{
    node->right = std::move(rotate_right(node->right));

    return rotate_left(node);
}
