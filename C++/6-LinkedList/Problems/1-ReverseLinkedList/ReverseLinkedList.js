// Definition of a ListNode (you can copy this into your environment)
function ListNode(val, next) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
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

// Example linked list for testing
const arrayForList = [1, 2, 3, 4, 5];
const head = createLinkedList(arrayForList);

console.log("Original Linked List:");
printLinkedList(head); // Output: 1 -> 2 -> 3 -> 4 -> 5

// 1. Iterative Approach
function reverseListIterative(head) {
    let prev = null;
    let current = head;
    let next = null;

    while (current) {
        next = current.next;  // Store the next node
        current.next = prev;  // Reverse the link
        prev = current;       // Move prev to current node
        current = next;       // Move current to next node
    }
    return prev; // prev is the new head
}

console.log("\nIterative Approach:");
const reversedHeadIterative = reverseListIterative(createLinkedList(arrayForList)); // Create a *new* list to avoid modifying the original
printLinkedList(reversedHeadIterative); // Output: 5 -> 4 -> 3 -> 2 -> 1


// 2. Recursive Approach
function reverseListRecursive(head) {
    if (!head || !head.next) {
        return head;
    }

    let newHead = reverseListRecursive(head.next);
    head.next.next = head;
    head.next = null;
    return newHead;
}

console.log("\nRecursive Approach:");
const reversedHeadRecursive = reverseListRecursive(createLinkedList(arrayForList));
printLinkedList(reversedHeadRecursive); // Output: 5 -> 4 -> 3 -> 2 -> 1


// 3. Using an Array (Stack)
function reverseListArray(head) {
    if (!head) return null;
    const stack = [];
    let current = head;
    while (current) {
        stack.push(current);
        current = current.next;
    }

    const newHead = stack.pop();
    let tail = newHead;

    while (stack.length > 0) {
        let node = stack.pop();
        node.next = null; // Important: Break original link
        tail.next = node;
        tail = node;
    }
    return newHead;
}

console.log("\nUsing an Array (Stack):");
const reversedHeadArray = reverseListArray(createLinkedList(arrayForList));
printLinkedList(reversedHeadArray); // Output: 5 -> 4 -> 3 -> 2 -> 1


// 4. In-place reversal (optimized iterative) - same as iterative, but more explicit
function reverseListInPlace(head) {
    let prev = null;
    let curr = head;

    while (curr) {
        const next = curr.next;
        curr.next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

console.log("\nIn-place Reversal (Optimized Iterative):");
const reversedHeadInPlace = reverseListInPlace(createLinkedList(arrayForList));
printLinkedList(reversedHeadInPlace);


// 5. Using ES6 Spread and Reverse (simplest, but not ideal for very large lists due to array conversion)
function reverseListES6(head) {
  if (!head) return null;
  const values = [];
  let current = head;
  while (current) {
    values.push(current.val);
    current = current.next;
  }
  values.reverse(); // Reverse the array of values

  // Reconstruct the linked list
  let newHead = new ListNode(values[0]);
  let tail = newHead;
  for (let i = 1; i < values.length; i++) {
    tail.next = new ListNode(values[i]);
    tail = tail.next;
  }
  return newHead;
}

console.log("\nUsing ES6 Spread and Reverse:");
const reversedHeadES6 = reverseListES6(createLinkedList(arrayForList));
printLinkedList(reversedHeadES6);
