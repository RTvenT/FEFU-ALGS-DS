// counting connected components
#include <bits/stdc++.h>

using namespace std;


ifstream fin("3.in");
ofstream fout("3.out");


void dfs(const vector<vector<int>>& graph, int v, vector<int>& visited, int c) {
    visited[v] = c;

    for (int to: graph[v]) {
        if (!visited[to]) {
            dfs(graph, to, visited, c);
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

    int componentCnt = 0;

    for (int v = 0; v < V; ++v) {
        if (!visited[v]) { 
            dfs(graph, v, visited, ++componentCnt);
        }
    }
   
    fout << componentCnt;

    return 0;
}