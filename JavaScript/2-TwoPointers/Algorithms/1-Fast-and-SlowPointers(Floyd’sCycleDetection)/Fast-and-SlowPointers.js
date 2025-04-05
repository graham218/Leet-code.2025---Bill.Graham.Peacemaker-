/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 * this.val = val;
 * this.next = null;
 * }
 */

/**
 * Floyd's Cycle Detection Algorithm (Tortoise and Hare)
 *
 * This algorithm is used to detect whether a linked list contains a cycle. It uses two pointers,
 * a slow pointer and a fast pointer. The slow pointer moves one node at a time, while the
 * fast pointer moves two nodes at a time.
 *
 * If there is a cycle in the linked list, the fast pointer will eventually meet the slow pointer.
 * If there is no cycle, the fast pointer will reach the end of the list (null).
 */

// Helper function to create a linked list for testing
function createLinkedList(values, cyclePos = -1) {
    let head = null;
    let tail = null;
    let cycleNode = null;

    for (let i = 0; i < values.length; i++) {
        const newNode = new ListNode(values[i]);
        if (!head) {
            head = newNode;
        } else {
            tail.next = newNode;
        }
        tail = newNode;

        if (cyclePos === i) {
            cycleNode = newNode;
        }
    }

    if (cyclePos !== -1) {
        tail.next = cycleNode; // Create the cycle
    }
    return head;
}

// Helper function to visualize the linked list (with cycle if present)
function visualizeLinkedList(head) {
  let nodes = [];
  let current = head;
  let visited = new Set();
  let cycleStart = null;

  while (current && !visited.has(current)) {
    nodes.push(current.val);
    visited.add(current);
    current = current.next;
  }

  let result = nodes.join(" -> ");

  if (current) { // Cycle detected
    let cycleIndex = nodes.indexOf(current.val);
    result += ` -> ${nodes.slice(cycleIndex).join(" -> ")} -> ... (Cycle)`;
  }

  return result;
}

function ListNode(val) {
    this.val = val;
    this.next = null;
}
/**
 * @param {ListNode} head
 * @return {boolean}
 */
var hasCycle = function(head) {
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
};



/**
 * 1. Floyd's Cycle Detection (Basic)
 * - Detects if a cycle exists.
 */
function floydCycleDetection(head) {
    if (!head || !head.next) {
        return false; // No cycle if list is empty or has only one node
    }

    let slow = head;
    let fast = head;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            return true; // Cycle detected
        }
    }
    return false; // No cycle
}

/**
 * 2. Floyd's Cycle Detection (Finding the meeting point)
 * - Detects a cycle and returns the meeting point of the slow and fast pointers.
 */
function floydCycleDetectionMeetingPoint(head) {
    if (!head || !head.next) {
        return null;
    }

    let slow = head;
    let fast = head;
    let meetingPoint = null;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            meetingPoint = slow;
            break;
        }
    }
    return meetingPoint; // Returns the meeting point if cycle exists else null
}

/**
 * 3. Floyd's Cycle Detection (Finding the start of the cycle)
 * - Detects a cycle and returns the node where the cycle begins.
 */
function floydCycleDetectionStart(head) {
    if (!head || !head.next) {
        return null;
    }

    let slow = head;
    let fast = head;
    let meetingPoint = null;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
        if (slow === fast) {
            meetingPoint = slow;
            break;
        }
    }

    if (!meetingPoint) {
        return null; // No cycle
    }

    slow = head; // Reset slow pointer to the head
    while (slow !== fast) {
        slow = slow.next;
        fast = fast.next;
    }
    return slow; // Returns the start node of the cycle
}

/**
 * 4. Floyd's Cycle Detection (Alternative implementation)
 * - A slightly different way to write the condition for the while loop.
 */
function floydCycleDetectionAlternative(head) {
     if (!head) return false;

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

/**
 * 5. Floyd's Cycle Detection (With detailed logging)
 * - Includes console logs to illustrate the execution process.
 */
function floydCycleDetectionWithLogs(head) {
    if (!head || !head.next) {
        console.log("List is too short to have a cycle.");
        return false;
    }

    let slow = head;
    let fast = head;

    console.log("Starting with slow and fast pointers at the head of the list.");

    while (fast && fast.next) {
        console.log(`Slow pointer moves to: ${slow.val}`);
        slow = slow.next;
        console.log(`Fast pointer moves to: ${fast.next ? fast.next.val : 'null'}${fast.next?.next? ` and then to: ${fast.next.next.val}`:''}`);
        fast = fast.next?.next;

        if (slow === fast) {
            console.log(`Slow and fast pointers meet at node with value: ${slow.val}`);
            return true;
        }
    }

    console.log("Fast pointer reached the end of the list. No cycle detected.");
    return false;
}



// Test cases
function runTestCases() {
    console.log("Running Test Cases for Floyd's Cycle Detection:");
    console.log("---------------------------------------------");

    // Test Case 1: No cycle
    let list1 = createLinkedList([1, 2, 3, 4, 5]);
    console.log("Test Case 1: No cycle - List: " + visualizeLinkedList(list1));
    console.log("Floyd's (Basic):", floydCycleDetection(list1));
    console.log("Floyd's (Meeting Point):", floydCycleDetectionMeetingPoint(list1));
    console.log("Floyd's (Start):", floydCycleDetectionStart(list1));
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list1));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list1));


    // Test Case 2: Cycle at the beginning
    let list2 = createLinkedList([1, 2, 3, 4, 5], 0);
    console.log("\nTest Case 2: Cycle at the beginning - List: " + visualizeLinkedList(list2));
    console.log("Floyd's (Basic):", floydCycleDetection(list2));
    let meetingPoint2 = floydCycleDetectionMeetingPoint(list2);
    console.log("Floyd's (Meeting Point):", meetingPoint2 ? meetingPoint2.val : null);
    let start2 = floydCycleDetectionStart(list2);
    console.log("Floyd's (Start):", start2 ? start2.val : null);
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list2));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list2));

    // Test Case 3: Cycle in the middle
    let list3 = createLinkedList([1, 2, 3, 4, 5], 2);
    console.log("\nTest Case 3: Cycle in the middle - List: " + visualizeLinkedList(list3));
    console.log("Floyd's (Basic):", floydCycleDetection(list3));
    let meetingPoint3 = floydCycleDetectionMeetingPoint(list3);
    console.log("Floyd's (Meeting Point):", meetingPoint3 ? meetingPoint3.val : null);
    let start3 = floydCycleDetectionStart(list3);
    console.log("Floyd's (Start):", start3 ? start3.val : null);
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list3));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list3));

    // Test Case 4: Cycle at the end
    let list4 = createLinkedList([1, 2, 3, 4, 5], 4);
    console.log("\nTest Case 4: Cycle at the end - List: " + visualizeLinkedList(list4));
    console.log("Floyd's (Basic):", floydCycleDetection(list4));
    let meetingPoint4 = floydCycleDetectionMeetingPoint(list4);
    console.log("Floyd's (Meeting Point):", meetingPoint4 ? meetingPoint4.val : null);
    let start4 = floydCycleDetectionStart(list4);
    console.log("Floyd's (Start):", start4 ? start4.val : null);
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list4));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list4));

    // Test Case 5: Single node with cycle
    let list5 = createLinkedList([1], 0);
    console.log("\nTest Case 5: Single node with cycle - List: " + visualizeLinkedList(list5));
    console.log("Floyd's (Basic):", floydCycleDetection(list5));
    let meetingPoint5 = floydCycleDetectionMeetingPoint(list5);
    console.log("Floyd's (Meeting Point):", meetingPoint5 ? meetingPoint5.val : null);
    let start5 = floydCycleDetectionStart(list5);
    console.log("Floyd's (Start):", start5 ? start5.val : null);
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list5));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list5));

    // Test Case 6: Empty list
    let list6 = createLinkedList([]);
    console.log("\nTest Case 6: Empty list - List: " + visualizeLinkedList(list6));
    console.log("Floyd's (Basic):", floydCycleDetection(list6));
    console.log("Floyd's (Meeting Point):", floydCycleDetectionMeetingPoint(list6));
    console.log("Floyd's (Start):", floydCycleDetectionStart(list6));
    console.log("Floyd's (Alternative):", floydCycleDetectionAlternative(list6));
    console.log("Floyd's (Logs):", floydCycleDetectionWithLogs(list6));
}

runTestCases();
