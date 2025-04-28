#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

// 1. Basic Kahn's Algorithm (Task Scheduling)
//
//   -   Problem:  You have a list of tasks to perform, and some tasks depend on others being completed first.  Find an order in which to perform the tasks.
//   -   Real-world:  This is the classic application of topological sort.  Think of a build system (like Make or CMake) where compiling a library depends on compiling its dependencies.
//   -   Code:
vector<int> topologicalSort_Kahn_Basic(int numTasks, const vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> adj(numTasks); // Adjacency list: adj[i] is a list of tasks that depend on task i.
    vector<int> inDegree(numTasks, 0); // inDegree[i] is the number of prerequisites for task i.
    vector<int> result;             // The topological order of tasks.

    // 1. Build the graph and calculate in-degrees.
    for (const auto& pair : prerequisites) {
        int task = pair.first;      // Task that depends on the other.
        int prerequisite = pair.second; // Task that must be done first.
        adj[prerequisite].push_back(task); // Add edge: prerequisite -> task
        inDegree[task]++;             // Increment in-degree of the dependent task.
    }

    // 2. Find starting tasks (nodes with in-degree 0).
    queue<int> q;
    for (int i = 0; i < numTasks; ++i) {
        if (inDegree[i] == 0) {
            q.push(i); // Start with tasks that have no dependencies.
        }
    }

    // 3. Process tasks in topological order.
    while (!q.empty()) {
        int task = q.front();
        q.pop();
        result.push_back(task); // Add the task to the result.

        // For each task that depends on this task:
        for (int dependentTask : adj[task]) {
            inDegree[dependentTask]--; // Reduce its in-degree.
            if (inDegree[dependentTask] == 0) {
                // If its in-degree becomes 0, it can be done next.
                q.push(dependentTask);
            }
        }
    }

    // 4. Check for cycles.  If not all tasks were processed, there's a cycle.
    if (result.size() != numTasks) {
        return {}; // Return an empty vector to indicate a cycle.
    }

    return result;
}

// 2. Kahn's Algorithm with Custom Data (Course Scheduling with Credits)
//
//   -   Problem:  Similar to task scheduling, but each task (course) has a certain number of credits.  Find a valid schedule and calculate the total credits earned.
//   -   Real-world:  University course scheduling, where courses have prerequisites and credit hours.
//   -   Code:
struct Course {
    int id;
    int credits;
};

vector<int> topologicalSort_Kahn_Credits(int numCourses, const vector<pair<int, int>>& prerequisites, const vector<Course>& courses) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegree(numCourses, 0);
    vector<int> result;
    unordered_map<int, int> courseCredits; // Map from course ID to credits.

    for (const auto& course : courses) {
        courseCredits[course.id] = course.credits;
    }

    for (const auto& pair : prerequisites) {
        int course = pair.first;
        int prerequisite = pair.second;
        adj[prerequisite].push_back(course);
        inDegree[course]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int totalCredits = 0; // Keep track of total credits.
    while (!q.empty()) {
        int courseId = q.front();
        q.pop();
        result.push_back(courseId);
        totalCredits += courseCredits[courseId]; // Add credits for the completed course.

        for (int dependentCourse : adj[courseId]) {
            inDegree[dependentCourse]--;
            if (inDegree[dependentCourse] == 0) {
                q.push(dependentCourse);
            }
        }
    }

    if (result.size() != numCourses) {
        return {};
    }
    cout << "Total Credits: " << totalCredits << endl;
    return result;
}

// 3. Kahn's Algorithm with Cycle Detection (Dependency Resolution with Error Handling)
//   -Problem: In a complex system, you need to resolve dependencies between components.  If there's a circular dependency, the system will fail.  Detect this case.
//   -Real world: Package management (like npm, apt), where packages can depend on each other.  A circular dependency ("package A depends on B, B depends on A") is a fatal error.
//   -Code:

vector<int> topologicalSort_Kahn_CycleDetection(int numNodes, const vector<pair<int, int>>& dependencies, bool& hasCycle) {
    vector<vector<int>> adj(numNodes);
    vector<int> inDegree(numNodes, 0);
    vector<int> result;
    hasCycle = false; // Initialize cycle detection flag.

    for (const auto& dependency : dependencies) {
        int node = dependency.first;
        int dependsOn = dependency.second;
        adj[dependsOn].push_back(node);
        inDegree[node]++;
    }

    queue<int> q;
    for (int i = 0; i < numNodes; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int visitedCount = 0; // Count of visited nodes.
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        visitedCount++;

        for (int dependentNode : adj[node]) {
            inDegree[dependentNode]--;
            if (inDegree[dependentNode] == 0) {
                q.push(dependentNode);
            }
        }
    }

    if (visitedCount != numNodes) {
        hasCycle = true; // A cycle exists if not all nodes were visited.
        return {};      // Return empty vector to signal a cycle.
    }

    return result;
}

// 4. Kahn's Algorithm with Prioritization (Job Scheduling with Priorities)
//   -Problem:  You have jobs with dependencies, but also priorities.  Schedule the high-priority jobs first, while still respecting dependencies.
//   -Real-world:  Real-time operating systems (RTOS), where tasks have priorities.  The scheduler needs to run high-priority tasks as soon as their dependencies are met.
//   -Code:
struct Job {
    int id;
    int priority;
};

vector<int> topologicalSort_Kahn_Prioritized(int numJobs, const vector<pair<int, int>>& dependencies, const vector<Job>& jobs) {
    vector<vector<int>> adj(numJobs);
    vector<int> inDegree(numJobs, 0);
    vector<int> result;
    unordered_map<int, int> jobPriorities;

     for (const auto& job : jobs) {
        jobPriorities[job.id] = job.priority;
    }

    for (const auto& dependency : dependencies) {
        int job = dependency.first;
        int dependsOn = dependency.second;
        adj[dependsOn].push_back(job);
        inDegree[job]++;
    }

    // Use a priority queue (max-heap) to get highest priority job first.
    priority_queue<pair<int, int>> pq; // {priority, job_id}
    for (int i = 0; i < numJobs; ++i) {
        if (inDegree[i] == 0) {
            pq.push({jobPriorities[i], i}); // Push with priority.
        }
    }

    while (!pq.empty()) {
        int job = pq.top().second;
        pq.pop();
        result.push_back(job);

        for (int dependentJob : adj[job]) {
            inDegree[dependentJob]--;
            if (inDegree[dependentJob] == 0) {
                pq.push({jobPriorities[dependentJob], dependentJob});
            }
        }
    }

    if (result.size() != numJobs) {
        return {};
    }

    return result;
}

// 5. Kahn's Algorithm with Feedback (Interactive Task Management)
//   -Problem:  A user is performing tasks with dependencies.  Provide feedback:
//     -  Show the order in which tasks *can* be done.
//     -  If a task is blocked (due to unmet dependencies), tell the user *why*.
//   -Real-world:  Interactive task management tools, installation wizards, or guided workflows.
//   -Code:

vector<int> topologicalSort_Kahn_Feedback(int numTasks, const vector<pair<int, int>>& dependencies, vector<string>& feedbackMessages) {
    vector<vector<int>> adj(numTasks);
    vector<int> inDegree(numTasks, 0);
    vector<int> result;
    feedbackMessages.resize(numTasks); // Ensure enough space for feedback.

    for (const auto& dependency : dependencies) {
        int task = dependency.first;
        int dependsOn = dependency.second;
        adj[dependsOn].push_back(task);
        inDegree[task]++;
    }

    queue<int> q;
    for (int i = 0; i < numTasks; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
            feedbackMessages[i] = "Ready to start."; // Initial feedback.
        }
        else
        {
             feedbackMessages[i] = "Waiting for dependencies.";
        }
    }

    while (!q.empty()) {
        int task = q.front();
        q.pop();
        result.push_back(task);
        feedbackMessages[task] = "Completed.";

        for (int dependentTask : adj[task]) {
            inDegree[dependentTask]--;
            if (inDegree[dependentTask] == 0) {
                q.push(dependentTask);
                feedbackMessages[dependentTask] = "Ready to start."; // Dependency met.
            }
            else
            {
                 feedbackMessages[dependentTask] = "Waiting for dependencies.";
            }
        }
    }

    if (result.size() != numTasks) {
        return {};
    }
    return result;
}

int main() {
    // Example usage for each approach:
    cout << "1. Basic Kahn's Algorithm (Task Scheduling):" << endl;
    int numTasks1 = 6;
    vector<pair<int, int>> prerequisites1 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}};
    vector<int> result1 = topologicalSort_Kahn_Basic(numTasks1, prerequisites1);
    if (!result1.empty()) {
        for (int task : result1) {
            cout << task << " ";
        }
        cout << endl;
    } else {
        cout << "Cycle detected!" << endl;
    }
    cout << endl;

    cout << "2. Kahn's Algorithm with Custom Data (Course Scheduling with Credits):" << endl;
    int numCourses2 = 4;
    vector<pair<int, int>> prerequisites2 = {{0, 1}, {2, 1}, {3, 0}};
    vector<Course> courses2 = {{0, 3}, {1, 2}, {2, 3}, {3, 1}};
    vector<int> result2 = topologicalSort_Kahn_Credits(numCourses2, prerequisites2, courses2);
    if (!result2.empty()) {
        for (int course : result2) {
            cout << course << " ";
        }
        cout << endl;
    } else {
        cout << "Cycle detected!" << endl;
    }
    cout << endl;

    cout << "3. Kahn's Algorithm with Cycle Detection (Dependency Resolution with Error Handling):" << endl;
    int numNodes3 = 4;
    vector<pair<int, int>> dependencies3 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}; // Introduce a cycle.
    bool hasCycle3;
    vector<int> result3 = topologicalSort_Kahn_CycleDetection(numNodes3, dependencies3, hasCycle3);
    if (!result3.empty()) {
        for (int node : result3) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        if(hasCycle3)
            cout << "Cycle detected!" << endl;
        else
            cout << "No Cycle detected!" << endl;
    }
    cout << endl;

    cout << "4. Kahn's Algorithm with Prioritization (Job Scheduling with Priorities):" << endl;
    int numJobs4 = 5;
    vector<pair<int, int>> dependencies4 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
    vector<Job> jobs4 = {{0, 2}, {1, 1}, {2, 3}, {3, 1}, {4, 2}};
    vector<int> result4 = topologicalSort_Kahn_Prioritized(numJobs4, dependencies4, jobs4);
    if (!result4.empty()) {
        for (int job : result4) {
            cout << job << " ";
        }
        cout << endl;
    } else {
        cout << "Cycle detected!" << endl;
    }
    cout << endl;

    cout << "5. Kahn's Algorithm with Feedback (Interactive Task Management):" << endl;
    int numTasks5 = 6;
    vector<pair<int, int>> dependencies5 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}};
    vector<string> feedbackMessages5;
    vector<int> result5 = topologicalSort_Kahn_Feedback(numTasks5, dependencies5, feedbackMessages5);
    if (!result5.empty()) {
        for (int task : result5) {
            cout << "Task " << task << ": " << feedbackMessages5[task] << endl;
        }
        cout << endl;
    } else {
        cout << "Cycle detected!" << endl;
    }
    cout << endl;

    return 0;
}

