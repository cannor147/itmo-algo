#include <iostream>
#include <stdlib.h>
using namespace std;

int size, head, tail;
int* queue;
void resize();
void resize2();

int main() {
    freopen("queue1.in", "r", stdin);
    freopen("queue1.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size = 1;
    head = 0;
    tail = -1;
    queue = (int*)malloc((size_t) size * sizeof(int));
    int queries;
    char query;
    cin >> queries;
    for (int i = 0; i < queries; i++){
        cin >> query;
        if (query == '+'){
            cin >> queue[++tail];
        }
        if (query == '-'){
            cout << queue[head++] << endl;
        }
        if (size < 3 * head && size > 2) resize();
        if (size == tail + 1) resize2();
        //cout << size " " << head  << endl;
    }
    free(queue);
    return 0;
}

void resize(){
    int newSize = tail - head + 1;
    int* temp = (int*)malloc((size_t) size * sizeof(int));
    for (int i = 0; i < newSize; i++){
        temp[i] = queue[head + i];
    }
    free(queue);
    queue = temp;
    tail = tail - head;
    head = 0;
}

void resize2(){
    int newSize = 2 * size;
    int* temp = (int*)malloc((size_t) newSize * sizeof(int));
    for (int i = 0; i < size; i++){
        temp[i] = queue[i];
    }
    free(queue);
    queue = temp;
    size *= 2;
}