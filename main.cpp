/*COMSC 210 | Lab 34 | Lawrence Bryant
IDE used: Visual Studio Code | LLM used: ChatGPT*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Total routers in the network (0–10)
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
        cout << "\n=== Network Topology (Adjacency List) ===\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Router " << i << " --> ";
            for (auto &p : adjList[i])
                cout << "(Router " << p.first << ", " << p.second << "ms) ";
            cout << endl;
        }
    }

    // ------------------- DFS -------------------
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << "Router " << node << " ";

        for (int i = adjList[node].size() - 1; i >= 0; i--) {
            int next = adjList[node][i].first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "\n=== DFS Diagnostic Trace from Router " << start << " ===\n";
        DFSUtil(start, visited);
        cout << "\n";
    }

    // ------------------- BFS -------------------
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\n=== Broadcast Routing from Router " << start << " ===\n";

        while (!q.empty()) {
            int node = q.front(); 
            q.pop();
            cout << "Router " << node << " ";

            for (auto &p : adjList[node]) {
                int next = p.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << "\n";
    }
};


// ==========================
//       MAIN APPLICATION
// ==========================

int main() {

    // Clean, renumbered network topology
    vector<Edge> edges = {
        {0,1,10}, {0,2,7}, {1,3,14}, {2,3,9},
        {2,4,11}, {3,5,6}, {4,6,13}, {5,7,8},
        {6,8,12}, {7,9,5}, {8,10,15},
        {4,7,4}, {2,9,3}, {1,8,16}
    };

    Graph network(edges);

    int choice = 0;
    int router;

    while (choice != 4) {
        cout << "\n==============================\n";
        cout << "   NETWORK ROUTING SIMULATOR\n";
        cout << "==============================\n";
        cout << "1. View Network Topology\n";
        cout << "2. Run DFS Diagnostic Trace\n";
        cout << "3. Simulate Broadcast Routing (BFS)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            network.printGraph();
            break;

        case 2:
            cout << "Enter starting router (0–10): ";
            cin >> router;
            if (router >= 0 && router < SIZE)
                network.DFS(router);
            else
                cout << "Invalid router ID.\n";
            break;

        case 3:
            cout << "Enter starting router (0–10): ";
            cin >> router;
            if (router >= 0 && router < SIZE)
                network.BFS(router);
            else
                cout << "Invalid router ID.\n";
            break;

        case 4:
            cout << "Exiting simulator...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
