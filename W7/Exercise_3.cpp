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

struct vertex{
    int v;
    vector<int> adj;
    bool visited;
    vertex(int u, vector<int> a, bool v) : v(u), adj(a), visited(v) {}
};

vector<int> find_adj(int u, const vector<edge> &edges){
    vector<int> ans;
    int E = edges.size();
    for (int i = 0; i < E; i++){
        if (u == edges[i].startVertex){
            ans.push_back(edges[i].endVertex);
        } else if (u == edges[i].endVertex){
            ans.push_back(edges[i].startVertex);
        }
    }
    return ans;
}

void prim(int** a, int n, int startVertex){ // Minimum Spanning Tree
    // create list edge
    vector<edge> edges;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i][j] != 0){
                edges.push_back(edge(i, j, a[i][j], false));
            }
        }
    }
    int E = edges.size();

    // create list vertex
    vector<vertex> vertexs;
    for (int i = 0; i < n; i++){
        vertexs.push_back(vertex(i, find_adj(i, edges), false));
    }
    vertexs[0].visited = true;
    int choosed = 0;
    while (choosed < n - 1){
        int edge_weight = INT_MAX;
        int edge_to_choose = -1;
        for (int i = 0; i < n; i++){
            if (vertexs[i].visited == false) continue;
            for (int j = 0; j < E; j++){
                if (edges[j].startVertex != i && edges[j].endVertex != i) continue;
                if (edges[j].visited == true) continue;

                if (edges[j].weight < edge_weight){
                    edge_to_choose = j;
                    edge_weight = edges[j].weight;
                }
            }
        }
        if (edge_to_choose == -1) break;
        else {
            edges[edge_to_choose].visited = true;
            vertexs[edges[edge_to_choose].startVertex].visited = true;
            vertexs[edges[edge_to_choose].endVertex].visited = true;
            choosed++;
        }
    }

    // cout << "edges:\n";
    // for (int i = 0; i < E; i++){
    //     cout << edges[i].startVertex << " <-> " << edges[i].endVertex << ": " << edges[i].weight << "\n";
    // }

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
    prim(a, n, 0);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    } delete[] a;
    fclose(fp);
    return 0;
}