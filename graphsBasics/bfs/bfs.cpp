#include <bits/stdc++.h>

using namespace std;


ifstream fin("bfs.in");
ofstream fout("bfs.out");

const int INF = 1e9;


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


vector<int> bfs(const vector<vector<int>>& graph, int v) {
    vector<int> visited(graph.size());
    vector<int> dist(graph.size(), INF);
    queue<int> q;  

    q.push(v);
    dist[v] = 0;
    visited[v] = 1;

    while (!q.empty()) {
        int a = q.front();
        q.pop();

        for (int b: graph[a]) {
            if (!visited[b]) {
                visited[b] = 1;
                dist[b] = dist[a] + 1;
                q.push(b);
            }
        }
    }

    return dist;
}


int main() {
    int V, E, start;
    fin >> V >> E;

    vector<vector<int>> graph(V);

    for (int i = 0; i < E; ++i) {
        int a, b;
        fin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    fin >> start;

    print_adj_list(graph);
    fout << "---------BFS_WITH_ADJ_LIST---------" << "\n";
    vector<int> dist = bfs(graph, start);

    fout << "vector dist: " << "\n";
    for (int v = 0; v < V; ++v) {
        fout << v << ": " << dist[v] << "\n";
    }
    fout << "\n" << "--------------------------------" << "\n";

    return 0;
}