#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <iomanip>
#include "RedBlackTreeNode.h"

using namespace std;

class RedBlackTree {
private:
    RedBlackTreeNode* root; // highest node

    // recursively search for node
    RedBlackTreeNode* searchHelper(RedBlackTreeNode* curr, const int target) const {
        if ((curr == RedBlackTreeNode::nil) || (curr->data == target))
            return curr; // stop on nil or target
        if (target < curr->data)
            return searchHelper(curr->left, target); // search left subtree
        return searchHelper(curr->right, target); // search right subtree
    }
    // recursively print node, its left, and then right
    void preOrderTraverseHelper(RedBlackTreeNode* curr) const {
        if (curr != RedBlackTreeNode::nil) { // base case
            cout << curr->data;
            if (curr->color == BLACK) {
                cout << "(B) ";
            } else {
                cout << "(R) ";
            }
            preOrderTraverseHelper(curr->left); // traverse left
            preOrderTraverseHelper(curr->right); // traverse right
        }
    }
    // recursively print left, right, and then node
    void postOrderTraverseHelper(RedBlackTreeNode* curr) const {
        if (curr != RedBlackTreeNode::nil) { // base case
            postOrderTraverseHelper(curr->left); // traverse left
            postOrderTraverseHelper(curr->right); // traverse right
            cout << curr->data;
            if (curr->color == BLACK) {
                cout << "(B) ";
            } else {
                cout << "(R) ";
            }
        }
    }
    // recursively print left, node, and then right
    void inOrderTraverseHelper(RedBlackTreeNode* curr) const {
        if (curr != RedBlackTreeNode::nil) { // base case 
            inOrderTraverseHelper(curr->left); // traverse left
            cout << curr->data;
            if (curr->color == BLACK) {
                cout << "(B) ";
            } else {
                cout << "(R) ";
            }
            inOrderTraverseHelper(curr->right); // traverse right
        }
    }
    // right-rotate subtree at node-a
    void rotateRight(RedBlackTreeNode* a) {
        RedBlackTreeNode* b = a->left;
        a->left = b->right; // swap children
        if (b->right != RedBlackTreeNode::nil)
            b->right->parent = a;
        // attach a's parent to b
        b->parent = a->parent;
        if (a->parent == nullptr) { // a is root
            this->root = b; 
        } else if ((a->parent->left) == a) { // a is left child
            a->parent->left = b;
        } else { // a is right child
            a->parent->right = b;
        }
        // drop a to b's left
        a->parent = b;
        b->right = a;
    }
    // left-rotate subtree at node-a
    void rotateLeft(RedBlackTreeNode* a) {
        RedBlackTreeNode* b = a->right;
        a->right = b->left; // swap children
        if (b->left != RedBlackTreeNode::nil)
            b->left->parent = a;
        // attach a's parent to b
        b->parent = a->parent;
        if (a->parent == nullptr) { // a is root
            root = b; 
        } else if ((a->parent->left) == a) { // a is left child
            a->parent->left = b;
        } else { // a is right child
            a->parent->right = b;
        }
        // drop a to b's left
        a->parent = b;
        b->left = a;
    }
    // link parent of deleted node to its child
    void transplant(RedBlackTreeNode* a, RedBlackTreeNode* b) {
        if (a == root) { // x is root
            this->root = b;
        } else if (a == (a->parent->left)) { // x is left child
            a->parent->left = b;
        } else { // x is right child
            a->parent->right = b;
        }
        // link parent pointers
        b->parent = a->parent;
    }
    // find min value in tree
    RedBlackTreeNode* min(RedBlackTreeNode* curr) {
        while (curr->left != RedBlackTreeNode::nil) {
			curr = curr->left; // move left if not nil
        }
        // return if found, else nil
        return curr;
    }
    // fixes violations from delete function
    void fixDeletion(RedBlackTreeNode* deletedNode) {
        // temp variables
        RedBlackTreeNode* siblingNode, *parentNode;
        parentNode = deletedNode->parent;

        // check tree for violations
		while ((deletedNode != root) && (deletedNode->color == BLACK)) {
			if (deletedNode == parentNode->left) { // deletedNode is left child
				siblingNode = parentNode->right;
				if (siblingNode->color == RED) { // case 1 (sibling is red)
                    parentNode->color = RED;
					siblingNode->color = BLACK;
                    // rebalance tree
					rotateLeft(parentNode);
					siblingNode = parentNode->right;
				}
				if ((siblingNode->right->color == BLACK) && (siblingNode->left->color == BLACK)) {
                    // case 2 (sibling's children are black)
					deletedNode = parentNode;
                    siblingNode->color = RED;
				} else if (siblingNode->right->color == BLACK) { // case 3 (sibling's right is black)
                    siblingNode->color = RED;
                    siblingNode->left->color = BLACK;
                    rotateRight(siblingNode);
                    siblingNode = parentNode->right;
				} else { // case 4 (sibling is black and sibling's right is red)
					siblingNode->color = parentNode->color;
					parentNode->color = BLACK;
					siblingNode->right->color = BLACK;
					rotateLeft(parentNode);
					deletedNode = root;
				}
			} else {  // deletedNode is right child
				siblingNode = parentNode->left;
				if (siblingNode->color == RED) { // case 1 (sibling is red)
					siblingNode->color = BLACK;
					parentNode->color = RED;
					rotateRight(parentNode);
					siblingNode = parentNode->left;
				}
				if (siblingNode->right->color == BLACK && siblingNode->left->color == BLACK) {
					// case 2 (sibling's children are black)
					siblingNode->color = RED;
					deletedNode = parentNode;
				} else if (siblingNode->left->color == BLACK) { // case 3 (sibling's right is black)
                    siblingNode->right->color = BLACK;
                    siblingNode->color = RED;
                    rotateLeft(siblingNode);
                    siblingNode = parentNode->left;
				} else { // case 4 (sibling is black and sibling's right is red)
					siblingNode->color = parentNode->color;
					siblingNode->left->color = BLACK;
                    parentNode->color = BLACK;
					rotateRight(parentNode);
					deletedNode = root;
				}
			} 
		}
        // set deleted node's color to black
		deletedNode->color = BLACK;
	}
    // delete a node
    void deleteNodeHelper(const int target) {
		RedBlackTreeNode* nodeToDelete = search(target);
        // node wasn't found
		if (nodeToDelete == RedBlackTreeNode::nil) {  
			cout << "Value to delete is not in the tree" << endl;
			return;
		} 
        // temp variables
		RedBlackTreeNode* childNode;
        RedBlackTreeNode* replacementNode = nodeToDelete;
		int replacementOriginColor = replacementNode->color;
        // rebalance tree based on node's children
		if (nodeToDelete->right == RedBlackTreeNode::nil) { // check if right child
			childNode = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
		} else if (nodeToDelete->left == RedBlackTreeNode::nil) { // check if left child
            childNode = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
		} else { // no children (leaf and/or root)
            // min node in right subtree replaces deleted node 
			replacementNode = min(nodeToDelete->right);
			childNode = replacementNode->right;
			replacementOriginColor = replacementNode->color;
            // replacement is child of node
			if (replacementNode->parent == nodeToDelete) {
				childNode->parent = replacementNode;
			} else { // replacement is not child of node
				transplant(replacementNode, replacementNode->right);
				replacementNode->right = nodeToDelete->right;
				replacementNode->right->parent = replacementNode;
			}
            transplant(nodeToDelete, replacementNode);
            replacementNode->color = nodeToDelete->color;
            // link parent to deleted, pointers updated
            replacementNode->left = nodeToDelete->left;
            replacementNode->left->parent = replacementNode;
		}
		delete nodeToDelete;
		if (replacementOriginColor == BLACK)
			fixDeletion(childNode);
	}
    // fix invalid tree after insertion
    void fixInsertion(RedBlackTreeNode* nodeToInsert){
        // temp variables
        RedBlackTreeNode* uncleNode, *parentNode, *gpNode;
        parentNode = nodeToInsert->parent;
        gpNode = nodeToInsert->parent->parent;

        // parent is RED
		while (parentNode->color != BLACK) {
			if (parentNode == gpNode->left) {
				uncleNode = gpNode->right; // uncle
                if (uncleNode->color == RED) { // uncle = red, flip colors
                    uncleNode->color = BLACK;
                    parentNode->color = BLACK;
                    gpNode->color = RED;
                    nodeToInsert = gpNode; // set node to gp
                } else { // uncle = black
                    // update/rotate according to nodes' positions
                    if (nodeToInsert == parentNode->right) { // left
                        nodeToInsert = parentNode;
                        rotateLeft(nodeToInsert);
                    }
                    parentNode->color = BLACK;
                    gpNode->color = RED;
                    rotateRight(gpNode);
                }
			} else {
				uncleNode = gpNode->left; // uncle
                if (uncleNode->color == RED) { // uncle = red, flip colors
                    uncleNode->color = BLACK;
                    parentNode->color = BLACK;
                    gpNode->color = RED;
                    nodeToInsert = gpNode; // set node to gp
                } else { // uncle = black
                    // update/rotate according to nodes' positions
                    if (nodeToInsert == parentNode->left) { // left
                        nodeToInsert = parentNode; 
                        rotateRight(nodeToInsert);
                    }
                    parentNode->color = BLACK;
                    gpNode->color = RED;
                    rotateLeft(gpNode);
                }
			}
			if (nodeToInsert == root)
				break;
		}
		root->color = BLACK;
	}
    // insert node object to tree
    void insertHelper(RedBlackTreeNode* curr, const int data) {
        //  temp variables
        RedBlackTreeNode* nodeToInsert = new RedBlackTreeNode(data, RED);
        RedBlackTreeNode* parentNode = nullptr;
        RedBlackTreeNode* traversalNode = curr;

        // finds nodeToInsert's insertion position
        while (traversalNode != RedBlackTreeNode::nil) {
            parentNode = traversalNode;
            if (nodeToInsert->data < traversalNode->data) {
                traversalNode = traversalNode->left;
            } else {
                traversalNode = traversalNode->right;
            }
        }

        // y is parent of x
        nodeToInsert->parent = parentNode;
        if (parentNode == nullptr) { // node is root
            this->root = nodeToInsert;
        } else if (nodeToInsert->data < parentNode->data) { // node < parent
            parentNode->left = nodeToInsert;
        } else {
            parentNode->right = nodeToInsert;
        }

        // return if node is root
        if (nodeToInsert->parent == nullptr){
            nodeToInsert->color = BLACK;
            return;
        }

        // return if gparent is null
        if (nodeToInsert->parent->parent == nullptr)
            return;
        // fix the tree after insertion
        fixInsertion(nodeToInsert);
    }
    // recursively deletes all nodes in tree
    void destructorHelper(RedBlackTreeNode* curr) {
        if (curr->parent == nullptr) // root node
            root = RedBlackTreeNode::nil;
        if (curr == RedBlackTreeNode::nil)
            return;
        destructorHelper(curr->left);
        destructorHelper(curr->right);
        delete curr;
    }
    // create deep copy of nodes
    RedBlackTreeNode* nodeCopy(const RedBlackTreeNode* other) {
        if(other == RedBlackTreeNode::nil) // base case
            return RedBlackTreeNode::nil;
        RedBlackTreeNode* tempNode = new RedBlackTreeNode(*other); // copy constructor
        tempNode->left = nodeCopy(other->left); // recursive calls
        tempNode->right = nodeCopy(other->right);
        return tempNode;
    }
    // print helper
    void printHelper(RedBlackTreeNode* curr, int spacing) const { 
        if (curr == RedBlackTreeNode::nil) // base case
            return;
        printHelper(curr->right, spacing + 4); // print right

        // create spacing between nodes
        cout << setw(spacing) << " ";
        // mark nodes by their color
        cout << curr->data;
        if (curr->color == BLACK) {
            cout << "B" << endl;
        } else {
            cout << "R" << endl;
        }

        printHelper(curr->left, spacing + 4);
    }

public:
    // constructor
    RedBlackTree() {
        root = RedBlackTreeNode::nil;
    }
    // function declarations
    RedBlackTreeNode* search(int target) const;
    // traversal
    void preOrderTraverse() const;
    void postOrderTraverse() const;
    void inOrderTraverse() const;
    // deletion/insertion
    void insert(const int data);
    void deleteNode(const int target);
    // special members
    RedBlackTree(const RedBlackTree& other); // copy constructor
    RedBlackTree& operator=(const RedBlackTree& other); // assignment operator
    ~RedBlackTree(); // destructor
    // print
    void print() const; // (pre-order)
    RedBlackTreeNode* getRoot() const {
        return this->root;
    }
};
#endif // REDBLACKTREE_H
