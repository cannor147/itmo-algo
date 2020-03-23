#include <iostream>
#include <fstream>
using namespace std;

const int s = 300001;
int parent[s], size[s], pmin[s], pmax[s];

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);

int main() {
    freopen("dsu.in", "r", stdin);
    freopen("dsu.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string action;
    cin >> n;
    for (int i = 1; i <= n; i++) makeSet(i);
    int a, b;
    while(cin >> action){
        if (action == "get"){
            cin >> a;
            b = findSet(a);
            cout << pmin[b] << " ";
            cout << pmax[b] << " ";
            cout << size[b] << endl;
        }
        if(action  == "union"){
            cin >> a >> b;
            unionSets(a, b);
        }
    }
    return 0;
}

void makeSet(int v){
    parent[v] = v;
    pmin[v] = v;
    pmax[v] = v;
    size[v] = 1;
}

int findSet(int v){
    if (v == parent[v]) return v;
    parent[v] = findSet(parent[v]);
    return parent[v];
}

void unionSets(int a, int b){
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (size[a] < size[b]) swap (a, b);
        parent[b] = a;
        size[a] += size[b];
        if (pmin[b] < pmin[a]) pmin[a] = pmin[b];
        if (pmax[b] > pmax[a]) pmax[a] = pmax[b];
    }
}