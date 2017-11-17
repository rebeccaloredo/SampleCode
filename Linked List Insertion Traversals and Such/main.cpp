
//
//  Created by Rebecca Loredo on 1/31/17.
//  Copyright © 2017 Rebecca Loredo. All rights reserved.
//

#include <iostream>
#include <cstddef>
using namespace std;

//Create Node Class
class Node {
public:
    Node(int n);
    Node* nextNodePointer;
    int value;

};

//Empty String Initialization
Node::Node(int n) {
    value = 0;
};

//Create Linked List Class
class LinkedList {
public:
    Node*head = NULL;
    void insertNodeAtHead(int num);
    void valueInput(int size, int v);
    void printList();
    bool traverseForValue(int a, int b);
    void deleteSequence(int a, int b, int s);
};

//Inserts node as many times as told
void LinkedList::insertNodeAtHead(int num) {
    Node* temp = head;
    head = new Node(num);
    head->nextNodePointer=temp;
};

void LinkedList::valueInput(int position, int v) {
    Node *temp = head;
    for (int i = 0; i < position; i++) {
        temp = temp->nextNodePointer;
    }
     temp->value = v;
};

void LinkedList::printList() {
    if (head != NULL){
    Node *temp = head;
    while(temp!=NULL){
        cout << temp->value << " ";
        temp = temp->nextNodePointer;
    }
    }
    else{
        cout << "";
    }
};

bool LinkedList::traverseForValue(int a, int b){
    bool aFound = false;
    bool bFound = false;
    bool found = false;
    int i = 0;
    Node *temp = head;
    while(temp!=NULL){
        if(temp->value == a){
            aFound = true;
            i++;
        }
        if(temp->value == b){
            bFound = true;
        }
        temp = temp->nextNodePointer;
    }
    if (a==b){
        if(i>1){
            found = true;
        }
        else{
            found = false;
        }
    }
    else{
        if(aFound && bFound){
            found = true;
        }
    }
    return found;
};


void LinkedList::deleteSequence(int a, int b, int s){
    bool bFound = false;
    bool bskip = false;
    bool aEqualb = (a==b);
    bool fSkip = false;
    bool delhead = false;
    int k = 0;
    Node *temp = head;
    Node* index = temp;
    if (s == 1 && temp->value == a){
        head = temp->nextNodePointer;
        index = head;
        temp = head;
        if (a == b ){
            aEqualb = false;
        }
    }
    else{
        while(temp != NULL && temp->value != a){
            index = temp;
            temp = temp->nextNodePointer;
            fSkip = true;
        }
    }
    //if (a==b && temp->value==a && index->value == a){
    //    aEqualb = false;
    //    oneIsA = true;
    //}
    while (temp != NULL && !bFound && !bskip){
        if (delhead){
            k=1;
        }
        delhead = false;
        for (int i = k; i < s-1; i++){
            if (temp->nextNodePointer != NULL){
                if (temp->value == b && fSkip){
                    bskip = true;
                }
                index = temp;
                temp = temp->nextNodePointer;
                if (temp->nextNodePointer == NULL && i != s-2){
                    i = i + 2;
                    if (i == s-1){
                        head = head->nextNodePointer;
                        index = head;
                        temp = head;
                        if (temp->value == b){
                            bskip = true;
                        }
                        if (temp->nextNodePointer != NULL){
                             temp = temp->nextNodePointer;
                        }

                        delhead = true;
                    }
                    else {
                        if (temp->value == b){
                            bskip = true;
                        }
                        temp = head;
                        temp = temp->nextNodePointer;
                        index = head;
                    }

                }
                fSkip = true;
            }
            else {
                if (temp->value == b && fSkip){
                    bskip = true;
                    bFound = false;
                    temp = index;
                }
                else{
                    if (temp->nextNodePointer == NULL && i == s-2){
                        i = i + 1;
                        if (i == s-1){
                            head = head->nextNodePointer;
                            index = head;
                            temp = head;
                            if (temp->value == b){
                                bskip = true;
                            }
                            if (temp->nextNodePointer != NULL){
                                temp = temp->nextNodePointer;
                            }

                            delhead = true;
                        }
                        else {
                            if (temp->value == b){
                                bskip = true;
                            }
                            temp = head;
                            temp = temp->nextNodePointer;
                            index = head;
                        }

                    }
                }
            }
        }
        k=0;
        if (!delhead){
        if (temp->value == b){
            if(aEqualb){
                bFound = false;
                aEqualb = false;
            }
            else{
                bFound = true;
            }
            if (index->nextNodePointer == temp->nextNodePointer && index->nextNodePointer == head->nextNodePointer){
                head = temp->nextNodePointer;
                index = head;
                temp = head;
            }
            else {
            index->nextNodePointer = temp->nextNodePointer;
            //delete temp;
            //temp = index;
            temp = temp->nextNodePointer;
            }
        }

        if(!bFound && !bskip){
            if(temp->nextNodePointer==NULL){
                index->nextNodePointer = NULL;
                index = head;
                //delete temp;
                temp = index;
            }
            else{
                if (index->nextNodePointer == temp->nextNodePointer && index->nextNodePointer == head->nextNodePointer){
                    head = temp->nextNodePointer;
                    index = head;
                    temp = head;
                }
                else {
                    index->nextNodePointer = temp->nextNodePointer;
                    //delete temp;
                    temp = index;
                    temp = temp->nextNodePointer;
                }

            }
        }

        //if (temp->value == b && oneIsA){
          //  bFound = true;
        //}

        if (temp == NULL && !bFound){
            bFound = false;
            bskip = false;
            temp = head;
            index = temp;
            if(temp->nextNodePointer!=NULL){
            temp = temp->nextNodePointer;
            }
        }
        }
    }
};

int main() {

    //handles linked list initialization
    int N;
    int number;
    int M;
    int a;
    int b;
    int s;


    cin >> N;
    LinkedList *L1 = new LinkedList();
    for (int i = 0; i<N; i++) {
        L1->insertNodeAtHead(i);
    }
    for (int i = 0; i < N; i++){
        cin >> number;
        L1->valueInput(i, number);
    }

    cin >> M;
    int aValues[M];
    int bValues[M];
    int sValues[M];
    for (int i = 0; i < M; i++){
        cin >> a;
        aValues[i] = a;
        cin >> b;
        bValues[i] = b;
        cin >> s;
        sValues[i] = s;

    }


    for (int i = 0; i < M ; i++) {
        if (L1->traverseForValue((aValues[i]), bValues[i])){
            L1->deleteSequence(aValues[i],bValues[i],sValues[i]);
        }
    }

    L1->printList();

    return 0;
}
