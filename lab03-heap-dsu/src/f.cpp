#include <iostream>
#include <fstream>
using namespace std;

const int s = 150001;
int parent[s], size[s];

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);

int main() {
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    int x, y;
    string action;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) makeSet(i);
    for (int i = 1; i <= m; i++) cin >> x >> y;
    int j = 0;
    int a[s], b[s], c[s], d[s];
    while(cin >> action){
        a[j] = 1;
        if (action == "cut") a[j] = 0;
        cin >> b[j] >> c[j];
        j++;
    }
    for (int i = k - 1; i >= 0; i--){
        if (a[i] == 0){
            unionSets(b[i], c[i]);
        }else{
            x = findSet(b[i]);
            y = findSet(c[i]);
            if (x == y){
                d[i] = true;
            }else{
                d[i] = false;
            }
        }
    }
    for (int i = 0; i < k; i++){
        if (a[i] == 1){
            if (d[i]){
                cout << "YES" << endl;
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