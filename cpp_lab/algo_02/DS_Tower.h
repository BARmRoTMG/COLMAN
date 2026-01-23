#ifndef DS_TOWER_H
#define DS_TOWER_H

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Box representation
struct Box {
    int length;
    int width;
    int height;
    int id;  // Original index for tracking
    
    Box() : length(0), width(0), height(0), id(0) {}
    Box(int l, int w, int h, int i) : length(l), width(w), height(h), id(i) {}
    
    // Check if this box can be placed on top of other
    bool canPlaceOn(const Box& other) const {
        return length < other.length && width < other.width;
    }
    
    // For sorting by base area (descending)
    int baseArea() const {
        return length * width;
    }
};

// Tower solution
struct TowerSolution {
    std::vector<int> boxIndices;  // Indices of boxes in the tower (bottom to top)
    int totalHeight;
    
    TowerSolution() : totalHeight(0) {}
};

// Generate random boxes with unique dimensions
class BoxGenerator {
private:
    static bool seeded;
    
    static void ensureSeeded() {
        if (!seeded) {
            srand(static_cast<unsigned>(time(0)));
            seeded = true;
        }
    }
    
public:
    // Generate n boxes with random dimensions in range [minVal, maxVal]
    static std::vector<Box> generateBoxes(int n, int minVal, int maxVal) {
        ensureSeeded();
        
        std::vector<Box> boxes;
        boxes.reserve(n);
        
        // Generate dimensions pool
        std::vector<int> dimensions;
        for (int i = minVal; i <= maxVal; i++) {
            dimensions.push_back(i);
        }
        
        // Shuffle
        for (size_t i = dimensions.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            std::swap(dimensions[i], dimensions[j]);
        }
        
        // Create boxes with different dimensions
        for (int i = 0; i < n; i++) {
            int idx1 = (i * 3) % dimensions.size();
            int idx2 = (i * 3 + 1) % dimensions.size();
            int idx3 = (i * 3 + 2) % dimensions.size();
            
            int length = dimensions[idx1];
            int width = dimensions[idx2];
            int height = dimensions[idx3];
            
            // Ensure all different
            while (length == width || length == height || width == height) {
                height = dimensions[rand() % dimensions.size()];
            }
            
            boxes.push_back(Box(length, width, height, i));
        }
        
        return boxes;
    }
};

bool BoxGenerator::seeded = false;

// ============================================
// NAIVE BRUTE FORCE SOLUTION - O(2^n)
// This is the reference for correctness
// ============================================

void findMaxTowerNaive_Helper(const std::vector<Box>& boxes, 
                               int index, 
                               const Box* lastBox,
                               int currentHeight,
                               std::vector<int>& currentTower,
                               int& maxHeight,
                               std::vector<int>& bestTower) {
    if (index == static_cast<int>(boxes.size())) {
        if (currentHeight > maxHeight) {
            maxHeight = currentHeight;
            bestTower = currentTower;
        }
        return;
    }
    
    // Option 1: Don't include current box
    findMaxTowerNaive_Helper(boxes, index + 1, lastBox, currentHeight, 
                            currentTower, maxHeight, bestTower);
    
    // Option 2: Include current box (if possible)
    if (lastBox == NULL || boxes[index].canPlaceOn(*lastBox)) {
        currentTower.push_back(boxes[index].id);
        findMaxTowerNaive_Helper(boxes, index + 1, &boxes[index], 
                                currentHeight + boxes[index].height,
                                currentTower, maxHeight, bestTower);
        currentTower.pop_back();
    }
}

TowerSolution findMaxTowerNaive(std::vector<Box>& boxes) {
    // Sort by base area
    std::sort(boxes.begin(), boxes.end(), 
              [](const Box& a, const Box& b) {
                  return a.baseArea() > b.baseArea();
              });
    
    int maxHeight = 0;
    std::vector<int> bestTower;
    std::vector<int> currentTower;
    
    findMaxTowerNaive_Helper(boxes, 0, NULL, 0, currentTower, maxHeight, bestTower);
    
    TowerSolution solution;
    solution.totalHeight = maxHeight;
    solution.boxIndices = bestTower;
    
    return solution;
}

#endif // DS_TOWER_H