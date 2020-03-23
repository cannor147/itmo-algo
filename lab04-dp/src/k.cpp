#include <iostream>
#include <memory.h>
using  namespace std;

const int m = 1000000000, h = 2002;
long long dp[h][h], a[h];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    memset(dp, 0, sizeof(dp));
    for (int i = n - 1; i >= 0; i--){
        for (int j = 0; j < n; j++){
            if (i == j) dp[i][j] = 1;
            if (i < j){
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % m;
                if (a[i] != a[j]){
                    dp[i][j] = (m + dp[i][j] - dp[i + 1][j - 1] - 1) % m;
                }
            }
        }
    }
    cout << dp[0][n - 1];
}