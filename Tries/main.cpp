//
//
//  Created by Rebecca Loredo on 4/3/17.
//  Copyright © 2017 Rebecca Loredo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

//definitions to quickly access certain functions

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define FREE(p) \
    free(p);    \
    p = NULL;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isLeaf = 0;
};

//creates new trie node initialized to NULLs
struct TrieNode *getNode(void){
    struct TrieNode *parent = NULL;
    parent = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (parent){
        int i;
        parent->isLeaf = 0;
        for (i = 0; i < ALPHABET_SIZE; i++){
            parent->children[i] = NULL;
        }
    }
    return parent;
}

//inserts into trie char by char making sure not to repeat
//the key if it is already present at the level, marks
//the last key in the word a leaf so that its count
//can be kept track of
void insert(struct TrieNode *root, string key) {
    int level;
    int length = key.length();
    int index;
    struct TrieNode *current = root;
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);
        if (!current->children[index]){
            current->children[index] = getNode();
        }
        current = current->children[index];
    }
    current->isLeaf++;
}

//checks to see if node is clear
//helper function
int isItFreeNode(struct TrieNode *root){
    int i;
    for(i = 0; i < ALPHABET_SIZE; i++)
    {
        if( root->children[i] )
            return 0;
    }

    return 1;
}

//checks if the node is a leaf or not
//helper function
int leafNode(struct TrieNode *root){
    return (root->isLeaf != 0);
}

//handles removing keys from the trie if they are present
//ensures that a word which is present twice is only
//removed once
bool decrement(struct TrieNode *root, string key, int level, int length) {
    if(root){
        if(level == length){
            if (root->isLeaf){
                root->isLeaf--;
                if(root->isLeaf > 0){
                    return false;
                }
                if(isItFreeNode(root)){
                    return true;
                }
                return false;
            }
        }
        else{
            int index = CHAR_TO_INDEX(key[level]);
            if (decrement(root->children[index], key, level+1, length)){
                FREE(root->children[index]);
                return (!leafNode(root) && isItFreeNode(root));
            }
        }
    }
    return false;
}

//calls the increment function
void incrementHelper (string temp, struct TrieNode *root){
    insert(root, temp);
}

//call to the decrement function
void decrementHelper (string temp, struct TrieNode *root){
    int length = temp.length();
    decrement(root, temp, 0, length);
}

//prints in a postOrder style due to conditions implemented to ensure
//that the longer word prints before the alphabetically correct word
void postOrderTraverse (struct TrieNode *root, string temp){
    bool lastLeaf = true;
    string pending = "";
    int leafOcc = 0;
    if(root == NULL) {
        return;
    }
    if(root->isLeaf >= 1) {
        for(int j = 0; j < 26; j++) {
            if(root->children[j] != NULL) {
                lastLeaf = false;
            }
        }
        if(lastLeaf){
           cout << temp << ": "  <<  root->isLeaf << endl;
        }
        else {
            pending = temp;
            leafOcc = root->isLeaf;
        }
    }
    for(int i = 0; i < 26; i++) {
        if(root->children[i]) {
            postOrderTraverse(root->children[i],temp+(char)(i+'a'));
        }
    }
    if(pending != ""){
        cout << pending << ": "  <<  leafOcc << endl;
        pending = "";
        leafOcc = 0;
    }
}

int main() {
    string inc;
    string dec;
    getline(cin, inc);
    getline(cin, dec);

    struct TrieNode *root = getNode();

    for (int i = 0; i < inc.length(); i++){
        string temp = "";
        while (isalpha(inc[i])){
            temp += inc[i];
            i++;
        }
        incrementHelper(temp,root);
    }

    for (int i = 0; i < dec.length(); i++){
        string temp;
        while (isalpha(dec[i])){
            temp += dec[i];
            i++;
        }
        decrementHelper(temp,root);
    }
    string temp = "";
    postOrderTraverse(root, temp);


    return 0;
}
