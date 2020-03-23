#include <iostream>
using namespace std;

const int mod = 999999937;
typedef long long ll;
struct arr{
    ll mass[5][5];
};
arr e;
arr pClear();
arr pE();
arr pPower(arr, ll);
arr pMul(arr, arr);

int main() {/*
	freopen("sequences.in", "r", stdin);
	freopen("sequences.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 */
    ll n;
    e = pE();
    while (cin >> n){
        if (n == 0) break;
        arr p = pClear();
        p = pPower(p, n - 1);
        ll s = 0;
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                s = (s + p.mass[i][j]) % mod;
            }
        }
        cout << s << endl;
    }
    return 0;
}

arr pClear(){
    arr tmp;
    tmp.mass[0][0] = 1; tmp.mass[0][1] = 1; tmp.mass[0][2] = 1; tmp.mass[0][3] = 1; tmp.mass[0][4] = 1;
    tmp.mass[1][0] = 1; tmp.mass[1][1] = 1; tmp.mass[1][2] = 1; tmp.mass[1][3] = 1; tmp.mass[1][4] = 1;
    tmp.mass[2][0] = 1; tmp.mass[2][1] = 1; tmp.mass[2][2] = 1; tmp.mass[2][3] = 0; tmp.mass[2][4] = 0;
    tmp.mass[3][0] = 1; tmp.mass[3][1] = 1; tmp.mass[3][2] = 1; tmp.mass[3][3] = 1; tmp.mass[3][4] = 1;
    tmp.mass[4][0] = 1; tmp.mass[4][1] = 1; tmp.mass[4][2] = 1; tmp.mass[4][3] = 0; tmp.mass[4][4] = 0;
    return tmp;
}

arr pE(){
    arr tmp;
    tmp.mass[0][0] = 1; tmp.mass[0][1] = 0; tmp.mass[0][2] = 0; tmp.mass[0][3] = 0; tmp.mass[0][4] = 0;
    tmp.mass[1][0] = 0; tmp.mass[1][1] = 1; tmp.mass[1][2] = 0; tmp.mass[1][3] = 0; tmp.mass[1][4] = 0;
    tmp.mass[2][0] = 0; tmp.mass[2][1] = 0; tmp.mass[2][2] = 1; tmp.mass[2][3] = 0; tmp.mass[2][4] = 0;
    tmp.mass[3][0] = 0; tmp.mass[3][1] = 0; tmp.mass[3][2] = 0; tmp.mass[3][3] = 1; tmp.mass[3][4] = 0;
    tmp.mass[4][0] = 0; tmp.mass[4][1] = 0; tmp.mass[4][2] = 0; tmp.mass[4][3] = 0; tmp.mass[4][4] = 1;
    return tmp;
}

arr pPower(arr m, ll n){
    arr t = e;
    if (n != 0){
        if (n == 1){
            t = m;
        }else{
            if (n % 2 == 0){
                t = pPower(m, n / 2);
                t = pMul(t, t);
            }else{
                t = pMul(m, pPower(m, n - 1));
            }
        }
    }
    return t;
}

arr pMul(arr a, arr b){
    arr tmp;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            ll s = 0;
            for (int g = 0; g < 5; g++){
                s = (((a.mass[i][g] * b.mass[g][j]) % mod) + s) % mod;
            }
            tmp.mass[i][j] = s;
        }
    }
    return tmp;
}