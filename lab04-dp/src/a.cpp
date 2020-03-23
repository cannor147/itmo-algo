#include <iostream>
#include <memory.h>
using namespace std;

const int h = 401, inf = 1111111111;
int a[h], dp[h][h], br[h][h];
string m(int, int);

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i] >> a[i + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < n; i++){
        for (int j = 1; j <= n - i; j++){
            dp[j][j + i] = inf;
            for (int g = j; g < j + i; g++){
                int p = a[j - 1] * a[g] * a[j + i];
                if (dp[j][j + i] > dp[j][g] + dp[g + 1][j + i] + p){
                    dp[j][j + i] = dp[j][g] + dp[g + 1][j + i] + p;
                    br[j][j + i] = g;
                }
            }
        }
    }
    cout << m(1, n);
    return 0;
}

string m(int i, int j){
    string s;
    if (j - i > 0){
        s = "(" + m(i, br[i][j]) + m(br[i][j] + 1, j) + ")";
    }else{
        s = "A";
    }
    return s;
}