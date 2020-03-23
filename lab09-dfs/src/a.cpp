#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class oriental_graph {

private:
    vector<vector<size_t>> matrix;

    bool dfs(size_t i, vector<size_t> &colors, vector<size_t> &result) {
        bool f = true;
        if (colors[i] == 0) {
            colors[i]++;
            for (size_t d : matrix[i]) {
                f &= dfs(d, colors, result);
            }
            colors[i]++;
            result.push_back(i);
        } else if (colors[i] == 1) {
            f = false;
        }
        return f;
    }

public:
    explicit oriental_graph(size_t n) {
        matrix = vector<vector<size_t>>(n, vector<size_t>());
    }
    size_t getSize() {
        return matrix.size();
    }
    bool getEdge(size_t i, size_t j) {
        for (size_t d : matrix[i]) {
            if (d == j) return true;
        }
        return false;
    }
    void setEdge(size_t i, size_t j) {
        matrix[i].push_back(j);
    }
    vector<size_t> top_sort() {
        vector<size_t> colors(getSize(), 0);
        vector<size_t> result;
        bool f = true;
        for (size_t d = 0; d < getSize(); d++) {
            f &= dfs(d, colors, result);
        }
        if (!f) {
            result.clear();
        } else {
            std::reverse(result.begin(), result.end());
        }
        return result;
    }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    oriental_graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        cin >> a >> b;
        g.setEdge(a - 1, b - 1);
    }
    vector<size_t> t = g.top_sort();
    if (t.empty()) {
        cout << -1;
    } else {
        for (size_t i = 0; i < t.size(); i++) {
            cout << t[i] + 1 << " ";
        }
    }
    return 0;
}