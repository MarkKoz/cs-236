#include "rb_tree.h"

#include <sstream>

template<typename... Args>
std::string to_string(Args&&... args)
{
    std::ostringstream stream;
    (stream << ... << args);

    return stream.str();
}

template<typename T>
typename rb_tree<T>::box_t rb_tree<T>::build_tree_string(const rb_tree::node_t* node) const
{
    if (node == nullptr) {
        return {};
    }

    auto value = to_string(node->value);
    if (node->is_red) {
        value += "(R)";
    } else {
        value += "(B)";
    }

    std::string horizontal_branch;
    std::string vertical_branch;
    auto gap_size = value.size(); // Space between the left and right child's root values.

    // Get boxes of left and right subtrees.
    const auto left = build_tree_string(node->left.get());
    const auto right = build_tree_string(node->right.get());

    // Build branch lines for the left subtree.
    build_left_branch(left, gap_size, horizontal_branch, vertical_branch);

    const auto start = horizontal_branch.size(); // Start position of the root value.
    horizontal_branch += value; // Add the root value.
    const auto end = horizontal_branch.size() - 1; // End position of the root value.

    // Offset the right branch by the width of the root value.
    vertical_branch += std::string(value.size(), ' ');

    // Build the branch lines for the right subtree.
    build_right_branch(right, gap_size, horizontal_branch, vertical_branch);

    // Combine the branch lines with the left and right subtree boxes.
    std::vector<std::string> box {horizontal_branch, vertical_branch};
    combine_boxes(box, gap_size, left, right);

    return {box, horizontal_branch.size(), start, end};
}

template<typename T>
void rb_tree<T>::build_left_branch(
    const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const
{
    if (box.width > 0) {
        const auto root_centre = (box.root_start + box.root_end) / 2 + 1;
        // Pad with spaces and then fill with underscores from the root start until the centre.
        horizontal += std::string(root_centre + 1, ' ') + std::string(box.width - root_centre, '_');
        // Pad with spaces until the root centre, add the slash pointing to the child, and pad
        // with spaces until the line reaches the box's width.
        vertical += std::string(root_centre, ' ') + '/' + std::string(box.width - root_centre, ' ');
        gap++;
    }
}

template<typename T>
void rb_tree<T>::build_right_branch(
    const box_t& box, std::size_t& gap, std::string& horizontal, std::string& vertical) const
{
    if (box.width > 0) {
        const auto root_centre = (box.root_start + box.root_end) / 2;
        // Fill with underscores from the root centre until the root end and then pad with spaces.
        horizontal += std::string(root_centre, '_') + std::string(box.width - root_centre + 1, ' ');
        // Pad with spaces until the root centre, add the slash pointing to the child, and pad
        // with spaces until the line reaches the box's width.
        vertical +=
            std::string(root_centre, ' ') + '\\' + std::string(box.width - root_centre, ' ');
        gap++;
    }
}

template<typename T>
void rb_tree<T>::combine_boxes(
    rb_tree::box_lines& destination,
    const std::size_t gap_size,
    const rb_tree::box_t& left,
    const rb_tree::box_t& right) const
{
    const auto gap = std::string(gap_size, ' ');
    // Determine which of the two boxes has the most lines.
    const auto limit =
        left.lines.size() > right.lines.size() ? left.lines.size() : right.lines.size();

    // Merge corresponding line pairs from the left and right boxes, putting the gap between them.
    // If one element of the pair doesn't exist, use spaces equal to the box's width.
    // This ensures the all lines are the same width and that lone right child nodes are properly
    // indented to the right.
    for (std::size_t i = 0; i < limit; ++i) {
        auto line = i < left.lines.size() ? left.lines[i] : std::string(left.width, ' ');
        line += gap;
        line += i < right.lines.size() ? right.lines[i] : std::string(right.width, ' ');

        destination.push_back(line);
    }
}
