#include <iostream>
using namespace std;

int main() {
    int n, m, k = 0;
    cin >> n >> m;
    int j = 1;
    for (int i = 2; i <= n; i++){
        k++;
        if (k > m) break;
        cout << "1 " << i << " " << j << endl;
        for (int g = 1; g < i; g++){
            k++;
            if (k > m) break;
            cout << "0 " << g << " " << g + 1 << endl;
        }
        j = i;
    }
    return 0;
}