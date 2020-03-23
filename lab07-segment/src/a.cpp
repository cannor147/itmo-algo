#include <iostream>
#include <vector>

using namespace std;
unsigned a, b, cur = 0, n = (1 << 24);
unsigned nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    freopen("fastadd.in", "r", stdin);
    freopen("fastadd.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unsigned m, q;
    cin >> m >> q >> a >> b;
    vector<unsigned> arr(n + 1, 0);
    for (unsigned i = 0; i < m; i++) {
        unsigned add = nextRand();
        unsigned a = nextRand();
        unsigned b = nextRand();
        unsigned l = min(a, b), r = max(a, b);
        arr[l] += add;
        arr[r + 1] -= add;
    }
    unsigned sum = 0;
    for (unsigned i = 0; i < n; i++) {
        sum += arr[i];
        arr[i] = sum;
    }
    sum = 0;
    for (unsigned i = 0; i < n; i++) {
        sum += arr[i];
        arr[i] = sum;
    }
    sum = 0;
    for (unsigned i = 0; i < q; i++) {
        unsigned a = nextRand();
        unsigned b = nextRand();
        unsigned l = min(a, b), r = max(a, b);
        sum += arr[r];
        if (l != 0) sum -= arr[l - 1];
    }
    cout << sum;
}