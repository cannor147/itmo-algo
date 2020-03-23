#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct item{
    int key;
    struct item* prev;
};

struct item* head = NULL;
void addItem(int value);
int deleteItem();

int main() {

    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string seq;
    int t = 0, size = 0;
    bool f;
    struct item* head = NULL;
    while(cin >> seq){
        head = NULL;
        f = true;
        size = 0;
        for(char& c: seq) {
            if (c == '('){
                addItem(1);
                size++;
            }
            if (c == '['){
                addItem(2);
                size++;
            }
            if (c == ')'){
                t = 1;
                if (size == 0){
                    f = false;
                }else{
                    if (deleteItem() != t) f = false;
                }
                size--;
            }
            if (c == ']'){
                t = 2;
                if (size == 0){
                    f = false;
                }else{
                    if (deleteItem() != t) f = false;
                }
                size--;
            }
            if (!f) break;
        }
        if (size != 0) f = false;
        if (f){
            cout << "YES";
        }else{
            cout << "NO";
        }
        cout << endl;
    }
    head = NULL;
    if (head == NULL) return 0;
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