#include "rb_tree.h"

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
void rb_tree<T>::insert_node(node_ptr& parent, node_ptr&& node)
{
    if (parent->value > node->value) {
        // Smaller values to the left.
        if (parent->left) {
            // The left node_t exists; start the search at the left node.
            insert_node(parent->left, std::move(node));

            auto& grandparent = parent;
            const auto parent_ = grandparent->left.get();
            const auto uncle = grandparent->right.get();

            if (parent_ && parent_->is_red) { // P is red
                typename node_ptr::pointer node_ = nullptr;
                if (parent_->left && parent_->left->is_red) {
                    node_ = parent_->left.get(); // The left node is red.
                } else if (parent_->right && parent_->right->is_red) {
                    node_ = parent_->right.get(); // The right node is red.
                }

                if (node_ != nullptr) { // At least one of P's children is also red.
                    if (uncle && uncle->is_red) {
                        // P is red and U is red; make them black and make G red.
                        parent_->is_red = false;
                        uncle->is_red = false;
                        if (grandparent != root_) {
                            grandparent->is_red = true;
                        }
                    } else { // P is red but U is black or null; rotation needed.
                        if (node_ == parent_->right.get()) {
                            // N is the right child of P and P is the left child of G.
                            grandparent->is_red = true;
                            node_->is_red = false;
                            grandparent = rotate_left_right(std::move(grandparent));
                        } else {
                            // N is the left child of P and P is the left child of G.
                            parent_->is_red = false;
                            grandparent->is_red = true;
                            grandparent = rotate_right(std::move(grandparent));
                        }
                    }
                } else {
                    // P is red but its children are black, so it's all correct.
                }
            } else {
                // P is black, so it doesn't matter what colour its children are.
            }
        } else {
            // The left node_t doesn't exist; found the free position.
            parent->left = std::move(node); // Inserts the node_t.
        }
    } else if (parent->value < node->value) {
        // Larger go right.
        if (parent->right) {
            // The right node_t exists; start the search at the right node.
            insert_node(parent->right, std::move(node));

            auto& grandparent = parent;
            const auto parent_ = grandparent->right.get();
            const auto uncle = grandparent->left.get();

            if (parent_ && parent_->is_red) { // P is red
                typename node_ptr::pointer node_ = nullptr;
                if (parent_->left && parent_->left->is_red) {
                    node_ = parent_->left.get(); // The left node is red.
                } else if (parent_->right && parent_->right->is_red) {
                    node_ = parent_->right.get(); // The right node is red.
                }

                if (node_ != nullptr) { // At least one of P's children is also red.
                    if (uncle && uncle->is_red) {
                        // P is red and U is red; make them black and make G red.
                        parent_->is_red = false;
                        uncle->is_red = false;
                        if (grandparent != root_) {
                            grandparent->is_red = true;
                        }
                    } else { // P is red but U is black or null; rotation needed.
                        if (node_ == parent_->left.get()) {
                            // N is the left child of P and P is the right child of G.
                            grandparent->is_red = true;
                            node_->is_red = false;
                            grandparent = rotate_right_left(std::move(grandparent));
                        } else {
                            // N is the right child of P and P is the right child of G.
                            parent_->is_red = false;
                            grandparent->is_red = true;
                            grandparent = rotate_left(std::move(grandparent));
                        }
                    }
                } else {
                    // P is red but its children are black, so it's all correct.
                }
            } else {
                // P is black, so it doesn't matter what colour its children are.
            }
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
