// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth  = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->value) return node;
        if (value < node->value) return search(node->left, value);
        return search(node->right, value);
    }

    void collectAll(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        collectAll(node->left, vec);
        vec.push_back({node->value, node->count});
        collectAll(node->right, vec);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}

    ~BST() { destroy(root); }

    void insert(const T& value) {
        root = insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int search(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }

    std::vector<std::pair<T, int>> getAllSortedByValue() const {
        std::vector<std::pair<T, int>> vec;
        collectAll(root, vec);
        return vec;
    }

    std::vector<std::pair<T, int>> getAllSortedByFreq() const {
        std::vector<std::pair<T, int>> vec;
        collectAll(root, vec);
        std::sort(vec.begin(), vec.end(),
            [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                return a.second > b.second;
            });
        return vec;
    }

    bool isEmpty() const { return root == nullptr; }
};

#endif  // INCLUDE_BST_H_
 
