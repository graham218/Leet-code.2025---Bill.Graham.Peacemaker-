import java.util.*;

public class HashMapSetOperations {

    public static void main(String[] args) {
        // 1. Basic HashMap Operations: Inventory Management
        System.out.println("1. Basic HashMap Operations: Inventory Management");
        inventoryManagement();

        // 2. HashMap for Counting: Word Frequency Analysis
        System.out.println("\n2. HashMap for Counting: Word Frequency Analysis");
        wordFrequencyAnalysis("The quick brown fox jumps over the lazy fox.");

        // 3. HashSet for Membership Test: User Role Management
        System.out.println("\n3. HashSet for Membership Test: User Role Management");
        userRoleManagement();

        // 4. HashMap for Caching: Simple Cache Implementation
        System.out.println("\n4. HashMap for Caching: Simple Cache Implementation");
        simpleCacheImplementation();

        // 5. Using HashMap to solve a problem: Two Sum
        System.out.println("\n5. Using HashMap to solve a problem: Two Sum");
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        int[] result = twoSum(nums, target);
        if (result != null) {
            System.out.println("Two Sum indices: [" + result[0] + ", " + result[1] + "]");
        } else {
            System.out.println("No two sum solution found.");
        }
    }

    // 1. Basic HashMap Operations: Inventory Management
    //   - Real-world application: Managing product stock in an e-commerce system.
    //   - Key operations: put (add/update stock), get (retrieve stock), remove (remove product),
    //                    containsKey (check if product exists).
    public static void inventoryManagement() {
        HashMap<String, Integer> inventory = new HashMap<>();

        // Add initial stock
        inventory.put("Laptop", 100);
        inventory.put("Mouse", 200);
        inventory.put("Keyboard", 150);
        System.out.println("Initial Inventory: " + inventory);

        // Update stock
        inventory.put("Laptop", 120); // Increase laptop stock
        System.out.println("Updated Laptop Stock: " + inventory);

        // Retrieve stock
        int mouseStock = inventory.get("Mouse");
        System.out.println("Mouse Stock: " + mouseStock);

        // Check if a product exists
        if (inventory.containsKey("Keyboard")) {
            System.out.println("Keyboard exists in inventory.");
        }

        // Remove a product
        inventory.remove("Mouse");
        System.out.println("Inventory after removing Mouse: " + inventory);

        //Check for non-existent product
        if(!inventory.containsKey("Monitor")){
            System.out.println("Monitor does not exist in inventory");
        }
        // Use getOrDefault
        int monitorStock = inventory.getOrDefault("Monitor", 0);  //returns 0 if "Monitor" key does not exist
        System.out.println("Monitor Stock: " + monitorStock);
    }

    // 2. HashMap for Counting: Word Frequency Analysis
    //   - Real-world application: Analyzing text data (e.g., log files, documents) to count occurrences of words or events.
    //   - Key idea: Use words as keys and their frequencies as values.
    public static void wordFrequencyAnalysis(String text) {
        HashMap<String, Integer> wordFrequencies = new HashMap<>();

        // Split the text into words
        String[] words = text.toLowerCase().split("\\s+"); // Use lowercase for case-insensitivity

        // Count word frequencies
        for (String word : words) {
            // If the word is already in the map, increment its count; otherwise, add it with a count of 1.
            wordFrequencies.put(word, wordFrequencies.getOrDefault(word, 0) + 1);
        }

        // Print word frequencies
        System.out.println("Word Frequencies: " + wordFrequencies);
    }

    // 3. HashSet for Membership Test: User Role Management
    //   - Real-world application: Managing user permissions and roles in a web application.
    //   - Key idea: Use a HashSet to store roles for each user and efficiently check if a user has a specific role.
    public static void userRoleManagement() {
        HashMap<String, HashSet<String>> userRoles = new HashMap<>();

        // Add user roles
        HashSet<String> johnRoles = new HashSet<>();
        johnRoles.add("admin");
        johnRoles.add("editor");
        userRoles.put("john", johnRoles);

        HashSet<String> janeRoles = new HashSet<>();
        janeRoles.add("editor");
        janeRoles.add("viewer");
        userRoles.put("jane", janeRoles);

        // Check user roles
        String userToCheck = "john";
        String roleToCheck = "admin";
        if (userRoles.containsKey(userToCheck) && userRoles.get(userToCheck).contains(roleToCheck)) {
            System.out.println(userToCheck + " has the role: " + roleToCheck);
        } else {
            System.out.println(userToCheck + " does not have the role: " + roleToCheck);
        }

        userToCheck = "jane";
        roleToCheck = "admin";
        if (userRoles.containsKey(userToCheck) && userRoles.get(userToCheck).contains(roleToCheck)) {
            System.out.println(userToCheck + " has the role: " + roleToCheck);
        } else {
            System.out.println(userToCheck + " does not have the role: " + roleToCheck);
        }
    }

    // 4. HashMap for Caching: Simple Cache Implementation
    //   - Real-world application: Implementing a simple cache to store frequently accessed data.
    //   - Key idea: Use a HashMap to store data with keys, providing fast lookups.  A simple example,
    //                more robust caches use techniques like LRU eviction.
    public static void simpleCacheImplementation() {
        HashMap<String, String> cache = new HashMap<>();

        // Add data to cache
        cache.put("user1", "John Doe");
        cache.put("user2", "Jane Smith");
        System.out.println("Cache: " + cache);

        // Retrieve data from cache
        String user1Data = cache.get("user1");
        if (user1Data != null) {
            System.out.println("Retrieved user1 data from cache: " + user1Data);
        } else {
            System.out.println("user1 data not found in cache.  Fetching from database...");
            // Simulate fetching from a database
            String user1DataFromDB = "John Doe"; // Assume this is fetched from DB
            cache.put("user1", user1DataFromDB); // Store in cache
            System.out.println("Fetched and stored user1 data in cache: " + user1DataFromDB);
        }

        // Check for non-existent data
        String user3Data = cache.get("user3");
        if (user3Data != null) {
            System.out.println("Retrieved user3 data from cache: " + user3Data);
        } else {
            System.out.println("user3 data not found in cache.");
        }
    }

    // 5. Using HashMap to solve a problem: Two Sum
    //   - Problem: Given an array of integers, find two numbers that add up to a specific target.
    //   - Solution: Use a HashMap to store each number and its index.  For each number, check if
    //               the complement (target - number) exists in the HashMap.
    public static int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> numMap = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (numMap.containsKey(complement)) {
                return new int[]{numMap.get(complement), i};
            }
            numMap.put(nums[i], i);
        }
        return null; // No solution found
    }
}

