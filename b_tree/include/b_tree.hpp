// Copyright [2020] <Taraimovych Igor>
#ifndef B_TREE_INCLUDE_B_TREE_HPP_
#define B_TREE_INCLUDE_B_TREE_HPP_

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace b_tree {

template <class T = int64_t>
struct __cell {
    typedef int64_t key_type;
    typedef T       value_type;

    key_type    key;
    value_type  value;
    bool        deleted;

    __cell() : key(0), value(value_type()), deleted(false) {}

    __cell(key_type key, value_type value) : key(key), value(value),
        deleted(false) {}

    __cell(const __cell& other) : key(other.key), value(other.value),
        deleted(other.deleted) {}

    __cell& operator=(const __cell& other) {
        key = other.key;
        value = other.value;
        deleted = other.deleted;
        return *this;
    }

    ~__cell() {}
};

template <size_t order = 2, class T = int64_t>
struct __b_node {
    typedef __b_node<order, T>  node;
    typedef __cell<T>   cell;
    typedef int64_t     key_type;
    typedef T           value_type;

    const size_t max_keys = 2 * order;
    const size_t max_child = 2 * order + 1;

    std::vector<cell>   cells;
    std::vector<node*>  children;

    node*   parent;
    size_t  key_count;
    size_t  child_count;
    bool    leaf;

    __b_node() : cells(std::vector<cell>(max_keys, cell())),
        children(std::vector<node*>(max_child, nullptr)),
        parent(nullptr), key_count(0), child_count(0), leaf(false) {}
    ~__b_node() {}
};

template <size_t order = 2, class T = int64_t>
class b_tree {
    public:
        typedef int64_t     key_type;
        typedef T           value_type;

        b_tree() {
            root_ = nullptr;
        }

        ~b_tree() {
            delete_node(root_);
        }

        void insert(key_type key, value_type value) {
            if (key == 0) {
                throw std::out_of_range("Not allowed to insert 0 as a key");
                return;
            }

            cell_& found = search_key(key, root_);
            if (key == found.key) {
                found.value = value;
                found.deleted = false;
                return;
            }

            if (root_ == nullptr) {
                root_ = new node_;
                root_->cells[0] = cell_(key, value);
                root_->key_count = 1;
                root_->leaf = true;
            } else {
                node_* ptr = root_;
                while (!ptr->leaf) {
                    for (size_t i = 0; i < max_keys_; ++i) {
                        if (ptr->cells[i].key == 0) {
                            break;
                        }
                        if (key < ptr->cells[i].key) {
                            ptr = ptr->children[i];
                            break;
                        }
                        if (ptr->cells[i + 1].key == 0 &&
                                key > ptr->cells[i].key) {
                            ptr = ptr->children[i + 1];
                            break;
                        }
                    }
                }
                insert_to_node(key, value, ptr);

                while (ptr->key_count == max_keys_) {
                    if (ptr == root_) {
                        restruct(ptr);
                        break;
                    }
                    node_* save = ptr->parent;
                    restruct(ptr);
                    ptr = save;
                }
            }
        }

        value_type search(key_type key) {
            cell_& found = search_key(key, root_);
            if (key != found.key || found.deleted) {
                throw std::out_of_range("No such key");
            }
            return found.value;
        }

        void remove(key_type key) {
            cell_& found = search_key(key, root_);
            if (key == found.key) {
                found.deleted = true;
            }
        }

        void print() {
            print_node(root_, 0);
        }

        b_tree& operator+=(const b_tree& other) {
            insert_all_nodes(other.root_);
            return *this;
        }

    private:
        typedef __b_node<order, T>  node_;
        typedef __cell<T>           cell_;

        const size_t max_keys_  = 2 * order;
        const size_t max_child_ = 2 * order + 1;

        node_* root_;

        void insert_all_nodes(node_* node) {
            if (node == nullptr) {
                return;
            }
            for (cell_ e : node->cells) {
                if (!e.deleted && e.key != 0) {
                    insert(e.key, e.value);
                }
            }
            for (node_* e : node->children) {
                insert_all_nodes(e);
            }
        }

        void delete_node(node_* node) {
            if (node == nullptr) {
                return;
            }
            for (size_t i = 0; i < max_child_; ++i) {
                delete_node(node->children[i]);
            }
            delete node;
        }

        void insert_to_node(key_type key, value_type value, node_* node) {
            node->cells[node->key_count] = cell_(key, value);
            ++node->key_count;
            sort_node(node);
        }

        void sort_node(node_* node) {
            auto begin = node->cells.begin();
            auto count = static_cast<ptrdiff_t>(node->key_count);
            std::sort(begin, begin + count, [](const cell_& a, const cell_& b) {
                return a.key < b.key;
            });
        }

        void restruct(node_* node) {
            if (node->key_count < max_keys_) {
                return;
            }

            node_* left = new node_;
            for (size_t i = 0; i < order - 1; ++i) {
                left->cells[i] = node->cells[i];
            }
            left->key_count = order - 1;

            if (node->child_count != 0) {
                for (size_t i = 0; i < order; ++i) {
                    left->children[i] = node->children[i];
                    left->children[i]->parent = left;
                }
                left->leaf = false;
                left->child_count = order - 1;
            } else {
                left->leaf = true;
                left->child_count = 0;
            }

            node_* right = new node_;
            for (size_t i = 0; i < order; ++i) {
                right->cells[i] = node->cells[i + order];
            }
            right->key_count = order;

            if (node->child_count != 0) {
                for (size_t i = 0; i <= order; ++i) {
                    right->children[i] = node->children[i + order];
                    right->children[i]->parent = right;
                }
                right->leaf = false;
                right->child_count = order;
            } else {
                right->leaf = true;
                right->child_count = 0;
            }

            if (node->parent == nullptr) {
                node->cells[0] = node->cells[order - 1];
                for (size_t i = 1; i < max_keys_; ++i) {
                    node->cells[i] = cell_();
                }
                node->children[0] = left;
                node->children[1] = right;
                for (size_t i = 2; i < max_child_; ++i) {
                    node->children[i] = nullptr;
                }
                node->leaf = false;
                node->key_count = 1;
                node->child_count = 2;
                left->parent = node;
                right->parent = node;
            } else {
                insert_to_node(node->cells[order - 1].key,
                    node->cells[order - 1].value, node->parent);
                for (size_t i = 0; i < max_child_; ++i) {
                    if (node->parent->children[i] == node) {
                        node->parent->children[i] = nullptr;
                    }
                }
                for (size_t i = 0; i < max_child_; ++i) {
                    if (node->parent->children[i] == nullptr) {
                        for (size_t j = max_child_ - 1; j > i + 1; --j) {
                            node->parent->children[j] =
                                node->parent->children[j - 1];
                        }
                        node->parent->children[i] = left;
                        node->parent->children[i + 1] = right;
                        break;
                    }
                }
                left->parent = node->parent;
                right->parent = node->parent;
                node->parent->leaf = false;
                delete node;
            }
        }

        cell_ error_cell_;
        cell_& search_key(key_type key, node_* node) {
            if (node == nullptr) {
                return error_cell_;
            }
            if (node->leaf) {
                for (size_t i = 0; i < max_keys_; ++i) {
                    if (key == node->cells[i].key) {
                        return node->cells[i];
                    }
                }
                return error_cell_;
            }
            size_t i;
            for (i = 0; i < max_keys_; ++i) {
                if (node->cells[i].key == 0) {
                    break;
                }
                if (key == node->cells[i].key) {
                    return node->cells[i];
                }
                if (key < node->cells[i].key) {
                    return search_key(key, node->children[i]);
                }
            }
            return search_key(key, node->children[i]);
        }

        void print_node(node_* node, size_t level) {
            if (node == nullptr) {
                return;
            }
            std::cout << "Level " << level << std::endl;
            std::cout << "Node " << reinterpret_cast<size_t>(node) << std::endl;
            std::cout << "Parent " << reinterpret_cast<size_t>(node->parent) <<
                std::endl;

            std::cout << "Keys:" << std::endl;
            for (cell_ e : node->cells) {
                std::cout << e.key << " ";
            }
            std::cout << std::endl;

            std::cout << "Values:" << std::endl;
            for (cell_ e : node->cells) {
                std::cout << e.value << " ";
            }
            std::cout << std::endl;

            std::cout << "Deleted:" << std::endl;
            for (cell_ e : node->cells) {
                std::cout << e.deleted << " ";
            }
            std::cout << std::endl;

            std::cout << "Children:" << std::endl;
            for (node_* e : node->children) {
                std::cout << reinterpret_cast<size_t>(e) << " ";
            }
            std::cout << std::endl;
            std::cout << std::endl;

            for (node_* e : node->children) {
                print_node(e, level + 1);
            }
        }
};

}  // namespace b_tree

#endif  // B_TREE_INCLUDE_B_TREE_HPP_
