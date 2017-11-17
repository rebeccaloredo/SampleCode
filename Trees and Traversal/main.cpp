//
//  Created by Rebecca Loredo on 3/1/17.
//  Copyright © 2017 Rebecca Loredo. All rights

#include <iostream>
#include <queue>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data);
int binaryTraversal(int arr[], int strt, int end, int value);

//initiallize all nodes to makes sure there is no null pointed
Node* newNode(int data){
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

//traversing method to find the location of value
int binaryTraversal(int arr[], int strt, int end, int value){
    int index;
    for (index = strt; index <= end; index++){
        if (arr[index] == value){
            break;
        }
    }
    return index;
}


//recursive method called upon to then insert in to the tree correctly
//returnig the root to be called upon to
Node* buildInorderPostOrder(int inOrder[], int postOrder[], int inOrderFront, int inOrderEnd, int *postIndex){
    if (inOrderFront > inOrderEnd)
        return NULL;
    Node *node = newNode(postOrder[*postIndex]);
    (*postIndex)--;

    if (inOrderFront == inOrderEnd){
         return node;
    }

    int inOrderIndex = binaryTraversal(inOrder, inOrderFront, inOrderEnd, node->data);
    node->right= buildInorderPostOrder(inOrder, postOrder, inOrderIndex+1, inOrderEnd, postIndex);
    node->left = buildInorderPostOrder(inOrder, postOrder, inOrderFront, inOrderIndex-1, postIndex);

    return node;
}

// the proper index for the tree creation is done through here.
Node *buildTree(int in[], int post[], int n){
    int pIndex = n-1;
    return buildInorderPostOrder(in, post, 0, n - 1, &pIndex);
}


//using previously imolemented level order on a queue basis
void levelOrder(Node* node){
    queue<Node*> levelPrintQueue;
    levelPrintQueue.push(node);
    while (!levelPrintQueue.empty()){
        Node *temp = levelPrintQueue.front();
        levelPrintQueue.pop();
        if(temp->left){
            levelPrintQueue.push(temp->left);
        }
        if(temp->right){
            levelPrintQueue.push(temp->right);
        }
        cout << temp->data << " ";
    }
}


int main() {
    int N;
    cin >> N;
    int postOrder [N];
    int inOrder [N];
    int arrayValue;

    for(int i =0; i < N; i++){
        cin >> arrayValue;
        postOrder [i] = arrayValue;
    }
    for(int i =0; i < N; i++){
        cin >> arrayValue;
        inOrder [i] = arrayValue;
    }

    Node *root = buildTree(inOrder, postOrder, N);
    levelOrder(root);

    return 0;
}
