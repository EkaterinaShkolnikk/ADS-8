// Copyright 2021 NNTU-CS
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;

    const char* filename = "src/war_peace.txt";
    makeTree(tree, filename);

    std::cout << "Tree depth: " << tree.depth() << std::endl;

    std::string testWord = "war";
    int count = tree.search(testWord);
    std::cout << "Word \"" << testWord << "\" appears " << count << " times." << std::endl;

    printFreq(tree);

    return 0;
}
