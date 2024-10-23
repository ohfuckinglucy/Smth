#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTICES 100

// Структура графа
struct Graph {
    int V; // Число вершин
    vector<vector<int>> adj; // Матрица смежности
};

// Инициализация графа
void initGraph(Graph &graph, int vertices) {
    graph.V = vertices;
    graph.adj.assign(vertices, vector<int>(vertices, 0));
}

// Добавление ребра в граф
void addEdge(Graph &graph, int u, int v) {
    graph.adj[u][v] = 1;
}

// Обход в глубину
void DFS(const Graph &graph, int v, vector<int> &visited, vector<int> &stack) {
    visited[v] = 1;
    for (int i = 0; i < graph.V; ++i) {
        if (!visited[i] && graph.adj[v][i]) {
            DFS(graph, i, visited, stack);
        }
    }
    stack.push_back(v);
}

// Транспонирование графа
Graph transposeGraph(const Graph &graph) {
    Graph transposedGraph;
    transposedGraph.V = graph.V;
    transposedGraph.adj.assign(graph.V, vector<int>(graph.V, 0));
    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            transposedGraph.adj[i][j] = graph.adj[j][i];
        }
    }
    return transposedGraph;
}

// Обход в глубину для обратного графа
void revdfs(const Graph &graph, int v, vector<int> &visited) {
    visited[v] = 1;
    cout << " " << v;
    for (int i = 0; i < graph.V; ++i) {
        if (!visited[i] && graph.adj[v][i]) {
            revdfs(graph, i, visited);
        }
    }
}

// Поиск компонент сильной связности
void scc(const Graph &graph) {
    int c = 0;
    vector<int> visited(graph.V, 0);
    vector<int> stack;

    // Обход в глубину для топологической сортировки
    for (int i = 0; i < graph.V; ++i) {
        if (!visited[i]) {
            DFS(graph, i, visited, stack);
        }
    }

    // Транспонирование графа
    Graph transposedGraph = transposeGraph(graph);

    // Сброс меток посещенных вершин
    fill(visited.begin(), visited.end(), 0);

    // Обход в глубину в обратном графе для формирования компонент сильной связности
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (!visited[v]) {
            c = c + 1;
            cout << c << " компонента" << ":";
            revdfs(transposedGraph, v, visited);
            cout << endl;
        }
    }
}

int main() {
    // Пример использования
    Graph graph;
    int size, one, sec, count = 0;

    cout << "Введите кол-во вершин" << endl;
    cin >> size;

    initGraph(graph, size);

    while(1){
        cout << "Для выхода введите -1" << endl;
        cout << "Введите две вершины между которыми нужно провести ребро: ";

        cin >> one;
        if(one == -1){
            break;
        }
        cin >> sec;
        if (sec == -1){
            break;
        }
        if(one > size || sec > size){
            cout << "Вершина(ы) не найдена(ы)" << endl;
            continue;
        }
        addEdge(graph, one-1, sec-1);

        count++;
    }
    scc(graph);

    return 0;
}