#include "rb_tree.h"

#include <cassert>
#include <stdexcept>

template<typename T>
template<typename... Args>
void rb_tree<T>::emplace(Args&&... args)
{
    auto node = std::make_unique<rb_tree<T>::node_t>(T(std::forward<Args>(args)...));

    if (!root_) {
        node->is_red = false; // Root should be black when the tree is empty.
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
typename rb_tree<T>::node_ptr rb_tree<T>::balance(
    rb_tree::node_t* parent, rb_tree::node_ptr&& grandparent)
{
    assert(parent != nullptr);
    if (!parent->is_red) {
        return std::move(grandparent); // Parent is black, so the children's colours don't matter.
    }

    // Determine which child was the inserted node.
    // It's impossible for both children to be red because the parent and the older child both being
    // red would be a violation that a previous balance would have fixed.
    typename node_ptr::pointer node = nullptr;
    if (parent->left && parent->left->is_red) {
        node = parent->left.get(); // The left node is red.
    } else if (parent->right && parent->right->is_red) {
        node = parent->right.get(); // The right node is red.
    } else {
        return std::move(grandparent); // parent is red but its children are black; already correct.
    }

    node_t* uncle = nullptr;
    node_ptr (rb_tree::*rotate_func)(node_ptr &&) = nullptr;

    // Determine the uncle and rotation function from the direction of the parent and node.
    if (parent == grandparent->left.get()) {
        // parent is the left child of grandparent.
        uncle = grandparent->right.get();

        if (node == parent->right.get()) {
            rotate_func = &rb_tree::rotate_left_right; // node is the right child of parent.
        } else {
            rotate_func = &rb_tree::rotate_right; // node is the left child of parent.
        }
    } else {
        // parent is the right child of grandparent.
        uncle = grandparent->left.get();

        if (node == parent->left.get()) {
            rotate_func = &rb_tree::rotate_right_left; // node is the left child of parent.
        } else {
            rotate_func = &rb_tree::rotate_left; // node is the right child of parent.
        }
    }

    // At this point, parent is red and node is red.
    if (uncle && uncle->is_red) {
        // parent is red and uncle is red; make them black.
        parent->is_red = false;
        uncle->is_red = false;
    } else {
        // uncle is black or null; rotation needed.
        grandparent->is_red = true;
        grandparent = (this->*rotate_func)(std::move(grandparent));
    }

    if (grandparent == root_) {
        grandparent->is_red = false; // Root node must never be red.
    } else {
        // Effectively set to red when uncle is red and set to black when a rotation is done.
        // For the latter case, keep in mind this is the new root rather than the original
        // i.e. `node` for double rotations or `parent` for single rotations.
        grandparent->is_red = !grandparent->is_red;
    }

    return std::move(grandparent);
}

template<typename T>
void rb_tree<T>::insert_node(node_ptr& parent, node_ptr&& node)
{
    if (parent->value > node->value) {
        // Smaller values to the left.
        if (parent->left) {
            // The left node_t exists; start the search at the left node.
            insert_node(parent->left, std::move(node));
            parent = balance(parent->left.get(), std::move(parent));
        } else {
            // The left node_t doesn't exist; found the free position.
            parent->left = std::move(node); // Insert the node_t.
        }
    } else if (parent->value < node->value) {
        // Larger go right.
        if (parent->right) {
            // The right node_t exists; start the search at the right node.
            insert_node(parent->right, std::move(node));
            parent = balance(parent->right.get(), std::move(parent));
        } else {
            // The right node_t doesn't exist; found the free position.
            parent->right = std::move(node); // Insert the node.
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
