// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"
 
void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string word;
  while (!file.eof()) {
    int ch = file.get();
    if (file.eof()) break;
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      if (ch >= 'A' && ch <= 'Z') ch += ('a' - 'A');
      word += static_cast<char>(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}
 
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq = tree.getAllSortedByFreq();
  for (const auto& p : freq) {
    std::cout << p.first << " - " << p.second << "\n";
  }
  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot write result/freq.txt" << std::endl;
    return;
  }
  for (const auto& p : freq) {
    out << p.first << " - " << p.second << "\n";
  }
  out.close();
}
