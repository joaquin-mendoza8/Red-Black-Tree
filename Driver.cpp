#include <iostream>
#include <ctime>
#include "RedBlackTreeNode.h"
#include "RedBlackTree.h"
#include "RedBlackTree.cpp"

using namespace std;

// method for validating user input
void validate_input(int& input, const string& prompt) {
    cout << prompt;
    bool flag = false;
    do {
        cin >> input;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter only integers" << endl;
            cout << prompt;
        } else {
            flag = true;
        }
    } while(!flag);
    // clear remaining input from the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    RedBlackTree* rb1 = new RedBlackTree();

    // function testing
    cout << "------------------------" << endl;
    cout << "RED BLACK TREE FUNCTIONS" << endl;
    cout << "------------------------" << endl << endl;
    rb1->insert(2); // insertion
    rb1->insert(1);
    rb1->insert(3);
    rb1->insert(4);
    rb1->insert(5);
    rb1->deleteNode(1);  // deletion
    cout << "\n(Copy Constructor -- rb2 = rb1)\n" << endl; // copy constructor
    RedBlackTree* rb2 = new RedBlackTree(*rb1);
    rb2->print();
    RedBlackTree* rb3 = rb1;
    cout << "\n(Assignment Operator -- rb3 = rb1)\n" << endl; // assignment operator
    rb3->print();
    // cout << "\n(Destructor -- ~rb3)\n" << endl; // destructor
    // rb3->~RedBlackTree();
    rb3->print();
    cout << "Post Order Traversal: "; // post-order
    rb1->postOrderTraverse();
    cout << "\n\n";
    cout << "Pre Order Traversal: "; // pre-order
    rb1->preOrderTraverse();
    cout << "\n\n";
    cout << "In Order Traversal: "; // in-order
    rb1->inOrderTraverse();
    cout << "\n\n";
    cout << "Search for 4: "; // search
    RedBlackTreeNode* returnNode = rb1->search(4);
    cout << "Returned->" << returnNode->getData() << endl << endl;

    // // interactive use 
    RedBlackTree* rbVisual = new RedBlackTree();
    cout << "------------------------" << endl;
    cout << "RED BLACK TREE FUNCTIONS" << endl;
    cout << "------------------------" << endl << endl;
     
    int value;
    int deletionValue;
    do {
        validate_input(value, "Insert value to tree (-1 to stop): ");
        if (value != -1) 
            rbVisual->insert(value); // interative insertion
    } while (value != -1);
    do {
        validate_input(value, "Delete value from tree (-1 to stop): ");
        if (value != -1) 
            rbVisual->deleteNode(value); // interactive deletion
    } while (value != -1);

    return 0;
}