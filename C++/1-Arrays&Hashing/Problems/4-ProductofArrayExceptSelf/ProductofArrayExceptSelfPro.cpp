#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::partial_sum (C++17 and later)
#include <execution> // For std::execution::par (C++17 and later)

// Function to print a vector (useful for debugging)
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// Approach 1: Brute Force
// - Computes the product for each element by iterating through the array.
// - Simple to understand but inefficient (Time Complexity: O(n^2)).
// - Real-world usage: Suitable for very small arrays where performance is not critical,
//   or for educational purposes to illustrate a basic approach.
std::vector<int> productExceptSelf_BruteForce(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        int product = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                product *= nums[j];
            }
        }
        result[i] = product;
    }
    return result;
}

// Approach 2: Using Division
// - Calculates the product of all elements and then divides by each element.
// - Efficient (Time Complexity: O(n)), but has a critical issue:
//   Handles zero elements in the input array, but may lead to division by zero.
// - Real-world usage: Potentially useful in specific scenarios where it's guaranteed
//   that the input array will *not* contain zero, such as in certain signal processing
//   or financial calculations.  However, it's generally risky due to the division.
std::vector<int> productExceptSelf_WithDivision(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);
    int totalProduct = 1;
    int zeroCount = 0;

    for (int num : nums) {
        if (num == 0) {
            zeroCount++;
        } else {
            totalProduct *= num;
        }
    }

    if (zeroCount > 1) {
        //If there are more than one zeros, the result will be all zeros.
        for(int i=0; i<n; ++i){
            result[i] = 0;
        }
    } else if (zeroCount == 1) {
        // If there is one zero, only the element at that index will be non-zero
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                result[i] = totalProduct;
            } else {
                result[i] = 0;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            result[i] = totalProduct / nums[i];
        }
    }
    return result;
}



// Approach 3: Prefix and Suffix Products
// - Calculates prefix and suffix products and multiplies them.
// - Efficient and robust (Time Complexity: O(n), Space Complexity O(n)).
// - Real-world usage: A very common and reliable approach.  Suitable for
//   general-purpose applications where efficiency and correctness are important,
//   such as in data analysis, scientific computing, and backend services.
std::vector<int> productExceptSelf_PrefixSuffix(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);
    std::vector<int> prefixProducts(n);
    std::vector<int> suffixProducts(n);

    // Calculate prefix products
    prefixProducts[0] = 1;
    for (int i = 1; i < n; ++i) {
        prefixProducts[i] = prefixProducts[i - 1] * nums[i - 1];
    }

    // Calculate suffix products
    suffixProducts[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        suffixProducts[i] = suffixProducts[i + 1] * nums[i + 1];
    }

    // Calculate the final result
    for (int i = 0; i < n; ++i) {
        result[i] = prefixProducts[i] * suffixProducts[i];
    }
    return result;
}

// Approach 4: Optimized Prefix and Suffix Products (Constant Space)
// - Similar to Approach 3, but optimizes space by reusing the output array.
// - Efficient and space-optimized (Time Complexity: O(n), Space Complexity O(1)).
// - Real-world usage: Highly recommended for scenarios where memory usage is a
//   concern, such as in embedded systems, mobile applications, or high-performance
//   computing with limited memory.
std::vector<int> productExceptSelf_Optimized(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1); // Initialize result with 1s

    // Calculate prefix products and store in result
    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] * nums[i - 1];
    }

    // Calculate suffix products and multiply with result
    int suffixProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= suffixProduct;
        suffixProduct *= nums[i];
    }
    return result;
}

// Approach 5: Using std::partial_sum (C++17 and later)
// - Uses the std::partial_sum algorithm to compute prefix products.
// - More concise, but might be slightly less readable for those not familiar with the algorithm.
// - Real-world usage: Good for modern C++ projects where code conciseness and
//   utilizing standard library algorithms are preferred.  It can improve
//   readability for developers familiar with modern C++ idioms.
std::vector<int> productExceptSelf_PartialSum(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1);
    std::vector<int> prefixProducts(n);

    // Calculate prefix products using std::partial_sum
    prefixProducts[0] = 1;
    std::partial_sum(nums.begin(), nums.end() - 1, prefixProducts.begin() + 1, std::multiplies<int>());

    // Calculate suffix products and multiply with result
    int suffixProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] = prefixProducts[i] * suffixProduct;
        suffixProduct *= nums[i];
    }
    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4};

    std::cout << "Input Array: ";
    printVector(nums);

    std::cout << "\nApproach 1: Brute Force" << std::endl;
    std::vector<int> result1 = productExceptSelf_BruteForce(nums);
    printVector(result1);

    std::cout << "\nApproach 2: Using Division" << std::endl;
    std::vector<int> result2 = productExceptSelf_WithDivision(nums);
    printVector(result2);

    std::cout << "\nApproach 3: Prefix and Suffix Products" << std::endl;
    std::vector<int> result3 = productExceptSelf_PrefixSuffix(nums);
    printVector(result3);

    std::cout << "\nApproach 4: Optimized Prefix and Suffix Products" << std::endl;
    std::vector<int> result4 = productExceptSelf_Optimized(nums);
    printVector(result4);

    std::cout << "\nApproach 5: Using std::partial_sum" << std::endl;
    std::vector<int> result5 = productExceptSelf_PartialSum(nums);
    printVector(result5);

    return 0;
}
