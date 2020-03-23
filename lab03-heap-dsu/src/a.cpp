#include <iostream>
using namespace std;

int main() {
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    int a[111111];
    bool f = true;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        if (2*i <= n){
            if (a[i] > a[2*i]) f = false;
        }
        if (2*i+1 <= n){
            if (a[i] > a[2*i+1]) f = false;
        }
    }
    if (f){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}