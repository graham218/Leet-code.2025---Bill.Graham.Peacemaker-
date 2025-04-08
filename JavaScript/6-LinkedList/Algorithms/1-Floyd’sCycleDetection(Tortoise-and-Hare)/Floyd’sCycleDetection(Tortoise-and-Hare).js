// Helper function to create a linked list node
function ListNode(val) {
  this.val = val;
  this.next = null;
}

// Helper function to create a linked list from an array
function createLinkedList(arr, pos) {
  if (!arr || arr.length === 0) {
    return null;
  }

  const head = new ListNode(arr[0]);
  let current = head;
  let cycleStart = null;

  for (let i = 1; i < arr.length; i++) {
    current.next = new ListNode(arr[i]);
    current = current.next;
    if (pos !== undefined && pos === i) {
      cycleStart = current;
    }
  }

  if (pos !== undefined && pos >= 0) {
    current.next = cycleStart;
  }

  return head;
}

// 1. Floyd's Cycle Detection (Tortoise and Hare)
function hasCycleFloyd(head) {
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

// 2. Using a Set to store visited nodes
function hasCycleSet(head) {
  if (!head) {
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

// 3.  Modifying the linked list (adding a property) - Destructive
function hasCycleModify(head) {
    if (!head) return false;
    let current = head;
    while (current) {
        if (current.visited) return true;
        current.visited = true;
        current = current.next;
    }
    return false;
}

// 4. Using an array to store visited nodes
function hasCycleArray(head) {
  if (!head) {
    return false;
  }
  const visited = [];
  let current = head;
  while (current) {
    if (visited.includes(current)) {
      return true;
    }
    visited.push(current);
    current = current.next;
  }
  return false;
}

// 5.  Using a Map to store visited nodes and their indices
function hasCycleMap(head) {
    if (!head) return false;

    const visitedMap = new Map();
    let current = head;
    let index = 0;

    while (current) {
        if (visitedMap.has(current)) {
            return true;
        }
        visitedMap.set(current, index);
        current = current.next;
        index++;
    }
    return false;
}

// Test cases
const testCases = [
  { arr: [1, 2, 3, 4, 5], pos: -1 }, // No cycle
  { arr: [1, 2, 3, 4, 5], pos: 1 },  // Cycle at node 2
  { arr: [1, 2, 3, 4, 5], pos: 4 }, // Cycle at node 5
  { arr: [1], pos: -1 },             // Single node, no cycle
  { arr: [1, 2], pos: 0 },           // Cycle at the first node
  { arr: [], pos: -1}             // Empty List
];

testCases.forEach((testCase, index) => {
  const list = createLinkedList(testCase.arr, testCase.pos);
  console.log(`\nTest Case ${index + 1}: Array = [${testCase.arr}], Cycle at position = ${testCase.pos}`);

  // Floyd's
  console.log("Floyd's Cycle Detection:", hasCycleFloyd(list));

  // Set
  const listSet = createLinkedList(testCase.arr, testCase.pos); // Create a new list for each test
  console.log("Using Set:", hasCycleSet(listSet));

  // Modify
    const listModify = createLinkedList(testCase.arr, testCase.pos);
    console.log("Modifying List:", hasCycleModify(listModify));

  // Array
  const listArray = createLinkedList(testCase.arr, testCase.pos);
  console.log("Using Array:", hasCycleArray(listArray));

  // Map
  const listMap = createLinkedList(testCase.arr, testCase.pos);
  console.log("Using Map:", hasCycleMap(listMap));
});
