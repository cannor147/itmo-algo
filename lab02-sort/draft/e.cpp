#include <iostream>

using namespace std;
const int s = 1001;

int main() {/*
	freopen("radixsort.in", "r", stdin);
	freopen("radixsort.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);*/

    int n, m, k, t, s;
    int c[26];
    char a[s][s], b[s][s];
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++){
        std::getline(cin, a[i]);
    }
    for (int i = 0; i < n; i++){
        cout << a[i] << '\n';
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b[i][j] = a[i][j];
        }
    }

    for (int j = 0; j < k; j++){
        for (int i = 0; i < 26; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[(int)(a[i][m-j]) - (int)('a')]++;
        s = 0;
        for (int i = 0; i < 26; i++){
            s = s + c[i];
            if (c[i] != 0){
                c[i] = s-1;
            }
        }
        for (int i = 0; i < n; i++){
            t = (int)(a[i][m-j]) - (int)('a');
            for (int h = 0; h < m; h++)	b[c[t]][h] = a[i][h];
            c[t]--;
        }
    }
    for (int i = 0; i < n; i++){
        cout << a[i] << '\n';
    }
}