/*
    Copyright [2020] <Taraimovych Igor>
*/

#include <unistd.h>
#include <iostream>
#include <vector>

#include "ps.hpp"

int main(void) {
    std::vector<ps::Process> res;
    res = ps::getAllProcesses();

    std::cout.width(8);
    std::cout << "PID" << " ";
    std::cout.width(7);
    std::cout << "TTY" << " ";
    std::cout.width(4);
    std::cout << "STAT" << " ";
    std::cout.width(6);
    std::cout << "TIME" << " ";
    std::cout << "COMMAND" << std::endl;

    for (auto e : res) {
        std::cout.width(8);
        std::cout << e.pid << " ";
        std::cout.width(7);
        std::cout << e.getTty() << " ";
        std::cout.width(4);
        std::cout << e.state << " ";
        int64_t time = (e.utime + e.stime) / sysconf(_SC_CLK_TCK);
        int64_t minutes = time / 60;
        int64_t seconds = time % 60;
        std::cout.width(4);
        std::cout << minutes << ":";
        std::cout << (seconds < 10 ? "0" : "");
        std::cout << seconds << " ";
        std::cout << e.getCommand() << std::endl;
    }

    return EXIT_SUCCESS;
}
