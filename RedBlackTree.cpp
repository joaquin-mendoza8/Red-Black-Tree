#include <iostream>
#include "RedBlackTreeNode.h"
#include "RedBlackTree.h"

// searches for a node in tree and returns the node
RedBlackTreeNode* RedBlackTree::search(int target) const { 
    cout << "\n(Searching for key ~" << target << "~)" << endl;
    return RedBlackTree::searchHelper(this->root, target); 
}
// traversal functions
void RedBlackTree::preOrderTraverse() const { RedBlackTree::preOrderTraverseHelper(this->root); }
void RedBlackTree::postOrderTraverse() const { RedBlackTree::postOrderTraverseHelper(this->root); }
void RedBlackTree::inOrderTraverse() const { RedBlackTree::inOrderTraverseHelper(this->root); }
// deletion/insertion functions
void RedBlackTree::deleteNode(int target) { 
    cout << "\n(Deleting " << target << " from tree)" << endl;
    RedBlackTree::deleteNodeHelper(target); 
    cout << "\n------------MODIFIED TREE------------\n" << endl;
    printHelper(this->root, 0);
    cout << "\n-------------------------------------\n" << endl;
}
void RedBlackTree::insert(int data) { 
    cout << "\n(Inserting " << data << " into tree)" << endl;
    RedBlackTree::insertHelper(this->root, data); 
    cout << "\n------------MODIFIED TREE------------\n" << endl;
    printHelper(this->root, 0);
    cout << "\n-------------------------------------\n" << endl;

}
// copy constructor
RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    this->root = RedBlackTreeNode::nil;
    this->root = RedBlackTree::nodeCopy(other.root);
}
// assignment operator
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    if (&other == this)
        return *this;
    // clear current tree
    this->RedBlackTree::~RedBlackTree();

    // call recursive tree copier 
    root = RedBlackTree::nodeCopy(other.root);
    return *this;
}
// destructor
RedBlackTree::~RedBlackTree() { RedBlackTree::destructorHelper(this->root); } 
// print tree (pre-order)
void RedBlackTree::print() const {
    cout << "\n------------TREE CONTENTS------------\n" << endl;
    printHelper(this->root, 0);
    cout << "\n-------------------------------------\n" << endl;
}
