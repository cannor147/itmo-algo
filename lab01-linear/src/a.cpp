#include <iostream>
#include <stdlib.h>
using namespace std;

int size, head;
int* stack;
void resize(int);

int main() {
    freopen("stack1.in", "r", stdin);
    freopen("stack1.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size = 1;
    head = -1;
    stack = (int*)malloc((size_t) size * sizeof(int));
    int queries;
    char query;
    cin >> queries;
    for (int i = 0; i < queries; i++){
        cin >> query;
        if (query == '+') cin >> stack[++head];
        if (query == '-') cout << stack[head--] << endl;
        if (size >= 4 * (head + 1) && size > 1) resize(size / 2);
        if (size == head + 1) resize(size * 2);
        //cout << size << " " << head << endl;
    }
    free(stack);
    return 0;
}

void resize(int newSize){
    size = newSize;
    int* temp = (int*)malloc((size_t) size * sizeof(int));
    for (int i = 0; i <= head; i++){
        temp[i] = stack[i];
    }
    free(stack);
    stack = temp;
}