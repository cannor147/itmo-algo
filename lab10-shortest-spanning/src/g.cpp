#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cfloat>
#include <math.h>
#include <iomanip>

using namespace std;

class graph {

private:
    vector<pair<int, int>> vertexes;

public:
    graph() {
        vertexes = vector<pair<int, int>>();
    }
    size_t size() {
        return vertexes.size();
    }
    double get_edge(size_t i, size_t j) {
        int a = vertexes[i].first, b = vertexes[i].second;
        int a1 = vertexes[j].first, b1 = vertexes[j].second;
        return sqrt((a - a1) * (a - a1) + (b - b1) * (b - b1));
    }
    void add_vertex(int a, int b) {
        vertexes.emplace_back(a, b);
    }

    double get_mst_weight() {
        double result = 0;
        vector<size_t> colors(size(), 0);
        vector<double> minw(size(), DBL_MAX);
        minw[0] = 0;
        for (size_t i = 0; i < size(); i++) {
            size_t min_j = SIZE_MAX;
            for (size_t j = 0; j < size(); j++) {
                if ((colors[j] == 0) && (min_j == SIZE_MAX || minw[j] < minw[min_j])) {
                    min_j = j;
                }
            }
            colors[min_j] = 1;
            result += minw[min_j];
            for (size_t j = 0; j < size(); j++) {
                if (j == min_j) continue;
                if (get_edge(j, min_j) < minw[j]) {
                    minw[j] = get_edge(j, min_j);
                }
            }
        }
        return result;
    }
};

int main() {
    size_t n;
    cin >> n;
    graph g;
    for (size_t i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g.add_vertex(a, b);
    }
    double mst = g.get_mst_weight();
    cout << fixed << setprecision(15) << mst;
    return 0;
}