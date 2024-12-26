#include <iostream>
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

struct path{
    int startVertex;
    int weight;
    bool check;
    path(int v, int w, bool c) : startVertex(v), weight(w), check(c) {}
};

string findPath(vector<path> graph, int sourceVertex, int vertex){
    if (graph[vertex].startVertex == -1) {
        return "-1";
    }
    if (sourceVertex == vertex) return to_string(sourceVertex + 1);
    return findPath(graph, sourceVertex, graph[vertex].startVertex) + " " + to_string(vertex + 1);
}

void dijkstra(int** a, int n, int sourceVertex){
    if (n == 0 || n == 1){
        cout << "Graph has no Vertex. Can't find shortest path.\n";
    } else if (n == 1){
        cout << "Graph has only one Vertex. Can't find shortest path.\n";
    }

    int vertex = sourceVertex;

    vector<path> graph;
    graph.resize(n, path(-1, -1, false)); // no startVertex, weight = inf, check = false
    graph[vertex].startVertex = 0; graph[vertex].weight = 0; graph[vertex].check = true; // a->a = 0
    
    for (int i = 0; i < n; i++){ // row - start vertex
        int preWeight = graph[vertex].weight;
        
        for (int j = 1; j < n; j++){ // col - BFS vertex
            if (graph[j].check || a[vertex][j] == 0) continue;

            if (graph[j].weight == -1){ // inf, new path
                graph[j].weight = preWeight + a[vertex][j]; 
                graph[j].startVertex = vertex;
            }
            else { // not inf, new shorter path
                if (graph[j].weight > preWeight + a[vertex][j]){
                    graph[j].weight =  preWeight + a[vertex][j];
                    graph[j].startVertex = vertex;
                }
            }
        }

        int nextVertex = vertex;
        int weightCompare;
        for (int k = 0; k < n; k++) weightCompare = max(weightCompare, graph[k].weight);
        
        for (int k = 0; k < n; k++){
            if (graph[k].check || graph[k].weight == -1) continue;
            if (graph[k].weight <= weightCompare){
                weightCompare = graph[k].weight;
                nextVertex = k;
            }
        }

        vertex = nextVertex;
        graph[vertex].check = true;
    }

    // answer

    for (int i = n - 1; i < n; i++){
        if (i == sourceVertex) continue;
        // cout << "The shortest path from " << sourceVertex << " to "<< i << ": ";
        cout << findPath(graph, sourceVertex, i) << "\n";
        // cout << i << ": (" << graph[i].startVertex << " : " << graph[i].weight << ") " << graph[i].check << "\n";
    }

    return;
}

void solve(){
    int v, e; cin >> v >> e;
    int* w = new int [e];
    int* a = new int [e];
    int* b = new int [e];
    for (int i = 0; i < e; i++){
        cin >> a[i] >> b[i] >> w[i];
    }

    int** m = new int*[v];
    for (int i = 0; i < v; i++){
        m[i] = new int [v];
    }

    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            m[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++){
        m[a[i] - 1][b[i] - 1] = (m[a[i] - 1][b[i] - 1] == 0) ? w[i] : min(w[i], m[a[i] - 1][b[i] - 1]);
    }
    for (int i = 0; i < e; i++){
        m[b[i] - 1][a[i] - 1] = (m[b[i] - 1][a[i] - 1] == 0) ? w[i] : min(w[i], m[b[i] - 1][a[i] - 1]);
    }
    // printMatrix(m, v);
    dijkstra(m, v, 0);
}

int main(){
    solve();
    return 0;
}