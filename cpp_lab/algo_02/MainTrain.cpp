#include <iostream>
#include <chrono>
#include <cmath>
#include "DS_Tower.h"
#include "Q_Tower.h"

using namespace std;
using namespace std::chrono;

// ============================================
// VALIDATION FUNCTIONS
// ============================================

// Validate that tower is stable and height is correct
bool isValidTower(const vector<Box>& originalBoxes, const TowerSolution& solution) {
    if (solution.boxIndices.empty()) return true;
    
    // Calculate actual height
    int calculatedHeight = 0;
    for (size_t i = 0; i < solution.boxIndices.size(); i++) {
        int boxId = solution.boxIndices[i];
        if (boxId < 0 || boxId >= static_cast<int>(originalBoxes.size())) {
            return false;  // Invalid box index
        }
        calculatedHeight += originalBoxes[boxId].height;
    }
    
    if (calculatedHeight != solution.totalHeight) {
        return false;  // Height mismatch
    }
    
    // Check stability constraints
    for (size_t i = 1; i < solution.boxIndices.size(); i++) {
        int topBoxId = solution.boxIndices[i];
        int bottomBoxId = solution.boxIndices[i - 1];
        
        const Box& topBox = originalBoxes[topBoxId];
        const Box& bottomBox = originalBoxes[bottomBoxId];
        
        // Top box must be strictly smaller
        if (!topBox.canPlaceOn(bottomBox)) {
            return false;  // Stability violated
        }
    }
    
    return true;
}

// Measure execution time in microseconds
long long measureTimeStudent(vector<Box> boxes) {
    auto start = high_resolution_clock::now();
    TowerSolution solution = findMaxTower(boxes);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long measureTimeNaive(vector<Box> boxes) {
    auto start = high_resolution_clock::now();
    TowerSolution solution = findMaxTowerNaive(boxes);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// ============================================
// MAIN TEST
// ============================================

int main() {
    int totalDeduction = 0;
    
    // ============================================
    // Test 1: Correctness on small input (n=10)
    // ============================================
    
    vector<Box> testBoxes = BoxGenerator::generateBoxes(10, 1, 100);
    vector<Box> originalBoxes = testBoxes;
    
    // Get student solution
    vector<Box> studentBoxes = testBoxes;
    TowerSolution studentSolution = findMaxTower(studentBoxes);
    
    // Validate tower structure
    if (!isValidTower(originalBoxes, studentSolution)) {
        printf("findMaxTower returned invalid tower for n=10 (-100)\n");
        totalDeduction += 10;
    } else {
        // Get correct solution using naive (feasible for n=10)
        vector<Box> naiveBoxes = testBoxes;
        TowerSolution correctSolution = findMaxTowerNaive(naiveBoxes);
        
        // Check if student found optimal height
        if (studentSolution.totalHeight < correctSolution.totalHeight) {
            printf("findMaxTower found suboptimal solution: height %d vs optimal %d (-100)\n",
                   studentSolution.totalHeight, correctSolution.totalHeight);
            totalDeduction += 10;
        }
    }
    
    // ============================================
    // Test 2: Performance comparison (n=18)
    // ============================================
    
    vector<Box> boxes18 = BoxGenerator::generateBoxes(18, 1, 200);
    
    // Measure times
    long long timeStudent = measureTimeStudent(boxes18);
    long long timeNaive = measureTimeNaive(boxes18);
    
    // Student solution should be significantly faster than naive
    // For n=18: naive is O(2^18) ≈ 262,000 operations
    //           DP is O(18²) ≈ 324 operations
    // Expected speedup: ~800x (in practice maybe 50-100x due to overhead)
    
    if (timeStudent >= timeNaive) {
        // Student is as slow or slower than naive - definitely not DP
        printf("findMaxTower is not faster than naive solution - likely not using DP (-50)\n");
        totalDeduction += 50;
    } else {
        double speedup = static_cast<double>(timeNaive) / timeStudent;
        
        if (speedup < 2.0) {
            // Very small speedup - likely O(n^3) or poorly optimized
            int deduction = 50 - static_cast<int>(speedup * 10);
            if (deduction > 40) deduction = 40;
            printf("findMaxTower shows minimal speedup (%.1fx) - likely inefficient implementation (-%d)\n", 
                   speedup, deduction);
            totalDeduction += deduction;
        } else if (speedup < 4.0) {
            // Some speedup but not great
            int deduction = 30 - static_cast<int>((speedup - 5.0) * 6);
            if (deduction > 0) {
                printf("findMaxTower speedup (%.1fx) suggests suboptimal O(n^2) implementation (-%d)\n",
                       speedup, deduction);
                totalDeduction += deduction;
            }
        }
        // else: Good speedup (>4x), no deduction
    }
    
    // ============================================
    // Test 3: Larger input validation (n=25)
    // ============================================
    
    vector<Box> boxes25 = BoxGenerator::generateBoxes(25, 1, 200);
    vector<Box> originalBoxes25 = boxes25;
    
    auto start25 = high_resolution_clock::now();
    TowerSolution solution25 = findMaxTower(boxes25);
    auto end25 = high_resolution_clock::now();
    long long time25 = duration_cast<microseconds>(end25 - start25).count();
    
    // Validate
    if (!isValidTower(originalBoxes25, solution25)) {
        printf("findMaxTower returned invalid tower for n=25 (-10)\n");
        totalDeduction += 10;
    }
    
    // Check if time is reasonable for O(n²)
    // For n=25, O(n²) = 625 operations, should be < 10ms typically
    if (time25 > 50000) {  // > 50ms is very suspicious for O(n²)
        printf("findMaxTower too slow for n=25 (%lld μs) - likely not O(n²) (-20)\n", time25);
        totalDeduction += 20;
    }
    
    // ============================================
    // Test 4: Scaling check (n=15 vs n=25)
    // ============================================
    
    vector<Box> boxes15 = BoxGenerator::generateBoxes(15, 1, 200);
    long long time15 = measureTimeStudent(boxes15);
    
    // For O(n²): time25/time15 should be roughly (25/15)² ≈ 2.78
    double timeRatio = static_cast<double>(time25) / time15;
    
    // Allow range [1.5, 5.0] for 2.78 expected
    if (timeRatio > 8.0) {
        // Likely O(n³) or worse
        printf("findMaxTower scaling suggests worse than O(n²) complexity (ratio %.1fx vs expected ~2.8x) (-10)\n",
               timeRatio);
        totalDeduction += 10;
    }
    
    // Cap at 100
    if (totalDeduction > 100) {
        totalDeduction = 100;
    }
    
    printf("done\n");
    
    return 0;
}