#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void printMatrix(int **a, int n){
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    return;
}

struct edge{
    int startVertex;
    int endVertex;
    int weight;
    bool visited;
    edge(int s, int e, int w, bool v) : startVertex(s), endVertex(e), weight(w), visited(v) {}
};

bool compare(edge e1, edge e2){
    return e1.weight < e2.weight;
}

vector<int> find_adj(int u, const vector<edge> &visited_edges){
    vector<int> ans;
    int E = visited_edges.size();
    for (int i = 0; i < E; i++){
        if (u == visited_edges[i].startVertex){
            ans.push_back(visited_edges[i].endVertex);
        } else if (u == visited_edges[i].endVertex){
            ans.push_back(visited_edges[i].startVertex);
        }
    }
    return ans;
}

bool hasCycleDFS(int u, int parent, vector<bool> &visited, const vector<edge> &visited_edges){
    visited[u] = true;
    vector<int> adj = find_adj(u, visited_edges);
    for (int v : adj){
        if (v == parent) continue; // skip parent node
        if (visited[v]) return true; // visited, hasCycle
        if (hasCycleDFS(v, u, visited, visited_edges)) return true; // recursion
    }
    return false; // dont have cycle
}

bool has_cycle(const vector<edge> &edges, int E, int edge_to_choose){
    vector<edge> visited_edges;
    for (int i = 0; i < E; i++){
        if (edges[i].visited){
            visited_edges.push_back(edges[i]);
        }
    }
    visited_edges.push_back(edges[edge_to_choose]);
    E = visited_edges.size();

    vector<bool> visited(E, false);
    for (int i = 0; i < E; i++){
        if (!visited[i] && hasCycleDFS(i, -1, visited, visited_edges)){
            return true;
        }
    }
    return false;
}

void kruskal(int** a, int n){ // Minimum Spanning Tree
    // create list edge
    vector<edge> edges;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i][j] != 0){
                edges.push_back(edge(i, j, a[i][j], false));
            }
        }
    }
    sort(edges.begin(), edges.end(), compare);
    int E = edges.size();

    // cout << "edges:\n";
    // for (int i = 0; i < E; i++){
    //     cout << edges[i].startVertex << " <-> " << edges[i].endVertex << ": " << edges[i].weight << "\n";
    // }

    int choosed = 0;
    while (choosed < n - 1){
        for (int i = 0; i < E; i++){
            if (edges[i].visited) continue;
            if (!has_cycle(edges, E, i)){
                edges[i].visited = true;
                choosed++;
                break;
            }
        }
    }

    cout << "Edge    Weight\n";
    for (int i = 0; i < E; i++){
        if (edges[i].visited == true){
            cout << edges[i].startVertex << " - " << edges[i].endVertex << ":     " << edges[i].weight << "\n";
        }
    }
}

int main(){
    FILE *fp;
    fp = freopen("graph.txt", "r", stdin);

    int n; cin >> n;
    int** a = new int*[n];
    for (int i = 0; i < n; i++){
        a[i] = new int [n];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }

    // printMatrix(a, n);
    kruskal(a, n);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    } delete[] a;
    fclose(fp);
    return 0;
}