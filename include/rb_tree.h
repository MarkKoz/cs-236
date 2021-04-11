#ifndef CS_236_04_RB_TREE_H
#define CS_236_04_RB_TREE_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

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

    /**
     * @brief Stream insertion operator.
     *
     * Insert a string representation of the tree into the stream.
     *
     * @tparam U The type of the values of the nodes.
     * @param stream The output stream in which to insert the tree.
     * @param tree The tree to insert.
     *
     * @return The given output stream.
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& stream, const rb_tree<U>& tree);

private:
    struct node_t;
    typedef typename std::unique_ptr<node_t> node_ptr;
    typedef typename std::vector<std::string> box_lines;

    /**
     * @brief A binary tree node.
     *
     * Contains the value, a pointer to the left child, a pointer to the right child, and a boolean
     * for whether the node is red or black. The node is red by default.
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

        /**
         * @brief @c true if the node is red; @c false if the node is black.
         */
        bool is_red = true;
    };

    /**
     * @brief A "box" of characters represent a binary sub-tree.
     *
     * It's a "box" because all lines have same length, which is @c width. It is used to build a
     * string representation of the tree.
     */
    struct box_t
    {
        /**
         * @brief The string lines representing the sub-tree. They are all the same width.
         *
         * The first line contains the horizontal branch, including the root node's value.
         * The second line contains the vertical branch, which are characters pointing towards the
         * children. Any subsequent lines are the same as above but for the children.
         */
        box_lines lines;

        /**
         * @brief The width of all @c lines.
         */
        std::size_t width = 0;

        /**
         * @brief The index to the first character of the root node's value.
         *
         * This is an index into the first line in @c lines.
         */
        std::size_t root_start = 0;

        /**
         * @brief The index to the last character of the root node's value.
         *
         * This is an index into the first line in @c lines.
         */
        std::size_t root_end = 0;
    };

    /**
     * @brief Balance and/or recolour a sub-tree within which a new node was just inserted.
     *
     * @param parent The parent node of the node that was just inserted.
     * @param grandparent The parent node of @c parent.
     *
     * @return The root node of the balanced sub-tree.
     */
    node_ptr balance(node_t* parent, node_ptr&& grandparent);

    /**
     * @brief Build horizontal and vertical branch strings connecting a parent to its left child.
     *
     * Store the results directly in @c horizontal and @c vertical (they're references.).
     *
     * @param box The box for the left child.
     * @param gap The size of the gap between the root nodes of the left child and its sibling.
     * @param horizontal The line of the horizontal branch from the parent to @c vertical.
     * @param vertical The line of the vertical branch from @c horizontal to the left child.
     */
    void build_left_branch(
        const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const;

    /**
     * @brief Build horizontal and vertical branch strings connecting a parent to its right child.
     *
     * Store the results directly in @c horizontal and @c vertical (they're references.).
     *
     * @param box The box for the left child.
     * @param gap The size of the gap between the root nodes of the right child and its sibling.
     * @param horizontal The line of the horizontal branch from the parent to @c vertical.
     * @param vertical The line of the vertical branch from @c horizontal to the right child.
     */
    void build_right_branch(
        const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const;

    /**
     * @brief Recursively build a list of strings representing the tree rooted at @c node.
     *
     * Perform a recursive breadth-first search to build strings representing each level of the
     * tree from the bottom to the top. Each branch has its own "box" to represent it, which is
     * basically a list of lines of equal length (achieved by padding with spaces). Combine the
     * boxes of the children to form the box of the parent. See the documentation of @c node_t for
     * more details.
     *
     * The algorithm was adapted from the Python package "binarytree".
     *
     * @param node The root node of the tree from which to build a string.
     *
     * @return The @c box_t for the root node, containing a list of strings representing the entire
     *         tree.
     */
    [[nodiscard]] box_t build_tree_string(const node_t* node) const;

    void combine_boxes(
        box_lines& destination,
        const std::size_t gap_size,
        const box_t& left,
        const box_t& right) const;

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
#include "tree_format.cpp"

#endif
