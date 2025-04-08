// Define the ListNode class
class ListNode {
  constructor(val) {
    this.val = val;
    this.next = null;
  }
}

// Function to create a linked list from an array
function createLinkedList(arr) {
  if (!arr || arr.length === 0) {
    return null;
  }
  const head = new ListNode(arr[0]);
  let current = head;
  for (let i = 1; i < arr.length; i++) {
    current.next = new ListNode(arr[i]);
    current = current.next;
  }
  return head;
}

// Function to create a linked list with a cycle for testing purposes
function createLinkedListWithCycle(arr, cyclePos) {
    const head = createLinkedList(arr);
    if (cyclePos === -1 || !head) {
        return head;
    }

    let cycleStart = head;
    for (let i = 0; i < cyclePos; i++) {
        if (!cycleStart) return head; // Handle invalid cyclePos
        cycleStart = cycleStart.next;
    }

    let tail = head;
    while (tail && tail.next) {
        tail = tail.next;
    }
    if(tail) {
      tail.next = cycleStart;
    }
    return head;
}

// Function to print the linked list
function printLinkedList(head) {
  let current = head;
  let str = "";
  let count = 0; // Add a counter to prevent infinite loops in case of cycles
  while (current && count < 100) { // Limit the loop to 100 to handle cycles
    str += current.val + " -> ";
    current = current.next;
    count++;
  }
  str += "null";
  console.log(str);
}

// Approach 1: Detect Cycle - Using a Set
function detectCycleUsingSet(head) {
  if (!head || !head.next) {
    return false;
  }
  const visited = new Set();
  let current = head;
  while (current) {
    if (visited.has(current)) {
      return true;
    }
    visited.add(current);
    current = current.next;
  }
  return false;
}

// Approach 2: Detect Cycle - Fast and Slow Pointers
function detectCycleFastSlow(head) {
  if (!head || !head.next) {
    return false;
  }
  let slow = head;
  let fast = head;
  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
    if (slow === fast) {
      return true;
    }
  }
  return false;
}

// Approach 3: Find Middle Node - Fast and Slow Pointers
function findMiddleNode(head) {
  if (!head) {
    return null;
  }
  let slow = head;
  let fast = head;
  while (fast && fast.next) {
    slow = slow.next;
    fast = fast.next.next;
  }
  return slow;
}

// Approach 4: Find the Kth Node from the End
function findKthNodeFromEnd(head, k) {
  if (!head || k <= 0) {
    return null;
  }
  let slow = head;
  let fast = head;
  // Move fast pointer k nodes ahead
  for (let i = 0; i < k; i++) {
    if (!fast) {
      return null; // k is larger than the length of the list
    }
    fast = fast.next;
  }
  // Move both pointers until fast reaches the end
  while (fast) {
    slow = slow.next;
    fast = fast.next;
  }
  return slow;
}

// Approach 5: Find the starting node of the cycle
function findCycleStart(head) {
    if (!head || !head.next) {
        return null;
    }
    let slow = head;
    let fast = head;

    // Detect the cycle
    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            break; // Cycle detected
        }
    }

    // If there is no cycle
    if (slow !== fast) {
        return null;
    }

    // Find the start of the cycle
    slow = head;
    while (slow !== fast) {
        slow = slow.next;
        fast = fast.next;
    }
    return slow;
}

// Test cases
const arr1 = [1, 2, 3, 4, 5];
const list1 = createLinkedList(arr1);
console.log("Linked List 1:");
printLinkedList(list1);

const arr2 = [1, 2, 3, 4, 5, 6];
const list2 = createLinkedList(arr2);
console.log("Linked List 2:");
printLinkedList(list2);

const arr3 = [1, 2, 3, 4, 5];
const list3WithCycle = createLinkedListWithCycle(arr3, 2); // Cycle starts at node with value 3
console.log("Linked List 3 (with cycle):");
printLinkedList(list3WithCycle); // Print with limit to avoid infinite loop

console.log("\n--- Test Cases ---");
console.log("Test Case 1: No Cycle");
console.log("Input List:");
printLinkedList(createLinkedList([1,2,3,4,5]));
console.log("Approach 1 (Set): Cycle Detection -", detectCycleUsingSet(list1));
console.log("Approach 2 (Fast/Slow): Cycle Detection -", detectCycleFastSlow(list1));
console.log("Approach 3 (Fast/Slow): Middle Node -", findMiddleNode(list1) ? findMiddleNode(list1).val : null);
console.log("Approach 4 (Fast/Slow): 2nd to last Node -", findKthNodeFromEnd(list1, 2) ? findKthNodeFromEnd(list1, 2).val : null);
console.log("Approach 5 (Fast/Slow): Cycle Start Node -", findCycleStart(list1));


console.log("\nTest Case 2: No Cycle");
console.log("Input List:");
printLinkedList(createLinkedList([10, 20, 30, 40, 50, 60]));
console.log("Approach 1 (Set): Cycle Detection -", detectCycleUsingSet(list2));
console.log("Approach 2 (Fast/Slow): Cycle Detection -", detectCycleFastSlow(list2));
console.log("Approach 3 (Fast/Slow): Middle Node -", findMiddleNode(list2) ? findMiddleNode(list2).val : null);
console.log("Approach 4 (Fast/Slow): 3rd to last Node -", findKthNodeFromEnd(list2, 3) ? findKthNodeFromEnd(list2, 3).val : null);
console.log("Approach 5 (Fast/Slow): Cycle Start Node -", findCycleStart(list2));

console.log("\nTest Case 3: Cycle Present");
console.log("Input List:");
printLinkedList(list3WithCycle);
console.log("Approach 1 (Set): Cycle Detection -", detectCycleUsingSet(list3WithCycle));
console.log("Approach 2 (Fast/Slow): Cycle Detection -", detectCycleFastSlow(list3WithCycle));
console.log("Approach 3 (Fast/Slow): Middle Node -", findMiddleNode(list3WithCycle) ? findMiddleNode(list3WithCycle).val: null); // This will likely cause an infinite loop or error if not handled carefully.
console.log("Approach 4 (Fast/Slow): Kth Node from End -", findKthNodeFromEnd(list3WithCycle, 2) ? findKthNodeFromEnd(list3WithCycle, 2).val : null); //This may also cause an issue
console.log("Approach 5 (Fast/Slow): Cycle Start Node -", findCycleStart(list3WithCycle) ? findCycleStart(list3WithCycle).val : null);
