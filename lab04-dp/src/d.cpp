#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a[10001][1001], w[1001], c[1001];
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            a[i][j] = a[i][j - 1];
            if (w[j] <= i) a[i][j] = max(a[i][j], a[i - w[j]][j - 1] + c[j]);
        }
    }
    vector<int> ans;
    int k = 0;
    int i = m, j = n;
    while (a[i][j] > 0){
        int s = a[i][j];
        while (a[i][j - 1] == s) j--;
        ans.push_back(j);
        i -= w[j];
        k++;
        j--;
    }
    sort(ans.begin(), ans.end());
    cout << k << endl;
    for (int i = 0; i < k; i++) cout << ans[i] << " ";
    return 0;
}