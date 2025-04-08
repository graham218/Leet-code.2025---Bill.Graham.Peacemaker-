// Definition of a ListNode (you can copy this into your environment)
class ListNode {
    constructor(val = 0, next = null) {
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

// Helper function to print a linked list
function printLinkedList(head) {
    console.log(linkedListToArray(head));
}



// Approach 1: Recursive Merge Sort (Classic)
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

function getMid(head) {
    let slow = head;
    let fast = head.next; // Important: Start fast one step ahead
    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
    }
    return slow;
}

function mergeSortRecursive(head) {
    if (!head || !head.next) return head;

    const mid = getMid(head);
    const left = head;
    const right = mid.next;
    mid.next = null; // Disconnect the two halves

    const sortedLeft = mergeSortRecursive(left);
    const sortedRight = mergeSortRecursive(right);
    return mergeTwoListsRecursive(sortedLeft, sortedRight);
}



// Approach 2: Iterative Merge Sort (Bottom-Up)
function mergeTwoListsIterative(l1, l2) {
    const dummy = new ListNode();
    let tail = dummy;

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

    tail.next = l1 || l2; // Append the remaining list
    return dummy.next;
}

function mergeSortIterative(head) {
    if (!head || !head.next) return head;

    let n = 0;
    let current = head;
    while (current) {
        n++;
        current = current.next;
    }

    let dummy = new ListNode(0, head); // Use a dummy node for easier handling
    for (let size = 1; size < n; size *= 2) {
        let prev = dummy;
        let cur = dummy.next;

        while (cur) {
            let left = cur;
            let right = cur;
            for (let i = 1; i < size && right && right.next; i++) {
                right = right.next;
            }
            if (!right || !right.next) break; // Important: Check for end of list
            let next = right.next;
            right.next = null; // Detach the first sublist

            let secondHalf = next;
             for (let i = 1; i < size && secondHalf && secondHalf.next; i++) {
                secondHalf = secondHalf.next;
            }
            let temp = secondHalf ? secondHalf.next: null;
            if(secondHalf) secondHalf.next = null;

            const merged = mergeTwoListsIterative(left, next);
            prev.next = merged;
            while (prev.next) {
                prev = prev.next;
            }
            cur = temp; // Move to the next pair
        }
    }
    return dummy.next;
}


// Approach 3: Optimized Recursive Merge Sort (Slightly more efficient mid finding)
function getMidOptimized(head) {
    let prev = null;
    let slow = head;
    let fast = head;
    while (fast && fast.next) {
        prev = slow;
        slow = slow.next;
        fast = fast.next.next;
    }
    return { mid: slow, prev }; // Return both mid and its previous node
}

function mergeSortRecursiveOptimized(head) {
    if (!head || !head.next) return head;

    const { mid, prev } = getMidOptimized(head);
    const left = head;
    const right = mid;
    if (prev) {
        prev.next = null; // Disconnect the lists
    }

    const sortedLeft = mergeSortRecursiveOptimized(left);
    const sortedRight = mergeSortRecursiveOptimized(right);
    return mergeTwoListsRecursive(sortedLeft, sortedRight);
}



// Approach 4: Merge Sort with Auxiliary Array (for comparison)
function mergeSortWithArray(head) {
    const arr = [];
    let current = head;
    while (current) {
        arr.push(current.val);
        current = current.next;
    }
    arr.sort((a, b) => a - b); // Use JavaScript's built-in sort (for comparison)

    // Reconstruct the linked list
    const dummy = new ListNode();
    let tail = dummy;
    for (const val of arr) {
        tail.next = new ListNode(val);
        tail = tail.next;
    }
    return dummy.next;
}



// Approach 5: Using a Stack (Simulating Recursion)
function mergeSortStack(head) {
    if (!head || !head.next) return head;

    const stack = [];
    let current = head;
    while (current) {
        stack.push(current);
        current = current.next;
    }

    const sortedStack = [];
    while (stack.length > 0)
    {
        let node = stack.pop();
        node.next = null;
        sortedStack.push(node);
    }
    while(sortedStack.length > 1)
    {
        let l2 = sortedStack.pop();
        let l1 = sortedStack.pop();
        sortedStack.push(mergeTwoListsRecursive(l1,l2));
    }
    return sortedStack[0];
}


// Example Usage and Testing
const unsortedList = createLinkedList([5, 3, 1, 6, 2, 7, 4, 8]);

console.log("Original List:");
printLinkedList(unsortedList);

console.log("\nApproach 1: Recursive Merge Sort");
const sortedList1 = mergeSortRecursive(unsortedList ? { ...unsortedList } : null); // Pass a copy
printLinkedList(sortedList1);

const unsortedList2 = createLinkedList([5, 3, 1, 6, 2, 7, 4, 8]); //reset
console.log("\nApproach 2: Iterative Merge Sort");
const sortedList2 = mergeSortIterative(unsortedList2 ? { ...unsortedList2 } : null);
printLinkedList(sortedList2);

const unsortedList3 = createLinkedList([5, 3, 1, 6, 2, 7, 4, 8]); //reset
console.log("\nApproach 3: Optimized Recursive Merge Sort");
const sortedList3 = mergeSortRecursiveOptimized(unsortedList3 ? { ...unsortedList3 } : null);
printLinkedList(sortedList3);

const unsortedList4 = createLinkedList([5, 3, 1, 6, 2, 7, 4, 8]); //reset
console.log("\nApproach 4: Merge Sort with Auxiliary Array");
const sortedList4 = mergeSortWithArray(unsortedList4 ? { ...unsortedList4 } : null);
printLinkedList(sortedList4);

const unsortedList5 = createLinkedList([5, 3, 1, 6, 2, 7, 4, 8]); //reset
console.log("\nApproach 5: Merge Sort with Stack");
const sortedList5 = mergeSortStack(unsortedList5);
printLinkedList(sortedList5);
