#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>

// Structure to represent an item
struct Item {
    int weight;
    int value;
    std::string name; // Added name for better tracking in real-world scenarios
};

// 1. Recursive Approach (Basic Implementation)
//   - Concept: Directly translates the problem's recursive definition.
//   - Real-world Use: Simple problems with small input sizes, like a very basic configuration optimizer.  Good for teaching DP.
int knapsackRecursive(int capacity, const std::vector<Item>& items, int index) {
    if (index < 0 || capacity == 0) {
        return 0;
    }

    if (items[index].weight > capacity) {
        return knapsackRecursive(capacity, items, index - 1);
    } else {
        int includeItem = items[index].value + knapsackRecursive(capacity - items[index].weight, items, index - 1);
        int excludeItem = knapsackRecursive(capacity, items, index - 1);
        return std::max(includeItem, excludeItem);
    }
}

// 2. Memoization (Top-Down DP)
//   - Concept: Stores results of subproblems to avoid redundant calculations.
//   - Real-world Use: Optimizing resource allocation where the same sub-problems are encountered repeatedly, such as in supply chain planning.
int knapsackMemoization(int capacity, const std::vector<Item>& items, int index, std::vector<std::vector<int>>& memo) {
    if (index < 0 || capacity == 0) {
        return 0;
    }

    if (memo[index][capacity] != -1) {
        return memo[index][capacity];
    }

    if (items[index].weight > capacity) {
        memo[index][capacity] = knapsackMemoization(capacity, items, index - 1, memo);
        return memo[index][capacity];
    } else {
        int includeItem = items[index].value + knapsackMemoization(capacity - items[index].weight, items, index - 1, memo);
        int excludeItem = knapsackMemoization(capacity, items, index - 1, memo);
        memo[index][capacity] = std::max(includeItem, excludeItem);
        return memo[index][capacity];
    }
}

// 3. Tabulation (Bottom-Up DP)
//   - Concept: Builds a table of solutions to subproblems in a bottom-up manner.
//   - Real-world Use: Inventory management systems, where you need to calculate optimal combinations of items to fit within constraints (e.g., shelf space, budget).
int knapsackTabulation(int capacity, const std::vector<Item>& items) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = std::max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            }
        }
    }
    return dp[n][capacity];
}

// 4. Space-Optimized Tabulation
//   - Concept: Reduces memory usage by using a 1D array instead of a 2D table.
//   - Real-world Use: Embedded systems or mobile applications with limited memory, such as optimizing the selection of software components for a constrained device.
int knapsackSpaceOptimized(int capacity, const std::vector<Item>& items) {
    std::vector<int> dp(capacity + 1, 0);

    for (const auto& item : items) {
        for (int w = capacity; w >= item.weight; --w) {
            dp[w] = std::max(dp[w], item.value + dp[w - item.weight]);
        }
    }
    return dp[capacity];
}

// 5. Value-Bound Optimization with Item Tracking
//    - Concept:  Adds a bound on the value and tracks which items are included.  This is a variation that's very useful in real-world scenarios.
//    - Real-world Use:  Portfolio optimization in finance (maximizing returns under a risk limit), or logistics (maximizing the value of goods loaded onto a truck with weight restrictions), and package selection.
struct Solution {
    int maxValue;
    std::vector<std::string> includedItems;
};

Solution knapsackValueBound(int capacity, const std::vector<Item>& items, int valueBound) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    std::vector<std::vector<std::vector<std::string>>> itemTracker(n + 1, std::vector<std::vector<std::string>>(capacity + 1)); // Keep track of items

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
                itemTracker[i][w] = itemTracker[i - 1][w]; // Copy the items from the previous row
            } else {
                int includeItemValue = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
                int excludeItemValue = dp[i - 1][w];

                if (includeItemValue > excludeItemValue) {
                    dp[i][w] = includeItemValue;
                    itemTracker[i][w] = itemTracker[i - 1][w - items[i - 1].weight]; // Copy items from the subproblem
                    itemTracker[i][w].push_back(items[i - 1].name);             // Add the current item
                } else {
                    dp[i][w] = excludeItemValue;
                    itemTracker[i][w] = itemTracker[i - 1][w];     // Copy the items
                }
            }
        }
    }

    Solution solution;
    if (dp[n][capacity] >= valueBound)
    {
        solution.maxValue = dp[n][capacity];
        solution.includedItems = itemTracker[n][capacity];
    }
    else
    {
        solution.maxValue = 0;
        solution.includedItems = {};
    }

    return solution;
}

// Function to generate a random knapsack problem instance for testing
std::vector<Item> generateRandomProblem(int numItems, int maxWeight, int maxValue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, maxWeight);
    std::uniform_int_distribution<> valueDist(1, maxValue);

    std::vector<Item> items(numItems);
    for (int i = 0; i < numItems; ++i) {
        items[i].weight = weightDist(gen);
        items[i].value = valueDist(gen);
        items[i].name = "Item-" + std::to_string(i + 1); // Unique names
    }
    return items;
}

// Function to display the items
void displayItems(const std::vector<Item>& items) {
    std::cout << "Items:\n";
    for (const auto& item : items) {
        std::cout << "Name: " << item.name << ", Weight: " << item.weight << ", Value: " << item.value << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Example usage with a small problem
    std::vector<Item> items = {
        {2, 10, "Item-1"},
        {3, 5,  "Item-2"},
        {5, 15, "Item-3"},
        {7, 7,  "Item-4"},
        {1, 6,  "Item-5"}
    };
    int capacity = 10;
    int numItems = items.size();

    std::cout << "--- 0/1 Knapsack Problem ---\n";
    displayItems(items);
    std::cout << "Capacity: " << capacity << "\n\n";

    // 1. Recursive Approach
    auto start = std::chrono::high_resolution_clock::now();
    int maxValueRecursive = knapsackRecursive(capacity, items, numItems - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "1. Recursive Approach:\nMax Value: " << maxValueRecursive << "\nTime: " << duration.count() << " seconds\n\n";

    // 2. Memoization
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> memo(numItems, std::vector<int>(capacity + 1, -1));
    int maxValueMemoization = knapsackMemoization(capacity, items, numItems - 1, memo);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "2. Memoization Approach:\nMax Value: " << maxValueMemoization << "\nTime: " << duration.count() << " seconds\n\n";

    // 3. Tabulation
    start = std::chrono::high_resolution_clock::now();
    int maxValueTabulation = knapsackTabulation(capacity, items);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "3. Tabulation Approach:\nMax Value: " << maxValueTabulation << "\nTime: " << duration.count() << " seconds\n\n";

    // 4. Space-Optimized Tabulation
    start = std::chrono::high_resolution_clock::now();
    int maxValueSpaceOptimized = knapsackSpaceOptimized(capacity, items);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "4. Space-Optimized Tabulation Approach:\nMax Value: " << maxValueSpaceOptimized << "\nTime: " << duration.count() << " seconds\n\n";

    // 5. Value-Bound Optimization with Item Tracking
    int valueBound = 20; // Example value bound
    start = std::chrono::high_resolution_clock::now();
    Solution solution = knapsackValueBound(capacity, items, valueBound);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "5. Value-Bound Optimization Approach (Value Bound: " << valueBound << "):\n";
    if (solution.maxValue > 0)
    {
        std::cout << "Max Value: " << solution.maxValue << "\n";
        std::cout << "Included Items: ";
        for (const auto& itemName : solution.includedItems) {
            std::cout << itemName << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout<< "No solution meets the value bound of " << valueBound << "\n";
    }
    std::cout << "Time: " << duration.count() << " seconds\n\n";

    // Example with a larger, randomly generated problem to demonstrate performance
    int numItemsLarge = 100;
    int maxWeight = 50;
    int maxValue = 100;
    std::vector<Item> largeItems = generateRandomProblem(numItemsLarge, maxWeight, maxValue);
    capacity = 200;

    std::cout << "--- Large Random Problem ( " << numItemsLarge << " items, Capacity = " << capacity << " )---\n";

    // Run only the more efficient algorithms on the larger problem
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> memoLarge(numItemsLarge, std::vector<int>(capacity + 1, -1)); // Declare memoLarge here
    int maxValueMemoizationLarge = knapsackMemoization(capacity, largeItems, numItemsLarge - 1, memoLarge);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "2. Memoization Approach (Large Problem):\nMax Value: " << maxValueMemoizationLarge << "\nTime: " << duration.count() << " seconds\n\n";

    start = std::chrono::high_resolution_clock::now();
    int maxValueTabulationLarge = knapsackTabulation(capacity, largeItems);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "3. Tabulation Approach (Large Problem):\nMax Value: " << maxValueTabulationLarge << "\nTime: " << duration.count() << " seconds\n\n";

    start = std::chrono::high_resolution_clock::now();
    int maxValueSpaceOptimizedLarge = knapsackSpaceOptimized(capacity, largeItems);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "4. Space-Optimized Tabulation Approach (Large Problem):\nMax Value: " << maxValueSpaceOptimizedLarge << "\nTime: " << duration.count() << " seconds\n\n";

    return 0;
}
