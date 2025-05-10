#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

class Node {
public:
    int data, height;
    Node *left, *right;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

int getHeight(Node *root);

int getBalance(Node *root);

Node* rightRotation(Node *root);

Node* leftRotation(Node *root);

bool search(Node *root, int key);

Node* insert(Node *root, int key);

Node* deleteNode(Node *root, int key);

Node* update(Node *root, int oldValue, int newValue );

void preOrder(Node *root);
void inOrder(Node *root);
void postOrder(Node *root);

#endif 