#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <bitset> // Required for bitset approach

using namespace std;

// Function to find the single number (the one that appears only once) in a vector of integers
// where all other numbers appear exactly twice.

// Approach 1: Using XOR (Bitwise Exclusive OR)
//
// - The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
// - We can XOR all the numbers in the vector.  The pairs of duplicates will cancel each other out (a ^ a = 0),
//   and the single number XORed with 0 will result in the single number itself.
// - This is the most efficient and widely used approach for this problem due to its simplicity and speed.
// - Real-world application:  Error detection in data transmission.  XOR is used to calculate parity bits.
int singleNumber_XOR(const vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}

// Approach 2: Using Summation
//
// - Calculate the sum of all numbers in the vector.
// - Create a set of the unique numbers in the vector.
// - Calculate the sum of the unique numbers and multiply it by 2.
// - The difference between (2 * sum of unique numbers) and (sum of all numbers) is the single number.
// - This approach is less efficient than XOR due to the overhead of set operations and extra calculations.
// - Real-world application:  Verifying data integrity in databases.  Summation can be used in checksum calculations.
int singleNumber_Summation(const vector<int>& nums) {
    long long sumOfNums = accumulate(nums.begin(), nums.end(), 0LL); // Use long long to avoid overflow
    unordered_map<int, bool> seen;
    long long sumOfUniqueNums = 0;

    for(int num : nums){
        if(seen.find(num) == seen.end()){
            sumOfUniqueNums += num;
            seen[num] = true;
        }
    }
    return static_cast<int>(2 * sumOfUniqueNums - sumOfNums);
}

// Approach 3: Using a Hash Map (unordered_map)
//
// - Store the frequency of each number in a hash map.
// - Iterate through the hash map and find the number with a frequency of 1.
// - This approach is more versatile and can be used for variations of the problem where numbers appear more than twice.
// - Real-world application:  Counting occurrences of events in log analysis.  Hash maps are used to efficiently track frequencies.
int singleNumber_HashMap(const vector<int>& nums) {
    unordered_map<int, int> numCounts;
    for (int num : nums) {
        numCounts[num]++;
    }
    for (const auto& pair : numCounts) {
        if (pair.second == 1) {
            return pair.first;
        }
    }
    return -1; // Or throw an exception, indicating no single number found.
}

// Approach 4: Using Sorting
//
// - Sort the vector.
// - Iterate through the sorted vector. If a number is different from the next number,
//   it is the single number.  Handle the edge case where the single number is the last element.
// - This approach modifies the input vector (which might not be desirable in some cases) and has a time complexity of O(n log n) due to sorting.
// - Real-world application:  Finding unique items in a sorted list of products.  Sorting is often a preprocessing step.

int singleNumber_Sorting(vector<int> nums) { // Pass by value to avoid modifying the original vector
    sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() - 1; i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back(); // If the single number is the last element
}

// Approach 5: Using Bitsets
//
// - This approach uses bitsets to count the number of times each bit is set across all numbers.
// - For each bit position (0 to 31 for 32-bit integers), count how many numbers have that bit set.
// - If the count is odd, the single number has that bit set.
// - This approach works because the duplicate numbers will have an even count for each bit.
// - Real-world application:  Analyzing binary data, such as network packet inspection or low-level hardware manipulation.
int singleNumber_Bitsets(const vector<int>& nums) {
    int singleNum = 0;
    for (int i = 0; i < 32; ++i) { // Iterate over each bit position (0 to 31 for 32-bit integers)
        int bitSum = 0;
        for (int num : nums) {
            // Check if the i-th bit is set in the current number
            if ((num >> i) & 1) {
                bitSum++;
            }
        }
        // If the sum of the bits is odd, set the corresponding bit in the result
        if (bitSum % 2 != 0) {
            singleNum |= (1 << i);
        }
    }
    return singleNum;
}

int main() {
    vector<int> numbers = {4, 1, 2, 1, 2};
    //vector<int> numbers = {2,2,1};
    //vector<int> numbers = {1};

    cout << "Numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Single Number (XOR): " << singleNumber_XOR(numbers) << endl;
    cout << "Single Number (Summation): " << singleNumber_Summation(numbers) << endl;
    cout << "Single Number (HashMap): " << singleNumber_HashMap(numbers) << endl;
    cout << "Single Number (Sorting): " << singleNumber_Sorting(numbers) << endl;
    cout << "Single Number (Bitsets): " << singleNumber_Bitsets(numbers) << endl;

    return 0;
}
