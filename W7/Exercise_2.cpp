#include <iostream>
#include <climits>
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
    int preVertex;
    int distance;
    path(int v, int w) : preVertex(v), distance(w) {}
};

struct edge{
    int startVertex;
    int endVertex;
    int weight;
    edge(int s, int e, int w) : startVertex(s), endVertex(e), weight(w) {}
};

string findPath(const vector<path>& graph, int sourceVertex, int vertex){
    if (graph[vertex].distance == INT_MAX) {
        return "Can't find shortest path.";
    }
    if (sourceVertex == vertex) return to_string(sourceVertex);
    return findPath(graph, sourceVertex, graph[vertex].preVertex) + " -> " + to_string(vertex);
}

void bellman_ford(int** a, int n, int sourceVertex){
    if (sourceVertex < 0 || sourceVertex >= n) return;
    if (n == 0 || n == 1){
        cout << "Graph has no Vertex. Can't find shortest path.\n";
    } else if (n == 1){
        cout << "Graph has only one Vertex. Can't find shortest path.\n";
    }
    // INT_MAX = 2147483647
    // cout << INT_MAX;

    // create list edge
    vector<edge> edges;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] != 0){
                edges.push_back(edge(i, j, a[i][j]));
            }
        }
    }
    int E = edges.size();

    // cout << "edges: \n";
    // for (int i = 0; i < E; i++){
    //     cout << edges[i].startVertex << " -> " << edges[i].endVertex << ": " << edges[i].weight << "\n";
    // } cout << "\n";

    // create graph
    vector<path> graph;
    graph.resize(n, path(-1, INT_MAX)); 
    graph[sourceVertex].preVertex = sourceVertex;
    graph[sourceVertex].distance = 0;

    // add edge
    for (int i = 1; i < n; i++){
        for (int j = 0; j < E; j++){ // for each (u, v) in edges
            int u = edges[j].startVertex;
            int v = edges[j].endVertex;
            int w = edges[j].weight;
            if (graph[u].distance != INT_MAX && graph[v].distance > graph[u].distance + w){
                graph[v].distance = graph[u].distance + w;
                graph[v].preVertex = u;
            }
        }
    }
    // cout << "graph:\n";
    // for (int i = 0; i < n; i++){
    //     cout << graph[i].distance << "\n";
    // }

    // negative cycle check
    for (int j = 0; j < E; j++){ // for each (u, v) in edges
        int u = edges[j].startVertex;
        int v = edges[j].endVertex;
        int w = edges[j].weight;
        if (graph[v].distance > graph[u].distance + edges[j].weight){
            cout << "Graph has negative cycle. Can't find shortest path.\n";
            return;
        }
    }

    // answer
    for (int i = 0; i < n; i++){
        if (i == sourceVertex) continue;
        cout << "The shortest path from " << sourceVertex << " to "<< i << ": ";
        cout << findPath(graph, sourceVertex, i) << "\n";
    }

    return;
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
    bellman_ford(a, n, 0);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    } delete[] a;
    fclose(fp);
    return 0;
}