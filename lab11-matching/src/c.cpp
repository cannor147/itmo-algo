#include <iostream>
#include <vector>

using namespace std;

class bipartial_graph {

private:
    vector<vector<size_t>> right, left;
    bool dfs_kunh(size_t i, vector<size_t> &colors, vector<size_t> &matching) {
        if (colors[i] == 0) {
            colors[i] = 1;
            for (auto j : right[i]) {
                if (matching[j] == SIZE_MAX || dfs_kunh(matching[j], colors, matching)) {
                    matching[j] = i;
                    return true;
                }
            }
        }
        return false;
    }
    void dfs_mvc(size_t i, vector<size_t> &now, vector<size_t> &next, bool o) {
        if (now[i] == 1) return;
        now[i] = 1;
        vector<vector<size_t>> &n = (o) ? left : right;
        for (size_t j = 0; j < n[i].size(); j++) {
            dfs_mvc(n[i][j], next, now, !o);
        }
    }

public:
    bipartial_graph(size_t n, size_t m) {
        left.resize(n);
        right.resize(m);
    }
    void add_edge(size_t i, size_t j) {
        add_ledge(i, j);
        add_redge(i, j);
    }
    void add_ledge(size_t i, size_t j) {
        left[i].push_back(j);
    }
    void add_redge(size_t i, size_t j) {
        right[j].push_back(i);
    }
    size_t lsize() {
        return left.size();
    }
    size_t rsize() {
        return right.size();
    }

    vector<pair<size_t, size_t>> find_maximum_matching() {
        vector<size_t> matching(lsize(), SIZE_MAX);
        for (size_t i = 0; i < rsize(); i++) {
            vector<size_t> colors(rsize(), 0);
            dfs_kunh(i, colors, matching);
        }
        vector<pair<size_t, size_t>> result;
        for (size_t i = 0; i < lsize(); i++) {
            if (matching[i] != SIZE_MAX) {
                result.push_back({i, matching[i]});
            }
        }
        return result;
    }
    pair<vector<size_t>, vector<size_t>> find_minimum_vertex_covering(vector<size_t> &free) {
        vector<size_t> lcolors(lsize(), 0), rcolors(rsize(), 0);
        for (size_t i = 0; i < free.size(); i++) {
            dfs_mvc(free[i], lcolors, rcolors, true);
        }
        vector<size_t> rresult, lresult;
        for (size_t i = 0; i < lsize(); i++) {
            if (lcolors[i] == 0) {
                lresult.push_back(i);
            }
        }
        for (size_t i = 0; i < rsize(); i++) {
            if (rcolors[i] == 1) {
                rresult.push_back(i);
            }
        }
        return {lresult, rresult};
    }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    bipartial_graph g(n, m);
    vector<vector<size_t>> edges(n);
    for (size_t i = 0; i < n; i++) {
        size_t k;
        cin >> k;
        edges[i].resize(k);
        for (size_t j = 0; j < k; j++) {
            cin >> edges[i][j];
            edges[i][j]--;
        }
    }
    vector<size_t> free;
    for (size_t i = 0; i < n; i++) {
        size_t b;
        cin >> b;
        if (!b) {
            free.push_back(i);
            b = SIZE_MAX;
        } else {
            b--;
        }
        for (size_t j = 0; j < edges[i].size(); j++) {
            if (edges[i][j] == b) {
                g.add_redge(i, edges[i][j]);
            } else {
                g.add_ledge(i, edges[i][j]);
            }
        }
    }
    auto ans = g.find_minimum_vertex_covering(free);
    cout << ans.first.size() + ans.second.size();
    cout << endl << ans.first.size() << " ";
    for (auto i : ans.first) {
        cout << i + 1 << " ";
    }
    cout << endl << ans.second.size() << " ";
    for (auto i : ans.second) {
        cout << i + 1 << " ";
    }
    return 0;
}