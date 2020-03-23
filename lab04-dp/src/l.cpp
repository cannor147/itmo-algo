#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int h = 100001;
long long a[h], b[h], c[h];
bool visited[h];
vector<vector<int>> childs;
vector<vector<long long>> weights;
int size[h];
void count(int);

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, u, v;
    long long w;
    cin >> n;
    vector<int> temp1;
    vector<long long> temp2;
    for (int i = 0; i <= n; i++){
        childs.push_back(temp1);
        weights.push_back(temp2);
        size[i] = 0;
        visited[i] = false;
    }
    for (int i = 0; i < n - 1; i++){
        cin >> u >> v >> w;
        childs[u].push_back(v);
        childs[v].push_back(u);
        weights[u].push_back(w);
        weights[v].push_back(w);
        size[u]++;
        size[v]++;
    }
    count(1);
    cout << c[1];
    return 0;
}

void count(int j){
    visited[j] = true;
    long long fa = 0, fb = 0;
    for (int i = 0; i < size[j]; i++){
        if (visited[childs[j][i]] == true) continue;
        count(childs[j][i]);
        fa = max(fa, b[childs[j][i]] - c[childs[j][i]] + weights[j][i]);
        fb += c[childs[j][i]];
    }
    a[j] = fa + fb;
    b[j] = fb;
    c[j] = max(a[j], b[j]);
}