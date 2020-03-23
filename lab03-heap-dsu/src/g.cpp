#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct query{
    int left, right, value;
};

bool operator<(query x, query y){
    return x.left < y.left;
}

const int t = 300001, maxInt = 2147483647;
vector <pair<int, int>> pq;
vector <query> q;
int s = 0, n = 0, m = 0;

void shiftUp(int k);
void shiftDown(int i);
void push(int x, int p);
void extractMax();

int main(){
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int j = 0;
    cin >> n >> m;
    q.resize(m);
    pq.resize(t);
    for (int i = 0; i < m; i++) cin >> q[i].left >> q[i].right >> q[i].value;
    std::sort(q.begin(), q.end());

    for (int i = 0; i < n; i++){
        while (j < m && q[j].left <= i + 1){
            push(q[j].value, j);
            j++;
        }
        while (s!=0 && q[pq[0].second].right <= i) extractMax();
        if (s == 0){
            cout << maxInt << " ";
        }else{
            cout << pq[0].first << " ";
        }
    }
    return 0;
}

void shiftUp(int k){
    int i = k;
    while (pq[i] > pq[(i - 1) / 2]){
        if(i == 0) return;
        swap(pq[i], pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void shiftDown(int i){
    int l, r;
    int j;
    while (2 * i + 1 < s){
        l = 2 * i + 1;
        r = 2 * i + 2;
        j = l;
        if (r < s && pq[r].first > pq[l].first) j = r;
        if (pq[i].first >= pq[j].first) break;
        swap(pq[i], pq[j]);
        i = j;
    }
}

void push(int x, int p){
    pq[s].first = x;
    pq[s].second = p;
    shiftUp(s);
    s++;
}

void extractMax(){
    swap(pq[s - 1], pq[0]);
    s--;
    shiftDown(0);
}