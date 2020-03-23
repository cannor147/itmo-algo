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
        return edges.count({i, j}) > 0 || edges.count({j, i}) > 0;
    }
    void add_edge(size_t i, size_t j, size_t w = 0) {
        if (is_edge(i, j)) return;
        matrix[i].emplace_back(j, w);
        matrix[j].emplace_back(i, w);
        edges.emplace(i, j);
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
};

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);

    size_t n, m;
    cin >> n >> m;
    graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1);
    }
    size_t k = 0;
    vector<size_t> comp = g.get_components(k);
    cout << k << endl;
    for (size_t i = 0; i < comp.size(); i++) {
        cout << comp[i] + 1 << " ";
    }
    return 0;
}