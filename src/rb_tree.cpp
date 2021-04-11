#include "rb_tree.h"

#include <stdexcept>

template<typename T>
template<typename... Args>
void rb_tree<T>::emplace(Args&&... args)
{
    auto node = std::make_unique<rb_tree<T>::node_t>(T(std::forward<Args>(args)...));

    if (!root_) {
        root_ = std::move(node);
    } else {
        insert_node(root_, std::move(node));
    }
}

template<typename T>
void rb_tree<T>::insert(const T& value)
{
    emplace(std::move(value));
}

template<typename T>
void rb_tree<T>::insert(T&& value)
{
    emplace(value);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const rb_tree<T>& tree)
{
    const auto result = tree.build_tree_string(tree.root_.get());
    for (const auto& line : result.lines) {
        stream << '\n' << line;
    }

    return stream;
}

template<typename T>
void rb_tree<T>::insert_node(node_ptr& parent, node_ptr&& node)
{
    if (parent->value > node->value) {
        // Smaller values to the left.
        if (parent->left) {
            // The left node_t exists; start the search at the left node.
            insert_node(parent->left, std::move(node));
        } else {
            // The left node_t doesn't exist; found the free position.
            parent->left = std::move(node); // Inserts the node_t.
        }
    } else if (parent->value < node->value) {
        // Larger go right.
        if (parent->right) {
            // The right node_t exists; start the search at the right node.
            insert_node(parent->right, std::move(node));
        } else {
            // The right node_t doesn't exist; found the free position.
            parent->right = std::move(node); // Inserts the node.
        }
    } else {
        // Value is equal to the parent's value; no duplicates allowed.
        throw std::runtime_error("Cannot insert a duplicate value.");
    }
}

template<typename T>
typename rb_tree<T>::node_ptr rb_tree<T>::rotate_left(node_ptr&& node)
{
    auto right = std::move(node->right);

    node->right = std::move(right->left);
    right->left = std::move(node);

    return right;
}

template<typename T>
typename rb_tree<T>::node_ptr rb_tree<T>::rotate_left_right(node_ptr&& node)
{
    if (node->left) {
        node->left = std::move(rotate_left(std::move(node->left)));
    }

    return rotate_right(std::move(node));
}

template<typename T>
typename rb_tree<T>::node_ptr rb_tree<T>::rotate_right(node_ptr&& node)
{
    auto left = std::move(node->left);

    node->left = std::move(left->right);
    left->right = std::move(node);

    return left;
}

template<typename T>
typename rb_tree<T>::node_ptr rb_tree<T>::rotate_right_left(node_ptr&& node)
{
    if (node->right) {
        node->right = std::move(rotate_right(std::move(node->right)));
    }

    return rotate_left(std::move(node));
}
