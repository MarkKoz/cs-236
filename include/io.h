#ifndef CS_236_06_IO_H
#define CS_236_06_IO_H

#include "graph.h"

#include <filesystem>
#include <fstream>
#include <vector>

std::filesystem::path get_file_path();

bool prompt_retry();

std::vector<vertex> read_file();

vertex read_vertex(std::ifstream& file);

#endif
