#ifndef DS_MST_H
#define DS_MST_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
#include <queue>
#include <limits>

struct Edge {
    int u, v;
    double weight;
    
    Edge() : u(0), v(0), weight(0.0) {}
    Edge(int u, int v, double w) : u(u), v(v), weight(w) {
        if (this->u > this->v) {
            std::swap(this->u, this->v);
        }
    }
    
    bool operator==(const Edge& other) const {
        return u == other.u && v == other.v;
    }
    
    bool operator<(const Edge& other) const {
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
};

class Graph {
public:
    int numVertices;
    std::vector<std::vector<std::pair<int, double> > > adjList;
    std::vector<Edge> allEdges;
    
    Graph(int n) : numVertices(n), adjList(n) {}
    
    void addEdge(int u, int v, double weight) {
        Edge e(u, v, weight);
        allEdges.push_back(e);
        adjList[u].push_back(std::make_pair(v, weight));
        adjList[v].push_back(std::make_pair(u, weight));
    }
    
    const std::vector<Edge>& getEdges() const {
        return allEdges;
    }
};

class MST {
public:
    std::vector<Edge> edges;
    double totalWeight;
    
    MST() : totalWeight(0.0) {}
    
    void addEdge(const Edge& e) {
        edges.push_back(e);
        totalWeight += e.weight;
    }
    
    bool isEquivalent(const MST& other) const {
        if (edges.size() != other.edges.size()) return false;
        std::set<Edge> thisSet(edges.begin(), edges.end());
        std::set<Edge> otherSet(other.edges.begin(), other.edges.end());
        return thisSet == otherSet;
    }
    
    int size() const {
        return edges.size();
    }
};

class GraphGenerator {
private:
    static bool seeded;
    
    static void ensureSeeded() {
        if (!seeded) {
            srand(static_cast<unsigned>(time(0)));
            seeded = true;
        }
    }
    
    static double randomWeight(double min, double max) {
        int range = static_cast<int>((max - min) * 1000);
        return min + (rand() % range) / 1000.0;
    }
    
    // BFS to find maximum weight on path in MST between u and v
    static double findMSTPathWeight(int u, int v, 
                                   const std::vector<std::vector<std::pair<int, double> > >& mstAdj,
                                   int numVertices) {
        std::vector<double> maxWeightOnPath(numVertices, -1);
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        
        q.push(u);
        visited[u] = true;
        maxWeightOnPath[u] = 0;
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            if (curr == v) {
                return maxWeightOnPath[v];
            }
            
            for (size_t i = 0; i < mstAdj[curr].size(); i++) {
                int neighbor = mstAdj[curr][i].first;
                double weight = mstAdj[curr][i].second;
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    maxWeightOnPath[neighbor] = std::max(maxWeightOnPath[curr], weight);
                    q.push(neighbor);
                }
            }
        }
        
        return 999.0; // Not connected (shouldn't happen)
    }
    
public:
    // Generate graph with known MST
    static Graph* generateGraphWithKnownMST(int numVertices, int numExtraEdges, MST& outMST) {
        ensureSeeded();
        
        Graph* g = new Graph(numVertices);
        outMST = MST();
        
        // Phase 1: Create MST with weights in range [1, 10]
        std::vector<bool> inMST(numVertices, false);
        std::vector<int> mstVertices;
        
        inMST[0] = true;
        mstVertices.push_back(0);
        
        // Build MST adjacency list as we go
        std::vector<std::vector<std::pair<int, double> > > mstAdj(numVertices);
        
        for (int i = 1; i < numVertices; i++) {
            int u = mstVertices[rand() % mstVertices.size()];
            int v = i;
            double weight = randomWeight(1.0, 10.0);
            
            Edge e(u, v, weight);
            g->addEdge(u, v, weight);
            outMST.addEdge(e);
            
            mstAdj[u].push_back(std::make_pair(v, weight));
            mstAdj[v].push_back(std::make_pair(u, weight));
            
            inMST[v] = true;
            mstVertices.push_back(v);
        }
        
        // Phase 2: Add extra edges that DON'T affect MST
        int addedEdges = 0;
        int attempts = 0;
        const int maxAttempts = numExtraEdges * 20;
        
        while (addedEdges < numExtraEdges && attempts < maxAttempts) {
            attempts++;
            
            int u = rand() % numVertices;
            int v = rand() % numVertices;
            
            if (u == v) continue;
            if (u > v) std::swap(u, v);
            
            // Check if edge exists
            bool exists = false;
            for (size_t i = 0; i < g->allEdges.size(); i++) {
                if (g->allEdges[i].u == u && g->allEdges[i].v == v) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                // Find the maximum weight on path u->v in MST
                double pathMaxWeight = findMSTPathWeight(u, v, mstAdj, numVertices);
                
                // Add edge with weight slightly higher than path max
                double newWeight = pathMaxWeight + randomWeight(0.5, 3.0);
                
                // Keep weights reasonable (< 20)
                if (newWeight < 20.0) {
                    g->addEdge(u, v, newWeight);
                    addedEdges++;
                }
            }
        }
        
        return g;
    }
    
    // Generate edge that won't affect MST
    static Edge generateNonAffectingEdge(const Graph& g, const MST& mst, int numVertices) {
        ensureSeeded();
        
        // Build MST adjacency
        std::vector<std::vector<std::pair<int, double> > > mstAdj(numVertices);
        for (size_t i = 0; i < mst.edges.size(); i++) {
            const Edge& e = mst.edges[i];
            mstAdj[e.u].push_back(std::make_pair(e.v, e.weight));
            mstAdj[e.v].push_back(std::make_pair(e.u, e.weight));
        }
        
        for (int attempt = 0; attempt < 100; attempt++) {
            int u = rand() % numVertices;
            int v = rand() % numVertices;
            
            if (u == v) continue;
            if (u > v) std::swap(u, v);
            
            // Check if exists
            bool exists = false;
            for (size_t i = 0; i < g.allEdges.size(); i++) {
                if (g.allEdges[i].u == u && g.allEdges[i].v == v) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                double pathMax = findMSTPathWeight(u, v, mstAdj, numVertices);
                double weight = pathMax + randomWeight(1.0, 5.0);
                
                if (weight < 30.0) {
                    return Edge(u, v, weight);
                }
            }
        }
        
        // Fallback
        return Edge(0, 1, 25.0);
    }
    
    // Generate edge that WILL affect MST
    static Edge generateAffectingEdge(const Graph& g, const MST& mst, int numVertices) {
        ensureSeeded();
        
        // Build MST adjacency
        std::vector<std::vector<std::pair<int, double> > > mstAdj(numVertices);
        for (size_t i = 0; i < mst.edges.size(); i++) {
            const Edge& e = mst.edges[i];
            mstAdj[e.u].push_back(std::make_pair(e.v, e.weight));
            mstAdj[e.v].push_back(std::make_pair(e.u, e.weight));
        }
        
        for (int attempt = 0; attempt < 100; attempt++) {
            int u = rand() % numVertices;
            int v = rand() % numVertices;
            
            if (u == v) continue;
            if (u > v) std::swap(u, v);
            
            bool exists = false;
            for (size_t i = 0; i < g.allEdges.size(); i++) {
                if (g.allEdges[i].u == u && g.allEdges[i].v == v) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                double pathMax = findMSTPathWeight(u, v, mstAdj, numVertices);
                // Weight LESS than path max will replace heaviest edge on path
                double weight = pathMax - randomWeight(0.5, pathMax * 0.5);
                
                if (weight > 0.1) {
                    return Edge(u, v, weight);
                }
            }
        }
        
        return Edge(0, numVertices - 1, 0.5);
    }
};

bool GraphGenerator::seeded = false;

#endif // DS_MST_H