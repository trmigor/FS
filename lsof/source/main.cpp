/*
    Copyright [2020] <Taraimovych Igor>
*/

#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>

#include "ps.hpp"

namespace fs = std::filesystem;

int main(void) {
    std::vector<ps::Process> res;
    res = ps::getAllProcesses();

    std::list<std::pair<int32_t, std::list<std::string> > > files;

    for (auto e : res) {
        std::list<std::string> proc_files;
        std::string path = "/proc/" + std::to_string(e.pid) + "/map_files";
        for (const auto& entry : fs::directory_iterator(path)) {
            std::string link = entry.path();
            char buffer[256];
            ssize_t count = readlink(link.c_str(), buffer, 255);
            buffer[count] = '\0';
            proc_files.push_back(buffer);
        }
        proc_files.unique();
        files.push_back(
            std::pair<int32_t, std::list<std::string> >(e.pid, proc_files));
    }

    for (auto e : files) {
        std::cout << "PID: " << e.first << std::endl;
        for (auto f : e.second) {
            std::cout << f << std::endl;
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
