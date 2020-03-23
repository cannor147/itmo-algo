#include <iostream>
#include <memory.h>

using namespace std;

const int a = 15553, b = 246982, s = 300000;
struct Element {
    int key, prev, next;
    bool isNotNull;
};
Element hashSet[s];

int getValue(int index, int key) {
    hashSet[index].key = key;
    hashSet[index].prev = -1;
    hashSet[index].next = -1;
    hashSet[index].isNotNull = true;
}

int hashCount(int key) {
    int hash = (a*key + b) % s;
    return hash;
}

void insertFromHashSet(int key) {
    int hash = hashCount(key), i = hash, j = -1;
    bool isExists = false;
    if (hashSet[i].isNotNull) {
        do {
            if (key == hashSet[i].key) {
                isExists = true;
                break;
            }
            j = i + 1;
            i = hashSet[i].next;
        } while (i != -1);
        while (hashSet[j].isNotNull) j = (j + 1) % s;
        getValue(j, key);
    } else {
        getValue(i, key);
    }
}

void deleteFromHashSet(int key) {

}

void existsFromHashSet(int key) {
    int hash = hashCount(key), i = hash;
    bool isExists = false;
    if (hashSet[i].isNotNull) {
        do {
            if (key == hashSet[i].key) {
                isExists = true;
                break;
            }
            i = hashSet[i].next;
        } while (i != -1);

    }
    if (isExists) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

int main() {
    string word;
    int number;
    memset(hashSet, 0, sizeof(hashSet));
    while (cin >> word) {
        cin >> number;
        if (word[0] == 'i') insertFromHashSet(number);
        if (word[0] == 'd') deleteFromHashSet(number);
        if (word[0] == 'e') existsFromHashSet(number);
    }
    return 0;
}