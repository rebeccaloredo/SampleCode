//
//
//  Created by Rebecca Loredo on 2/14/17.
//  Copyright © 2017 Rebecca Loredo. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

//contains individual get functions for items within table

class HashEntry {
private:
    int key;
    int value;
    int size;
public:
    HashEntry(int key, int value){
        this->key = key;
        this->value = value;
    }
    int getKey() {
        return key;
    }
    int getValue() {
        return value;
    }
};

const int size = 1000;

//actual hash map class containing the decleration for a table, search and insert method

class HashMap {
private:
    HashEntry **table;
public:
    HashMap() {
        table = new HashEntry*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }

    // searches for a specific key and returns its value

    int search (int key) {
        int hash = (key % size);
        while (table[hash] != NULL && table[hash]->getKey() != key){
            hash = (hash + 1) % size;
        }
        if (table[hash] == NULL)
            return -1;
        else {
            return table[hash]->getValue();
        }
    }

    //used as a helper method in order to check if the product was actually found in the table

    bool productExist(int product, int num){
        bool found = false;
        int check;
        int tableSize;
        int temp;
        check = product;
        tableSize = num;
        for (int i = 0; i < num; i++){
            temp = table[i]->getValue();
                if(check == temp){
                   found = true;
            }
        }
        return found;
    }

    // inserts values into the table

    void insert (int key, int value){
        int hash = (key % size);
        while (table[hash] != NULL && table[hash]->getKey() != key){
            hash = (hash + 1) % size;
        }
        if (table[hash] != NULL){
            delete table[hash];
        }
        table[hash] = new HashEntry(key, value);
    }

    ~HashMap() {
        for(int i =0; i < size; i++)
            if (table[i] != NULL)
                delete table[i];
            delete[] table;
    }
};

int main() {
    HashMap hash;
    int N;
    int key;
    int value;
    int currProduct = 0;
    int maxProduct = -1;
    int checkedProduct = -1;
    bool falseInput = false;

    cin >> N;

    // collects values for the hash table N amount of times

    for (int i = 0; i < N; i++){
        cin >> value;
        if(value > 0) {
            key = i;
            hash.insert(key, value);
        }
        else{
            falseInput = true;
        }
    }

    // boolean check for false input to display negative one is necessary

    if(falseInput){
        cout << "-1";
        return 0;
    }

    //contains product function with comparisons and check with bool method

    else {
        for(int i = 0; i < N; i++){
            for (int j = 1; j < N; j++){
                if(j != N && j != i){
                    currProduct = hash.search(i)*hash.search(j);
                }
                if(hash.productExist(currProduct,N)){
                    checkedProduct = currProduct;
                }
                if(checkedProduct > maxProduct){
                    maxProduct = checkedProduct;
                }
            }
        }
        cout << maxProduct;
    }
    return 0;
}
