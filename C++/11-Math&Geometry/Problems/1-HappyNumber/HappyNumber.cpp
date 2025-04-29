#include <iostream>
#include <unordered_set>
#include <vector>
#include <numeric> // for std::accumulate
#include <cmath>   // for std::pow

// Function to calculate the sum of the squares of the digits of a number
int sumOfSquaredDigits(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

// Approach 1: Using a HashSet to detect cycles
bool isHappy_Approach1(int n) {
    std::unordered_set<int> seenNumbers;
    while (n != 1) {
        if (seenNumbers.find(n) != seenNumbers.end()) {
            return false; // Cycle detected, not a happy number
        }
        seenNumbers.insert(n);
        n = sumOfSquaredDigits(n);
    }
    return true; // Reached 1, it's a happy number
}

// Approach 2: Using the Floyd Cycle Detection Algorithm (Tortoise and Hare)
bool isHappy_Approach2(int n) {
    int slow = n;
    int fast = n;
    do {
        slow = sumOfSquaredDigits(slow);
        fast = sumOfSquaredDigits(sumOfSquaredDigits(fast));
    } while (slow != fast);
    return slow == 1; // If they meet at 1, it's a happy number
}

// Approach 3: Using a vector to store previously seen numbers
bool isHappy_Approach3(int n) {
    std::vector<int> seenNumbers;
    while (n != 1) {
        for (int seenNum : seenNumbers) {
            if (seenNum == n) {
                return false; // Cycle detected
            }
        }
        seenNumbers.push_back(n);
        n = sumOfSquaredDigits(n);
    }
    return true;
}

// Approach 4: Iterative approach with a hardcoded check for 4
bool isHappy_Approach4(int n) {
    while (n != 1 && n != 4) { // 4 is the start of the cycle for non-happy numbers
        n = sumOfSquaredDigits(n);
    }
    return n == 1;
}

// Approach 5: Using string conversion
bool isHappy_Approach5(int n) {
    std::unordered_set<std::string> seenNumbers;
    while (n != 1) {
        std::string n_str = std::to_string(n);
        if (seenNumbers.find(n_str) != seenNumbers.end())
            return false;
        seenNumbers.insert(n_str);
        n = 0;
        for (char c : n_str) {
            int digit = c - '0';
            n += digit * digit;
        }
    }
    return true;
}

int main() {
    int number = 19; // Example number to check

    std::cout << "Number: " << number << std::endl;
    std::cout << "Approach 1 (HashSet): " << (isHappy_Approach1(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 2 (Floyd's Cycle Detection): " << (isHappy_Approach2(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 3 (Vector): " << (isHappy_Approach3(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 4 (Check for 4): " << (isHappy_Approach4(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 5 (String Conversion): " << (isHappy_Approach5(number) ? "Happy" : "Not Happy") << std::endl;

    number = 2;
    std::cout << "\nNumber: " << number << std::endl;
    std::cout << "Approach 1 (HashSet): " << (isHappy_Approach1(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 2 (Floyd's Cycle Detection): " << (isHappy_Approach2(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 3 (Vector): " << (isHappy_Approach3(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 4 (Check for 4): " << (isHappy_Approach4(number) ? "Happy" : "Not Happy") << std::endl;
    std::cout << "Approach 5 (String Conversion): " << (isHappy_Approach5(number) ? "Happy" : "Not Happy") << std::endl;

    return 0;
}

