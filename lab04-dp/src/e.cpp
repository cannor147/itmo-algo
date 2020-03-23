#include <iostream>
#include <string>
using namespace std;

int a[5001][5001];

int main() {
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    string s1, s2;
    cin >> s1;
    cin >> s2;
    n = (int) (s1.length());
    m = (int) (s2.length());
    for (int i = 1; i <= m; i++) a[i][0] = i;
    for (int j = 1; j <= n; j++) a[0][j] = j;
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            int t = 1;
            if (s1[j - 1] == s2[i - 1]) t = 0;
            a[i][j] = min(a[i - 1][j], a[i][j - 1]) + 1;
            a[i][j] = min(a[i][j], a[i - 1][j - 1] + t);
        }
    }
    cout << a[m][n];
    return 0;
}