// Undirected graphs representations
#include <bits/stdc++.h>


using namespace std;


void print_edges_list(const vector<pair<int, int>>& edges) {
    cout << "\n" << "---------edges-list---------" << "\n";
    for (const auto& [a, b] : edges) {
        cout << a << " " << b << "\n";
    }
}

void print_adj_mat(const vector<vector<int>>& mat) {
    cout << "\n" << "---------adjacency-matrix---------" << "\n";
    for (const auto& row : mat) {
        for (int v : row) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

void print_adj_list(const vector<vector<int>>& adj_list) {
    cout << "\n" << "---------adjacency-list---------" << "\n";
    for (size_t i = 0; i < adj_list.size(); ++i) { 
        cout << i << ": ";

        for (int v : adj_list[i]) { 
            cout << v << " ";
        }

        cout << "\n";
    }
}

vector<vector<int>> edges_list_to_matrix(const vector<pair<int, int>>& edges, int V) {
    vector<vector<int>> mat(V, vector<int>(V));

    for (auto& [a, b] : edges) {
        mat[a][b] = 1;
        mat[b][a] = 1;
    }

    return mat;
} 

vector<vector<int>> edges_to_adj_list(const vector<pair<int, int>>& edges, int V) {
    vector<vector<int>> adj_list(V);

    for (auto& [a, b] : edges) { 
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    return adj_list;
}


int main() {
    int V, E;
    cin >> V >> E;

    vector<pair<int, int>> edges(E);

    for (auto& [a, b] : edges) {
        cin >> a >> b;
    }

    print_edges_list(edges);

    vector<vector<int>> adj_mat = edges_list_to_matrix(edges, V);

    print_adj_mat(adj_mat);

    vector<vector<int>> adj_list = edges_to_adj_list(edges, V);

    print_adj_list(adj_list);

    return 0;
}