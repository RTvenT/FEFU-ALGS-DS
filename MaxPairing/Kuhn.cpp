
#include <bits/stdc++.h>


using namespace std;


class Kuhn {
private:
    int n_left, n_right;

    vector<vector<int>> graph;
    vector<int> pair_right; 
    vector<bool> visited;

    bool dfs(int u) {
        if (visited[u]) return false;

        visited[u] = true;

        for (int v: graph[u]) {
            if (pair_right[v] == -1 || dfs(pair_right[v])) {
                pair_right[v] = u;
                return true;
            }
        }

        return false;
    }

public:
    Kuhn(int n_left, int n_right): 
        n_left(n_left),
        n_right(n_right),
        graph(n_left),
        pair_right(n_right, -1),
        visited(n_left, false) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
    }

    int max_matching() {
        fill(pair_right.begin(), pair_right.end(), -1);

        int matching_size = 0;

        for (int u = 0; u < n_left; ++u) {
            fill(visited.begin(), visited.end(), false);

            if (dfs(u)) {
                ++matching_size;
            }
        }

        return matching_size;
    }

    const vector<int>& get_matching() const {
        return pair_right;
    }
};


int main() {
    Kuhn kuhn(3, 3);

    // A = 0, B = 1, C = 2
    // Правая доля: 1 = 0, 2 = 1, 3 = 2

    kuhn.add_edge(0, 0);
    kuhn.add_edge(0, 1);

    kuhn.add_edge(1, 1);
    kuhn.add_edge(1, 2);

    kuhn.add_edge(2, 0);

    cout << kuhn.max_matching() << '\n';

    return 0;
}
