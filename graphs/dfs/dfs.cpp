// DFS on Undirected graph
#include <bits/stdc++.h>

using namespace std;

ifstream fin("g1.in");
ofstream fout("g1.out");


void print_adj_list(const vector<vector<int>>& adj_list) {
    fout << "\n" << "---------adjacency-list---------" << "\n";
    for (size_t i = 0; i < adj_list.size(); ++i) { 
        fout << i << ": ";

        for (int v : adj_list[i]) { 
            fout << v << " ";
        }

        fout << "\n";
    }
}


void print_adj_mat(const vector<vector<int>>& mat) {
    fout << "\n" << "---------adjacency-matrix---------" << "\n";
    for (const auto& row : mat) {
        for (int v : row) {
            fout << v << " ";
        }
        fout << "\n";
    }
}


void dfs_adj_list(const vector<vector<int>>& graph, int v, vector<int>& visited) {
    fout << "cur vertex: " << v << "\n";
    visited[v] = 1;

    for (int to: graph[v]) {
        if (!visited[to]) {
            dfs_adj_list(graph, to, visited);
        }
    }
}


void dfs_adj_mat(const vector<vector<int>>& graph, int v, vector<int>& visited) { 
    fout << "cur vertex: " << v << "\n";
    visited[v] = 1;

    for (size_t to = 0; to < graph.size(); ++to) {
        if (graph[v][to] && !visited[to]) {
            dfs_adj_mat(graph, to, visited);
        }
    }
}


int main() {
    int V, E;
    fin >> V >> E;

    vector<vector<int>> adj_list(V);
    vector<vector<int>> adj_mat(V, vector<int>(V));

    for (size_t i = 0; i < E; ++i) {
        int a, b;
        fin >> a >> b;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
        adj_mat[a][b] = 1;
        adj_mat[b][a] = 1;
    }

    print_adj_list(adj_list);
    fout << "---------DFS_WITH_ADJ_LIST---------" << "\n";
    vector<int> visited(V);
    dfs_adj_list(adj_list, 7, visited);

    fout << "vector visited: ";
    for (int v: visited) {
        fout << v << " ";
    }
    fout << "\n" << "--------------------------------" << "\n";


    print_adj_mat(adj_mat);
    fout << "---------DFS_WITH_ADJ_MATRIX---------" << "\n";
    fill(visited.begin(), visited.end(), 0);
    dfs_adj_mat(adj_mat, 7, visited);

    fout << "vector visited: ";
    for (int v: visited) {
        fout << v << " ";
    }
    fout << "\n" << "--------------------------------" << "\n";

    return 0;
}