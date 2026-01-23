#ifndef Q_TOWER_H
#define Q_TOWER_H

#include "DS_Tower.h"
#include <algorithm>

// ============================================
// DYNAMIC PROGRAMMING SOLUTION - O(n²)
// Students must implement this
// ============================================

TowerSolution findMaxTower(std::vector<Box>& boxes) {
    TowerSolution solution;

    if (boxes.empty())
        return solution;

    std::sort(boxes.begin(), boxes.end(), [](const Box & a, const Box & b)
    {
            return a.baseArea() > b.baseArea();
    });

    int n = boxes.size();

    std::vector<int> heights(n);
    std::vector<int> parents(n, -1);

    for (int i = 0; i < n; i++)
        heights[i] = boxes[i].height;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (boxes[i].canPlaceOn(boxes[j]))
            {
                if (heights[j] + boxes[i].height > heights[i])
                {
                    heights[i] = heights[j] + boxes[i].height;
                    parents[i] = j;
                }
            }
        }
    }

    int maxHeight = 0;
    int maxIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (heights[i] > maxHeight)
        {
            maxHeight = heights[i];
            maxIndex = i;
        }
    }

    if (maxIndex == -1) 
        return solution;

    int curr = maxIndex;
    while (curr != -1)
    {
        solution.boxIndices.push_back(boxes[curr].id);
        curr = parents[curr];
    }

    std::reverse(solution.boxIndices.begin(), solution.boxIndices.end());
    solution.totalHeight = maxHeight;
        
    return solution;
}

#endif // Q_TOWER_H