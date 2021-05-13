#ifndef CS_236_06_IO_H
#define CS_236_06_IO_H

#include "graph.h"

#ifdef EXPERIMENTAL_FS
    #include <experimental/filesystem>
    namespace filesystem = std::experimental::filesystem;
#else
    #include <filesystem>
    namespace filesystem = std::filesystem;
#endif

#include <fstream>
#include <vector>

#define DEFAULT_PATH "res/network_file.txt"

/**
 * @brief Prompt for the path to the network file.
 *
 * Keep prompting until a valid path is given to an existing file.
 * If no path is given, default to @c DEFAULT_PATH.
 *
 * @return The path to the network file.
 */
filesystem::path get_file_path();

/**
 * @brief Prompt for one-based city index.
 *
 * Keep prompting until a valid integer is entered in the range 1 <= index <= max.
 *
 * @param max The maximum possible one-based city index (the lowest is 1).
 *
 * @return The one-based index for the city.
 */
std::size_t prompt_city(std::size_t max);

/**
 * @brief Prompt for whether to convert another input.
 *
 * Keep prompting for an input until a valid input ('y' or 'n', case-insensitive) is given.
 *
 * @return @c true to prompt again; @c false otherwise.
 */
bool prompt_retry();

/**
 * @brief Read a network file into a vector of vertices.
 *
 * Prompt for a file path. @see get_file_path
 *
 * @return A vector of vertices representing the weighted directed graph.
 */
std::vector<vertex> read_file();

/**
 * @brief Read the next two lines from a file and create a vertex.
 *
 * The first line should be the vertex's name. The second line should be a space-delimited sequence
 * of integers, where the first integer is the out-degree of that vertex and the subsequent integers
 * are indexes of neighbours.
 *
 * @param file The file stream from which to read the vertex data.
 * @return A vertex created from a pair of lines in the file.
 */
vertex read_vertex(std::ifstream& file);

#endif
