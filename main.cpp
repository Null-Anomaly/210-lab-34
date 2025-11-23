/*COMSC 210 | Lab 34 | Lawrence Bryant
IDE used: Visual Studio Code | LLM used: ChatGPT*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight)); // undirected
        }
    }

    // ---------------------------
    // Print adjacency list
    // ---------------------------
    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (auto &p : adjList[i])
                cout << "(" << p.first << ", " << p.second << ") ";
            cout << endl;
        }
    }

    // ---------------------------
    // DFS (reverse adjacency order)
    // ---------------------------
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        // iterate in *reverse* order to match expected output
        for (int i = adjList[node].size() - 1; i >= 0; i--) {
            int next = adjList[node][i].first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << start << ":\n";
        DFSUtil(start, visited);
        cout << endl;
    }

    // ---------------------------
    // BFS (normal adjacency order)
    // ---------------------------
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":\n";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto &p : adjList[node]) {
                int next = p.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{0,3,21},
        {2,3,6},{2,6,2},{5,6,6},
        {4,5,9},{2,4,4},{2,5,5}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
