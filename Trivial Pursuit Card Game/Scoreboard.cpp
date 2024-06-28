#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_BinaryTree.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

BinaryTree::BinaryTree() {
	root = nullptr;
	nodeCount = 0;
	currentIndex = 0;
	nodesList = new TreeNode[30]; // Allocate space for top 30 nodes
}

BinaryTree::~BinaryTree() {
	delete[] nodesList;
}

void BinaryTree::addNode(const string& name, double score) {
	if (currentIndex < 30) {
		nodesList[currentIndex].name = name;
		nodesList[currentIndex].score = score;
		currentIndex++;
		nodeCount = currentIndex;
	}
}

void BinaryTree::buildTree() {
	root = buildTree(0);
}

TreeNode* BinaryTree::buildTree(int index) {
	if (index >= nodeCount) return nullptr;

	TreeNode* newNode = new TreeNode;
	newNode->name = nodesList[index].name;
	newNode->score = nodesList[index].score;

	// Build the left and right subtrees based on the described hierarchical structure
	newNode->right = (2 * index + 1 < nodeCount) ? buildTree(2 * index + 1) : nullptr; // Second highest score
	newNode->left = (2 * index + 2 < nodeCount) ? buildTree(2 * index + 2) : nullptr; // Third highest score

	return newNode;
}

void BinaryTree::displayHierarchical() const {
	if (!root) return;

	const int MAX_NODES = 100; // Assuming a maximum of 100 nodes for simplicity
	TreeNode* queue[MAX_NODES];
	int start = 0, end = 0;

	queue[end++] = root;

	int level = 0;
	while (start < end) {
		int levelSize = end - start;
		cout << "Level " << level << ": ";
		for (int i = 0; i < levelSize; ++i) {
			TreeNode* currentNode = queue[start++];
			cout << currentNode->name << "(" << currentNode->score << ") ";
			if (currentNode->left) queue[end++] = currentNode->left;
			if (currentNode->right) queue[end++] = currentNode->right;

			if (i < levelSize - 1) cout << " - ";
		}
		cout << endl;
		level++;
	}
}

void BinaryTree::displayInOrder() const {
	inOrder(root);
}

void BinaryTree::displayPreOrder() const {
	preOrder(root);
}

void BinaryTree::displayPostOrder() const {
	postOrder(root);
}

void BinaryTree::inOrder(TreeNode* node) const {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->name << ": " << node->score << endl;
		inOrder(node->right);
	}
}

void BinaryTree::preOrder(TreeNode* node) const {
	if (node != nullptr) {
		cout << node->name << ": " << node->score << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void BinaryTree::postOrder(TreeNode* node) const {
	if (node != nullptr) {
		postOrder(node->left);
		postOrder(node->right);
		cout << node->name << ": " << node->score << endl;
	}
}

/*bool BinaryTree::searchStudent(const string& name) const {
	return search(root, name);
}

bool BinaryTree::search(TreeNode* node, const string& name) const {
	if (node == nullptr) return false;
	if (node->name == name) return true;
	return search(node->left, name) || search(node->right, name);
}*/

/*#include <iostream>
using namespace std;

struct treenode {
	string data;
	double weight;
	treenode* left;
	treenode* right;
};

class BinaryTree {
	treenode* root;
	int size;
	string treelistname;
	treenode* listnode;
	int i = 0;
public:
	BinaryTree(string treelistname) {
		root = NULL;
		size = 0;
		this->treelistname = treelistname;
		listnode = new treenode[50];
	}
	void addNewNode(string data, double weight) {
		listnode[i].data = data;
		listnode[i].weight = weight;
		i++;
		size = i;
	}
	void buildtree() {
		root = buildtree(0);
		delete[] listnode;
	}
	void preOrder() {
		preOrder(root);
	}
	void postOrder() {
		postOrder(root);
	}
	void inOrder() {
		inOrder(root);
	}
	int getSize() {
		return size;
	}
	int HeightofTree() {
		return HeightofTree(root);
	}
	double Sum() {
		return Sum(root);
	}
	int findNodeAmountInTree() {
		return findNodeAmountInTree(root);
	}
private:
	void preOrder(treenode* root) {
		if (root != NULL) {
			cout << root->data << ", ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	treenode* buildtree(int index) {
		treenode* newnode = nullptr;
		if (listnode[index].data != "") {
			newnode = new treenode;
			newnode->data = listnode[index].data;
			newnode->weight = listnode[index].weight;
			newnode->left = buildtree(2*index+1); //(2*0+1) =>5
			newnode->right = buildtree(2 * index + 1); // =>9
		}
		return newnode;
	}
	void postOrder(treenode* root) {
		if (root != NULL) {
			postOrder(root->left);
			postOrder(root->right);
			cout << root->data << ", ";
		}
	}
	void inOrder(treenode* root) {
		if (root != NULL) {
			inOrder(root->left);
			cout << root->data << ", ";
			inOrder(root->right);
		}
	}
	int HeightofTree(treenode* currentnode) {
		if (currentnode != NULL) {
			return 1 + max(HeightofTree(currentnode->left), HeightofTree(currentnode->right));
		}
		return 0;
	}
	double Sum(treenode* currentnode) {
		if (currentnode != nullptr) {
			return currentnode->weight + Sum(currentnode->left) + Sum(currentnode->right);
		}
		return 0;
	}
	int findNodeAmountInTree(treenode* currentnode) {
		if (currentnode != NULL) {
			return 1 + findNodeAmountInTree(currentnode->left)
				+ findNodeAmountInTree(currentnode->right);
		}
		return 0;
	}
};*/