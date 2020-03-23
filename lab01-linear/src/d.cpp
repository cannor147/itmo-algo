#include <iostream>
#include <stdlib.h>
using namespace std;

struct item{
    int key;
    struct item* prev;
};

int size = 0;
struct item* head = NULL;
struct item* tail = NULL;
void addItem();
void deleteItem();

int main() {
    freopen("queue2.in", "r", stdin);
    freopen("queue2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int queries;
    char query;
    cin >> queries;
    while(cin >> query){
        if (query == '+') addItem();
        if (query == '-') deleteItem();
    }
    return 0;
}

void addItem(){
    int value;
    cin >> value;
    struct item* temp = (struct item* )malloc((size_t) sizeof(struct item));
    temp->key = value;
    temp->prev = NULL;
    if (size == 0){
        head = temp;
    }else{
        tail->prev = temp;
    }
    tail = temp;
    size++;
}

void deleteItem(){
    cout << head->key << endl;
    struct item* temp = head;
    head = temp->prev;
    if (size == 1){
        tail = NULL;
    }
    size--;
    free(temp);
}