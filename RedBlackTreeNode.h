#ifndef REDBLACKTREENODE_H
#define REDBLACKTREENODE_H
#include <cstddef>

// enumeration of color
enum ColorType { RED, BLACK };

// RBT node class
class RedBlackTreeNode {
    friend class RedBlackTree;

private:
    int data;
    ColorType color;
    RedBlackTreeNode* parent;
    RedBlackTreeNode* left;
    RedBlackTreeNode* right;
    static RedBlackTreeNode* nil; // sentinel node
public:
    // default constructor
    RedBlackTreeNode() : data(0), color(RED), left(nil), right(nil), parent(nullptr){}
    // explicit constructor
    RedBlackTreeNode(int tData, ColorType Color, RedBlackTreeNode* tLeft = nil, \
                    RedBlackTreeNode* tRight = nil, RedBlackTreeNode* tParent = nullptr) \
        :data(tData), left(tLeft), right(tRight), parent(tParent), color(Color)
    {}
    // set this's children to other's children
    void copyChildren(const RedBlackTreeNode& other) {
        if (other.left != nil) {
            this->left = new RedBlackTreeNode(*other.left);
            this->left->parent = this;
        }
        if (other.right != nil) {
            this->right = new RedBlackTreeNode(*other.right);
            this->right->parent = this;
        }
    }
    // copy constructor
    RedBlackTreeNode(const RedBlackTreeNode& other) {
        this->~RedBlackTreeNode();
        this->data = other.data;
        this->color = other.color;
        this->copyChildren(other);
    }
    // accessors 
    inline int getData() const { return this->data; }
    inline ColorType getColor() const { return this->color; }
    //mutators
    inline void setData(int data) { this->data = data; }
    inline void setColor(ColorType color) { this->color = color; }
};

// initialize nil node
RedBlackTreeNode* RedBlackTreeNode::nil = new RedBlackTreeNode(0, BLACK, nullptr, nullptr, nullptr);
#endif // REDBLACKTREENODE_H