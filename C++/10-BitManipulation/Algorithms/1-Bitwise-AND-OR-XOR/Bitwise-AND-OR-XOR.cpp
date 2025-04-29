#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

// Function to print the binary representation of an integer (for clarity)
void printBinary(unsigned int n) {
    if (n == 0) {
        std::cout << "0";
        return;
    }
    std::vector<int> binary;
    while (n > 0) {
        binary.push_back(n % 2);
        n /= 2;
    }
    for (int i = binary.size() - 1; i >= 0; i--) {
        std::cout << binary[i];
    }
}

int main() {
    unsigned int num1 = 10; // 1010 in binary
    unsigned int num2 = 7;  // 0111 in binary

    std::cout << "Number 1: " << num1 << " (Binary: ";
    printBinary(num1);
    std::cout << ")" << std::endl;
    std::cout << "Number 2: " << num2 << " (Binary: ";
    printBinary(num2);
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    // Approach 1: Using the basic bitwise operators directly
    std::cout << "Approach 1: Direct Application of Bitwise Operators" << std::endl;
    unsigned int andResult1 = num1 & num2; // Bitwise AND
    unsigned int orResult1 = num1 | num2;  // Bitwise OR
    unsigned int xorResult1 = num1 ^ num2; // Bitwise XOR

    std::cout << "AND: " << andResult1 << " (Binary: ";
    printBinary(andResult1);
    std::cout << ")" << std::endl;
    std::cout << "OR:  " << orResult1 << " (Binary: ";
    printBinary(orResult1);
    std::cout << ")" << std::endl;
    std::cout << "XOR: " << xorResult1 << " (Binary: ";
    printBinary(xorResult1);
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    // Approach 2:  Using a function for bitwise AND
    std::cout << "Approach 2: Bitwise AND Function" << std::endl;
    auto bitwiseAndFunc = [](unsigned int a, unsigned int b) {
        return a & b;
    };
    unsigned int andResult2 = bitwiseAndFunc(num1, num2);
    std::cout << "AND: " << andResult2 << " (Binary: ";
    printBinary(andResult2);
    std::cout << ")" << std::endl;
    std::cout << std::endl;


    // Approach 3: Using a function for bitwise OR
    std::cout << "Approach 3: Bitwise OR Function" << std::endl;
    auto bitwiseOrFunc = [](unsigned int a, unsigned int b) {
        return a | b;
    };
    unsigned int orResult3 = bitwiseOrFunc(num1, num2);
    std::cout << "OR: " << orResult3 << " (Binary: ";
    printBinary(orResult3);
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    // Approach 4: Using a function for bitwise XOR
    std::cout << "Approach 4: Bitwise XOR Function" << std::endl;
    auto bitwiseXorFunc = [](unsigned int a, unsigned int b) {
        return a ^ b;
    };
    unsigned int xorResult4 = bitwiseXorFunc(num1, num2);
    std::cout << "XOR: " << xorResult4 << " (Binary: ";
    printBinary(xorResult4);
    std::cout << ")" << std::endl;
    std::cout << std::endl;

   // Approach 5: Combining all operations in one function
    std::cout << "Approach 5: Combined Bitwise Operations Function" << std::endl;
    auto bitwiseOperations = [](unsigned int a, unsigned int b) {
        return std::make_tuple(a & b, a | b, a ^ b);
    };

    unsigned int andResult5, orResult5, xorResult5;
    std::tie(andResult5, orResult5, xorResult5) = bitwiseOperations(num1, num2);

    std::cout << "AND: " << andResult5 << " (Binary: ";
    printBinary(andResult5);
    std::cout << ")" << std::endl;
    std::cout << "OR:  " << orResult5 << " (Binary: ";
    printBinary(orResult5);
    std::cout << ")" << std::endl;
    std::cout << "XOR: " << xorResult5 << " (Binary: ";
    printBinary(xorResult5);
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    return 0;
}
