#include <iostream>
#include <memory.h>
using namespace std;

int x, a, y, b, n;
int dp[151][151];
bool check(int);

int main(){
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> x >> a >> y >> b >> n;
    int l, m, r;
    l = 1;
    r = ((x * a + y * b) / n) + 1;
    while (l + 1 < r){
        m = (l + r) >> 1;
        if (check(m)){
            l = m;
        }else{
            r = m;
        }
    }
    cout << l;
    return 0;
}

bool check(int m){
    memset(dp, 0, sizeof(dp));
    bool f = false;
    for (int i = 0; i <= x; i++){
        for (int j = 0; j <= y; j++){
            for (int ii = 0; ii <= i; ii++){
                int jj = 0;
                if (ii * a < m) jj = (m - ii * a) / b;
                if (ii * a + jj * b < m) jj++;
                if (j >= jj){
                    dp[i][j] = max(dp[i][j], dp[i - ii][j - jj] + 1);
                }
            }
        }
    }
    if (dp[x][y] >= n) f = true;
    return f;
}

