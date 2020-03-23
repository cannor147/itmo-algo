#include <iostream>
using namespace std;

const int s = 200002, p = 1000003;
int parent[s], size[s], all[s], read[s];
int n, m, t = 0;

void makeSet(int v);
int findSet(int v);
void unionSets(int a, int b);
int countZerg(int key, int zerg, int data);
int countMessages(int v);

int main() {
    cin >> n >> m;
    t = n;
    for (int i = 0; i <= n; i++) makeSet(i);
    int action, a = 0, b = 0;
    unsigned int zerg = 0;
    while(cin >> action){
        if (action == 1){
            cin >> a;
            a = (a + zerg) % n;
            b = findSet(a);
            all[b]++;
            zerg = countZerg(action, zerg, b);
        }
        if(action  == 2){
            cin >> a >> b;
            a = (a + zerg) % n;
            b = (b + zerg) % n;
            if (findSet(a) != findSet(b)){
                unionSets(a, b);
                zerg = countZerg(action, zerg, b);
            }
        }
        if(action  == 3){
            cin >> a;
            a = (a + zerg) % n;
            b = countMessages(a) - read[a];
            read[a] += b;
            cout << b << endl;
            zerg = countZerg(action, zerg, b);
        }
        /*
        for (int g = 0; g <= t; g++) cout << all[g];
        cout << " - ";
        for (int g = 0; g <= n; g++) cout << read[g];
        cout << " - ";
        for (int g = 0; g <= t; g++) cout << parent[g];
        cout << endl;
        */
    }
    return 0;
}

void makeSet(int v){
    parent[v] = v;
    size[v] = 1;
    all[v] = 0;
    read[v] = 0;
}

int findSet(int v){
    if (v == parent[v]) return v;
    return findSet(parent[v]);
}

void unionSets(int ae, int be){
    int a = findSet(ae);
    int b = findSet(be);
    if (a != b) {
        if (size[a] < size[b]) swap (a, b);
        parent[b] = a;
        all[b] -= all[a];
        size[a] += size[b];
    }
}

int countZerg(int key, int zerg, int data){
    long long tmp = 0;
    long long rush = (long long)zerg;
    long long q = (long long)data;
    switch(key){
        case 1: tmp = (30 * rush + 239) % p; break;
        case 2: tmp = (13 * rush + 11) % p; break;
        case 3: tmp = (100500 * rush + q) % p; break;
    }
    int ans = (int)tmp;
    //cout << "zerg " << zerg << endl;
    return ans;
}

int countMessages(int v){
    int g = all[v];
    if (v == parent[v]) return g;
    g += countMessages(parent[v]);
    return g;
}