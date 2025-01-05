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
        return "Can't find shortest path.";
    }
    if (sourceVertex == vertex) return to_string(sourceVertex);
    return findPath(graph, sourceVertex, graph[vertex].startVertex) + " -> " + to_string(vertex);
}

void dijkstra(int** a, int n, int sourceVertex){
    if (sourceVertex < 0 || sourceVertex >= n) return;
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

    for (int i = 0; i < n; i++){
        if (i == sourceVertex) continue;
        cout << "The shortest path from " << sourceVertex << " to "<< i << ": ";
        cout << findPath(graph, sourceVertex, i) << "\n";
        // cout << i << ": (" << graph[i].startVertex << " : " << graph[i].weight << ") " << graph[i].check << "\n";
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
    dijkstra(a, n, 0);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    } delete[] a;
    fclose(fp);
    return 0;
}