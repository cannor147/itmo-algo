#include <iostream>
#include <string>
#include <memory.h>
using namespace std;

const int h = 10002;
bool dp[h][h];

int main() {
    string a, b;
    cin >> a >> b;
    a = ' ' + a;
    b = ' ' + b;
    int n = (int) a.size();
    int m = (int) b.size();
    memset(dp, false, sizeof(dp));
    dp[0][0] = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if ((a[i] == '?') || (a[i] == b[j])){
                dp[i + 1][j + 1] = dp[i][j];
            }else{
                if(a[i] == '*'){
                    dp[i + 1][j + 1] = dp[i][j + 1] || dp[i + 1][j];
                }else{
                    dp[i + 1][j + 1] = false;
                }
            }
        }
    }
    if(dp[n][m]){
        cout << "YES";
    }else{
        cout << "NO";
    }
}