#include "io.h"

#include "graph.h"

#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

std::filesystem::path get_file_path()
{
    std::string path_string;
    std::filesystem::path path;

    std::cout << "Enter a relative or absolute path to a network file: ";
    while (true) {
        std::getline(std::cin, path_string);
        path = path_string;

        try {
            if (std::filesystem::exists(path)) {
                // Make it absolute and resolve symlinks.
                path = std::filesystem::canonical(path);

                // Canonical path doesn't necessarily exist.
                if (std::filesystem::exists(path)) {
                    if (std::filesystem::is_regular_file(path)) {
                        return path;
                    } else {
                        std::cerr << "Path does not point to a file, try again: ";
                    }
                } else {
                    std::cerr << "Path does not exist, try again: ";
                }
            } else {
                std::cerr << "Path does not exist, try again: ";
            }
        } catch (std::filesystem::filesystem_error& e) {
            std::cerr << e.what() << '\n';
            std::cerr << "Try again: ";
        }
    }
}

bool prompt_retry()
{
    std::string selection;

    std::cout << "More (y/n)? ";
    while (true) {
        std::cin >> std::ws >> selection;

        // Consume the rest of the line.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (selection == "y" || selection == "Y") {
            std::cout << '\n';
            return true;
        } else if (selection == "n" || selection == "N") {
            return false;
        } else {
            std::cerr << "Unknown value, try again: ";
        }
    }
}

std::vector<vertex> read_file()
{
    std::ifstream file(get_file_path());
    std::vector<vertex> vertices;

    while (file) {
        vertices.push_back(read_vertex(file));
    }

    return vertices;
}

vertex read_vertex(std::ifstream& file)
{
    vertex v;
    std::getline(file, v.name);

    // Read the out degree.
    std::size_t num = 0;
    file >> std::ws >> num;
    v.neighbours.reserve(num);

    // Read the neighbours.
    std::string neighbours_line;
    std::getline(file, neighbours_line);
    std::istringstream neighbours_ss(neighbours_line);

    while (neighbours_ss >> num) {
        v.neighbours.push_back(num);
    }

    return v;
}
