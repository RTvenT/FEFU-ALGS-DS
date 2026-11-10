// is vertex v reachable from vertex u?
#include <bits/stdc++.h>

using namespace std;


ifstream fin("1.in");
ofstream fout("1.out");


void dfs(const vector<vector<int>>& graph, int v, vector<int>& visited) {
    visited[v] = 1;

    for (int to: graph[v]) {
        if (!visited[to]) {
            dfs(graph, to, visited);
        }
    }
}



int main() { 
    int V, E;
    fin >> V >> E;

    vector<vector<int>> graph(V);
    vector<int> visited(V);

    for (int i = 0; i < E; ++i) { 
        int a, b;
        fin >> a >> b;
        
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int start, end;
    fin >> start >> end;

    dfs(graph, start, visited);
    
    if (visited[end]) {
        fout << "YES"; 
    } else {
        fout << "NO";
    }

    return 0;
}