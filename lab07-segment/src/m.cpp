#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct P {
    int index, depth;
    P() {
        this->depth = INT32_MAX;
        this->index = 0;
    }
    P(int index, int depth) {
        this->index = index;
        this->depth = depth;
    }
};
P min(const P &first, const P &second) {
    if (first.depth < second.depth) {
        return first;
    } else {
        return second;
    }
}
class Sparse_table {

private:
    vector<vector<P>> table;

public:
    Sparse_table(vector<P> &arr) {
        int s = arr.size();
        table.resize((int)444444, vector<P>(20, P()));
        for (int j = 0; (1 << j) <= s; j++) {
            for (int i = 0; i < s; i++) {
                if (j == 0) {
                    table[i][j] = arr[i];
                } else {
                    table[i][j] = min(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
                }
            }
        }
    }
    P get_min(int l, int r) {
        int j = 0;
        while ((1 << j + 1) <= r - l + 1) {
            j++;
        }
        return min(table[l][j], table[r - (1 << j) + 1][j]);
    }
};
class Binary_tree {

private:
    struct Node {
        int number;
        vector<int> children;
        Node() {
            this->number = 0;
        }
        Node(int number) {
            this->number = number;
        }
    };
    vector<Node> nodes;

public:
    Binary_tree(int n) {
        for (int i = 0; i < n; i++) {
            nodes.emplace_back(i);
        }
    }
    int size() {
        return nodes.size();
    }
    int add_node(int parent, int number) {
        nodes[parent].children.push_back(number);
    }
    void count_arr(vector<P> *arr, int number, int depth) {
        arr->emplace_back(number, depth);
        for (int &i : nodes[number].children) {
            count_arr(arr, i, depth + 1);
            arr->emplace_back(number, depth);
        }
    }
};

int main() {
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Binary_tree bin_tree(n);
    string word;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        bin_tree.add_node(p, i);
    }
    vector<P> arr;
    bin_tree.count_arr(&arr, 0, 0);
    int s = bin_tree.size();
    vector<pair<int, int>> pos(s, make_pair(-1, -1));
    for (int i = 0; i < arr.size(); i++) {
        P &c = arr[i];
        if (pos[c.index].first == -1) pos[c.index].first = i;
        pos[c.index].second = i;
    }

    int x, y, z;
    vector<int> h(2 * m + 1);
    cin >> h[1] >> h[2] >> x >> y >> z;
    for (int i = 3; i < h.size(); i++) {
        h[i] = (int)(((long long)x * (long long)h[i - 2] + (long long)y * (long long)h[i - 1] + (long long)z) % n);
    }

    Sparse_table table(arr);
    P ans;
    long long sum = 0;
    int q1 = h[1], q2 = h[2];
    for (int j = 1; j <= m; j++) {
        int l = min(pos[q1].first, pos[q2].first);
        int r = max(pos[q1].second, pos[q2].second);
        ans = table.get_min(l, r);
        sum += ans.index;
        q1 = ((h[2 * j + 1] + ans.index) % n);
        q2 = h[2 * j + 2];
    }
    cout << sum;
}