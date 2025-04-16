// Definition of a ListNode (same as before for consistency)
class ListNode {
  constructor(val) {
    this.val = val;
    this.next = null;
  }
}

// Helper function to create a linked list from an array
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

// Helper function to print the linked list
function printLinkedList(head) {
  let current = head;
  let result = [];
  while (current) {
    result.push(current.val);
    current = current.next;
  }
  console.log(result.join(" -> "));
}

/****************************************************************************************
 * 1. Detect a Cycle (Real-world application: Memory Leak Detection)
 *
 * Fast and slow pointers are used to detect if a linked list has a cycle.
 * In memory management, this can detect circular references that prevent garbage collection,
 * leading to memory leaks.
 ****************************************************************************************/
function hasCycle(head) {
  if (!head || !head.next) return false;

  let slow = head;
  let fast = head.next;

  while (fast && fast.next) {
    if (slow === fast) return true; // Cycle detected
    slow = slow.next;
    fast = fast.next.next;
  }
  return false; // No cycle
}

// Example Usage (Memory Leak Detection)
let listWithCycle = createLinkedList([1, 2, 3, 4, 5]);
// Create a cycle for testing
listWithCycle.next.next.next.next.next = listWithCycle.next; // Connect 5 to 2

let listWithoutCycle = createLinkedList([1, 2, 3, 4, 5]);

console.log("1. Detect Cycle (Memory Leak Detection):");
console.log("List with cycle:", hasCycle(listWithCycle)); // true
console.log("List without cycle:", hasCycle(listWithoutCycle)); // false

/****************************************************************************************
 * 2. Find the Middle Node (Real-world application: Efficient Data Retrieval)
 *
 * Finding the middle node is useful in applications where data needs to be accessed
 * or processed in the middle of a list, such as in database systems or streaming algorithms.
 ****************************************************************************************/
function findMiddle(head) {
  if (!head) return null;

  let slow = head;
  let fast = head;

  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
  }
  return slow;
}

// Example Usage (Efficient Data Retrieval)
let list1 = createLinkedList([1, 2, 3, 4, 5]);
let list2 = createLinkedList([1, 2, 3, 4, 5, 6]);

console.log("\n2. Find Middle Node (Efficient Data Retrieval):");
console.log("Middle of list1:", findMiddle(list1).val); // 3
console.log("Middle of list2:", findMiddle(list2).val); // 4

/****************************************************************************************
 * 3. Find the Start of a Cycle (Real-world application: Data Corruption Detection)
 *
 * In data storage systems, finding the start of a cycle can help locate the point
 * where data corruption occurred, allowing for targeted repair.
 ****************************************************************************************/
function findCycleStart(head) {
  if (!head || !head.next) return null;

  let slow = head;
  let fast = head;

  // Detect the cycle
  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
    if (slow === fast) break; // Cycle detected
  }

  // If no cycle, return null
  if (!fast || !fast.next) return null;

  // Find the start of the cycle
  slow = head;
  while (slow !== fast) {
    slow = slow.next;
    fast = fast.next;
  }
  return slow;
}

// Example Usage (Data Corruption Detection)
let listWithCycleStart = createLinkedList([1, 2, 3, 4, 5]);
listWithCycleStart.next.next.next.next.next = listWithCycleStart.next.next; // Connect 5 to 3

console.log("\n3. Find Cycle Start (Data Corruption Detection):");
let cycleStartNode = findCycleStart(listWithCycleStart);
console.log("Cycle start:", cycleStartNode ? cycleStartNode.val : "No cycle"); // 3

/****************************************************************************************
 * 4. Check if a Linked List is a Palindrome (Real-world application: Data Validation)
 *
 * Useful in data validation to ensure that data is symmetrical, like in genetic sequence
 * analysis or verifying transmitted data integrity.
 ****************************************************************************************/
function isPalindrome(head) {
  if (!head || !head.next) return true; // Empty or single-node list

  let slow = head;
  let fast = head;

  // Find the middle
  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
  }

  // Reverse the second half
  let prev = null;
  let current = slow;
  let next;
  while (current) {
    next = current.next;
    current.next = prev;
    prev = current;
    current = next;
  }

  // Compare the first and reversed second halves
  let firstHalf = head;
  let secondHalf = prev; // prev is now the head of the reversed second half
  while (secondHalf) {
    if (firstHalf.val !== secondHalf.val) return false;
    firstHalf = firstHalf.next;
    secondHalf = secondHalf.next;
  }
  return true;
}

// Example Usage (Data Validation)
let palindromeList1 = createLinkedList([1, 2, 3, 2, 1]);
let palindromeList2 = createLinkedList([1, 2, 3, 4, 5]);
let palindromeList3 = createLinkedList([1, 2, 2, 1]);

console.log("\n4. Check Palindrome (Data Validation):");
console.log("List 1 is palindrome:", isPalindrome(palindromeList1)); // true
console.log("List 2 is palindrome:", isPalindrome(palindromeList2)); // false
console.log("List 3 is palindrome:", isPalindrome(palindromeList3)); // true

/****************************************************************************************
 * 5. Reorder List (Real-world application: Optimizing Data Access Order)
 *
 * Reordering a list can optimize data access patterns, such as in UI rendering
 * or network packet processing, by interleaving elements for faster retrieval.
 ****************************************************************************************/
function reorderList(head) {
  if (!head || !head.next || !head.next.next) return; // Nothing to reorder

  let slow = head;
  let fast = head;

  // 1. Find the middle
  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
  }

  // 2. Reverse the second half
  let prev = null;
  let current = slow.next;
  slow.next = null; // Disconnect the first half
  let next;
  while (current) {
    next = current.next;
    current.next = prev;
    prev = current;
    current = next;
  }

  // 3. Merge the two halves
  let firstHalf = head;
  let secondHalf = prev; // prev is the head of the reversed second half

  while (secondHalf) {
    let temp1 = firstHalf.next;
    let temp2 = secondHalf.next;

    firstHalf.next = secondHalf;
    secondHalf.next = temp1;

    firstHalf = temp1;
    secondHalf = temp2;
  }
}

// Example Usage (Optimizing Data Access Order)
let reorderListExample = createLinkedList([1, 2, 3, 4, 5]);
reorderList(reorderListExample);
console.log("\n5. Reorder List (Optimizing Data Access Order):");
printLinkedList(reorderListExample); // Output: 1 -> 5 -> 2 -> 4 -> 3
