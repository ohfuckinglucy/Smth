#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int vertex, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    stack<int> stack;
    stack.push(vertex);
    visited[vertex] = true;
    component.push_back(vertex);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        for (int neighbor = 0; neighbor < graph.size(); ++neighbor) {
            if (graph[current][neighbor] && !visited[neighbor]) {
                stack.push(neighbor);
                visited[neighbor] = true;
                component.push_back(neighbor);
            }
        }
    }
}

void findConnectedComponents(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            DFS(i, graph, visited, component);

            cout << "Компонента связности: ";
            for (int vertex : component) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int n;
    cout << "Введите количество вершин графа: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Введите матрицу смежности:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    findConnectedComponents(graph);

    return 0;
}
