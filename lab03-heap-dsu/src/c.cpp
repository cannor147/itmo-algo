#include <iostream>
#include <vector>
using namespace std;

const int s = 300000;
vector <pair<int, int>> pq;
int n = 0;

void shiftUp(int k);
void shiftDown(int i);
void push(int x, int p);
void decreaseKey(int a,int p);
void extractMin();

int main(){
    freopen("priorityqueue2.in", "r", stdin);
    freopen("priorityqueue2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pq.resize(s);
    string action;
    int a, b, c = 0;
    while(cin >> action){
        c++;
        if(action == "push"){
            cin >> a;
            push(a, c);
        }
        if(action == "extract-min"){
            if (n <= 0){
                cout << "*" << endl;
            } else{
                extractMin();
            }
        }
        if(action == "decrease-key"){
            cin >> a >> b;
            decreaseKey(a, b);
        }
    }
    return 0;
}

void shiftUp(int k){
    int i = k;
    while (pq[i] < pq[(i - 1) / 2]){
        if(i == 0) return;
        swap(pq[i], pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void shiftDown(int i){
    int l, r;
    int j;
    while (2 * i + 1 < n){
        l = 2 * i + 1;
        r = 2 * i + 2;
        j = l;
        if (r < n && pq[r].first < pq[l].first) j = r;
        if (pq[i].first <= pq[j].first) break;
        swap(pq[i], pq[j]);
        i = j;
    }
}

void push(int x, int p){
    pq[n].first = x;
    pq[n].second = p;
    shiftUp(n);
    n++;
}

void decreaseKey(int a, int p){
    for (int i = 0; i < n; i++){
        if (pq[i].second == a){
            pq[i].first = p;
            shiftUp(i);
        }
    }
}

void extractMin(){
    cout << pq[0].first << " " << pq[0].second << endl;
    //cout << pq[0].first << endl;
    swap(pq[n - 1], pq[0]);
    n--;
    shiftDown(0);
}