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
    int n, m;
    cin >> n >> m;

    vector<string> board(n);

    for (int i = 0; i < n; ++i) {
        cin >> board[i];
    }

    vector<pair<int, int>> left_coords; // left graph part -> board coords
    vector<pair<int, int>> right_coords; // right graph part -> board coords

    vector<vector<int>> left_nodes(n, vector<int>(m, -1)); // board coords -> left graph part
    vector<vector<int>> right_nodes(n, vector<int>(m, -1)); // board coords -> right graph part

    int dc[4] = {-1, 1, 0, 0};
    int dr[4] = {0, 0, -1, 1};
    
    int left = 0;
    int right = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = board[i][j];

            if (c == '#') continue;
            
            if ((i + j) % 2 == 0) {
                left_coords.push_back({i, j});
                left_nodes[i][j] = left++;
            } else {
                right_coords.push_back({i, j});
                right_nodes[i][j] = right++;      
            }
        }
    }

    Kuhn kuhn(left, right);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int left_node = left_nodes[i][j];
            if (left_node == -1) continue;

            for (int d = 0; d < 4; ++d) {
                int r_i = i + dr[d];
                int r_j = j + dc[d];

                if (r_i < 0 || r_i >= n || r_j < 0 || r_j >= m) continue;
                int right_node = right_nodes[r_i][r_j];
                if (right_node == -1) continue;
                
                kuhn.add_edge(left_node, right_node);
            }
        }
    }

    int max_cnt = kuhn.max_matching();
    vector<int> pair_right = kuhn.get_matching();

    cout << max_cnt << '\n';

    for (int r = 0; r < right; ++r) { 
        int l = pair_right[r];

        if (l == -1) continue;

        pair<int, int> r_pos = right_coords[r];
        pair<int, int> l_pos = left_coords[l];

        cout << r_pos.first+1 << ' ' << r_pos.second+1 << ' ' << l_pos.first+1 << ' ' << l_pos.second+1 << '\n';
    }
    
    
    return 0;
}
