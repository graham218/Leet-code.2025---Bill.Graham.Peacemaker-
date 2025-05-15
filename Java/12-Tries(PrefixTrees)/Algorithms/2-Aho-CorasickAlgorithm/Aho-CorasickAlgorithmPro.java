/*
 * Java Implementation of Aho-Corasick Algorithm using Trie (Prefix Tree)
 * This file includes 5 different approaches applied in real-world scenarios.
 * Each approach builds on the basic Trie structure and integrates Aho-Corasick features for pattern matching.
 */

import java.util.*;

// Main Aho-Corasick Automaton class
class AhoCorasick {
    private final TrieNode root;

    public AhoCorasick() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    public void insert(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            node = node.children.computeIfAbsent(c, k -> new TrieNode());
        }
        node.output.add(word);
    }

    // Build failure links to prepare for efficient search
    public void buildFailureLinks() {
        Queue<TrieNode> queue = new LinkedList<>();
        root.failureLink = root;
        queue.add(root);

        while (!queue.isEmpty()) {
            TrieNode current = queue.poll();

            for (Map.Entry<Character, TrieNode> entry : current.children.entrySet()) {
                char c = entry.getKey();
                TrieNode child = entry.getValue();

                TrieNode failure = current.failureLink;
                while (failure != root && !failure.children.containsKey(c)) {
                    failure = failure.failureLink;
                }
                if (failure.children.containsKey(c) && failure.children.get(c) != child) {
                    failure = failure.children.get(c);
                }
                child.failureLink = failure;
                child.output.addAll(failure.output);
                queue.add(child);
            }
        }
    }

    // Search for pattern matches in the given text
    public Map<String, List<Integer>> search(String text) {
        TrieNode node = root;
        Map<String, List<Integer>> result = new HashMap<>();

        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            while (node != root && !node.children.containsKey(c)) {
                node = node.failureLink;
            }
            if (node.children.containsKey(c)) {
                node = node.children.get(c);
            }
            for (String match : node.output) {
                result.computeIfAbsent(match, k -> new ArrayList<>()).add(i - match.length() + 1);
            }
        }
        return result;
    }

    // Approach 1: Spam Filtering in Emails
    public static void spamFilterExample() {
        AhoCorasick ac = new AhoCorasick();
        String[] spamWords = {"win", "free", "money", "credit card"};
        for (String word : spamWords) ac.insert(word);
        ac.buildFailureLinks();
        String emailText = "You have won free money on your credit card!";
        System.out.println("Spam Filter Matches: " + ac.search(emailText));
    }

    // Approach 2: Intrusion Detection Systems (IDS)
    public static void intrusionDetectionExample() {
        AhoCorasick ac = new AhoCorasick();
        String[] attackSignatures = {"malware", "virus", "trojan", "exploit"};
        for (String sig : attackSignatures) ac.insert(sig);
        ac.buildFailureLinks();
        String networkPacket = "This contains a known trojan signature";
        System.out.println("IDS Matches: " + ac.search(networkPacket));
    }

    // Approach 3: Keyword-based Content Moderation
    public static void contentModerationExample() {
        AhoCorasick ac = new AhoCorasick();
        String[] badWords = {"hate", "kill", "abuse"};
        for (String word : badWords) ac.insert(word);
        ac.buildFailureLinks();
        String post = "We must stop abuse and hate in society.";
        System.out.println("Content Moderation Matches: " + ac.search(post));
    }

    // Approach 4: Search Suggestions in Typing
    public static void searchSuggestionsExample() {
        AhoCorasick ac = new AhoCorasick();
        String[] dictionary = {"search", "suggestion", "engine", "query"};
        for (String word : dictionary) ac.insert(word);
        ac.buildFailureLinks();
        String input = "This is a search engine that gives suggestion";
        System.out.println("Search Suggestion Matches: " + ac.search(input));
    }

    // Approach 5: Log Monitoring for Alerts
    public static void logMonitoringExample() {
        AhoCorasick ac = new AhoCorasick();
        String[] alertKeywords = {"ERROR", "FAIL", "CRITICAL"};
        for (String keyword : alertKeywords) ac.insert(keyword);
        ac.buildFailureLinks();
        String logs = "2025-05-15 10:00:00 [ERROR] System failed to start. CRITICAL process missing.";
        System.out.println("Log Alert Matches: " + ac.search(logs));
    }

    // Main method to run all examples
    public static void main(String[] args) {
        spamFilterExample();
        intrusionDetectionExample();
        contentModerationExample();
        searchSuggestionsExample();
        logMonitoringExample();
    }
}

// Node class representing a single character in the Trie
class TrieNode {
    Map<Character, TrieNode> children = new HashMap<>();
    TrieNode failureLink;
    List<String> output = new ArrayList<>();
}