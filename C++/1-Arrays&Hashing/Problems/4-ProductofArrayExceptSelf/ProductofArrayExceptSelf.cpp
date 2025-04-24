#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate

using namespace std;

// Approach 1: Brute Force
// For each element, calculate the product of all other elements.
// Time Complexity: O(n^2), Space Complexity: O(n)
vector<int> productExceptSelf_BruteForce(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);

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
// Calculate the product of all elements, then divide by each element.
// Handles zero elements in the array.
// Time Complexity: O(n), Space Complexity: O(n)
vector<int> productExceptSelf_WithDivision(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    long long totalProduct = 1; // Use long long to prevent overflow
    int zeroCount = 0;

    for (int num : nums) {
        if (num == 0) {
            zeroCount++;
        } else {
            totalProduct *= num;
        }
    }

    if (zeroCount > 1) {
        // If there are more than one zero, the result is all zeros.
        return result; // vector<int> result(n, 0); // Initialize vector with 0, already default.
    } else if (zeroCount == 1) {
        // If there is exactly one zero, only the element at that index has a non-zero product.
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                result[i] = totalProduct;
            }
        }
    } else {
        // If there are no zeros, divide the total product by each element.
        for (int i = 0; i < n; ++i) {
            result[i] = totalProduct / nums[i];
        }
    }
    return result;
}

// Approach 3: Left and Right Products
// Calculate the product of elements to the left and right of each element.
// Time Complexity: O(n), Space Complexity: O(n)
vector<int> productExceptSelf_LeftRight(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    vector<int> leftProducts(n);
    vector<int> rightProducts(n);

    // Calculate left products
    leftProducts[0] = 1;
    for (int i = 1; i < n; ++i) {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
    }

    // Calculate right products
    rightProducts[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
    }

    // Calculate the final result
    for (int i = 0; i < n; ++i) {
        result[i] = leftProducts[i] * rightProducts[i];
    }
    return result;
}

// Approach 4: Optimized Left and Right Products (Constant Space)
// Optimized version of Approach 3, reducing space complexity to O(1).
// Time Complexity: O(n), Space Complexity: O(1) (excluding the output array)
vector<int> productExceptSelf_Optimized(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);

    // Calculate left products and store them in the result array
    result[0] = 1;
    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] * nums[i - 1];
    }

    // Calculate right products and multiply them with the left products
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return result;
}

// Approach 5: Using accumulate() and division (Handles Zero Case)
// Uses the accumulate function to efficiently get the product, and handles edge cases.
// Time Complexity: O(n), Space Complexity: O(n)
vector<int> productExceptSelf_Accumulate(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 0); // Initialize result vector with 0s.
    int zeroCount = 0;
    long long product = 1;

    for(int num : nums){
        if(num == 0){
            zeroCount++;
        }
        else{
            product *= num;
        }
    }
    if(zeroCount > 1){
        return result; // Return vector of 0s
    }
    else if (zeroCount == 1){
        for(int i = 0; i< n; ++i){
            if(nums[i] == 0){
                result[i] = product;
                break;
            }
        }
    }
    else{
        for(int i = 0; i< n; ++i){
            result[i] = product/nums[i];
        }
    }

    return result;
}

int main() {
    vector<int> nums = {1, 2, 3, 4};

    cout << "Input: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Brute Force: ";
    vector<int> result1 = productExceptSelf_BruteForce(nums);
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "With Division: ";
    vector<int> result2 = productExceptSelf_WithDivision(nums);
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Left and Right Products: ";
    vector<int> result3 = productExceptSelf_LeftRight(nums);
    for (int num : result3) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Optimized Left and Right Products: ";
    vector<int> result4 = productExceptSelf_Optimized(nums);
    for (int num : result4) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Using accumulate(): ";
    vector<int> result5 = productExceptSelf_Accumulate(nums);
     for (int num : result5) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
