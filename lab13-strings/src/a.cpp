#include <iostream>
#include <vector>

using namespace std;

int main() {
    string p, t;
    cin >> p;
    cin >> t;
    if (p.length() > t.length()) {
        cout << 0;
        return 0;
    }
    vector<size_t> ans;
    for (size_t i = 0; i <= t.length() - p.length(); i++) {
        bool f = true;
        for (size_t j = 0; j < p.length(); j++) {
            if (t[i + j] != p[j]) f = false;
            if (!f) break;
        }
        if (f) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}