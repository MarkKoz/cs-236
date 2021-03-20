#ifndef CS_236_03_AVL_TREE_H
#define CS_236_03_AVL_TREE_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

template<typename T>
class avl_tree
{
public:
    template<typename... Args>
    void emplace(Args&&... args);

    void insert(const T& value);

    void insert(T&& value);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& stream, const avl_tree<U>& tree);

private:
    struct node_t;
    typedef typename std::unique_ptr<node_t> node_ptr;
    typedef typename std::vector<std::string> box_lines;

    struct node_t
    {
        explicit node_t(const T& value_) : value {value_} { }

        explicit node_t(T&& value_) : value {std::move(value_)} { }

        T value;
        node_ptr left;
        node_ptr right;
    };

    struct box_t
    {
        box_lines lines;
        std::size_t width = 0;
        std::size_t root_start = 0;
        std::size_t root_end = 0;
    };

    node_ptr balance(node_ptr&& node);

    void build_left_branch(
        const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const;

    void build_right_branch(
        const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const;

    [[nodiscard]] box_t build_tree_string(const node_t* root_pos) const;

    void combine_boxes(
        box_lines& destination,
        const std::size_t gap_size,
        const box_t& left,
        const box_t& right) const;

    [[nodiscard]] std::size_t height(const node_t* node) const;

    void insert_node(node_ptr& parent, node_ptr&& node);

    node_ptr rotate_left(node_ptr&& node);

    node_ptr rotate_left_right(node_ptr&& node);

    node_ptr rotate_right(node_ptr&& node);

    node_ptr rotate_right_left(node_ptr&& node);

    node_ptr root_ = nullptr;
};

#include "avl_tree.cpp"
#include "tree_format.cpp"

#endif
