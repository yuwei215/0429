#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
};

class RedBlackTree {
private:
    Node *root;
    Node *NIL;

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;

        if (x->right != NIL)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == NIL)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node *z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node *uncle = z->parent->parent->right;

                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node *uncle = z->parent->parent->left;

                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void inorder(Node *node) {
        if (node == NIL)
            return;

        inorder(node->left);
        cout << node->data << "(";
        if (node->color == RED)
            cout << "R";
        else
            cout << "B";
        cout << ") ";
        inorder(node->right);
    }

public:
    RedBlackTree() {
        NIL = new Node;
        NIL->color = BLACK;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;

        root = NIL;
    }

    void insert(int value) {
        Node *z = new Node;
        z->data = value;
        z->color = RED;
        z->left = NIL;
        z->right = NIL;
        z->parent = NIL;

        Node *y = NIL;
        Node *x = root;

        while (x != NIL) {
            y = x;

            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == NIL)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    bool search(int value) {
        Node *current = root;

        while (current != NIL) {
            if (value == current->data)
                return true;
            else if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }

    void printTree() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }

    void printTimeComplexity() {
        cout << "\nTime Complexity:" << endl;
        cout << "Insert: O(log n)" << endl;
        cout << "Search: O(log n)" << endl;
        cout << "Traversal: O(n)" << endl;
        cout << "Left Rotate / Right Rotate: O(1)" << endl;
    }
};

int main() {
    RedBlackTree tree;

    int values[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(values) / sizeof(values[0]);

    cout << "Red-Black Tree Insert Process" << endl;

    for (int i = 0; i < n; i++) {
        cout << "Insert: " << values[i] << endl;
        tree.insert(values[i]);
    }

    cout << endl;
    tree.printTree();

    int key;
    cout << "\nEnter number to search: ";
    cin >> key;

    if (tree.search(key))
        cout << key << " found in the tree." << endl;
    else
        cout << key << " not found in the tree." << endl;

    tree.printTimeComplexity();

    return 0;
}
