#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int rr = 1000000;

enum Command {
    ADD, SET, NO
};
class Segment_tree {

private:
    struct Node {
        long long max, add;
        Command command;
        Node() {
            this->max = 0;
            this->add = 0;
            this->command = NO;
        }
        Node(long long value) {
            this->max = value;
            this->add = 0;
            this->command = NO;
        }
        void set(long long value1, long long value2, Command value3) {
            this->max = value1;
            this->add = value2;
            this->command = value3;
        }
    };
    int size;
    vector<Node> tree;
    void update(int index) {
        tree[index].max = max(tree[2 * index].max, tree[2 * index + 1].max);
    }
    void lazy_propagation(int index) {
        int ch1 = 2 * index ;
        int ch2 = 2 * index + 1;
        if (tree[index].command == ADD) {
            tree[index].max += tree[index].add;
            if (index < size) {
                switch (tree[ch1].command) {
                    case ADD: tree[ch1].set(tree[ch1].max, tree[ch1].add + tree[index].add, ADD); break;
                    case SET: tree[ch1].set(tree[ch1].max, tree[ch1].add + tree[index].add, SET); break;
                    case NO: tree[ch1].set(tree[ch1].max, tree[index].add, ADD); break;
                }
                switch (tree[ch2].command) {
                    case ADD: tree[ch2].set(tree[ch2].max, tree[ch2].add + tree[index].add, ADD); break;
                    case SET: tree[ch2].set(tree[ch2].max, tree[ch2].add + tree[index].add, SET); break;
                    case NO: tree[ch2].set(tree[ch2].max, tree[index].add, ADD); break;
                }
            }
        } else if (tree[index].command == SET) {
            tree[index].max = tree[index].add;
            if (index < size) {
                tree[ch1].set(tree[ch1].max, tree[index].add, SET);
                tree[ch2].set(tree[ch2].max, tree[index].add, SET);
            }
        }
        tree[index].set(tree[index].max, 0, NO);
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
    long long get_max(const int i, const int lb, const int rb, const int l, const int r) {
        lazy_propagation(i);
        if (l > r) return 0;
        if (l == lb && r == rb) return tree[i].max;
        int mid = (lb + rb + 1) / 2;
        return max(get_max(i * 2, lb, mid - 1, l, min(r, mid - 1)), get_max(i * 2 + 1, mid, rb, max(l, mid), r));
    }
    long long get_index_max(const int i, const int l, const int r) {
        lazy_propagation(i);
        if (i >= size) return l - rr;
        lazy_propagation(2 * i);
        lazy_propagation(2 * i + 1);
        int mid = (l + r + 1) / 2;
        if (tree[2 * i].max == tree[i].max) {
            return get_index_max(i * 2, l, min(r, mid - 1));
        } else {
            return get_index_max(i * 2 + 1, max(l, mid), r);
        }
    }
};
struct X {
    bool is_closing;
    int my_x, upper_y, lower_y;

    X(bool is_closing, int my_x, int lower_y, int upper_y) {
        this->is_closing = is_closing;
        this->my_x = my_x + rr;
        this->lower_y = lower_y + rr;
        this->upper_y = upper_y + rr;
    }
    bool operator<(const X &arg) {
        return (this->my_x < arg.my_x) || ((this->my_x == arg.my_x) && (this->is_closing < arg.is_closing));
    }
    int get_x() {
        return my_x - rr;
    }
};

int main() {
    freopen("windows.in", "r", stdin);
    freopen("windows.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    vector<long long> arr(2 * rr + 1, 0);
    vector<X> coordinates;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        coordinates.emplace_back(false, x1, y1, y2);
        coordinates.emplace_back(true, x2, y1, y2);
    }
    sort(coordinates.begin(), coordinates.end());
    Segment_tree tree(arr);
    long long max_x = 0, max_y = 0, max_number = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (coordinates[i].is_closing) {
            tree.change(ADD, -1, 1, 0, tree.get_size() - 1, coordinates[i].lower_y, coordinates[i].upper_y);
        } else {
            tree.change(ADD, 1, 1, 0, tree.get_size() - 1, coordinates[i].lower_y, coordinates[i].upper_y);
            long long tmp = tree.get_max(1, 0, tree.get_size() - 1, 0, tree.get_size() - 1);
            if (tmp > max_number) {
                max_number = tmp;
                max_x = coordinates[i].get_x();
                max_y = tree.get_index_max(1, 0, tree.get_size() - 1);
            }
        }
    }
    cout << max_number << endl << max_x << " " << max_y;
}