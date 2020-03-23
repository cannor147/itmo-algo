#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    double a, d[1000];
    cin >> n >> a;
    double l = 0, r = a;
    double mid;
    bool g;
    for (int j = 0; j < 50; j++){
        mid = (l + r) / 2;
        d[0] = a;
        d[1] = mid;
        g = true;
        for (int i = 2; i < n; i++){
            d[i] = 2*d[i - 1] - d[i - 2] + 2;
            if (d[i] <= 0) g = false;
        }
        if (g){
            r = mid;
        }else{
            l = mid;
        }
    }
    cout << fixed << setprecision(2) << d[n-1];
}