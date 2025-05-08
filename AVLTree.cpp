#include<iostream>
using namespace std;

class Node {
    public:
    int data, height;
    Node *left, *right;

    Node(int value) {
        data = value;
        left = right = NULL;
        height = 1; 
    }
};

int getBalance(Node *root) {
    return getHeight(root->left) - getHeight(root->right); 
}

int getHeight(Node *root) {
    if (!root) return 0;
    return root-> height;
}

Node* rightRotation(Node *root) {

}

Node* leftRotation(Node *root) {
    
}


Node* insert(Node *root, int key) {
    if (!root) return new Node(key);

    // Find a place where need to add a new element (recursive)
    if (key<root->data) root->left = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    else {return root;}

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);  

    // Left Left rotation
    if (balance > 1 && key < root->left->data){
        rightRotation(root);
    }
    // right right rotation
    else if (balance < -1 && root->right->data < key) {
        leftRotation(root);
    }
    // left right rotation
    else if (balance > 1 && key > root->left->data) {
        leftRotation(root->left);
        rightRotation(root);
    }
    // right left rotation
    else if (balance < -1 && root->right->data > key) {
        rightRotation(root->right);
        leftRotation(root);
    }
    else {
        return root;
    }
}


int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 140);
    root = insert(root, 1);
    root = insert(root, 19);
    root = insert(root, 50);
    root = insert(root, 20);
    root = insert(root, 30);

}