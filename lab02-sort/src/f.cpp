#include <iostream>

using namespace std;

int main() {
    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, temp;
    cin >> n;
    int a[70001];
    for (int i = 0; i < n; i++)
        a[i] = i+1;
    for (int i = 0; i < n; i++){
        temp = a[i];
        a[i] = a[i / 2];
        a[i / 2] = temp;
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
}