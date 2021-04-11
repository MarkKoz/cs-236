#ifndef CS_236_04_RB_TREE_H
#define CS_236_04_RB_TREE_H

#include <memory>

/**
 * @brief Red-black tree: a self-balancing binary search tree.
 *
 * @tparam T The type of the values stored in the tree's nodes.
 */
template<typename T>
class rb_tree
{
public:
    /**
     * @brief Insert a new node into the tree by constructing it in-place.
     *
     * Perform no copy or move operations on the node. Call the constructor of the node with
     * exactly the same arguments as supplied to this function.
     *
     * @tparam Args The types of the arguments.
     * @param args The arguments to forward to the node's constructor.
     *
     * @raise std::runtime_error The value of @c node already exists in a node in the tree.
     */
    template<typename... Args>
    void emplace(Args&&... args);

    /**
     * @brief Insert a new node into the tree as a copy of @c value.
     *
     * @param value The value of the node to insert.
     *
     * @raise std::runtime_error The value of @c node already exists in a node in the tree.
     */
    void insert(const T& value);

    /**
     * @brief Insert a new node into the tree by moving @c value.
     *
     * @param value The value of the node to insert.
     *
     * @raise std::runtime_error The value of @c node already exists in a node in the tree.
     */
    void insert(T&& value);

private:
    struct node_t;
    typedef typename std::unique_ptr<node_t> node_ptr;

    /**
     * @brief A binary tree node.
     *
     * Contains the value, a pointer to the lef child, and a pointer to the right child.
     */
    struct node_t
    {
        /**
         * @brief Construct a new node with a copy of @c value_.
         *
         * @param value_ The value to store in the node.
         */
        explicit node_t(const T& value_) : value {value_} { }

        /**
         * @brief Construct a new node by moving @c value_.
         *
         * @param value_ The value to store in the node.
         */
        explicit node_t(T&& value_) : value {std::move(value_)} { }

        /**
         * @brief The node's value.
         */
        T value;

        /**
         * @brief The node's left child.
         */
        node_ptr left;

        /**
         * @brief The node's right child.
         */
        node_ptr right;
    };

    /**
     * @brief Insert a node intro the tree and then balance the tree.
     *
     * Recursively find the position at which to insert @c node depending on the evaluation of the
     * comparison of its value against the value of @c parent. Smaller values go left and larger
     * values go right.
     *
     * If the appropriate child of the parent is not empty, recursively search starting at that
     * child. Otherwise, insert @c node into the empty position.
     *
     * @param parent The node at which to begin the search.
     * @param node The node to insert.
     *
     * @raise std::runtime_error The value of @c node already exists in a node in the tree.
     */
    void insert_node(node_ptr& parent, node_ptr&& node);

    /**
     * @brief Rotate the root of a subtree left around its right child.
     *
     * @param node The root node of the subtree to rotate.
     *
     * @return The root of the rotated subtree.
     */
    node_ptr rotate_left(node_ptr&& node);

    /**
     * @brief Rotate the left child of a subtree left and then rotate the new subtree's parent
     * right.
     *
     * @param node The root node of the subtree to rotate.
     *
     * @return The root of the rotated subtree.
     */
    node_ptr rotate_left_right(node_ptr&& node);

    /**
     * @brief Rotate the root of a subtree right around its left child.
     *
     * @param node The root node of the subtree to rotate.
     *
     * @return The root of the rotated subtree.
     */
    node_ptr rotate_right(node_ptr&& node);

    /**
     * @brief Rotate the right child of a subtree right and then rotate the new subtree's parent
     * left.
     *
     * @param node The root node of the subtree to rotate.
     *
     * @return The root of the rotated subtree.
     */
    node_ptr rotate_right_left(node_ptr&& node);

    /**
     * @brief The root node of the tree.
     */
    node_ptr root_ = nullptr;
};

// This is indeed strange to see, but it allows the definitions of the templated object to be
// separate from its declarations. These files must not be listed as sources for CMake; the goal
// is to make the compiler think these definitions were in the header file all along.
#include "rb_tree.cpp"

#endif
