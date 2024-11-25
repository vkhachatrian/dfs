#include <iostream>
#include <vector>
#include "Graph.h"

int logTime;

void dfsVisit(const Graph &graph, std::shared_ptr<Vertex> u, std::vector<std::shared_ptr<Vertex>> &dfsResult)
{
    logTime += 1;
    u->discoveryTime = logTime;
    u->color = Color::Gray;
    for (const auto &v : graph.getAdjList(u->number))
    {
        if (v->color == Color::White)
        {
            v->predecessor = u.get();
            dfsVisit(graph, v, dfsResult);
        }
    }

    logTime += 1;
    u->finishTime = logTime;
    u->color = Color::Black;
    dfsResult.push_back(u); // Add the vertex to the result vector when finished
}

std::vector<std::shared_ptr<Vertex>> dfs(const Graph &graph, int startVertex)
{
    std::vector<std::shared_ptr<Vertex>> dfsResult;

    for (auto &elem : graph.getVertices())
    {
        elem->color = Color::White;
        elem->predecessor = nullptr;
    }

    logTime = 0;

    auto start = graph.getVertex(startVertex);
    if (start->color == Color::White)
    {
        dfsVisit(graph, start, dfsResult);
    }
    return dfsResult;
}

int main()
{
    std::cout << "Simple DFS application\n";

    Graph g; // Create a graph

    g.addEdge(1, 2);
    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    std::vector<std::shared_ptr<Vertex>> dfsResult = dfs(g, 0);

    g.displayGraph();

    std::cout << "DFS Result:\n";
    for (const auto &vertex : dfsResult)
    {
        std::cout << vertex->number << " ";
    }
    std::cout << std::endl;

    return 0;
}