// Definition of a ListNode (used for all approaches)
function ListNode(val, next) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
}

// Helper function to create a linked list from an array (used for testing)
function createLinkedList(arr) {
    if (!arr || arr.length === 0) return null;
    let head = new ListNode(arr[0]);
    let current = head;
    for (let i = 1; i < arr.length; i++) {
        current.next = new ListNode(arr[i]);
        current = current.next;
    }
    return head;
}

// Helper function to convert a linked list to an array (used for output and verification)
function linkedListToArray(head) {
    const result = [];
    let current = head;
    while (current) {
        result.push(current.val);
        current = current.next;
    }
    return result;
}

// Helper function to visualize linked list
function printLinkedList(head) {
  let current = head;
  let str = "";
  while (current) {
    str += current.val + " -> ";
    current = current.next;
  }
  str += "null";
  console.log(str);
}

/**
 * Merge two sorted linked lists.
 *
 * Input:
 * - l1: The head of the first sorted linked list.
 * - l2: The head of the second sorted linked list.
 *
 * Output:
 * - The head of the merged sorted linked list.
 */

// Approach 1: Iterative with Dummy Node
// Time Complexity: O(m + n), where m and n are the lengths of the two lists.
// Space Complexity: O(1) - Constant space.
const mergeTwoListsV1 = function(l1, l2) {
    let dummy = new ListNode(-1); // Dummy node to simplify the head handling
    let tail = dummy;

    while (l1 && l2) {
        if (l1.val <= l2.val) {
            tail.next = l1;
            l1 = l1.next;
        } else {
            tail.next = l2;
            l2 = l2.next;
        }
        tail = tail.next;
    }

    // Append the remaining non-null list
    tail.next = l1 || l2;

    return dummy.next; // Return the merged list starting from the node after the dummy
};

// Approach 2: Recursive
// Time Complexity: O(m + n)
// Space Complexity: O(m + n) - Due to the recursive call stack.
const mergeTwoListsV2 = function(l1, l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1.val <= l2.val) {
        l1.next = mergeTwoListsV2(l1.next, l2);
        return l1;
    } else {
        l2.next = mergeTwoListsV2(l1, l2.next);
        return l2;
    }
};

// Approach 3: Iterative In-Place (No Dummy Node)
// Time Complexity: O(m + n)
// Space Complexity: O(1) - Constant space.  Modifies the original lists.
const mergeTwoListsV3 = function(l1, l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    // Determine the head of the merged list
    if (l1.val > l2.val) {
        [l1, l2] = [l2, l1]; // Swap l1 and l2
    }
    let head = l1; // head of the merged list
    let prev = l1;
    l1 = l1.next;

    while (l1 && l2) {
        if (l1.val <= l2.val) {
            prev.next = l1;
            l1 = l1.next;
        } else {
            prev.next = l2;
            let temp = l2.next;
            l2.next = l1;
            l2 = temp;
        }
        prev = prev.next;
    }
    prev.next = l1 || l2; // append what is left of l1 or l2
    return head;
};

// Approach 4: Using Array and Sorting (Not a true linked list merge, but for comparison)
// Time Complexity: O((m + n) log (m + n)) - Due to sorting.
// Space Complexity: O(m + n) - To store the combined array.
const mergeTwoListsV4 = function(l1, l2) {
    const arr1 = linkedListToArray(l1);
    const arr2 = linkedListToArray(l2);
    const mergedArray = arr1.concat(arr2);
    mergedArray.sort((a, b) => a - b); // Sort the merged array
    return createLinkedList(mergedArray);
};

// Approach 5: Iterative with Carry (For demonstration -  not directly applicable here, but shows a different pattern)
// This approach is more relevant for merging sorted arrays where you might have
// a carry-over, like in adding two numbers represented as linked lists.  It's
// included here to show a different linked list manipulation pattern.  It does NOT correctly merge sorted lists.
// Time Complexity: O(m+n)
// Space Complexity: O(1)
const mergeTwoListsV5 = function(l1, l2) {
    let dummy = new ListNode(-1);
    let current = dummy;
    let carry = 0;

    while (l1 || l2 || carry) {
        const val1 = l1 ? l1.val : 0;
        const val2 = l2 ? l2.val : 0;
        const sum = val1 + val2 + carry;

        carry = Math.floor(sum / 10);  // Corrected carry calculation.
        current.next = new ListNode(sum % 10); // Corrected node creation.
        current = current.next;

        l1 = l1 ? l1.next : null;
        l2 = l2 ? l2.next : null;
    }
    return dummy.next;
};



// Test Cases
const list1 = createLinkedList([1, 2, 4]);
const list2 = createLinkedList([1, 3, 4]);
const list3 = createLinkedList([]);
const list4 = createLinkedList([]);
const list5 = createLinkedList([5]);
const list6 = createLinkedList([1,2,3,4,5,6]);

console.log("Input Lists:");
printLinkedList(list1);
printLinkedList(list2);
console.log("\n");

// Test Case 1: Basic merge
console.log("Test Case 1: Basic Merge");
let merged1_1 = mergeTwoListsV1(createLinkedList([1, 2, 4]), createLinkedList([1, 3, 4]));
let merged1_2 = mergeTwoListsV2(createLinkedList([1, 2, 4]), createLinkedList([1, 3, 4]));
let merged1_3 = mergeTwoListsV3(createLinkedList([1, 2, 4]), createLinkedList([1, 3, 4]));
let merged1_4 = mergeTwoListsV4(createLinkedList([1, 2, 4]), createLinkedList([1, 3, 4]));
let merged1_5 = mergeTwoListsV5(createLinkedList([1, 2, 4]), createLinkedList([1, 3, 4]));
console.log("V1:", linkedListToArray(merged1_1)); // Expected: [1, 1, 2, 3, 4, 4]
console.log("V2:", linkedListToArray(merged1_2)); // Expected: [1, 1, 2, 3, 4, 4]
console.log("V3:", linkedListToArray(merged1_3)); // Expected: [1, 1, 2, 3, 4, 4]
console.log("V4:", linkedListToArray(merged1_4)); // Expected: [1, 1, 2, 3, 4, 4]
console.log("V5:", linkedListToArray(merged1_5)); // Note: This is NOT a correct merge.
console.log("\n");

// Test Case 2: One list is empty
console.log("Test Case 2: One List Empty");
let merged2_1 = mergeTwoListsV1(createLinkedList([1, 2, 4]), createLinkedList([]));
let merged2_2 = mergeTwoListsV2(createLinkedList([1, 2, 4]), createLinkedList([]));
let merged2_3 = mergeTwoListsV3(createLinkedList([1, 2, 4]), createLinkedList([]));
let merged2_4 = mergeTwoListsV4(createLinkedList([1, 2, 4]), createLinkedList([]));
let merged2_5 = mergeTwoListsV5(createLinkedList([1, 2, 4]), createLinkedList([]));
console.log("V1:", linkedListToArray(merged2_1)); // Expected: [1, 2, 4]
console.log("V2:", linkedListToArray(merged2_2)); // Expected: [1, 2, 4]
console.log("V3:", linkedListToArray(merged2_3)); // Expected: [1, 2, 4]
console.log("V4:", linkedListToArray(merged2_4)); // Expected: [1, 2, 4]
console.log("V5:", linkedListToArray(merged2_5));
console.log("\n");

// Test Case 3: Both lists are empty
console.log("Test Case 3: Both Lists Empty");
let merged3_1 = mergeTwoListsV1(createLinkedList([]), createLinkedList([]));
let merged3_2 = mergeTwoListsV2(createLinkedList([]), createLinkedList([]));
let merged3_3 = mergeTwoListsV3(createLinkedList([]), createLinkedList([]));
let merged3_4 = mergeTwoListsV4(createLinkedList([]), createLinkedList([]));
let merged3_5 = mergeTwoListsV5(createLinkedList([]), createLinkedList([]));
console.log("V1:", linkedListToArray(merged3_1)); // Expected: []
console.log("V2:", linkedListToArray(merged3_2)); // Expected: []
console.log("V3:", linkedListToArray(merged3_3)); // Expected: []
console.log("V4:", linkedListToArray(merged3_4)); // Expected: []
console.log("V5:", linkedListToArray(merged3_5));
console.log("\n");

// Test Case 4: One element lists
console.log("Test Case 4: One Element Lists");
let merged4_1 = mergeTwoListsV1(createLinkedList([5]), createLinkedList([1]));
let merged4_2 = mergeTwoListsV2(createLinkedList([5]), createLinkedList([1]));
let merged4_3 = mergeTwoListsV3(createLinkedList([5]), createLinkedList([1]));
let merged4_4 = mergeTwoListsV4(createLinkedList([5]), createLinkedList([1]));
let merged4_5 = mergeTwoListsV5(createLinkedList([5]), createLinkedList([1]));
console.log("V1:", linkedListToArray(merged4_1)); // Expected: [1, 5]
console.log("V2:", linkedListToArray(merged4_2)); // Expected: [1, 5]
console.log("V3:", linkedListToArray(merged4_3)); // Expected: [1, 5]
console.log("V4:", linkedListToArray(merged4_4)); // Expected: [1, 5]
console.log("V5:", linkedListToArray(merged4_5));
console.log("\n");

// Test Case 5: Unequal length lists
console.log("Test Case 5: Unequal Length Lists");
let merged5_1 = mergeTwoListsV1(createLinkedList([1,2,3]), createLinkedList([4,5,6,7,8]));
let merged5_2 = mergeTwoListsV2(createLinkedList([1,2,3]), createLinkedList([4,5,6,7,8]));
let merged5_3 = mergeTwoListsV3(createLinkedList([1,2,3]), createLinkedList([4,5,6,7,8]));
let merged5_4 = mergeTwoListsV4(createLinkedList([1,2,3]), createLinkedList([4,5,6,7,8]));
let merged5_5 = mergeTwoListsV5(createLinkedList([1,2,3]), createLinkedList([4,5,6,7,8]));
console.log("V1:", linkedListToArray(merged5_1));
console.log("V2:", linkedListToArray(merged5_2));
console.log("V3:", linkedListToArray(merged5_3));
console.log("V4:", linkedListToArray(merged5_4));
console.log("V5:", linkedListToArray(merged5_5));
console.log("\n");

// Test case 6: one list is null
console.log("Test Case 6: one list is null");
const merged6_1 = mergeTwoListsV1(list5, null);
const merged6_2 = mergeTwoListsV2(list5, null);
const merged6_3 = mergeTwoListsV3(list5, null);
const merged6_4 = mergeTwoListsV4(list5, null);
const merged6_5 = mergeTwoListsV5(list5, null);
console.log("V1:", linkedListToArray(merged6_1));
console.log("V2:", linkedListToArray(merged6_2));
console.log("V3:", linkedListToArray(merged6_3));
console.log("V4:", linkedListToArray(merged6_4));
console.log("V5:", linkedListToArray(merged6_5));
console.log("\n");
