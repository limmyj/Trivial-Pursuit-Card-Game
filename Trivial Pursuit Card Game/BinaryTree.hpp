#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
using namespace std;

struct TreeNode {
    string name;
    double score;
    TreeNode* left;
    TreeNode* right;
};

class BinaryTree {
private:
    TreeNode* root;
    TreeNode* nodesList;
    int nodeCount;
    int currentIndex;

    TreeNode* buildTree(int index);
    void inOrder(TreeNode* node) const;
    void preOrder(TreeNode* node) const;
    void postOrder(TreeNode* node) const;
    bool search(TreeNode* node, const string& name) const;

public:
    BinaryTree();
    ~BinaryTree();
    void addNode(const string& name, double score);
    void buildTree();
    void displayInOrder() const;
    void displayPreOrder() const;
    void displayPostOrder() const;
    bool searchStudent(const string& name) const;
    void displayHierarchical() const;
};

#endif // BINARYTREE_H