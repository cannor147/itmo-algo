#include <iostream>
#include <memory.h>
using namespace std;

const int h = 1004, hh = h * h;
bool visited[h][h];
int x[h][h], y[h][h], a[hh], b[hh], c[hh], m[h][10];

int main(){
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, u, v;
    int i, j, g;
    cin >> n;
    for (i = 0; i < n; i++){
        for (j = 0; j <= 9; j++){
            m[i][j] = (i * 10 + j) % n;
        }
    }
    u = 0; v = 0;
    i = 0; j = 1; g = 0;
    memset(visited, false, sizeof(visited));
    visited[0][0] = true;
    while ((i < j) && ((u != 0) || (v != n))){
        for (int g = 0; g <= min(n - v, 9); g++){
            if (!(visited[m[u][g]][v + g])){
                visited[m[u][g]][v + g] = true;
                a[j] = m[u][g];
                b[j] = v + g;
                x[a[j]][b[j]] = u;
                y[a[j]][b[j]] = v;
                j++;
            }
        }
        i++;
        u = a[i];
        v = b[i];
    }
    i = 0; j = n; g = 0;
    while (j > 0){
        c[g] = j - y[i][j];
        int q = i;
        i = x[q][j];
        j = y[q][j];
        g++;
    }
    for (i = g - 1; i >= 0; i--) cout << c[i];
    return 0;
}

