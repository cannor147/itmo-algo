#include <iostream>
#include <vector>

using namespace std;

class Sorting_network {

private:
    int number;
    vector<vector<pair<int, int>>> layers;
    void add_head(int k, int first, int last) {

    }
    void add_layers(int k, int first, int last) {
        if (first == last) return;
        int r = (last - first + 1) / 2;
        if (k >= layers.size()) layers.push_back({});
        for (int i = first; i < first + r; i++) {
            layers[k].push_back(make_pair(i, last - i + first));
        }
        if ((last - first + 1) % 2 != 0) {
            k++;
            if (k >= layers.size()) layers.push_back({});
            layers[k].push_back(make_pair(first + r, last));
        }
        k++;
        add_layers(k, first, last - r);
        add_layers(k, last - r + 1, last);
    }

public:
    Sorting_network() {
        this->number = 0;
        this->layers.resize(0);
    }
    Sorting_network(int number, vector<vector<pair<int, int>>> layers) {
        this->number = number;
        this->layers = layers;
    }
    int get_size() {
        return layers.size();
    }
    vector<bool> sort(vector<bool> original) {
        for (int i = 0; i < get_size(); i++) {
            for (int j = 0; j < layers[i].size(); j++) {
                bool x = original[layers[i][j].first];
                bool y = original[layers[i][j].second];
                original[layers[i][j].first] = min(x, y);
                original[layers[i][j].second] = max(x, y);
            }
        }
        return original;
    }
    bool is_sorted(vector<bool> &original) {
        auto result = sort(original);
        for (int i = 1; i < result.size(); i++) {
            if (result[i] < result[i - 1]) {
                return false;
            }
        }
        return true;
    }
    bool check() {
        int i = 0;
        bool ans = true;
        vector<bool> original(number, false);
        while (i < (1 << number)) {
            int k = i;
            for (int j = 0; j < number; j++) {
                original[j] = k % 2;
                k /= 2;
            }
            ans &= is_sorted(original);
            if (!ans) return false;
            i++;
        }
        return true;
    }
    void generate(int n) {
        number = n;
        add_head(0, 1, n);
        int k = layers.size();
        add_layers(k, 1, n);
    }
    void print() {
        int n = number, m = 0, k = layers.size();
        for (int i = 0; i < k; i++) {
            m += layers[i].size();
        }
        cout << n << " " << m << " " << k << endl;
        for (int i = 0; i < k; i++) {
            cout << layers[i].size() << " ";
            for (int j = 0; j < layers[i].size(); j++) {
                cout << layers[i][j].first << " " << layers[i][j].second << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    Sorting_network my_network;
    my_network.generate(n);
    my_network.print();
    return 0;
}