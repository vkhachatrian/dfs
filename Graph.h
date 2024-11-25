#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <memory>

#include "Vertex.h"

class Graph
{
public:
    void addEdge(int src, int dst)
    {
        auto srcVertex = getOrCreateVertex(src);
        auto dstVertex = getOrCreateVertex(dst);
        m_adjList[srcVertex].push_back(dstVertex);
        m_adjList[dstVertex].push_back(srcVertex); // For undirected graph, keep this line
    }

    void removeEdge(int u, int v)
    {
        auto uVertex = getOrCreateVertex(u);
        auto vVertex = getOrCreateVertex(v);
        m_adjList[uVertex].remove_if([v](const std::shared_ptr<Vertex> &vertex)
                                   { return vertex->number == v; });

        m_adjList[vVertex].remove_if([u](const std::shared_ptr<Vertex> &vertex)
                                   { return vertex->number == u; }); // For undirected graph, keep this line
    }

    void printGraph() const
    {
        for (const auto &pair : m_adjList)
        {
            std::cout << pair.first->number << ": ";
            for (const auto &vertex : pair.second)
            {
                std::cout << vertex->number << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::shared_ptr<Vertex>> getVertices() const
    {
        std::vector<std::shared_ptr<Vertex>> vertices;
        for (const auto &pair : m_adjList)
        {
            vertices.push_back(pair.first);
        }
        return vertices;
    }

    const std::list<std::shared_ptr<Vertex>> &getAdjList(int vertex) const
    {
        auto it = m_adjList.find(getOrCreateVertex(vertex));
        if (it != m_adjList.end())
        {
            return it->second;
        }
        static const std::list<std::shared_ptr<Vertex>> emptyList;
        return emptyList;
    }

    void displayGraph() const
    {
        std::cout << "Graph adjacency list representation:" << std::endl;
        for (const auto &pair : m_adjList)
        {
            std::cout << "Vertex " << pair.first->number << " -> ";
            for (const auto &vertex : pair.second)
            {
                std::cout << vertex->number << " ";
            }
            std::cout << std::endl;
        }
    }

    std::shared_ptr<Vertex> getVertex(int number) const
    {
        return getOrCreateVertex(number);
    }

private:
    std::unordered_map<std::shared_ptr<Vertex>, std::list<std::shared_ptr<Vertex>>, VertexHash, VertexEqual> m_adjList;

    std::shared_ptr<Vertex> getOrCreateVertex(int number) const
    {
        for (const auto &pair : m_adjList)
        {
            if (pair.first->number == number)
            {
                return pair.first;
            }
        }
        return std::make_shared<Vertex>(number);
    }
};

#endif // GRAPH_H