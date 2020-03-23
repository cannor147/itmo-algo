#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
unsigned a, b, cur = 0;
unsigned nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}
unsigned nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

vector<unsigned> operator*(vector<unsigned> const &first, vector<unsigned> const &second) {
    vector<unsigned> result;
    unsigned i = 0, j = 0;
    while (i < first.size() || j < second.size()) {
        if (i >= first.size()) {
            result.push_back(second[j]);
            j++;
        } else if (j >= second.size()) {
            result.push_back(first[i]);
            i++;
        } else {
            if (first[i] <= second[j]) {
                result.push_back(first[i]);
                i++;
            } else {
                result.push_back(second[j]);
                j++;
            }
        }
    }
    return result;
}
class Segment_tree {

private:
    struct Node {
        vector<unsigned> sorted;
        Node() {
            sorted.resize(0);
        }
        Node(unsigned value) {
            this->sorted.push_back(value);
        }
    };
    unsigned size;
    vector<Node> tree;
    void update(unsigned index) {
        tree[index].sorted = tree[2 * index].sorted * tree[2 * index + 1].sorted;
    }

public:
    Segment_tree(vector<unsigned> &arr) {
        unsigned n = arr.size();
        size = 1 << (((unsigned) log2(n)) + (((n & (n - 1)) == 0) ? 0 : 1));
        tree.resize(2 * size, Node());
        for (unsigned i = 0; i < n; i++) tree[size + i] = Node(arr[i]);
        for (unsigned i = size - 1; i >= 1; i--) update(i);
    }
    unsigned get_size() {
        return size;
    }
    unsigned get_ans(const unsigned x, const unsigned y, const unsigned &i, const unsigned &lb, const unsigned &rb, const unsigned &l, const unsigned &r) {
        if (l > r) return 0;
        if (l == lb && r == rb) return count(x, y, tree[i].sorted);
        unsigned mid = (lb + rb + 1) / 2;
        return get_ans(x, y, i * 2, lb, mid - 1, l, min(r, mid - 1)) + get_ans(x, y, i * 2 + 1, mid, rb, max(l, mid), r);
    }
    unsigned count(unsigned x, unsigned y, vector<unsigned> &v) {
        if (v.size() == 1) {
            if (v[0] >= x && v[0] <= y) {
                return 1;
            } else {
                return 0;
            }
        }
        auto w1 = static_cast<unsigned>(distance(v.begin(), lower_bound(v.begin(), v.end(), x)) + 4);
        auto w2 = static_cast<unsigned>(distance(v.begin(), upper_bound(v.begin(), v.end(), y)) + 4);
        unsigned ans = w2 - w1;
        return ans;
    }
};

int main() {
    freopen("find2d.in", "r", stdin);
    freopen("find2d.out", "w", stdout);

    unsigned n = (1 << 17), q;
    vector<unsigned> arr(n);
    cin >> q >> a >> b;
    arr.resize(n);
    for (unsigned i = 0; i < n; i++) {
        arr[i] = nextRand24();
    }
    unsigned sum = 0;
    Segment_tree tree(arr);
    for (unsigned i = 0; i < q; i++) {
        unsigned ll = nextRand17();
        unsigned rr = nextRand17();
        unsigned l = min(ll, rr), r = max(ll, rr);
        unsigned xx = nextRand24();
        unsigned yy = nextRand24();
        unsigned x = min(xx, yy), y = max(xx, yy);
        unsigned c = tree.get_ans(x, y, 1, 0, tree.get_size() - 1, l, r);
        b += c;
        sum += c;
    }
    cout << sum;
}