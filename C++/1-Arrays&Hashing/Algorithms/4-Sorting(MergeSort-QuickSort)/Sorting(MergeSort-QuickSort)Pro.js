/**
 * Sorting Algorithms in JavaScript
 *
 * This document provides implementations of several sorting algorithms in JavaScript,
 * including Merge Sort and Quick Sort, along with explanations and real-world use case
 * examples for each.
 */

/**
 * 1. Merge Sort
 *
 * -   Concept: A divide-and-conquer algorithm that divides the input array into smaller subarrays,
 * recursively sorts them, and then merges the sorted subarrays.
 * -   Time Complexity: O(n log n) in all cases (best, average, and worst).
 * -   Space Complexity: O(n) due to the auxiliary space used for merging.
 * -   Stability: Stable (maintains the relative order of equal elements).
 */
function mergeSort(arr) {
    // Base case: If the array has one or zero elements, it's already sorted.
    if (arr.length <= 1) {
        return arr;
    }

    // 1. Divide: Find the middle point of the array.
    const middle = Math.floor(arr.length / 2);
    const left = arr.slice(0, middle);  // Create a new array, a shallow copy
    const right = arr.slice(middle); // Create a new array, a shallow copy

    // 2. Conquer: Recursively sort the left and right subarrays.
    const sortedLeft = mergeSort(left);
    const sortedRight = mergeSort(right);

    // 3. Combine: Merge the sorted subarrays.
    return merge(sortedLeft, sortedRight);
}

/**
 * Helper function to merge two sorted arrays.
 */
function merge(left, right) {
    let result = [];
    let leftIndex = 0;
    let rightIndex = 0;

    // Compare elements from both arrays and add the smaller one to the result.
    while (leftIndex < left.length && rightIndex < right.length) {
        if (left[leftIndex] < right[rightIndex]) {
            result.push(left[leftIndex]);
            leftIndex++;
        } else {
            result.push(right[rightIndex]);
            rightIndex++;
        }
    }

    // Add any remaining elements from the left array.
    while (leftIndex < left.length) {
        result.push(left[leftIndex]);
        leftIndex++;
    }

    // Add any remaining elements from the right array.
    while (rightIndex < right.length) {
        result.push(right[rightIndex]);
        rightIndex++;
    }

    return result;
}

// Example Usage of Merge Sort:
const unsortedArrayMerge = [38, 27, 43, 3, 9, 82, 10];
const sortedArrayMerge = mergeSort(unsortedArrayMerge);
console.log("Merge Sort:", sortedArrayMerge); // Output: [3, 9, 10, 27, 38, 43, 82]

/**
 * Merge Sort - Real-World Application Example:
 *
 * -   Scenario: Sorting large datasets of user records based on their IDs in a database system.
 * -   Justification: Merge Sort's guaranteed O(n log n) time complexity makes it suitable for
 * handling large amounts of data efficiently.  Its stability is important if we want to
 * preserve any existing order of users with the same ID (e.g., sorted by join date).
 */
function sortUserRecordsById(userRecords) {
    return mergeSort(userRecords); // Assuming userRecords is an array of objects with an 'id' property.
}

const userRecords = [
  { id: 12, name: "Alice" },
  { id: 5, name: "Bob" },
  { id: 12, name: "Charlie" }, // Duplicate ID, but different data
  { id: 8, name: "David" },
];
const sortedUsers = sortUserRecordsById(userRecords);
console.log("Sorted User Records by ID:", sortedUsers);
// Output:
// [
//   { id: 5, name: 'Bob' },
//   { id: 8, name: 'David' },
//   { id: 12, name: 'Alice' },
//   { id: 12, name: 'Charlie' }
// ]
/**
 * 2. Quick Sort
 *
 * -   Concept: A divide-and-conquer algorithm that selects a 'pivot' element from the array
 * and partitions the other elements into two sub-arrays, according to whether they are
 * less than or greater than the pivot. The sub-arrays are then recursively sorted.
 * -   Time Complexity:
 * -   Best and Average Case: O(n log n)
 * -   Worst Case: O(n^2) (occurs when the pivot is consistently the smallest or largest element)
 * -   Space Complexity: O(log n) (average case, due to recursive call stack), O(n) (worst case)
 * -   Stability: Unstable (does not necessarily maintain the relative order of equal elements).
 */
function quickSort(arr) {
    // Base case: If the array has one or zero elements, it's already sorted.
    if (arr.length <= 1) {
        return arr;
    }

    // 1. Choose Pivot: Select a pivot element.  Here, we choose the last element.
    const pivot = arr[arr.length - 1];
    const left = [];
    const right = [];

    // 2. Partition: Divide the array into two sub-arrays based on the pivot.
    for (let i = 0; i < arr.length - 1; i++) { // Exclude the pivot element
        if (arr[i] < pivot) {
            left.push(arr[i]);
        } else {
            right.push(arr[i]);
        }
    }

    // 3. Recursively Sort: Recursively sort the left and right sub-arrays, and combine.
    return [...quickSort(left), pivot, ...quickSort(right)];
}

// Example Usage of Quick Sort:
const unsortedArrayQuick = [38, 27, 43, 3, 9, 82, 10];
const sortedArrayQuick = quickSort(unsortedArrayQuick);
console.log("Quick Sort:", sortedArrayQuick); // Output: [3, 9, 10, 27, 38, 43, 82]

/**
 * Quick Sort - Real-World Application Example:
 *
 * -   Scenario: Sorting search query results by relevance score in a search engine.
 * -   Justification: Quick Sort is often very efficient in practice (average case O(n log n))
 * and performs well with large datasets.  While not stable, the order of search results
 * with the same relevance score is usually not critical.  Randomized pivot selection
 * (not shown here for simplicity) can further improve performance and avoid worst-case
 * scenarios.
 */
function sortSearchResultsByRelevance(searchResults) {
    return quickSort(searchResults); // Assuming searchResults is an array of objects with a 'relevance' property.
}

const searchResults = [
  { query: "apple", relevance: 0.8 },
  { query: "banana", relevance: 0.3 },
  { query: "apple pie", relevance: 0.9 },
  { query: "orange", relevance: 0.5 },
];
const sortedResults = sortSearchResultsByRelevance(searchResults);
console.log("Sorted Search Results by Relevance:", sortedResults);
// Output:
// [
//   { query: 'banana', relevance: 0.3 },
//   { query: 'orange', relevance: 0.5 },
//   { query: 'apple', relevance: 0.8 },
//   { query: 'apple pie', relevance: 0.9 }
// ]

/**
 * 3. JavaScript's Built-in sort() method
 *
 * -   Concept:  The Array.prototype.sort() method sorts the elements of an array in place
 * and returns the sorted array.  The default sort order is ascending, built upon
 * converting the elements into strings, then comparing their sequences of UTF-16 code units values.
 * A compareFunction can be provided to customize the sort order.
 * -   Time Complexity:  O(n log n) on average, but the specific implementation varies
 * across JavaScript engines (e.g., V8 uses a variation of merge sort or quicksort).
 * Worst-case is often O(n^2), but engines try to avoid this.
 * -   Space Complexity: O(log n) for typical implementations (due to recursion),
 * but can be O(n) in some cases.
 * -   Stability:  Stable in modern implementations (ES2019 and later).
 */
function javaScriptSort(arr) {
    // Sorts the array in place, and also returns the sorted array.
    arr.sort((a, b) => a - b); // Ascending order for numbers.
    return arr;
}

// Example Usage of JavaScript's sort():
const unsortedArrayJS = [38, 27, 43, 3, 9, 82, 10];
const sortedArrayJS = javaScriptSort(unsortedArrayJS.slice()); // .slice() creates a copy to avoid modifying the original
console.log("JavaScript's sort():", sortedArrayJS); // Output: [3, 9, 10, 27, 38, 43, 82]
console.log("Original Array (not modified if using slice()):", unsortedArrayJS); // Output: [38, 27, 43, 3, 9, 82, 10]

/**
 * JavaScript's sort() - Real-World Application Example:
 *
 * -   Scenario: Sorting a list of products by price on an e-commerce website.
 * -   Justification:  JavaScript's built-in sort() is convenient and often efficient.  For
 * e-commerce, stability might be desirable to maintain the order of products with
 * the same price (e.g., based on publication date or popularity).
 */
function sortProductsByPrice(products) {
    // products is an array of objects, e.g., { name: "Product A", price: 25.99 }
    products.sort((a, b) => a.price - b.price);
    return products;
}

const products = [
  { name: "Product A", price: 25.99 },
  { name: "Product B", price: 19.99 },
  { name: "Product C", price: 25.99 }, // Same price as Product A
  { name: "Product D", price: 32.50 },
];
const sortedProducts = sortProductsByPrice(products.slice()); // Sort a copy
console.log("Sorted Products by Price:", sortedProducts);
// Output:
// [
//   { name: 'Product B', price: 19.99 },
//   { name: 'Product A', price: 25.99 },
//   { name: 'Product C', price: 25.99 },
//   { name: 'Product D', price: 32.5 }
// ]

/**
 * 4. Insertion Sort
 *
 * - Concept: Builds the final sorted array one item at a time.  It iterates through the input
 * array, and at each iteration, it removes one element, finds the correct position
 * for it in the sorted portion of the array, and inserts it there.
 * - Time Complexity:
 * - Best Case: O(n) (when the input is already sorted)
 * - Average and Worst Case: O(n^2)
 * - Space Complexity: O(1) (sorts in place)
 * - Stability: Stable
 */
function insertionSort(arr) {
  for (let i = 1; i < arr.length; i++) {
    let key = arr[i];
    let j = i - 1;

    // Move elements of arr[0..i-1] that are greater than key
    // to one position ahead of their current position
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
  return arr;
}

// Example
const unsortedArrayInsertion = [12, 11, 13, 5, 6];
const sortedArrayInsertion = insertionSort(unsortedArrayInsertion.slice());
console.log("Insertion Sort:", sortedArrayInsertion); // Output: [5, 6, 11, 12, 13]

/**
 * Insertion Sort Real-World Application Example:
 *
 * - Scenario: Sorting a hand of playing cards.
 * - Justification: Insertion sort is intuitive and efficient for small datasets or nearly sorted data.
 * When you pick up a card in a card game, you insert it into the correct position in your hand.
 */
function sortPlayingCards(cards) {
  return insertionSort(cards); // Assuming cards is an array of card objects.
}

const handOfCards = [
    { rank: '5', suit: 'Hearts' },
    { rank: '2', suit: 'Diamonds' },
    { rank: 'K', suit: 'Clubs' },
    { rank: '3', suit: 'Spades' },
    { rank: 'J', suit: 'Hearts' }
];

const sortedHand = sortPlayingCards(handOfCards.slice());
console.log("Sorted Playing Cards:", sortedHand);
// Output:
// [
//   { rank: '2', suit: 'Diamonds' },
//   { rank: '3', suit: 'Spades' },
//   { rank: '5', suit: 'Hearts' },
//   { rank: 'J', suit: 'Hearts' },
//   { rank: 'K', suit: 'Clubs' }
// ]

/**
 * 5. Selection Sort
 *
 * - Concept: The selection sort algorithm sorts an array by repeatedly finding the minimum
 * element (or maximum element, depending on the desired order) from the unsorted part
 * and putting it at the beginning. The algorithm divides the array into two parts: the
 * sorted subarray, which is built up from left to right, and the remaining unsorted subarray.
 * - Time Complexity: O(n^2) in all cases.
 * - Space Complexity: O(1)
 * - Stability: Unstable
 */
function selectionSort(arr) {
    const n = arr.length;

    for (let i = 0; i < n - 1; i++) {
        let minIndex = i;
        for (let j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex !== i) {
            // Swap arr[i] and arr[minIndex]
            [arr[i], arr[minIndex]] = [arr[minIndex], arr[i]];
        }
    }
    return arr;
}

// Example:
const unsortedArraySelection = [64, 25, 12, 22, 11];
const sortedArraySelection = selectionSort(unsortedArraySelection.slice());
console.log("Selection Sort:", sortedArraySelection); // Output: [11, 12, 22, 25, 64]

/**
 * Selection Sort Real-World Application Example:
 *
 * - Scenario:  Sorting a small list of student grades.
 * - Justification: Selection sort is simple to implement and performs well for small datasets.
 * Although its O(n^2) time complexity makes it inefficient for large lists, it has a minimal
 * memory footprint, which can be advantageous in memory-constrained environments.
 */
function sortStudentGrades(grades) {
  return selectionSort(grades);
}

const studentGrades = [85, 92, 78, 95, 88];
const sortedGrades = sortStudentGrades(studentGrades.slice());
console.log("Sorted Student Grades:", sortedGrades); // Output: [ 78, 85, 88, 92, 95 ]

/**
 * 6. Bubble Sort
 *
 * - Concept: Bubble Sort is the simplest sorting algorithm that repeatedly steps through the
 * list, compares adjacent elements and swaps them if they are in the wrong order. The pass
 * through the list is repeated until no swaps are needed, which indicates that the list is sorted.
 * - Time Complexity:
 * - Best Case: O(n) (when the array is already sorted)
 * - Average and Worst Case: O(n^2)
 * - Space Complexity: O(1)
 * - Stability: Stable
 */
function bubbleSort(arr) {
  const n = arr.length;
  for (let i = 0; i < n - 1; i++) {
    for (let j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        // Swap arr[j] and arr[j+1]
        [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
      }
    }
  }
  return arr;
}

// Example:
const unsortedArrayBubble = [5, 1, 4, 2, 8];
const sortedArrayBubble = bubbleSort(unsortedArrayBubble.slice());
console.log("Bubble Sort:", sortedArrayBubble); // Output: [1, 2, 4, 5, 8]

/**
 * Bubble Sort Real-World Application Example:
 *
 * - Scenario: Displaying a "loading..." animation while sorting a small dataset.
 * - Justification: Bubble sort's simplicity makes it easy to visualize.  Its swaps can be
 * used to drive an animation, even if the sorting itself is inefficient.  It's rarely
 * used for actual sorting in production.
 */
function visualizeSort(data) {
  const n = data.length;
  const animations = []; // Array to store swap operations for animation

  for (let i = 0; i < n - 1; i++) {
    for (let j = 0; j < n - i - 1; j++) {
      if (data[j] > data[j + 1]) {
        // Swap data[j] and data[j+1]
        [data[j], data[j + 1]] = [data[j + 1], data[j]];
        animations.push([j, j + 1, data[j], data[j + 1]]); // Store swap for animation
      }
    }
  }
  return { sortedData: data, animations };
}

const dataToSort = [10, 5, 8, 1, 7];
const { sortedData, animations } = visualizeSort(dataToSort.slice());
console.log("Visualize Sort - Sorted Data:", sortedData);
console.log("Visualize Sort - Animations:", animations);
/* Output:
Visualize Sort - Sorted Data: [ 1, 5, 7, 8, 10 ]
Visualize Sort - Animations: [
  [ 0, 1, 5, 10 ],
  [ 1, 2, 8, 5 ],
  [ 0, 1, 1, 5 ],
  [ 1, 2, 5, 8 ],
  [ 2, 3, 1, 8 ],
  [ 3, 4, 7, 1 ]
]
*/
