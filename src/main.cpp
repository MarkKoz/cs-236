#include "avl_tree.h"

#include <iostream>

/**
 * Represents a menu selection.
 */
typedef enum
{
    insert = 1,
    preorder = 2,
    inorder = 3,
    postorder = 4,
    end = 5,
} selection;

selection menu();

void insert_input(avl_tree<int>& tree);

int main()
{
    avl_tree<int> tree;
    selection selected = selection::end;

    do {
        selected = menu();

        switch (selected) {
            case selection::insert:
                insert_input(tree);
                std::cout << tree;
                break;
            case selection::inorder:
                std::cout << tree << '\n';
                tree.print_inorder();
                break;
            case selection::postorder:
                std::cout << tree << '\n';
                tree.print_postorder();
                break;
            case selection::preorder:
                std::cout << tree << '\n';
                tree.print_preorder();
                break;
            default:
                break;
        }

        std::cout << '\n';
    } while (selected != selection::end);

    return 0;
}

selection menu()
{
    std::cout << "--------------------------------------------------\n"
              << "                 AVL Tree Implementation\n"
              << "1: Insert an integer to tree and show the balanced tree at each insertion.\n"
              << "2: Display the balanced tree and show preorder traversal.\n"
              << "3: Display the balanced tree and show inorder traversal.\n"
              << "4: Display the balanced tree and show postorder traversal.\n"
              << "5: Exit\n\n"
              << "Enter a number to select a menu option: ";

    std::string input;

    while (true) {
        std::cin >> std::ws >> input;

        try {
            const int i = std::stoi(input);

            if (i < 1 || i > 5) {
                throw std::invalid_argument("The input is out of the valid range [1,5].");
            }

            return static_cast<selection>(i);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << " Try again: ";
        }
    }
}

void insert_input(avl_tree<int>& tree)
{
    std::string input;
    std::cout << "Enter integer to be added to tree: ";

    while (true) {
        std::cin >> std::ws >> input;

        try {
            const int i = std::stoi(input);
            tree.insert(i);
            std::cout << "Node(" << i << ") inserted.\n";

            return;
        } catch (std::invalid_argument& e) {
            std::cerr << "Invalid input. Try again: ";
        } catch (std::runtime_error& e) {
            std::cerr << e.what() << " Try again: ";
        }
    }
}
