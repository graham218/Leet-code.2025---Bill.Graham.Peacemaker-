// Definition of a linked list node (needed for all solutions)
class ListNode {
  constructor(val) {
    this.val = val;
    this.next = null;
  }
}

// Helper function to create a linked list with an optional cycle
function createLinkedList(values, cyclePos = -1) {
  const head = new ListNode(values[0]);
  let current = head;
  let cycleNode = null;

  for (let i = 1; i < values.length; i++) {
    current.next = new ListNode(values[i]);
    current = current.next;
    if (i === cyclePos) {
      cycleNode = current;
    }
  }

  if (cyclePos !== -1) {
    current.next = cycleNode; // Create the cycle
  }
  return head;
}

// Helper function to visualize the linked list (with cycle or without)
function visualizeLinkedList(head, message = "") {
    let current = head;
    let nodes = [];
    let visited = new Set();
    let cycleStart = null;
    let i = 0;

    while (current && !visited.has(current) && i < 20) { // Limit to 20 to avoid infinite loops in console if cycle is present
        nodes.push(current.val);
        visited.add(current);
        current = current.next;
        i++;
        if (visited.has(current)) {
            cycleStart = current.val;
            break;
        }
    }
    let resultString = "";
    if (cycleStart)
        resultString = `${message} List: ${nodes.join(" -> ")} -> ${cycleStart} (Cycle Detected!)`;
    else
        resultString = `${message} List: ${nodes.join(" -> ")} (No Cycle)`;

    console.log(resultString);
}

// 1. Floyd's Cycle Detection (Fast and Slow Pointer)
function hasCycleFloyd(head) {
  if (!head || !head.next) {
    return false;
  }

  let slow = head;
  let fast = head.next;

  while (slow && fast && fast.next) {
    if (slow === fast) {
      return true;
    }
    slow = slow.next;
    fast = fast.next.next;
  }
  return false;
}

// 2. Using a Set to store visited nodes
function hasCycleSet(head) {
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

// 3.  Modifying the linked list (adding a property - not recommended for real-world use, as it changes the original list)
function hasCycleModify(head) {
  let current = head;
  while (current) {
    if (current.visited) {
      return true;
    }
    current.visited = true;
    current = current.next;
  }
  return false;
}

// 4. Using an array to store visited nodes (less efficient than Set)
function hasCycleArray(head) {
    const visitedNodes = [];
    let current = head;

    while (current) {
        if (visitedNodes.includes(current)) {
            return true;
        }
        visitedNodes.push(current);
        current = current.next;
    }
    return false;
}

// 5. Recursive approach (not ideal for long lists due to stack overflow potential)
function hasCycleRecursive(head, visited = new Set()) {
  if (!head) {
    return false;
  }

  if (visited.has(head)) {
    return true;
  }

  visited.add(head);
  return hasCycleRecursive(head.next, visited);
}



// Test cases
const list1 = createLinkedList([1, 2, 3, 4, 5]);
const list2 = createLinkedList([1, 2, 3, 4, 5], 2); // Cycle starts at node with value 3
const list3 = createLinkedList([1]);
const list4 = createLinkedList([1,2]);
const list5 = createLinkedList([1,2], 0);

visualizeLinkedList(list1, "List 1");
visualizeLinkedList(list2, "List 2");
visualizeLinkedList(list3, "List 3");
visualizeLinkedList(list4, "List 4");
visualizeLinkedList(list5, "List 5");


console.log("--- Floyd's Cycle Detection ---");
console.log("List 1 has cycle:", hasCycleFloyd(list1)); // false
console.log("List 2 has cycle:", hasCycleFloyd(list2)); // true
console.log("List 3 has cycle:", hasCycleFloyd(list3)); // false
console.log("List 4 has cycle:", hasCycleFloyd(list4)); // false
console.log("List 5 has cycle:", hasCycleFloyd(list5)); // true


console.log("--- Set Approach ---");
console.log("List 1 has cycle:", hasCycleSet(list1)); // false
console.log("List 2 has cycle:", hasCycleSet(list2)); // true
console.log("List 3 has cycle:", hasCycleSet(list3)); // false
console.log("List 4 has cycle:", hasCycleSet(list4)); // false
console.log("List 5 has cycle:", hasCycleSet(list5)); // true

console.log("--- Modification Approach ---");
console.log("List 1 has cycle:", hasCycleModify(list1)); // false
console.log("List 2 has cycle:", hasCycleModify(list2)); // true - WARNING: Modifies List
console.log("List 3 has cycle:", hasCycleModify(list3)); // false
console.log("List 4 has cycle:", hasCycleModify(list4)); // false
console.log("List 5 has cycle:", hasCycleModify(list5)); // true - WARNING: Modifies List

console.log("--- Array Approach ---");
console.log("List 1 has cycle:", hasCycleArray(list1)); // false
console.log("List 2 has cycle:", hasCycleArray(list2)); // true
console.log("List 3 has cycle:", hasCycleArray(list3)); // false
console.log("List 4 has cycle:", hasCycleArray(list4)); // false
console.log("List 5 has cycle:", hasCycleArray(list5)); // true

console.log("--- Recursive Approach ---");
console.log("List 1 has cycle:", hasCycleRecursive(list1)); // false
console.log("List 2 has cycle:", hasCycleRecursive(list2)); // true
console.log("List 3 has cycle:", hasCycleRecursive(list3)); // false
console.log("List 4 has cycle:", hasCycleRecursive(list4)); // false
console.log("List 5 has cycle:", hasCycleRecursive(list5)); // true
