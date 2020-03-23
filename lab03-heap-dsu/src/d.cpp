#include <iostream>
using namespace std;

const int s = 300001;
int parent[s], size[s], pmax[s];
bool isCycling[s];

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    string action;
    cin >> n;
    for (int i = 1; i <= n; i++) makeSet(i);
    int a, b, c, d;
    for (int i = 1; i <= n; i++){
        cin >> a;
        b = findSet(a);
        if (pmax[b] == n){
            if (isCycling[pmax[b]]){
                b = findSet(1);
                d = pmax[b];
                unionSets(pmax[b], pmax[b] + 1);
            }else{
                for (int i = 1; i <= n; i++){
                    c = findSet(a);
                    if (c == b) isCycling[i] = true;
                }
                d = pmax[b];
            }
        }else{
            d = pmax[b];
            unionSets(pmax[b], pmax[b] + 1);
        }
        cout << d << " ";
    }
    return 0;
}

void makeSet(int v){
    parent[v] = v;
    pmax[v] = v;
    size[v] = 1;
    isCycling[v] = false;
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
        if (pmax[b] > pmax[a]) pmax[a] = pmax[b];
    }
}