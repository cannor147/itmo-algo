#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class graph {

private:
    class edge {
    private:
        size_t index;
        int weight;
    public:
        edge() {
            index = 0;
            weight = 0;
        }
        explicit edge(size_t i, int w = 0) {
            index = i;
            weight = w;
        }
        size_t get_index() {
            return index;
        }
        int get_weight() {
            return weight;
        }
    };
    vector<vector<edge>> matrix;
    set<pair<size_t, size_t>> edges;

    void dfs_cc(size_t i, vector<size_t> &colors, vector<size_t> &cc) {
        if (colors[i] == 0) {
            colors[i]++;
            cc.push_back(i);
            if (matrix[i].empty()) return;
            for (auto &e : matrix[i]) {
                dfs_cc(e.get_index(), colors, cc);
            }
        }
    }
    void dfs_br(size_t i, int q, vector<size_t> &colors, vector<size_t> &a, vector<size_t> &b, vector<int> &result, size_t &t) {
        colors[i]++;
        a[i] = b[i] = t++;
        for (auto &e : matrix[i]) {
            if (e.get_weight() == q) continue;
            if (colors[e.get_index()] == 1) {
                a[i] = min(a[i], b[e.get_index()]);
            } else {
                dfs_br(e.get_index(), e.get_weight(), colors, a, b, result, t);
                a[i] = min(a[i], a[e.get_index()]);
                if (a[e.get_index()] > b[i]) {
                    result.push_back(e.get_weight());
                }
            }
        }
    }

public:
    graph() {
        matrix = vector<vector<edge>>();
        edges = set<pair<size_t, size_t>>();
    }
    explicit graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
        edges = set<pair<size_t, size_t>>();
    }
    size_t size() {
        return matrix.size();
    }
    bool is_edge(size_t i, size_t j) {
        return edges.count({i, j}) > 0;
    }
    void add_edge(size_t i, size_t j, size_t w = 0) {
        matrix[i].emplace_back(j, w);
        matrix[j].emplace_back(i, w);
        edges.emplace(i, j);
        edges.emplace(j, i);
    }
    void add_vertex() {
        matrix.emplace_back();
    }

    vector<size_t> get_components(size_t &k) {
        vector<size_t> colors(size(), 0), result(size());
        k = 0;
        for (size_t i = 0; i < size(); i++) {
            vector<size_t> cc;
            dfs_cc(i, colors, cc);
            for (size_t j = 0; j < cc.size(); j++) {
                result[cc[j]] = k;
            }
            if (!cc.empty()) k++;
            cc.clear();
        }
        return result;
    }
    vector<int> bridges() {
        vector<size_t> colors(size(), 0), a(size(), 0), b(size(), 0);
        vector<int> result;
        size_t t = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                dfs_br(i, -1, colors, a, b, result, t);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);

    size_t n, m;
    cin >> n >> m;
    graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1, i);
    }
    vector<int> br = g.bridges();
    cout << br.size() << endl;
    for (size_t i = 0; i < br.size(); i++) {
        cout << br[i] + 1 << " ";
    }
    return 0;
}