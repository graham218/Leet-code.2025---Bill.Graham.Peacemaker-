// Definition of a ListNode (same as before for consistency)
function ListNode(val, next) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
}

/**
 * Merge two sorted linked lists.
 *
 * Input: l1 = [1,2,4], l2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 */

// Approach 1: Iterative with Dummy Node
function mergeTwoListsIterative(l1, l2) {
    let dummy = new ListNode(-1); // Dummy node to simplify head handling
    let tail = dummy; // Tail pointer to build the merged list

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

    // Append the remaining list (if any)
    tail.next = l1 || l2;

    return dummy.next; // Return the merged list starting from the actual head
}

// Approach 2: Recursive
function mergeTwoListsRecursive(l1, l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1.val <= l2.val) {
        l1.next = mergeTwoListsRecursive(l1.next, l2);
        return l1;
    } else {
        l2.next = mergeTwoListsRecursive(l1, l2.next);
        return l2;
    }
}

// Approach 3: Iterative in-place (modifying l1) - assumes you can modify input
function mergeTwoListsInPlace(l1, l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    // Ensure l1 starts with the smaller value
    if (l2.val < l1.val) {
        [l1, l2] = [l2, l1]; // Swap l1 and l2
    }
    let head = l1; // Keep track of the head of the merged list

    while (l1 && l2) {
        let prev = null;
        // Find the point to insert l2
        while (l1 && l1.val <= l2.val) {
            prev = l1;
            l1 = l1.next;
        }
        // Insert l2 into l1
        prev.next = l2;
        // Move l2's head
        let temp = l1;
        l1 = l2;
        l2 = temp;
    }
    return head;
}

// Approach 4: Using an Array and Sorting (Less efficient for LLs, good for understanding)
function mergeTwoListsArraySort(l1, l2) {
    let arr = [];
    while (l1) {
        arr.push(l1.val);
        l1 = l1.next;
    }
    while (l2) {
        arr.push(l2.val);
        l2 = l2.next;
    }
    arr.sort((a, b) => a - b); // Sort the array

    // Build the linked list from the sorted array
    let dummy = new ListNode(-1);
    let tail = dummy;
    for (let val of arr) {
        tail.next = new ListNode(val);
        tail = tail.next;
    }
    return dummy.next;
}

// Approach 5:  ES6 Spread and Sort (Concise, but creates an intermediate array)
function mergeTwoListsSpread(l1, l2) {
  const values = [];
  let current1 = l1;
  let current2 = l2;

  while (current1) {
    values.push(current1.val);
    current1 = current1.next;
  }
  while (current2) {
    values.push(current2.val);
    current2 = current2.next;
  }
  const sortedValues = values.sort((a, b) => a - b);

  if (!sortedValues.length) {
    return null;
  }

  let head = new ListNode(sortedValues[0]);
  let current = head;

  for (let i = 1; i < sortedValues.length; i++) {
    current.next = new ListNode(sortedValues[i]);
    current = current.next;
  }
  return head;
}



// Helper function to convert a linked list to an array for easy printing
function linkedListToArray(head) {
    let arr = [];
    let current = head;
    while (current) {
        arr.push(current.val);
        current = current.next;
    }
    return arr;
}

// Create sample linked lists for testing
let l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
let l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
let l3 = new ListNode(5);
let l4 = new ListNode(5);

// Test and print the results
console.log("Input Lists:");
console.log("l1:", linkedListToArray(l1));
console.log("l2:", linkedListToArray(l2));
console.log("l3:", linkedListToArray(l3));
console.log("l4:", linkedListToArray(l4));


console.log("\nApproach 1: Iterative with Dummy Node");
let mergedList1 = mergeTwoListsIterative(l1, l2);
console.log("Merged List:", linkedListToArray(mergedList1));

l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
console.log("\nApproach 2: Recursive");
let mergedList2 = mergeTwoListsRecursive(l1, l2);
console.log("Merged List:", linkedListToArray(mergedList2));

l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
console.log("\nApproach 3: Iterative In-Place");
let mergedList3 = mergeTwoListsInPlace(l1, l2);
console.log("Merged List:", linkedListToArray(mergedList3));

l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
console.log("\nApproach 4: Using Array and Sort");
let mergedList4 = mergeTwoListsArraySort(l1, l2);
console.log("Merged List:", linkedListToArray(mergedList4));

l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
console.log("\nApproach 5: Using Spread and Sort");
let mergedList5 = mergeTwoListsSpread(l1, l2);
console.log("Merged List:", linkedListToArray(mergedList5));

// Test case with one empty list
l1 = null;
l2 = new ListNode(0);
console.log("\nTest Case: One Empty List");
console.log("Merged List (Iterative):", linkedListToArray(mergeTwoListsIterative(l1, l2)));

// Test case with both empty lists
l1 = null;
l2 = null;
console.log("\nTest Case: Both Empty Lists");
console.log("Merged List (Iterative):", linkedListToArray(mergeTwoListsIterative(l1, l2)));

// Test case with single node lists
l1 = new ListNode(1);
l2 = new ListNode(2);
console.log("\nTest Case: Single Node Lists");
console.log("Merged List (Iterative):", linkedListToArray(mergeTwoListsIterative(l1, l2)));
