#include "avl_tree.h"

#include <stdexcept>

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
std::ostream& operator<<(std::ostream& stream, const avl_tree<T>& tree)
{
    const auto result = tree.build_tree_string(tree.root_.get());
    for (const auto& line : result.lines) {
        stream << '\n' << line;
    }

    return stream;
}

template<typename T>
typename avl_tree<T>::node_ptr avl_tree<T>::balance(node_ptr&& node)
{
    // Don't use the difference because that can lead to an overflow.
    const auto left_height = height(node->left.get());
    const auto right_height = height(node->right.get());

    if (left_height > right_height + 1) {
        // Left subtree is taller.
        const auto left_left_height = height(node->left->left.get());
        const auto left_right_height = height(node->left->right.get());

        if (left_left_height >= left_right_height) {
            return rotate_right(std::move(node));
        } else {
            return rotate_left_right(std::move(node));
        }
    } else if (right_height > left_height + 1) {
        // Right subtree is taller.
        const auto right_left_height = height(node->right->left.get());
        const auto right_right_height = height(node->right->right.get());

        if (right_right_height >= right_left_height) {
            return rotate_left(std::move(node));
        } else {
            return rotate_right_left(std::move(node));
        }
    } else {
        // Already balanced; heights don't differ by more than 1.
        return std::move(node);
    }
}

// Passing a raw pointer is more convenient cause, unlike a reference,
// it doesn't need to be null-checked before being passed.
template<typename T>
std::size_t avl_tree<T>::height(const node_t* node) const
{
    if (node == nullptr) {
        return 0;
    } else {
        const auto left_height = height(node->left.get());
        const auto right_height = height(node->right.get());

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
        }
    } else if (parent->value < node->value) {
        // Larger go right.
        if (parent->right) {
            // The right node_t exists; start the search at the right node_t.
            insert_node(parent->right, std::move(node));
        } else {
            // The right node_t doesn't exist; found the free position.
            parent->right = std::move(node); // Inserts the node_t.
        }
    } else {
        // Value is equal to the parent's value; no duplicates allowed.
        throw std::runtime_error("Cannot insert a duplicate value.");
    }

    parent = balance(std::move(parent));
}

template<typename T>
typename avl_tree<T>::node_ptr avl_tree<T>::rotate_left(node_ptr&& node)
{
    auto right = std::move(node->right);

    node->right = std::move(right->left);
    right->left = std::move(node);

    return right;
}

template<typename T>
typename avl_tree<T>::node_ptr avl_tree<T>::rotate_left_right(node_ptr&& node)
{
    if (node->left) {
        node->left = std::move(rotate_left(std::move(node->left)));
    }

    return rotate_right(std::move(node));
}

template<typename T>
typename avl_tree<T>::node_ptr avl_tree<T>::rotate_right(node_ptr&& node)
{
    auto left = std::move(node->left);

    node->left = std::move(left->right);
    left->right = std::move(node);

    return left;
}

template<typename T>
typename avl_tree<T>::node_ptr avl_tree<T>::rotate_right_left(node_ptr&& node)
{
    if (node->right) {
        node->right = std::move(rotate_right(std::move(node->right)));
    }

    return rotate_left(std::move(node));
}
