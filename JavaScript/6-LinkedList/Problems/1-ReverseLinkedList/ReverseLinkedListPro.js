// Definition of a ListNode (used for all approaches)
class ListNode {
  constructor(val, next = null) {
    this.val = val;
    this.next = next;
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

// Helper function to convert a linked list to an array for easy printing
function linkedListToArray(head) {
  const result = [];
  let current = head;
  while (current) {
    result.push(current.val);
    current = current.next;
  }
  return result;
}

// --- Approach 1: Iterative Approach ---
// This is the most common and efficient way to reverse a linked list.
//
// Real-world application:
//   - Reversing the order of items in a playlist (e.g., reversing a queue).
//   - Implementing undo/redo functionality in a text editor.  The history can be stored as a linked list, and undo/redo involves reversing the list.
function reverseListIterative(head) {
  let prev = null;
  let current = head;
  let next = null;

  while (current) {
    next = current.next; // Store the next node
    current.next = prev; // Reverse the link
    prev = current;       // Move prev to current node
    current = next;       // Move current to the next node
  }
  return prev; // prev is the new head
}

// --- Approach 2: Recursive Approach ---
// Reverses the list using recursion.  While elegant, it can be less efficient
// for very long lists due to the call stack.
//
// Real-world application:
//   - Useful for reversing lists of moderate size where code clarity is prioritized.
//   - Can be adapted for tree traversals, which have similar recursive structures.
function reverseListRecursive(head) {
  if (!head || !head.next) {
    return head; // Base case: empty list or single node
  }

  const newHead = reverseListRecursive(head.next); // Recursively reverse the rest
  head.next.next = head; // Make the next node point back to the current
  head.next = null;       // Set the original next pointer to null
  return newHead;         // Return the new head from the recursion
}


// --- Approach 3: Using a Stack ---
// Uses a stack to store the nodes, then pops them off in reverse order.
//
// Real-world application:
//   - This is similar to how a browser's history works (though browsers may use a doubly linked list).
//   - Useful in situations where you need to reverse the order of elements in a sequence, and a stack is a natural data structure.
function reverseListStack(head) {
  if (!head) return null;

  const stack = [];
  let current = head;
  while (current) {
    stack.push(current); // Push each node onto the stack
    current = current.next;
  }

  const newHead = stack.pop(); // The last node becomes the new head
  let prev = newHead;

  while (stack.length > 0) {
    const node = stack.pop();
    prev.next = node;     // Connect the previous node to the current
    node.next = null;    // Ensure the current node's next is null
    prev = node;
  }
  return newHead;
}

// --- Approach 4: In-place Reversal (Slightly Optimized Iterative) ---
// This is a variation of the iterative approach, but it's often written more concisely.
//
// Real-world application:
//   - This optimized iterative approach is often preferred in performance-critical applications.
function reverseListInPlace(head) {
  let prev = null;
  let current = head;

  while (current) {
    [current.next, prev, current] = [prev, current, current.next];
  }
  return prev;
}

// --- Approach 5: Using Array.reverse() (Not ideal for true linked lists) ---
// Converts the linked list to an array, reverses the array, and then
// creates a new linked list.  This is NOT an in-place reversal and has
// the overhead of array conversion.  It's generally not recommended for
// true linked list manipulation in real-world scenarios, especially with very large lists.
//
// Real-world application:
//   -  This approach is more of an academic exercise.  In practice, if you're frequently converting between linked lists and arrays, you might reconsider your data structure choice.  However, it could be used in a very specific scenario where you need to reverse a small linked list *and* you already have efficient functions to convert between lists and arrays.  Performance would need to be carefully benchmarked.
function reverseListArray(head) {
  if (!head) return null;

  const arr = [];
  let current = head;
  while (current) {
    arr.push(current.val);
    current = current.next;
  }

  arr.reverse(); // Use the built-in array reverse
  return createLinkedList(arr); // Create a new linked list from the reversed array.
}



// --- Test Cases ---
const testCases = [
  [],
  [1],
  [1, 2, 3, 4, 5],
  [5, 4, 3, 2, 1],
  [1, 2, 2, 1], // Test case with duplicate values
];

console.log("--- Linked List Reversal ---");

testCases.forEach((arr, index) => {
  console.log(`\n--- Test Case ${index + 1}: [${arr}] ---`);
  const head = createLinkedList(arr);

  // Avoid modifying the original head, create copies for each test.
  let head1 = head ? { ...head } : null; // Create shallow copies, good enough for this
  let head2 = head ? { ...head } : null;
  let head3 = head ? { ...head } : null;
  let head4 = head ? { ...head } : null;
  let head5 = head ? { ...head } : null;


  // --- Approach 1: Iterative ---
  console.log("1. Iterative:");
  let reversed1 = reverseListIterative(head1);
  console.log("   Reversed List:", linkedListToArray(reversed1));

  // --- Approach 2: Recursive ---
  console.log("2. Recursive:");
  let reversed2 = reverseListRecursive(head2);
  console.log("   Reversed List:", linkedListToArray(reversed2));

  // --- Approach 3: Stack ---
  console.log("3. Stack:");
  let reversed3 = reverseListStack(head3);
  console.log("   Reversed List:", linkedListToArray(reversed3));

  // --- Approach 4: In-place (Optimized Iterative) ---
  console.log("4. In-place:");
  let reversed4 = reverseListInPlace(head4);
  console.log("   Reversed List:", linkedListToArray(reversed4));

  // --- Approach 5: Array.reverse() ---
  console.log("5. Array.reverse():");
  let reversed5 = reverseListArray(head5);
  console.log("   Reversed List:", linkedListToArray(reversed5));
});
