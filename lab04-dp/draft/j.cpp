#include <iostream>
#include <string>
using namespace std;

int a[10001][10001];
int pi[10001][10001];
int pj[10001][10001];
int n = 0, m = 0;
string s1, s2;
void printing();

int main() {
    cin >> s1;
    cin >> s2;
    n = (int) (s1.length());
    m = (int) (s2.length());
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            if (s1[j - 1] == s2[i - 1]){
                a[i][j] = a[i - 1][j - 1] + 1;
                pi[i][j] = i - 1;
                pj[i][j] = j - 1;
            }else{
                a[i][j] = a[i - 1][j];
                pi[i][j] = i - 1;
                pj[i][j] = j;
                if (a[i][j - 1] > a[i][j]){
                    a[i][j] = a[i][j - 1];
                    pi[i][j]++;
                    pj[i][j]--;
                }
            }
        }
    }
    printing();
    cout << endl;
    return 0;
}

void printing(){
    if (m == 0 || n == 0) return;
    bool f = (m == pi[m][n] + 1 && n == pj[m][n] + 1);
    m = pi[m][n];
    n = pj[m][n];
    char r = s2[m];
    printing();
    if (f) cout << r;
}