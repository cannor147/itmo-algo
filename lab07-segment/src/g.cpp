#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

enum Command {
    ADD, SET, NO
};
class Segment_tree {

private:
    struct Node {
        long long min, add;
        Command command;
        Node() {
            this->min = INT64_MAX;
            this->add = 0;
            this->command = NO;
        }
        Node(long long value) {
            this->min = value;
            this->add = 0;
            this->command = NO;
        }
        void set(long long value1, long long value2, Command value3) {
            this->min = value1;
            this->add = value2;
            this->command = value3;
        }
    };
    int size;
    vector<Node> tree;
    void update(int index) {
        tree[index].min = min(tree[2 * index].min, tree[2 * index + 1].min);
    }
    void lazy_propagation(int index) {
        int ch1 = 2 * index ;
        int ch2 = 2 * index + 1;
        if (tree[index].command == ADD) {
            tree[index].min += tree[index].add;
            if (index < size) {
                switch (tree[ch1].command) {
                    case ADD: tree[ch1].set(tree[ch1].min, tree[ch1].add + tree[index].add, ADD); break;
                    case SET: tree[ch1].set(tree[ch1].min, tree[ch1].add + tree[index].add, SET); break;
                    case NO: tree[ch1].set(tree[ch1].min, tree[index].add, ADD); break;
                }
                switch (tree[ch2].command) {
                    case ADD: tree[ch2].set(tree[ch2].min, tree[ch2].add + tree[index].add, ADD); break;
                    case SET: tree[ch2].set(tree[ch2].min, tree[ch2].add + tree[index].add, SET); break;
                    case NO: tree[ch2].set(tree[ch2].min, tree[index].add, ADD); break;
                }
            }
        } else if (tree[index].command == SET) {
            tree[index].min = tree[index].add;
            if (index < size) {
                tree[ch1].set(tree[ch1].min, tree[index].add, SET);
                tree[ch2].set(tree[ch2].min, tree[index].add, SET);
            }
        }
        tree[index].set(tree[index].min, 0, NO);
    }

public:
    Segment_tree(vector<long long> &arr) {
        int n = arr.size();
        size = 1 << (((int) log2(n)) + (((n & (n - 1)) == 0) ? 0 : 1));
        tree.resize(2 * size, Node());
        for (int i = 0; i < n; i++) tree[size + i] = Node(arr[i]);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    int get_size() {
        return size;
    }
    void change(Command c, const long long x, const int i, const int lb, const int rb, const int l, const int r) {
        lazy_propagation(i);
        if (l > r) return;
        if (l == lb && r == rb) {
            tree[i].command = c;
            tree[i].add = x;
            lazy_propagation(i);
            return;
        }
        int mid = (lb + rb + 1) / 2;
        change(c, x, i * 2, lb, mid - 1, l, min(r, mid - 1));
        change(c, x, i * 2 + 1, mid, rb, max(l, mid), r);
        update(i);
    }
    long long get_min(const int i, const int lb, const int rb, const int l, const int r) {
        lazy_propagation(i);
        if (l > r) return INT64_MAX;
        if (l == lb && r == rb) return tree[i].min;
        int mid = (lb + rb + 1) / 2;
        return min(get_min(i * 2, lb, mid - 1, l, min(r, mid - 1)), get_min(i * 2 + 1, mid, rb, max(l, mid), r));
    }
};

int main() {
    freopen("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    vector<long long> arr;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Segment_tree tree(arr);
    string word;
    while (cin >> word) {
        int a, b;
        cin >> a >> b;
        if (word == "min") {
            cout << tree.get_min(1, 0, tree.get_size() - 1, a - 1, b - 1) << endl;
        } else {
            long long c;
            cin >> c;
            if (word == "set") tree.change(SET, c, 1, 0, tree.get_size() - 1, a - 1, b - 1);
            if (word == "add") tree.change(ADD, c, 1, 0, tree.get_size() - 1, a - 1, b - 1);
        }
    }
}