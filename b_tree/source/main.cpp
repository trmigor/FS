// Copyright [2020] <Taraimovych Igor>
#include <iostream>
#include "b_tree.hpp"

void help_message() {
    std::cout << "Commands:" << std::endl;
    std::cout << "  q" << std::endl;
    std::cout << "    - quits" << std::endl;
    std::cout << "  c <tree>" << std::endl;
    std::cout << "    - chooses current tree: 1 (default) or 2" << std::endl;
    std::cout << "  m" << std::endl;
    std::cout << "    - merges second tree to the first" << std::endl;
    std::cout << "  i <key> <value>" << std::endl;
    std::cout << "    - inserts key-value pair" << std::endl;
    std::cout << "  s <key>" << std::endl;
    std::cout << "    - searches value for given key" << std::endl;
    std::cout << "  r <key>" << std::endl;
    std::cout << "    - removes value for given key" << std::endl;
    std::cout << "  p" << std::endl;
    std::cout << "    - prints verbose structure of current tree" << std::endl;
}

int main() {
    help_message();
    char cmd;
    b_tree::b_tree<2, int64_t> a;
    b_tree::b_tree<2, int64_t> b;
    b_tree::b_tree<2, int64_t>* current = &a;
    while (std::cin >> cmd) {
        int64_t key;
        switch (cmd) {
            case 'c':
                int tree;
                std::cin >> tree;
                if (tree == 1) {
                    current = &a;
                }
                if (tree == 2) {
                    current = &b;
                }
                if (tree != 1 && tree != 2) {
                    std::cerr << "No such tree" << std::endl;
                }
                break;

            case 'm':
                a += b;
                break;

            case 'i':
                int64_t value;
                std::cin >> key >> value;
                try {
                    current->insert(key, value);
                } catch (std::out_of_range& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;

            case 's':
                std::cin >> key;
                int64_t result;
                try {
                    result = current->search(key);
                    std::cout << "Found: " << result << std::endl;
                } catch (std::out_of_range& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 'r':
                std::cin >> key;
                current->remove(key);
                break;

            case 'p':
                std::cout << "Current tree: " << (current == &a ? 1 : 2) <<
                    std::endl;
                current->print();
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
