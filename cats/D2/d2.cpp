#include <bits/stdc++.h>


using namespace std;


struct Trip {
    int x0, x1, y0, y1, t0, t1;
};


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


int dist(int x0, int x1, int y0, int y1) {
    return abs(x0 - x1) + abs(y0 - y1);
}


int main() {
    int n;
    cin >> n;

    vector<Trip> trips(n);
    Kuhn kuhn(n, n);
    
    
    for (int i = 0; i < n; ++i) {
        cin >> trips[i].x0 >> trips[i].y0 >> trips[i].x1 >> trips[i].y1 >> trips[i].t0;
        trips[i].t1 = trips[i].t0 + dist(trips[i].x0, trips[i].x1, trips[i].y0, trips[i].y1);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++ j) { 
            if (i == j) continue;

            const Trip& left = trips[i];
            const Trip& right = trips[j];

            if (left.t1 + dist(left.x1, right.x0, left.y1, right.y0) <= right.t0) {
                kuhn.add_edge(i, j);
            }
        }
    }

    int m = kuhn.max_matching();
    int bus_cnt = n - m;

    vector<int> pair_right = kuhn.get_matching();

    vector<int> next(n, -1);
    vector<int> prev(n, -1);

    for (int v = 0; v < n; ++v) {
        if (pair_right[v] != -1) {
            prev[v] = pair_right[v];
            next[pair_right[v]] = v;
        }
    }

    cout << bus_cnt << '\n';

    for (int u = 0; u < n; ++u) {
        if (prev[u] == -1) {
            int cnt = 1;
            vector<int> route;
            route.push_back(u);

            for (int v = next[u]; v != -1; v = next[v]) {
                cnt++;
                route.push_back(v);
            }


            cout << cnt << ' ';
            for (int t: route) cout << t+1 << ' ';
            cout << '\n';
        }
    }
    
    return 0;
}
