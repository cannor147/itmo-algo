#include <iostream>
using namespace std;

const int s = 200001;
int parent[s], size[s], parity[s];

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) makeSet(i);
    int action, shift = 0;
    int a, b;
    while(cin >> action){
        cin >> a >> b;
        a = ((a + shift) % n);
        b = ((b + shift) % n);
        if (a == 0) a = n;
        if (b == 0) b = n;
        if (action == 0){
            unionSets(a, b);
            //for (int i = 1; i <= n; i++) cout << parity[i];
            //cout << endl;
        }
        if(action == 1){
            findSet(a);
            findSet(b);
            if (parity[a] == parity[b]){
                cout << "YES" << endl;
                shift = (shift + 1) % n;
            }else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}

void makeSet(int v){
    parent[v] = v;
    size[v] = 1;
    parity[v] = 0;
}

int findSet(int v){
    if (v == parent[v]) return v;
    int r = findSet(parent[v]);
    parity[v] = (parity[v] + parity[parent[v]]) % 2;
    parent[v] = r;
    return parent[v];
}

void unionSets(int a, int b){
    int x = a, y = b;
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        parity[b] = (parity[x] + parity[y] + 1) % 2;
    }
}