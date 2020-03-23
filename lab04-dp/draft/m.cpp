#include <iostream>
#include <memory.h>
using namespace std;

const int h = 19, th = (1 << h), inf = 111111111;
int dp[h][th], g[h][h];
int ham(int, int);
int n, m;

int main() {/*
	freopen("salesman.in", "r", stdin);
	freopen("salesman.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	*/
    int v, u, w;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < (1 << n); j++){
            dp[i][j] = inf;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            g[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < m; i++){
        cin >> u >> v >> w;
        g[v - 1][u - 1] = w;
        g[u - 1][v - 1] = w;
    }
    for (int mask = 1; mask < (1 << n); mask++){
        for (int i = 0; i < n - 1; i++){
            if ((mask >> i) % 2 == 0) continue;
            for (int j = 0; j < n; j++){
                if (g[i][j] == -1) continue;
                if (dp[i][mask] == inf){
                    dp[i][mask] = min(dp[i][mask], dp[j][mask - (1 << j)] + g[i][j]);
                }
            }
        }
    }
    int ans = inf;
    cout << dp[n - 1][(1 << n) - 1] << endl;
    for (int i = 0; i < n - 1; i++){
        cout << "x " << i << " " << (1 << n) - 1 - (1 << i) << " " << dp[i][(1 << n) - 1 - (1 << i)] << " " << g[n - 1][i] << endl;
        if (dp[n - 1][(1 << n) - 1] == dp[i][(1 << n) - 1 - (1 << i)] + g[n - 1][i]){
            ans = min(ans, dp[i][(1 << n) - 1 - (1 << i)]);
        }
    }
    for (int i = 0; i < n; i++){
        for (int mask = 0; mask < (1 << n); mask++){
            cout << dp[i][mask] << " ";
        }
        cout << endl;
    }
    if (ans == inf){
        cout << -1;
    }else{
        cout << ans;
    }
}