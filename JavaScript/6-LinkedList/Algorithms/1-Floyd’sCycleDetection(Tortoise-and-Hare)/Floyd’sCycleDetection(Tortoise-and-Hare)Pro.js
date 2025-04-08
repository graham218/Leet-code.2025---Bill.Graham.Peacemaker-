// Node class for the linked list
class ListNode {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

// Function to create a linked list
function createLinkedList(arr) {
  if (!arr || arr.length === 0) return null;
  const head = new ListNode(arr[0]);
  let current = head;
  for (let i = 1; i < arr.length; i++) {
    current.next = new ListNode(arr[i]);
    current = current.next;
  }
  return head;
}

// Function to create a cycle in the linked list (for testing purposes)
function createCycle(head, pos) {
  if (!head || pos === 0) return;
  let current = head;
  let cycleStart = null;
  let count = 1;

  while (current.next) {
    if (count === pos) {
      cycleStart = current;
    }
    current = current.next;
    count++;
  }
  current.next = cycleStart; // Create the cycle
}

// 1. Floyd's Cycle Detection (Tortoise and Hare)
function hasCycleFloyd(head) {
  if (!head || !head.next) return false;

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

// 2. Floyd's Cycle Detection with Cycle Start Point
function detectCycleStart(head) {
    if (!head || !head.next) return null;

    let slow = head;
    let fast = head;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            // Cycle detected, find the start
            slow = head;
            while (slow !== fast) {
                slow = slow.next;
                fast = fast.next;
            }
            return slow;
        }
    }
    return null;
}

// 3. Using a Set (for comparison)
function hasCycleSet(head) {
  if (!head) return false;
  const set = new Set();
  let current = head;
  while (current) {
    if (set.has(current)) {
      return true;
    }
    set.add(current);
    current = current.next;
  }
  return false;
}

// 4. Detecting Cycle Length
function detectCycleLength(head) {
    if (!head || !head.next) return 0;

    let slow = head;
    let fast = head;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            // Cycle detected, find the length
            let current = slow;
            let length = 1;
            current = current.next;
            while (current !== slow) {
                length++;
                current = current.next;
            }
            return length;
        }
    }
    return 0;
}

// 5.  Broken Linked List Detection
function isListBroken(head) {
  if (!head) return false;

  let slow = head;
  let fast = head;
  let count = 0;

  while (fast && fast.next) {
      slow = slow.next;
      fast = fast.next.next;
      count++;
      if(count > 10000) return true; //Arbitrary limit to avoid infinite loop.
      if (slow === fast) {
          return false; // It is not broken, it has a cycle
      }
  }
  return false; // No cycle, list is properly terminated.
}

// --- Test Cases ---
const list1 = createLinkedList([1, 2, 3, 4, 5]);
const list2 = createLinkedList([1, 2, 3, 4, 5]);
createCycle(list2, 2); // Create a cycle starting at node with value 2
const list3 = createLinkedList([1]);
const list4 = createLinkedList([]);
const list5 = createLinkedList([1,2,3,4,5,6,7,8,9,10]);
createCycle(list5, 5);

// Test Floyd's cycle detection
console.log("--- Floyd's Cycle Detection ---");
console.log("List 1 (no cycle):", hasCycleFloyd(list1)); // false
console.log("List 2 (with cycle):", hasCycleFloyd(list2)); // true
console.log("List 3 (single node, no cycle):", hasCycleFloyd(list3)); // false
console.log("List 4 (empty list, no cycle):", hasCycleFloyd(list4)); // false
console.log("List 5 (with cycle):", hasCycleFloyd(list5)); // true

// Test Floyd's cycle detection with start point
console.log("\n--- Floyd's Cycle Start Detection ---");
console.log("List 1 (no cycle):", detectCycleStart(list1)); // null
console.log("List 2 (with cycle):", detectCycleStart(list2).data); // 2
console.log("List 3 (single node, no cycle):", detectCycleStart(list3)); // null
console.log("List 4 (empty list, no cycle):", detectCycleStart(list4)); // null
console.log("List 5 (with cycle):", detectCycleStart(list5).data); // 5

// Test Set approach
console.log("\n--- Set Approach ---");
console.log("List 1 (no cycle):", hasCycleSet(list1)); // false
console.log("List 2 (with cycle):", hasCycleSet(list2)); // true
console.log("List 3 (single node, no cycle):", hasCycleSet(list3)); // false
console.log("List 4 (empty list, no cycle):", hasCycleSet(list4)); // false
console.log("List 5 (with cycle):", hasCycleSet(list5)); // true

// Test detecting cycle length
console.log("\n--- Cycle Length Detection ---");
console.log("List 1 (no cycle):", detectCycleLength(list1)); // 0
console.log("List 2 (with cycle):", detectCycleLength(list2)); // 4
console.log("List 3 (single node, no cycle):", detectCycleLength(list3)); // 0
console.log("List 4 (empty list, no cycle):", detectCycleLength(list4)); // 0
console.log("List 5 (with cycle):", detectCycleLength(list5)); // 6

// Test Broken List Detection
console.log("\n--- Broken List Detection ---");
console.log("List 1 (no cycle):", isListBroken(list1));
console.log("List 2 (with cycle):", isListBroken(list2));
console.log("List 3 (no cycle):", isListBroken(list3));
console.log("List 4 (no cycle):", isListBroken(list4));
console.log("List 5 (with cycle):", isListBroken(list5));

// --- Application Examples ---

// 1. Detecting Infinite Loops in Web Crawlers:  (Conceptual)
//    - Web crawlers traverse links.  A cycle means the crawler is stuck in a loop.
//    - Use Floyd's to detect if a URL has been visited before in the current crawl path.
function crawlWeb(startUrl, maxDepth = 100) {
  const visited = new Set();
  const queue = [{ url: startUrl, depth: 0 }];

  while (queue.length > 0) {
    const { url, depth } = queue.shift();

    if (depth > maxDepth) {
      console.log(`Reached maximum depth of ${maxDepth}.  Possible infinite loop.`);
      break; // Stop crawling to prevent infinite loop
    }

    if (visited.has(url)) {
      console.log(`Cycle detected!  URL "${url}" visited again.`);
      continue; // Skip to the next URL
    }

    visited.add(url);
    console.log(`Crawling ${url} at depth ${depth}`);

    // Simulate fetching links from the page
    const links = getLinksFromPage(url); //  Assume this function exists

    if (!links) continue; // error in getLinksFromPage

    for (const link of links) {
      queue.push({ url: link, depth: depth + 1 });
    }
  }
  console.log("Crawl complete.");
}

// Simulate getting links (in real implementation, this would use fetch/XHR)
function getLinksFromPage(url) {
    if (url === "http://example.com/page1") return ["http://example.com/page2", "http://example.com/page3"];
    if (url === "http://example.com/page2") return ["http://example.com/page3", "http://example.com/page4"];
    if (url === "http://example.com/page3") return ["http://example.com/page1", "http://example.com/page4"]; // Cycle
    if (url === "http://example.com/page4") return [];
    return null; //error
}
console.log("\n--- Web Crawler Example (Conceptual) ---");
crawlWeb("http://example.com/page1", 3);

// 2. Detecting Circular Dependencies in Build Systems (Conceptual)
//    -  Build systems (like Make, Gradle, npm) have dependencies between files/modules.
//    -  A cycle means a file depends on itself (indirectly), causing an infinite build loop.
function buildSystemExample() {
  const files = {
    "A": ["B"],
    "B": ["C", "D"],
    "C": ["A"], // Cycle!
    "D": []
  };

  function createDependencyList(files) {
      const nodes = {};
      for(const file in files){
          nodes[file] = new ListNode(file);
      }

      for(const file in files){
          let current = nodes[file];
          const dependencies = files[file];
          if(!dependencies) continue;
          for(const dependency of dependencies){
              current.next = nodes[dependency];
              current = current.next;
          }
      }
      return nodes;
  }

  const fileNodes = createDependencyList(files);
  const fileA = fileNodes["A"];


  if (hasCycleFloyd(fileA)) {
    console.log("Circular dependency detected!  The build process cannot continue.");
  } else {
    console.log("No circular dependencies found.  Build can proceed.");
  }
}

console.log("\n--- Build System Example (Conceptual) ---");
buildSystemExample();


// 3. Detecting Loops in Game State (Conceptual)
//    -  In some games, state transitions can form loops (e.g., an AI getting stuck in a loop).
//    -  Floyd's can detect these loops to prevent the game from freezing.

function gameStateLoopExample() {
    const states = ['A', 'B', 'C', 'D', 'E'];

    // Function to simulate state transition
    function transition(currentState) {
        switch (currentState) {
            case 'A': return 'B';
            case 'B': return 'C';
            case 'C': return 'D';
            case 'D': return 'E';
            case 'E': return 'C'; // Intentionally create a loop
            default: return null;
        }
    }

    // Simulate game state transitions
    let currentState = 'A';
    const visitedStates = new Set();
    let steps = 0;
    const maxSteps = 20; // Add a maximum step limit

    while (currentState && steps < maxSteps) {
        if (visitedStates.has(currentState)) {
            console.log(`\nGame state loop detected!  Current state: ${currentState}`);
            break;
        }
        visitedStates.add(currentState);
        console.log(`Game state: ${currentState}`);
        currentState = transition(currentState);
        steps++;
    }
    if(steps >= maxSteps){
        console.log("\nMaximum steps reached.  Possible infinite loop.");
    }
}
console.log("\n--- Game State Loop Example (Conceptual) ---");
gameStateLoopExample();

// 4. Memory Leak Detection (Conceptual)
//   -  In languages without garbage collection, a cycle of object references can prevent memory from being freed.
//   -  While not a direct Floyd's application, the *idea* of detecting cycles is relevant to memory leak detection.
//   -  Tools might use cycle detection to find unreachable memory.
function memoryLeakExample() {
  // Simulate objects with references (simplified)
  const objA = { name: 'A', ref: null };
  const objB = { name: 'B', ref: null };
  const objC = { name: 'C', ref: null };

  objA.ref = objB;
  objB.ref = objC;
  objC.ref = objA; // Create a cycle

  console.log("\n--- Memory Leak Example (Conceptual) ---");
  console.log("Objects objA, objB, and objC now form a reference cycle.");
  console.log("In languages without GC, this cycle could lead to a memory leak.");
}

memoryLeakExample();

// 5.  Data Validation in Distributed Systems (Conceptual)
//     -  In distributed systems, data can be passed between nodes.  A cycle in data flow could indicate an error.
//     -  Detecting cycles can help prevent infinite loops in data processing.
function distributedSystemExample() {
    // Simulate data flow with nodes
    const nodeA = { name: 'A', sendTo: 'B', data: null};
    const nodeB = { name: 'B', sendTo: 'C', data: null};
    const nodeC = { name: 'C', sendTo: 'A', data: null}; // Cycle
    const nodes = {A: nodeA, B: nodeB, C: nodeC};

    function createDataFlowList(nodes) {
        const nodeList = {};
        for (const nodeName in nodes) {
            nodeList[nodeName] = new ListNode(nodes[nodeName]);
        }

        for (const nodeName in nodes) {
            const currentNode = nodeList[nodeName];
            const sendToName = nodes[nodeName].sendTo;
            if (sendToName && nodeList[sendToName]) {
                currentNode.next = nodeList[sendToName];
            }
        }
        return nodeList;
    }
    const listHead = createDataFlowList(nodes)['A'];

    if(hasCycleFloyd(listHead)){
        console.log("\n--- Distributed System Example (Conceptual) ---");
        console.log("Data flow cycle detected.  Check nodes A, B, and C.");
    } else {
        console.log("\n--- Distributed System Example (Conceptual) ---");
        console.log("No data flow cycles detected.");
    }
}

distributedSystemExample();
