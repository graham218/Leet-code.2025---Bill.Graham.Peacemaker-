// Definition of a ListNode (you can assume this is given)
class ListNode {
  constructor(val) {
    this.val = val;
    this.next = null;
  }
}

// Helper function to create a linked list from an array
function createLinkedList(arr, pos = -1) {
  if (!arr || arr.length === 0) {
    return { head: null, tail: null };
  }

  const head = new ListNode(arr[0]);
  let current = head;
  let tail = head;
  let cycleStart = null;

  if (pos === 0) {
    cycleStart = head;
  }

  for (let i = 1; i < arr.length; i++) {
    const newNode = new ListNode(arr[i]);
    current.next = newNode;
    current = newNode;
    tail = newNode;
    if (i === pos) {
      cycleStart = newNode;
    }
  }

  if (cycleStart) {
    tail.next = cycleStart;
  }

  return { head, tail };
}

// Helper function to visualize linked list with cycle
function visualizeLinkedList(head, highlightCycle = false) {
  let current = head;
  let nodes = [];
  let visited = new Set();
  let cycleStartNode = null;

  while (current) {
    if (visited.has(current)) {
      cycleStartNode = current;
      break; // Break, but we still want to process the last node
    }
    nodes.push(current.val);
    visited.add(current);
    current = current.next;
  }

  let displayString = nodes.join(" -> ");
  if (cycleStartNode && highlightCycle) {
        let cycleStartIndex = nodes.indexOf(cycleStartNode.val);
        let cycleString = nodes.slice(cycleStartIndex).join(" -> ");
        displayString = displayString.substring(0, displayString.indexOf(cycleString[0])) + "[" + cycleString + "]";
  } else if (cycleStartNode) {
        let cycleStartIndex = nodes.indexOf(cycleStartNode.val);
        let cycleString = nodes.slice(cycleStartIndex).join(" -> ");
        displayString = displayString.substring(0, displayString.indexOf(cycleString[0])) + "[" + cycleString + "...(cycle)]";
  }


  return displayString;
}

// 1. Floyd's Cycle Detection (Fast and Slow Pointers) - Most common and efficient
function hasCycleFloyd(head) {
  if (!head || !head.next) {
    return false;
  }
  let slow = head;
  let fast = head.next;
  while (slow !== fast) {
    if (!fast || !fast.next) {
      return false;
    }
    slow = slow.next;
    fast = fast.next.next;
  }
  return true;
}

// 2. Hashing (Using a Set) - Simple, but uses extra space
function hasCycleHashing(head) {
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

// 3. Modifying the List (Not recommended for real-world, alters original list)
function hasCycleModify(head) {
  let current = head;
  while (current) {
    if (current.visited) {
      return true;
    }
    current.visited = true; // Add a visited property
    current = current.next;
  }
  return false;
}

// 4. Using an Array to Store Nodes - Another approach using extra space
function hasCycleArray(head) {
  const nodes = [];
  let current = head;
  while (current) {
    if (nodes.includes(current)) {
      return true;
    }
    nodes.push(current);
    current = current.next;
  }
  return false;
}

// 5. Recursive Approach (Not ideal for very long lists due to call stack)
function hasCycleRecursive(node, visited = new Set()) {
  if (!node) {
    return false;
  }
  if (visited.has(node)) {
    return true;
  }
  visited.add(node);
  return hasCycleRecursive(node.next, visited);
}

// Test cases
function runTestCases() {
  let list1 = createLinkedList([1, 2, 3, 4, 5]);
  let list2 = createLinkedList([1, 2, 3, 4, 5], 2); // Cycle starts at 3
  let list3 = createLinkedList([1, 2]);
  let list4 = createLinkedList([1, 2], 0); // Cycle starts at 1
  let list5 = createLinkedList([1]);
  let list6 = createLinkedList([]);
  let list7 = createLinkedList([1,2,3,4,5,6,7,8,9,10], 5); // Cycle at 6th element

  console.log("Test Case 1: No cycle");
  console.log("Input: ", visualizeLinkedList(list1.head));
  console.log("Floyd's:", hasCycleFloyd(list1.head));
  console.log("Hashing:", hasCycleHashing(list1.head));
  console.log("Modifying:", hasCycleModify(list1.head));
  console.log("Array:", hasCycleArray(list1.head));
  console.log("Recursive:", hasCycleRecursive(list1.head));
  console.log("------------------");

  // Reset visited property for modify approach
  list1 = createLinkedList([1, 2, 3, 4, 5]);

  console.log("Test Case 2: Cycle in the middle");
  console.log("Input: ", visualizeLinkedList(list2.head, true));
  console.log("Floyd's:", hasCycleFloyd(list2.head));
  console.log("Hashing:", hasCycleHashing(list2.head));
  console.log("Modifying:", hasCycleModify(list2.head));
  console.log("Array:", hasCycleArray(list2.head));
  console.log("Recursive:", hasCycleRecursive(list2.head));
  console.log("------------------");

    // Reset visited property for modify approach
    list2 = createLinkedList([1, 2, 3, 4, 5], 2);

  console.log("Test Case 3: No cycle, short list");
  console.log("Input: ", visualizeLinkedList(list3.head));
  console.log("Floyd's:", hasCycleFloyd(list3.head));
  console.log("Hashing:", hasCycleHashing(list3.head));
  console.log("Modifying:", hasCycleModify(list3.head));
  console.log("Array:", hasCycleArray(list3.head));
  console.log("Recursive:", hasCycleRecursive(list3.head));
  console.log("------------------");

    // Reset visited property for modify approach
    list3 = createLinkedList([1, 2]);

  console.log("Test Case 4: Cycle at the beginning");
  console.log("Input: ", visualizeLinkedList(list4.head, true));
  console.log("Floyd's:", hasCycleFloyd(list4.head));
  console.log("Hashing:", hasCycleHashing(list4.head));
  console.log("Modifying:", hasCycleModify(list4.head));
  console.log("Array:", hasCycleArray(list4.head));
  console.log("Recursive:", hasCycleRecursive(list4.head));
  console.log("------------------");

    list4 = createLinkedList([1, 2], 0);

  console.log("Test Case 5: Single node, no cycle");
  console.log("Input: ", visualizeLinkedList(list5.head));
  console.log("Floyd's:", hasCycleFloyd(list5.head));
  console.log("Hashing:", hasCycleHashing(list5.head));
  console.log("Modifying:", hasCycleModify(list5.head));
  console.log("Array:", hasCycleArray(list5.head));
  console.log("Recursive:", hasCycleRecursive(list5.head));
  console.log("------------------");

  list5 = createLinkedList([1]);

  console.log("Test Case 6: Empty list");
  console.log("Input: ", visualizeLinkedList(list6.head));
  console.log("Floyd's:", hasCycleFloyd(list6.head));
  console.log("Hashing:", hasCycleHashing(list6.head));
  console.log("Modifying:", hasCycleModify(list6.head));
  console.log("Array:", hasCycleArray(list6.head));
  console.log("Recursive:", hasCycleRecursive(list6.head));
  console.log("------------------");

  list6 = createLinkedList([]);

  console.log("Test Case 7: Larger list with cycle");
  console.log("Input: ", visualizeLinkedList(list7.head, true));
  console.log("Floyd's:", hasCycleFloyd(list7.head));
  console.log("Hashing:", hasCycleHashing(list7.head));
  console.log("Modifying:", hasCycleModify(list7.head));
  console.log("Array:", hasCycleArray(list7.head));
  console.log("Recursive:", hasCycleRecursive(list7.head));
  console.log("------------------");
}

runTestCases();
