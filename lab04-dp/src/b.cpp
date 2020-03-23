#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 1111111111;
const int h = 300001;
int a[h], d[h], p[h], l[h], r[h];

int main(){
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, s = 0, j = 0;
    cin >> n;
    d[0] = -inf;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        d[i + 1] = inf;
    }

    for (int i = 0; i < n; i++){
        j = (int) (upper_bound(d, d + n, a[i]) - d);
        if (d[j-1] < a[i] && a[i] < d[j]){
            d[j] = a[i];
            p[j] = i;
            l[i] = p[j - 1];
            s = max(s, j);
        }
    }
    j = p[s];
    for (int i = 0; i < s; i++){
        r[i] = a[j];
        j = l[j];
    }
    cout << s << endl;
    for (int i =0; i < s; i++) cout << r[s - i - 1] << " ";
    return 0;
}