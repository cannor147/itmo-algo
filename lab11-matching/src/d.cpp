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
    pair<vector<size_t>, vector<size_t>> fill_mvc(vector<size_t> &free) {
        vector<size_t> lcolors(lsize(), 0), rcolors(rsize(), 0);
        for (size_t i = 0; i < free.size(); i++) {
            if (free[i] == 1) continue;
            dfs_mvc(i, lcolors, rcolors, true);
        }
        return {lcolors, rcolors};
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
    pair<vector<size_t>, vector<size_t>> find_minimum_vertex_covering() {
        auto max_matching = find_maximum_matching();
        vector<size_t> free(lsize(), 0), matched(lsize());
        for (size_t i = 0; i < max_matching.size(); i++) {
            free[max_matching[i].first] = 1;
            matched[max_matching[i].first] = max_matching[i].second;
        }
        bipartial_graph u(lsize(), rsize());
        for (size_t i = 0; i < lsize(); i++) {
            for (size_t j = 0; j < left[i].size(); j++) {
                if (free[i] == 1 || matched[i] == left[i][j]) {
                    u.add_redge(i, left[i][j]);
                } else {
                    u.add_ledge(i, left[i][j]);
                }
            }
        }
        auto result = u.fill_mvc(free);
        vector<size_t> rresult, lresult;
        for (size_t i = 0; i < lsize(); i++) {
            if (result.first[i] == 0) {
                lresult.push_back(i);
            }
        }
        for (size_t i = 0; i < rsize(); i++) {
            if (result.second[i] == 1) {
                rresult.push_back(i);
            }
        }
        return {lresult, rresult};
    }
    pair<vector<size_t>, vector<size_t>> find_maximum_indepentent_set() {
        auto max_matching = find_maximum_matching();
        vector<size_t> free(lsize(), 0), matched(lsize());
        for (size_t i = 0; i < max_matching.size(); i++) {
            free[max_matching[i].first] = 1;
            matched[max_matching[i].first] = max_matching[i].second;
        }
        bipartial_graph u(lsize(), rsize());
        for (size_t i = 0; i < lsize(); i++) {
            for (size_t j = 0; j < left[i].size(); j++) {
                if (free[i] == 1 && matched[i] == left[i][j]) {
                    u.add_redge(i, left[i][j]);
                } else {
                    u.add_ledge(i, left[i][j]);
                }
            }
        }
        auto result = u.fill_mvc(free);
        vector<size_t> rresult, lresult;
        for (size_t i = 0; i < lsize(); i++) {
            if (result.first[i] == 1) {
                lresult.push_back(i);
            }
        }
        for (size_t i = 0; i < rsize(); i++) {
            if (result.second[i] == 0) {
                rresult.push_back(i);
            }
        }
        return {lresult, rresult};
    }
};

void kek() {
    size_t n, m;
    cin >> n >> m;
    bipartial_graph g(n, m);
    vector<vector<size_t>> edges(n, vector<size_t>(m, 0));
    for (size_t i = 0; i < n; i++) {
        bool f = true;
        while (f) {
            size_t w;
            cin >> w;
            if (w == 0) {
                f = false;
            } else {
                edges[i][w - 1]++;
            }
        }
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (edges[i][j] == 1) continue;
            g.add_edge(i, j);
        }
    }
    auto ans = g.find_maximum_indepentent_set();
    cout << ans.first.size() + ans.second.size() << endl;
    cout << ans.first.size() << " " << ans.second.size() << endl;
    for (auto i : ans.first) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (auto i : ans.second) {
        cout << i + 1 << " ";
    }
    cout << endl << endl;
}

int main() {
    size_t k;
    cin >> k;
    for (size_t i = 0; i < k; i++) {
        kek();
    }
    return 0;
}