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
}