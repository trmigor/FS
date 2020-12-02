// Copyright [2020] <Taraimovych Igor>
#include <iostream>
#include "b_tree.hpp"

void help_message() {
    std::cout << "Commands:" << std::endl;
    std::cout << "  q" << std::endl;
    std::cout << "    - quits" << std::endl;
    std::cout << "  i <key> <value>" << std::endl;
    std::cout << "    - inserts key-value pair" << std::endl;
    std::cout << "  s <key>" << std::endl;
    std::cout << "    - searches value for given key" << std::endl;
    std::cout << "  r <key>" << std::endl;
    std::cout << "    - removes value for given key" << std::endl;
    std::cout << "  p" << std::endl;
    std::cout << "    - prints verbose structure of B-tree" << std::endl;
}

int main() {
    help_message();
    char cmd;
    b_tree::b_tree<2, int64_t> a;
    while (std::cin >> cmd) {
        int64_t key;
        switch (cmd) {
            case 'i':
                int64_t value;
                std::cin >> key >> value;
                try {
                    a.insert(key, value);
                } catch (std::out_of_range& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;

            case 's':
                std::cin >> key;
                int64_t result;
                try {
                    result = a.search(key);
                    std::cout << "Found: " << result << std::endl;
                } catch (std::out_of_range& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 'r':
                std::cin >> key;
                a.remove(key);
                break;

            case 'p':
                a.print();
                break;

            case 'q':
                exit(EXIT_SUCCESS);

            default:
                std::cerr << "Unknown command" << std::endl;
                help_message();
        }
    }
    return EXIT_SUCCESS;
}
