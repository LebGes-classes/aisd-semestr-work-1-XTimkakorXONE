#include "AVLTree.hpp"
#include<iostream>
using namespace std;

int getHeight(Node *root) {
    if (!root) return 0;
    return root-> height;
}

int getBalance(Node *root) {
    return getHeight(root->left) - getHeight(root->right); 
}

Node* rightRotation(Node *root) {
    Node *child = root->left;
    Node *childRight = child->right;

    child->right = root;
    root->left = childRight;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}

Node* leftRotation(Node *root) {
    Node *child = root->right;
    Node *childLeft = child->left;

    child->left = root;
    root->right = childLeft;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}

bool search(Node *root, int key) {
    if (!root) return false;
    if (key < root->data) {
        return search(root->left, key);
    }
    else if (key > root->data) {
        return search(root->right, key);
    }
    return true;
}

Node* insert(Node *root, int key) {
    if (!root) return new Node(key);

    if (key<root->data) root->left = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    else {return root;}

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);  

    if (balance > 1 && key < root->left->data){
        return rightRotation(root);
    }
    else if (balance < -1 && root->right->data < key) {
        return leftRotation(root);
    }
    else if (balance > 1 && key > root->left->data) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    else if (balance < -1 && root->right->data > key) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    else {
        return root;
    }
}


Node* deleteNode(Node *root, int key) {
    if (!root) return NULL;

    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        }
        else if (root->left && !root->right) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else if (!root->left && root->right) {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else {
            Node *current = root->right;
            while (current->left) {
                current=current->left;
            }
            root->data = current->data;
            root->right = deleteNode(root->right, current->data);
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));  
    int balance = getBalance(root);
    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rightRotation(root);
        } else {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    } 
    else if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return leftRotation(root);
        } else {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    else {return root;}
}

Node* update(Node *root, int oldValue, int newValue) {
    if (search(root, oldValue)) {
        root = deleteNode(root, oldValue);
        root =insert(root, newValue);
    }
    return root;
}


void preOrder(Node *root) {
    if (!root) return;

    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);  
}


void inOrder(Node *root) {
    if (!root) return;

    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);  
}

void postOrder(Node *root) {
    if (!root) return;

    postOrder(root->left);
    postOrder(root->right);
    cout <<root->data<< " ";
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
    cout<<"preorder: " <<endl;
    preOrder(root);
    cout<<"\ninOrder: " <<endl;
    inOrder(root);
    root = deleteNode(root, 30);
    root = update(root, 50, 42);
    cout<<"\npreorder: " <<endl;
    preOrder(root);
    cout<<"\ninOrder: " <<endl;
    inOrder(root);
}