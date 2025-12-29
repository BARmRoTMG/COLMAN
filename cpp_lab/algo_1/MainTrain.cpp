#include <iostream>
#include "DS_MST.h"
#include "Q_MST.h"

using namespace std;

int main() {
    int totalDeduction = 0;
    
    // ============ Part 1: Test Prim (50 points) ============
    
    MST knownMST;
    Graph* g = GraphGenerator::generateGraphWithKnownMST(20, 30, knownMST);
    
    MST studentMST = primMST(*g);
    
    if (studentMST.size() != knownMST.size()) {
        int diff = abs(static_cast<int>(studentMST.size()) - static_cast<int>(knownMST.size()));
        int deduction = min(50, diff * 5);
        printf("primMST: wrong number of edges, expected %d got %d (-%d)\n",
               static_cast<int>(knownMST.size()), static_cast<int>(studentMST.size()), deduction);
        totalDeduction += deduction;
    } else if (!studentMST.isEquivalent(knownMST)) {
        printf("primMST: incorrect MST edges (-50)\n");
        totalDeduction += 50;
    }
    
    // ============ Part 2: Test updateMST (50 points) ============
    
    // Test 2a: Non-affecting edge
    Edge nonAffecting = GraphGenerator::generateNonAffectingEdge(*g, knownMST, g->numVertices);
    MST updated1 = updateMST(knownMST, nonAffecting, g->numVertices);
    
    if (!updated1.isEquivalent(knownMST)) {
        printf("updateMST: incorrectly changed MST for non-affecting edge (-25)\n");
        totalDeduction += 25;
    }
    
    // Test 2b: Affecting edge
    Edge affecting = GraphGenerator::generateAffectingEdge(*g, knownMST, g->numVertices);
    
    // Calculate correct answer
    Graph* g2 = new Graph(g->numVertices);
    for (const Edge& e : g->allEdges) {
        g2->addEdge(e.u, e.v, e.weight);
    }
    g2->addEdge(affecting.u, affecting.v, affecting.weight);
    
    MST correctMST = primMST(*g2);
    MST updated2 = updateMST(knownMST, affecting, g->numVertices);
    
    if (!updated2.isEquivalent(correctMST)) {
        printf("updateMST: incorrect MST after adding affecting edge (-25)\n");
        totalDeduction += 25;
    }
    
    delete g;
    delete g2;
    
    if (totalDeduction > 100) totalDeduction = 100;
    
    printf("done\n");
    return 0;
}