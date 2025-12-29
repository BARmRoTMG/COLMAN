#ifndef Q_MST_SOLUTION_H
#define Q_MST_SOLUTION_H
#include "DS_MST.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

// ============================================
// Part 1: Prim's Algorithm
// ============================================
MST primMST(const Graph& g)
{
    MST mst;
    int n = g.numVertices;

    if (n == 0) return mst;

    std::vector<bool> inMST(n, false);
    std::vector<double> minWeight(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::priority_queue<std::pair<double, int>,
        std::vector<std::pair<double, int> >,
        std::greater<std::pair<double, int> > > pq;

    minWeight[0] = 0.0;
    pq.push(std::make_pair(0.0, 0));

    while (!pq.empty())
    {
        double w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;

        if (parent[u] != -1)
        {
            Edge edge(parent[u], u, w);
            mst.addEdge(edge);
        }

        const std::vector<std::pair<int, double> >& neighbors = g.adjList[u];
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            int v = neighbors[i].first;
            double weight = neighbors[i].second;

            if (!inMST[v] && weight < minWeight[v])
            {
                minWeight[v] = weight;
                parent[v] = u;
                pq.push(std::make_pair(weight, v));
            }
        }
    }

    return mst;
}

bool findPath(int start, int end,
    const std::vector<std::vector<std::pair<int, double> > >& tree,
    std::vector<Edge>& path,
    std::vector<bool>& visited)
{
    if (start == end) return true;

    visited[start] = true;

    for (size_t i = 0; i < tree[start].size(); i++)
    {
        int v = tree[start][i].first;
        double w = tree[start][i].second;

        if (!visited[v])
        {
            Edge e(start, v, w);
            path.push_back(e);

            if (findPath(v, end, tree, path, visited))
            {
                return true;
            }

            path.pop_back();
        }
    }

    return false;
}

// ============================================
// Part 2: Update MST
// ============================================
MST updateMST(const MST& currentMST, const Edge& newEdge, int numVertices)
{
    if (currentMST.edges.empty())
    {
        return currentMST;
    }

    std::vector<std::vector<std::pair<int, double> > > tree(numVertices);
    const std::vector<Edge>& edges = currentMST.edges;

    for (size_t i = 0; i < edges.size(); i++)
    {
        const Edge& edge = edges[i];
        tree[edge.u].push_back(std::make_pair(edge.v, edge.weight));
        tree[edge.v].push_back(std::make_pair(edge.u, edge.weight));
    }

    std::vector<Edge> path;
    std::vector<bool> visited(numVertices, false);

    bool pathExists = findPath(newEdge.u, newEdge.v, tree, path, visited);

    if (!pathExists || path.empty())
    {
        return currentMST;
    }

    double maxWeight = -1.0;
    int maxEdgeIdx = -1;

    for (size_t i = 0; i < path.size(); i++)
    {
        if (path[i].weight > maxWeight)
        {
            maxWeight = path[i].weight;
            maxEdgeIdx = static_cast<int>(i);
        }
    }

    if (newEdge.weight < maxWeight)
    {
        MST updated;

        for (size_t i = 0; i < edges.size(); i++)
        {
            const Edge& edge = edges[i];

            Edge pathEdge = path[maxEdgeIdx];
            bool isMaxEdge = (edge.u == pathEdge.u && edge.v == pathEdge.v) ||
                (edge.u == pathEdge.v && edge.v == pathEdge.u);

            if (!isMaxEdge)
            {
                updated.addEdge(edge);
            }
        }

        updated.addEdge(newEdge);

        return updated;
    }
    return currentMST;
}

#endif // Q_MST_SOLUTION_H