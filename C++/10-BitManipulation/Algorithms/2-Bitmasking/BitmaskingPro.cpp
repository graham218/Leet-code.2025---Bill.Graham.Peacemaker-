#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <functional> // Include for std::function

using namespace std;

// Function to print the binary representation of a number (for debugging)
void printBinary(unsigned int n) {
    if (n == 0) {
        cout << "0";
        return;
    }
    vector<int> binary;
    while (n > 0) {
        binary.push_back(n % 2);
        n /= 2;
    }
    for (int i = binary.size() - 1; i >= 0; i--) {
        cout << binary[i];
    }
}

// 1. Representing Sets using Bitmasks
//
// Real-world application: Feature flags in software development.  Imagine you're building a complex application,
// and you want to enable/disable certain features for different users or during A/B testing.  Bitmasks provide
// an efficient way to represent which features are active.
//
// Example: Let's say you have 8 features in your application.
// You can use an 8-bit number (e.g., an unsigned char) to represent the state of these features.
// Each bit corresponds to a feature: 1 = enabled, 0 = disabled.

void featureFlagsExample() {
    // Define constants for feature indices (good practice for readability and maintainability)
    const int FEATURE_A = 0; // Rightmost bit
    const int FEATURE_B = 1;
    const int FEATURE_C = 2;
    const int FEATURE_D = 3;
    const int FEATURE_E = 4;
    const int FEATURE_F = 5;
    const int FEATURE_G = 6;
    const int FEATURE_H = 7; // Leftmost bit

    // Initialize feature flags (all disabled initially)
    unsigned char featureFlags = 0; // 8 bits, all 0

    cout << "Initial Feature Flags: ";
    printBinary(featureFlags);
    cout << endl;

    // Enable Feature A and C
    featureFlags |= (1 << FEATURE_A); // Set the bit at position FEATURE_A to 1
    featureFlags |= (1 << FEATURE_C);

    cout << "After enabling A and C: ";
    printBinary(featureFlags);
    cout << endl;

    // Check if Feature C is enabled
    if (featureFlags & (1 << FEATURE_C)) {
        cout << "Feature C is enabled." << endl;
    } else {
        cout << "Feature C is disabled." << endl;
    }

    // Disable Feature A
    featureFlags &= ~(1 << FEATURE_A); // Clear the bit at position FEATURE_A to 0

    cout << "After disabling A: ";
    printBinary(featureFlags);
    cout << endl;

     // Toggle Feature B (enable if disabled, disable if enabled)
    featureFlags ^= (1 << FEATURE_B);
    cout << "After toggling B: ";
    printBinary(featureFlags);
    cout << endl;

    // Check how many features are enabled.
    int enabledCount = __builtin_popcount(featureFlags); // Efficiently counts set bits (compiler intrinsic)
    cout << "Number of enabled features: " << enabledCount << endl;
}

// 2. Representing subsets
//
// Real-world application:  Recommendation systems.  Imagine you're building an e-commerce site.  You might want to
// represent the set of products a user has purchased, the set of products in their shopping cart, or the set of
// products they've viewed.  Bitmasks can efficiently represent these subsets of items.
//
// Example:  Let's say you have 16 products.  Each product can be represented by a bit in a 16-bit number.
// If the bit is set, the product is in the subset; otherwise, it's not.

void subsetExample() {
    const int NUM_PRODUCTS = 16;
    unsigned short userCart = 0; // 16 bits to represent the shopping cart

    // Add products 1, 3, and 5 (product numbering starts from 0) to the cart
    userCart |= (1 << 1);
    userCart |= (1 << 3);
    userCart |= (1 << 5);

    cout << "User Cart: ";
    printBinary(userCart);
    cout << endl;

    // Check if product 3 is in the cart
    if (userCart & (1 << 3)) {
        cout << "Product 3 is in the cart." << endl;
    } else {
        cout << "Product 3 is not in the cart." << endl;
    }

    // Remove product 1 from the cart
    userCart &= ~(1 << 1);

    cout << "Cart after removing product 1: ";
    printBinary(userCart);
    cout << endl;

    // Add product 15
    userCart |= (1 << 15);
    cout << "Cart after adding product 15: ";
    printBinary(userCart);
    cout << endl;

    // Iterate through the cart and print the products.
    cout << "Products in cart: ";
    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        if (userCart & (1 << i)) {
            cout << i << " "; // Print the product index
        }
    }
    cout << endl;
}

// 3. Game State Representation
//
// Real-world application: Representing the state of a game board.  Bitmasks can be very efficient for games
// with a limited number of positions or pieces, such as chess, tic-tac-toe, or smaller board games.
//
// Example:  Tic-tac-toe.  You can represent the state of the board using three 9-bit numbers:
// one for X's positions, one for O's positions, and one for empty positions (optional, can be derived).

void ticTacToeExample() {
    unsigned short xPositions = 0; // 9 bits for the 9 squares
    unsigned short oPositions = 0;
    // 000 000 000
    //  7 8 9
    //  4 5 6
    //  1 2 3

    // X plays at position 1 (bottom-left)
    xPositions |= (1 << 0); //  000 000 001

    // O plays at position 5 (center)
    oPositions |= (1 << 4); //  000 001 000

     // X plays at position 9 (top-right)
    xPositions |= (1 << 8);

    cout << "X positions: ";
    printBinary(xPositions);
    cout << endl;
    cout << "O positions: ";
    printBinary(oPositions);
    cout << endl;

    // Check if X has won (horizontally, row 1)
    bool xWins = (xPositions & 0b111) == 0b111; // Check last 3 bits

    if (xWins)
    {
        cout << "X wins (row 1)" << endl;
    }
    else
        cout << "X has not won (row 1)" << endl;

    // A more general way to check for a win (any row, column, or diagonal) would require more complex bit manipulation.
    //  For brevity, a full win-checking function is not included here, but the principle of using bitmasks to
    //  represent the board state is illustrated.
}

// 4.  Efficiently Processing Subsets
//
// Real-world application:  Solving optimization problems where you need to iterate through all possible
// combinations of a set of items.  For example, finding the best combination of products to bundle in a
// promotion, or finding the optimal set of tasks to assign to a team.
//
// Example:  Given a set of items, generate all possible subsets.

void generateSubsetsExample() {
    vector<string> items = {"A", "B", "C", "D"};
    int numItems = items.size();

    // Iterate through all possible bitmasks (from 0 to 2^n - 1)
    for (int mask = 0; mask < (1 << numItems); ++mask) {
        cout << "{ ";
        // Iterate through each item
        for (int i = 0; i < numItems; ++i) {
            // Check if the i-th bit is set in the current mask
            if (mask & (1 << i)) {
                cout << items[i] << " "; // If set, include the item in the subset
            }
        }
        cout << "}" << endl;
    }
}

// 5. Compression and Hashing
//
// Real-world application:  Bloom filters.  A Bloom filter is a space-efficient probabilistic data structure
// used to test whether an element is a member of a set.  It uses bit manipulation for its core operations.
//
//  A Bloom filter can tell you that an element is *possibly* in the set or *definitely* not in the set.
//  It's very efficient for checking if an element is NOT in a set.
void bloomFilterExample() {
    const int BLOOM_FILTER_SIZE = 256; // Number of bits in the filter
    unsigned char bloomFilter[BLOOM_FILTER_SIZE / 8] = {0}; // Array of bytes (256 bits)
    // We divide by 8 because each element in the array is a byte (8 bits).

    // Hash functions (simplified for demonstration)
    // In a real Bloom filter, you'd use multiple, independent hash functions.  These should be fast and
    // distribute the keys relatively evenly.  Good hash functions are crucial for the performance
    // and accuracy of a Bloom filter.
    std::function<int(string)> hash1 = [](string s) {
        int hash = 0;
        for (char c : s) hash = (hash * 31 + c) % BLOOM_FILTER_SIZE;
        return hash;
    };
    std::function<int(string)> hash2 = [](string s) {
        int hash = 0;
        for (char c : s) hash = (hash * 17 + c) % BLOOM_FILTER_SIZE;
        return hash;
    };
    std::function<int(string)> hash3 = [](string s) {
        int hash = 0;
        for (char c : s) hash = (hash * 101 + c) % BLOOM_FILTER_SIZE;
        return hash;
    };

    // Function to add an element to the Bloom filter
    auto add = [&](string s) {
        int h1 = hash1(s);
        int h2 = hash2(s);
        int h3 = hash3(s);

        // Set the corresponding bits in the filter
        bloomFilter[h1 / 8] |= (1 << (h1 % 8)); //  h1 / 8 gets the byte, h1 % 8 gets the bit in that byte.
        bloomFilter[h2 / 8] |= (1 << (h2 % 8));
        bloomFilter[h3 / 8] |= (1 << (h3 % 8));
    };

    // Function to check if an element is possibly in the Bloom filter
    auto contains = [&](string s) {
        int h1 = hash1(s);
        int h2 = hash2(s);
        int h3 = hash3(s);

        // Check if all corresponding bits are set
        bool present = (bloomFilter[h1 / 8] & (1 << (h1 % 8))) &&
                       (bloomFilter[h2 / 8] & (1 << (h2 % 8))) &&
                       (bloomFilter[h3 / 8] & (1 << (h3 % 8)));
        return present;
    };

    // Add some elements to the Bloom filter
    add("apple");
    add("banana");
    add("orange");

    // Check for membership
    cout << "Is apple in the set? " << (contains("apple") ? "Possibly" : "Definitely not") << endl;
    cout << "Is banana in the set? " << (contains("banana") ? "Possibly" : "Definitely not") << endl;
    cout << "Is orange in the set? " << (contains("orange") ? "Possibly" : "Definitely not") << endl;
    cout << "Is grape in the set? " << (contains("grape") ? "Possibly" : "Definitely not") << endl;

    //  Important Note:  Bloom filters can have false positives (they might say an element is in the set
    //  when it's not), but they never have false negatives.  The probability of a false positive depends
    //  on the size of the filter and the number of hash functions.
}

int main() {
    cout << "1. Feature Flags Example:" << endl;
    featureFlagsExample();
    cout << endl;

    cout << "2. Subset Example:" << endl;
    subsetExample();
    cout << endl;

    cout << "3. Tic-Tac-Toe Example:" << endl;
    ticTacToeExample();
    cout << endl;

    cout << "4. Generate Subsets Example:" << endl;
    generateSubsetsExample();
    cout << endl;

    cout << "5. Bloom Filter Example:" << endl;
    bloomFilterExample();
    cout << endl;

    return 0;
}
