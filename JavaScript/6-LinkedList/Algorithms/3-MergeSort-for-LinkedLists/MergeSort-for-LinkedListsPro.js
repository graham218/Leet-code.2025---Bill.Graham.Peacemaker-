// Node class for the linked list
class ListNode {
    constructor(val = 0, next = null) {
        this.val = val;
        this.next = next;
    }
}

// Function to create a linked list from an array (for testing)
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

// Function to print a linked list (for testing)
function printLinkedList(head) {
    let result = [];
    let current = head;
    while (current) {
        result.push(current.val);
        current = current.next;
    }
    console.log(result.join(" -> "));
}

// Function to get the length of a linked list
function getLength(head) {
    let count = 0;
    let current = head;
    while (current) {
        count++;
        current = current.next;
    }
    return count;
}

// Helper function to merge two sorted linked lists
function merge(left, right) {
    let dummy = new ListNode();
    let tail = dummy;

    while (left && right) {
        if (left.val <= right.val) {
            tail.next = left;
            left = left.next;
        } else {
            tail.next = right;
            right = right.next;
        }
        tail = tail.next;
    }

    tail.next = left || right; // Append the remaining list
    return dummy.next;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. Top-Down Recursive Merge Sort
//   - Classic recursive approach.
//   - Divides the list into halves, recursively sorts them, and then merges.
//   - Uses a slow and fast pointer to find the middle.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function mergeSortRecursive(head) {
    if (!head || !head.next) return head;

    // Find the middle using slow and fast pointer
    let slow = head;
    let fast = head.next;
    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
    }

    let mid = slow.next;
    slow.next = null; // Split the list

    let left = mergeSortRecursive(head);
    let right = mergeSortRecursive(mid);
    return merge(left, right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2. Bottom-Up Iterative Merge Sort
//   - Iterative approach, merging sublists of increasing size.
//   - Avoids recursion, which can be helpful for very large lists to prevent stack overflow.
//   - More complex to implement than the recursive version.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function mergeSortIterative(head) {
    if (!head || !head.next) return head;

    let n = getLength(head);
    let dummy = new ListNode(0, head); // Use a dummy node to simplify merging
    let subLength;

    for (subLength = 1; subLength < n; subLength <<= 1) { // subLength doubles in each iteration
        let prev = dummy;
        let cur = dummy.next;

        while (cur) {
            let left = cur;
            let right = null;
            let i = 1;
            while (i < subLength && cur.next) {
                cur = cur.next;
                i++;
            }
            if(cur.next){
               right = cur.next;
               cur.next = null; //split
               cur = right;
               i = 1;
                while (i < subLength && cur && cur.next) {
                    cur = cur.next;
                    i++;
                }
            }

            let next = null;
            if(cur){
                next = cur.next;
                cur.next = null; //split
            }


            prev.next = merge(left, right);
            while(prev.next){
                prev = prev.next;
            }
            cur = next;
        }
    }
    return dummy.next;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3. Optimized Recursive Merge Sort (Slightly Optimized)
//    - Recursive, but attempts to reduce overhead.
//    - Uses a helper function to split, potentially improving readability.
//    - The core logic remains the same as the standard recursive approach.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function splitList(head) {
    if (!head || !head.next) {
        return { left: head, right: null };
    }
    let slow = head;
    let fast = head.next;
    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
    }
    let mid = slow.next;
    slow.next = null;
    return { left: head, right: mid };
}

function mergeSortRecursiveOptimized(head) {
    if (!head || !head.next) return head;

    const { left, right } = splitList(head);
    const sortedLeft = mergeSortRecursiveOptimized(left);
    const sortedRight = mergeSortRecursiveOptimized(right);
    return merge(sortedLeft, sortedRight);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 4. Merge Sort with Tail Recursion (If Supported by JS Engine - Not truly optimized in standard JS)
//    - Attempts to use tail recursion, which *can* be optimized by some compilers/interpreters
//      to avoid stack overflow.  JavaScript engines generally don't optimize tail recursion.
//    - In standard JavaScript, this offers no real performance benefit, and can be less readable.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function mergeSortTailRecursive(head) {
    function _mergeSort(node, tail) {
        if (!node || !node.next) return node;

        const { left, right } = splitList(node);
        const sortedLeft = _mergeSort(left, null);
        const sortedRight = _mergeSort(right, null);
        return mergeTail(sortedLeft, sortedRight, tail);
    }

    function mergeTail(left, right, tail) {
        if (!left) {
            if (tail) tail.next = right;
            return right;
        }
        if (!right) {
            if (tail) tail.next = left;
            return left;
        }

        if (left.val <= right.val) {
            const next = left.next;
            left.next = null;
            if (tail) {
                tail.next = left;
            }
            return mergeTail(next, right, left);
        } else {
            const next = right.next;
            right.next = null;
            if (tail) {
                tail.next = right;
            }
            return mergeTail(left, next, right);
        }
    }

    return _mergeSort(head, null);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 5. Natural Merge Sort
//    - Exploits existing order in the input list.
//    - Merges already sorted runs, potentially performing better on partially sorted data.
//    - More complex logic, but can be more efficient in specific cases.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function naturalMergeSort(head) {
    if (!head || !head.next) return head;

    let dummy = new ListNode(0, head); // Dummy node for easier handling
    let next;

    while (true) {
        let merged = false;
        let prev = dummy;
        let left = prev.next;

        if (!left) break; // No more lists to merge

        while (left) {
            let right = left;
            while (right.next && right.val <= right.next.val) {
                right = right.next;
            }

            if (!right.next) break;  // Only one sublist remaining

            next = right.next;
            right.next = null; // Terminate the left sublist

            let leftEnd = right; //store end of left to connect after merge

            let rightStart = next;
            let rightEnd = next;
            if(next.next){
                 while (rightEnd.next && rightEnd.val <= rightEnd.next.val) {
                    rightEnd = rightEnd.next;
                }
            }


            let nextStart = rightEnd.next;
            rightEnd.next = null; // Terminate right sublist

            prev.next = merge(left, rightStart);
            while (prev.next) {
                prev = prev.next;
            }
            prev.next = nextStart;
            left = nextStart;
            merged = true;
        }
        if (!merged) break; // If no merges occurred, the list is sorted
    }
    return dummy.next;
}



// Test cases
const testArrays = [
    [5, 3, 1, 9, 2, 8, 4, 7, 6],
    [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    [5, 2, 8, 1, 9, 4],
    [1, 1, 1, 1, 1],
    [],
    [2, 1],
    [1,2,2,1,3,5,4,6,7,5,1,2,5,8,9,4,1,2,3,5,8,7,4,1,2,5,8,9,6,3,2,5,8,7,4,1,2,5,8,9,6,3,2,5,8,7,4,1,2,5,8,9,6,3,2,5,8,7,4,1,2,5,8,9,6,3,2,5,8,7,4,1,2,5,8,9,6,3,2,5,8,7,4] // Large array
];

console.log("--- Test Cases ---");
testArrays.forEach((arr, index) => {
    console.log(`\nTest Case ${index + 1}: [${arr.join(", ")}]`);
    const head = createLinkedList(arr);

    console.log("\nOriginal List:");
    printLinkedList(head);

    let sortedHead;

    // 1. Top-Down Recursive Merge Sort
    sortedHead = mergeSortRecursive(createLinkedList(arr)); //important to create a new linked list for each test
    console.log("\n1. Top-Down Recursive Merge Sort:");
    printLinkedList(sortedHead);

    // 2. Bottom-Up Iterative Merge Sort
    sortedHead = mergeSortIterative(createLinkedList(arr));
    console.log("\n2. Bottom-Up Iterative Merge Sort:");
    printLinkedList(sortedHead);

    // 3. Optimized Recursive Merge Sort
    sortedHead = mergeSortRecursiveOptimized(createLinkedList(arr));
    console.log("\n3. Optimized Recursive Merge Sort:");
    printLinkedList(sortedHead);

    // 4. Merge Sort with Tail Recursion (Not truly optimized in standard JS)
    sortedHead = mergeSortTailRecursive(createLinkedList(arr));
    console.log("\n4. Merge Sort with Tail Recursion:");
    printLinkedList(sortedHead);

    // 5. Natural Merge Sort
    sortedHead = naturalMergeSort(createLinkedList(arr));
    console.log("\n5. Natural Merge Sort:");
    printLinkedList(sortedHead);
});
