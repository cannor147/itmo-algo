#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Sparse_table {

private:
    vector<vector<int>> table;

public:
    Sparse_table(vector<int> &arr) {
        int s = arr.size();
        table.resize((int)1111111, vector<int>(17, INT32_MAX));
        for (int j = 0; (1 << j) <= s; j++) {
            for (int i = 0; i < s; i++) {
                if (j == 0) {
                    table[i][j] = arr[i];
                } else {
                    table[i][j] = min(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
                }
            }
        }
    }
    int get_min(int l, int r) {
        int j = 0;
        while ((1 << j + 1) <= r - l + 1) {
            j++;
        }
        return min(table[l][j], table[r - (1 << j) + 1][j]);
    }
};

int main() {
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);

    int n, m, a, b, l, r, ans;
    cin >> n >> m;
    vector<int> arr(n);
    cin >> arr[0] >> a >> b;
    for (int i = 1; i < n; i++) {
        arr[i] = (23 * arr[i - 1] + 21563) % 16714589;
    }
    Sparse_table table(arr);
    for (int i = 0; i < m; i++) {
        if (i > 0) {
            a = ((17 * a + 751 + ans + 2 * i) % n) + 1;
            b = ((13 * b + 593 + ans + 5 * i) % n) + 1;
        }
        l = min(a, b);
        r = max(a, b);
        ans = table.get_min(l - 1, r - 1);
    }
    cout << a << " " << b << " " << ans <<  endl;
}