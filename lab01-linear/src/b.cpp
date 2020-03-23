#include <iostream>
#include <stdlib.h>
using namespace std;

struct item{
    int key;
    struct item* prev;
};

struct item* head = NULL;
void addItem();
void deleteItem();

int main() {
    freopen("stack2.in", "r", stdin);
    freopen("stack2.out", "w", stdout);
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
    temp->prev = head;
    head = temp;
}

void deleteItem(){
    cout << head->key << endl;
    struct item* temp = head;
    head = temp->prev;
    free(temp);
}