#include <iostream>
using namespace std;

const int s = 300001;
int parent[s], size[s], nextSegment[s];
int n, q;

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);
void unionSegments(int a, int b);

int main() {
    freopen("restructure.in", "r", stdin);
    freopen("restructure.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) makeSet(i);
    int action;
    int a, b;
    while (cin >> action){
        cin >> a >> b;
        if (action == 1){
            unionSets(a, b);
        }
        if(action == 2){
            unionSegments(a, b);
        }
        if(action == 3){
            if (findSet(a) == findSet(b)){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
        /*
        for (int i = 1; i <= n; i++) cout << parent[i];
        cout << " - ";
        for (int i = 1; i <= n; i++) cout << nextSegment[i];
        cout << " - " << action << " " << a << " " << b << endl;
        */

    }
    return 0;
}

void makeSet(int v){
    parent[v] = v;
    size[v] = 1;
    nextSegment[v] = v + 1;
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
    }
}

void unionSegments(int a, int b){
    int smin = 0, pmin = 0;
    int i = a, j = nextSegment[b], p;
    while (i < j){
        p = findSet(i);
        if (smin < size[p]) pmin = p;
        i = nextSegment[i];
    }
    i = a;
    while (i < j){
        unionSets(i, pmin);
        p = nextSegment[i];
        nextSegment[i] = j;
        i = p;
    }
}
