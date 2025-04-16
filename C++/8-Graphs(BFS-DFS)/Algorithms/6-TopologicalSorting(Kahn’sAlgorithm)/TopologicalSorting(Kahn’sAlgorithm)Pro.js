/**
 * Topological Sorting (Kahn's Algorithm) - 5 Approaches
 *
 * Kahn's algorithm is used to find a topological ordering of a directed acyclic graph (DAG).
 * It works by finding nodes with no incoming edges, adding them to the result,
 * and removing their outgoing edges.  This process is repeated until all nodes
 * have been processed.
 */

// Helper function to create an adjacency list from edge list
function createAdjacencyList(edges, numNodes) {
    const adjList = Array.from({ length: numNodes }, () => []);
    for (const [u, v] of edges) {
        adjList[u].push(v);
    }
    return adjList;
}

// Helper function to calculate in-degrees
function calculateInDegrees(adjList, numNodes) {
    const inDegrees = Array(numNodes).fill(0);
    for (let u = 0; u < numNodes; u++) {
        for (const v of adjList[u]) {
            inDegrees[v]++;
        }
    }
    return inDegrees;
}

// 1. Basic Kahn's Algorithm
//    - Uses a queue to store nodes with in-degree 0.
//    - Suitable for simple DAG sorting.
function topologicalSortBasic(edges, numNodes) {
    const adjList = createAdjacencyList(edges, numNodes);
    const inDegrees = calculateInDegrees(adjList, numNodes);
    const queue = [];
    const result = [];

    // Enqueue nodes with in-degree 0
    for (let i = 0; i < numNodes; i++) {
        if (inDegrees[i] === 0) {
            queue.push(i);
        }
    }

    while (queue.length > 0) {
        const u = queue.shift();
        result.push(u);

        for (const v of adjList[u]) {
            inDegrees[v]--;
            if (inDegrees[v] === 0) {
                queue.push(v);
            }
        }
    }

    // Check for cycles (if not all nodes are in result)
    if (result.length !== numNodes) {
        return null; // Cycle detected
    }

    return result;
}

// 2. Kahn's Algorithm with Object Representation
//    - Uses an object to represent the adjacency list.
//    - Useful when node IDs are not simple integers.
function topologicalSortObject(edges) {
    const adjList = {};
    const inDegrees = {};

    // Find all unique nodes
    const nodes = new Set();
    for (const [u, v] of edges) {
        nodes.add(u);
        nodes.add(v);
    }
    for (const node of nodes) {
        adjList[node] = [];
        inDegrees[node] = 0;
    }

    // Build the adjacency list and in-degree counts
    for (const [u, v] of edges) {
        adjList[u].push(v);
        inDegrees[v]++;
    }

    const queue = [];
    const result = [];

    // Enqueue nodes with in-degree 0
    for (const node in inDegrees) {
        if (inDegrees[node] === 0) {
            queue.push(node);
        }
    }

    while (queue.length > 0) {
        const u = queue.shift();
        result.push(u);

        if (adjList[u]) { // Check if the node has outgoing edges.
            for (const v of adjList[u]) {
                inDegrees[v]--;
                if (inDegrees[v] === 0) {
                    queue.push(v);
                }
            }
        }
    }
    if (result.length !== nodes.size) {
        return null; // Cycle
    }
    return result;
}

// 3. Kahn's Algorithm for Job Scheduling
//    - Represents tasks with dependencies.
//    - Useful for scheduling jobs or tasks.
function topologicalSortJobScheduling(jobs, dependencies) {
    const adjList = Array.from({ length: jobs.length }, () => []);
    const inDegrees = Array(jobs.length).fill(0);

    // Build adjacency list and in-degrees
    for (const [job, dependency] of dependencies) {
        adjList[dependency].push(job); // Corrected: dependency -> job
        inDegrees[job]++;
    }

    const queue = [];
    const result = [];

    // Enqueue jobs with no dependencies (in-degree 0)
    for (let i = 0; i < jobs.length; i++) {
        if (inDegrees[i] === 0) {
            queue.push(i);
        }
    }

    while (queue.length > 0) {
        const job = queue.shift();
        result.push(job);

        for (const dependentJob of adjList[job]) {
            inDegrees[dependentJob]--;
            if (inDegrees[dependentJob] === 0) {
                queue.push(dependentJob);
            }
        }
    }

    if (result.length !== jobs.length) {
        return null; // Cycle
    }

    return result;
}

// 4. Kahn's Algorithm with Custom Node IDs (Strings)
function topologicalSortCustomIds(edges) {
  const adjList = {};
  const inDegrees = {};

  // Initialize adjList and inDegrees.  Use a Set to get unique nodes.
  const nodes = new Set();
  for (const [u, v] of edges) {
      nodes.add(u);
      nodes.add(v);
  }
  nodes.forEach(node => {
      adjList[node] = [];
      inDegrees[node] = 0;
  });

  // Build the adjacency list and in-degree counts.
  for (const [u, v] of edges) {
      adjList[u].push(v);
      inDegrees[v]++;
  }

  const queue = [];
  const result = [];

  // Enqueue nodes with in-degree 0.
  for (const node in inDegrees) {
      if (inDegrees[node] === 0) {
          queue.push(node);
      }
  }

  while (queue.length > 0) {
      const u = queue.shift();
      result.push(u);

      if (adjList[u]) { // Check for null or undefined
          for (const v of adjList[u]) {
              inDegrees[v]--;
              if (inDegrees[v] === 0) {
                  queue.push(v);
              }
          }
      }
  }
  if (result.length !== nodes.size) {
      return null;
  }
  return result;
}

// 5. Kahn's Algorithm for Course Scheduling
//    - Represents courses and their prerequisites.
//    - Useful for determining a valid course schedule.
function topologicalSortCourseSchedule(numCourses, prerequisites) {
    const adjList = Array.from({ length: numCourses }, () => []);
    const inDegrees = Array(numCourses).fill(0);

    // Build adjacency list and in-degrees
    for (const [course, prerequisite] of prerequisites) {
        adjList[prerequisite].push(course);
        inDegrees[course]++;
    }

    const queue = [];
    const result = [];

    // Enqueue courses with no prerequisites
    for (let i = 0; i < numCourses; i++) {
        if (inDegrees[i] === 0) {
            queue.push(i);
        }
    }

    while (queue.length > 0) {
        const course = queue.shift();
        result.push(course);

        for (const nextCourse of adjList[course]) {
            inDegrees[nextCourse]--;
            if (inDegrees[nextCourse] === 0) {
                queue.push(nextCourse);
            }
        }
    }

    if (result.length !== numCourses) {
        return null; // Cycle
    }

    return result;
}

// Example Usage
const numNodes1 = 6;
const edges1 = [[5, 2], [5, 0], [4, 0], [4, 1], [2, 3], [3, 1]];
console.log("1. Basic Kahn's Algorithm:");
console.log(topologicalSortBasic(edges1, numNodes1)); // Output: [5, 4, 2, 0, 3, 1]

const edges2 = [['A', 'B'], ['A', 'C'], ['B', 'D'], ['C', 'D'], ['D', 'E']];
console.log("\n2. Kahn's Algorithm with Object Representation:");
console.log(topologicalSortObject(edges2)); // Output:  ['A', 'B', 'C', 'D', 'E']

const jobs = ['Design', 'Coding', 'Testing', 'Documentation', 'Deployment'];
const dependencies = [
    [ 'Coding', 'Design' ],
    [ 'Testing', 'Coding' ],
    [ 'Documentation', 'Coding' ],
    [ 'Deployment', 'Testing' ],
    [ 'Deployment', 'Documentation' ]
];
console.log("\n3. Kahn's Algorithm for Job Scheduling:");
const jobIndices = dependencies.map(dep => [jobs.indexOf(dep[0]), jobs.indexOf(dep[1])]);
const jobSchedule = topologicalSortJobScheduling(jobs, jobIndices);
const jobNames = jobSchedule ? jobSchedule.map(index => jobs[index]) : null;
console.log(jobNames); // Output:  ['Design', 'Coding', 'Documentation', 'Testing', 'Deployment']

const edges4 = [["A", "B"], ["A", "C"], ["B", "D"], ["C", "E"], ["D", "F"], ["E", "F"]];
console.log("\n4. Kahn's Algorithm with Custom Node IDs (Strings):");
console.log(topologicalSortCustomIds(edges4));

const numCourses = 4;
const prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]];
console.log("\n5. Kahn's Algorithm for Course Scheduling:");
console.log(topologicalSortCourseSchedule(numCourses, prerequisites)); // Output: [0, 1, 2, 3] or [0, 2, 1, 3]
