/*COMSC 210 | Lab 34 | Lawrence Bryant
IDE used: Visual Studio Code | LLM used: ChatGPT*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Final renumbered node count (11 nodes: 0–10)
const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int,int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &e : edges) {
            adjList[e.src].push_back(make_pair(e.dest, e.weight));
            adjList[e.dest].push_back(make_pair(e.src, e.weight)); // undirected
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (auto &p : adjList[i])
                cout << "(" << p.first << ", " << p.second << ") ";
            cout << endl;
        }
    }

    // DFS ---------------------------------------------------
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

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

    // BFS ---------------------------------------------------
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":\n";

        while (!q.empty()) {
            int node = q.front(); q.pop();
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

    // ----------------------------------------------------
    // Renumbered graph: nodes 0–10 (11 total)
    // New edges + new weights
    // ----------------------------------------------------
    vector<Edge> edges = {
        {0,1,10}, {0,2,7}, {1,3,14}, {2,3,9},
        {2,4,11}, {3,5,6}, {4,6,13}, {5,7,8},
        {6,8,12}, {7,9,5}, {8,10,15},
        {4,7,4}, {2,9,3}, {1,8,16}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
