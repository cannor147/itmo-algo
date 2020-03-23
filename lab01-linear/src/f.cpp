#include <iostream>
#include <stdlib.h>
using namespace std;

struct item{
    int key;
    struct item* prev;
};

struct item* head = NULL;
void addItem(int value);
int deleteItem();

int main() {

    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    char word;
    int ans = 0, a = 0, b = 0;
    while(cin >> word){
        if (word == '+' || word == '-' || word == '*'){
            b = deleteItem();
            a = deleteItem();
            if (word == '+') ans = a + b;
            if (word == '-') ans = a - b;
            if (word == '*') ans = a * b;
            addItem(ans);
        }else{
            addItem(word - '0');
        }
    }
    cout << ans;
    return 0;
}

void addItem(int value){
    struct item* temp = (struct item* )malloc((size_t) sizeof(struct item));
    temp->key = value;
    temp->prev = head;
    head = temp;
}

int deleteItem(){
    int value = head->key;
    struct item* temp = head;
    head = temp->prev;
    free(temp);
    return value;
}