import java.util.PriorityQueue;
import java.util.HashMap;
import java.util.Map;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class HuffmanCoding {

    // Method to build the Huffman tree
    public static HuffmanNode buildHuffmanTree(Map<Character, Integer> frequencyMap) {
        // Create a priority queue to store the nodes
        PriorityQueue<HuffmanNode> pq = new PriorityQueue<>(new HuffmanComparator());

        // Create a leaf node for each character and add it to the priority queue
        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            pq.add(new HuffmanNode(entry.getValue(), entry.getKey()));
        }

        // If the input has only one unique character
        if (pq.size() == 1) {
            return pq.poll();
        }

        // Build the Huffman tree by merging the two nodes with the lowest frequency
        while (pq.size() > 1) {
            HuffmanNode left = pq.poll();
            HuffmanNode right = pq.poll();
            HuffmanNode parent = new HuffmanNode(left.data + right.data, left, right);
            pq.add(parent);
        }

        // The remaining node in the priority queue is the root of the Huffman tree
        return pq.poll();
    }

    // Method to generate the Huffman codes for each character (Recursive Approach) - Approach 1
    public static void generateHuffmanCodes(HuffmanNode root, String code, Map<Character, String> huffmanCodes) {
        if (root == null) {
            return;
        }
        if (root.left == null && root.right == null) {
            huffmanCodes.put(root.c, code);
            return;
        }
        generateHuffmanCodes(root.left, code + "0", huffmanCodes);
        generateHuffmanCodes(root.right, code + "1", huffmanCodes);
    }

    // Method to generate Huffman codes using iterative approach (Approach 2)
    public static Map<Character, String> generateHuffmanCodesIterative(HuffmanNode root) {
        Map<Character, String> huffmanCodes = new HashMap<>();
        if (root == null) return huffmanCodes;

        if (root.left == null && root.right == null) {
            huffmanCodes.put(root.c, "0"); // Special case for a single character
            return huffmanCodes;
        }

        List<Pair<HuffmanNode, String>> stack = new ArrayList<>();
        stack.add(new Pair<>(root, ""));

        while (!stack.isEmpty()) {
            Pair<HuffmanNode, String> current = stack.remove(stack.size() - 1); // Get and remove the last element
            HuffmanNode node = current.getKey();
            String code = current.getValue();

            if (node.left == null && node.right == null) {
                huffmanCodes.put(node.c, code);
            } else {
                if (node.right != null) {
                    stack.add(new Pair<>(node.right, code + "1"));
                }
                if (node.left != null) {
                    stack.add(new Pair<>(node.left, code + "0"));
                }
            }
        }
        return huffmanCodes;
    }

    // Helper class to create key value pair for huffman code generation
    private static class Pair<K, V> {
        private final K key;
        private final V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }
    }

    // Method to encode the text using the Huffman codes
    public static String encodeText(String text, Map<Character, String> huffmanCodes) {
        StringBuilder encodedText = new StringBuilder();
        for (char c : text.toCharArray()) {
            encodedText.append(huffmanCodes.get(c));
        }
        return encodedText.toString();
    }

    // Method to decode the text using the Huffman tree
    public static String decodeText(String encodedText, HuffmanNode root) {
        StringBuilder decodedText = new StringBuilder();
        HuffmanNode current = root;
        for (char bit : encodedText.toCharArray()) {
            if (bit == '0') {
                current = current.left;
            } else {
                current = current.right;
            }
            if (current.left == null && current.right == null) {
                decodedText.append(current.c);
                current = root;
            }
        }
        return decodedText.toString();
    }

    // Method to calculate the frequency of each character in the text
    public static Map<Character, Integer> getCharacterFrequency(String text) {
        Map<Character, Integer> frequencyMap = new HashMap<>();
        for (char c : text.toCharArray()) {
            frequencyMap.put(c, frequencyMap.getOrDefault(c, 0) + 1);
        }
        return frequencyMap;
    }

    // Method to print Huffman codes (Approach 3)
    public static void printHuffmanCodes(Map<Character, String> huffmanCodes) {
        System.out.println("Huffman Codes:");
        for (Map.Entry<Character, String> entry : huffmanCodes.entrySet()) {
            System.out.println("Character: " + entry.getKey() + ", Code: " + entry.getValue());
        }
    }

    // Method to implement Huffman coding (Driver method)
    public static void huffmanCoding(String text) {
        // Get the frequency of each character in the text
        Map<Character, Integer> frequencyMap = getCharacterFrequency(text);

        // Build the Huffman tree
        HuffmanNode root = buildHuffmanTree(frequencyMap);

        // Generate the Huffman codes
        Map<Character, String> huffmanCodes = new HashMap<>();
        generateHuffmanCodes(root, "", huffmanCodes); // Using recursion

        // Print the Huffman codes
        printHuffmanCodes(huffmanCodes);

        // Encode the text
        String encodedText = encodeText(text, huffmanCodes);
        System.out.println("Encoded Text: " + encodedText);

        // Decode the text
        String decodedText = decodeText(encodedText, root);
        System.out.println("Decoded Text: " + decodedText);
    }

    // Approach 4: Using a static inner class for node and comparator
    static class Node {
        int data;
        char c;
        Node left;
        Node right;

        Node(int data, char c) {
            this.data = data;
            this.c = c;
            this.left = null;
            this.right = null;
        }

        Node(int data, Node left, Node right) {
            this.data = data;
            this.c = '\0';
            this.left = left;
            this.right = right;
        }
    }

    static class NodeComparator implements Comparator<Node> {
        public int compare(Node x, Node y) {
            return x.data - y.data;
        }
    }

    public static void huffmanCodingStaticInnerClass(String text) {
        Map<Character, Integer> frequencyMap = getCharacterFrequency(text);
        PriorityQueue<Node> pq = new PriorityQueue<>(new NodeComparator());

        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            pq.add(new Node(entry.getValue(), entry.getKey()));
        }

        while (pq.size() > 1) {
            Node left = pq.poll();
            Node right = pq.poll();
            Node parent = new Node(left.data + right.data, left, right);
            pq.add(parent);
        }

        Node root = pq.poll();
        Map<Character, String> huffmanCodes = new HashMap<>();
        generateCodes(root, "", huffmanCodes);

        System.out.println("\nHuffman Codes (Static Inner Class):");
        for (Map.Entry<Character, String> entry : huffmanCodes.entrySet()) {
            System.out.println("Character: " + entry.getKey() + ", Code: " + entry.getValue());
        }

        String encodedText = encodeText(text, huffmanCodes);
        System.out.println("Encoded Text: " + encodedText);
        String decodedText = decodeTextFromStatic(encodedText, root);
        System.out.println("Decoded Text: " + decodedText);
    }

    static void generateCodes(Node node, String code, Map<Character, String> huffmanCodes) {
        if (node == null) return;
        if (node.left == null && node.right == null) {
            huffmanCodes.put(node.c, code);
            return;
        }
        generateCodes(node.left, code + "0", huffmanCodes);
        generateCodes(node.right, code + "1", huffmanCodes);
    }

    static String decodeTextFromStatic(String encodedText, Node root) {
        StringBuilder decodedText = new StringBuilder();
        Node current = root;
        for (char bit : encodedText.toCharArray()) {
            if (bit == '0') {
                current = current.left;
            } else {
                current = current.right;
            }
            if (current.left == null && current.right == null) {
                decodedText.append(current.c);
                current = root;
            }
        }
        return decodedText.toString();
    }

    // Approach 5:  Using a Lambda Expression for Comparator
    public static void huffmanCodingLambda(String text) {
        Map<Character, Integer> frequencyMap = getCharacterFrequency(text);

        // Use a lambda expression for the Comparator
        PriorityQueue<HuffmanNode> pq = new PriorityQueue<>((a, b) -> a.data - b.data);

        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            pq.add(new HuffmanNode(entry.getValue(), entry.getKey()));
        }

        while (pq.size() > 1) {
            HuffmanNode left = pq.poll();
            HuffmanNode right = pq.poll();
            HuffmanNode parent = new HuffmanNode(left.data + right.data, left, right);
            pq.add(parent);
        }

        HuffmanNode root = pq.poll();
        Map<Character, String> huffmanCodes = new HashMap<>();
        generateHuffmanCodes(root, "", huffmanCodes);

        System.out.println("\nHuffman Codes (Lambda):");
        for (Map.Entry<Character, String> entry : huffmanCodes.entrySet()) {
            System.out.println("Character: " + entry.getKey() + ", Code: " + entry.getValue());
        }

        String encodedText = encodeText(text, huffmanCodes);
        System.out.println("Encoded Text: " + encodedText);
        String decodedText = decodeText(encodedText, root);
        System.out.println("Decoded Text: " + decodedText);
    }

    public static void main(String[] args) {
        String text = "this is an example of huffman coding";

        // Approach 1: Basic Huffman Coding
        System.out.println("Approach 1: Basic Huffman Coding");
        huffmanCoding(text);

        // Approach 2: Iterative Huffman Code Generation
        System.out.println("\nApproach 2: Iterative Huffman Code Generation");
        Map<Character, Integer> frequencyMap = getCharacterFrequency(text);
        HuffmanNode root = buildHuffmanTree(frequencyMap);
        Map<Character, String> iterativeCodes = generateHuffmanCodesIterative(root);
        printHuffmanCodes(iterativeCodes);
        String encodedTextIterative = encodeText(text, iterativeCodes);
        System.out.println("Encoded Text: " + encodedTextIterative);
        String decodedTextIterative = decodeText(encodedTextIterative, root);
        System.out.println("Decoded Text: " + decodedTextIterative);

        // Approach 3: Printing Huffman Codes
        System.out.println("\nApproach 3: Printing Huffman Codes");
        huffmanCoding(text); // This already prints the codes, but we can modify if needed

        // Approach 4: Using static inner class
        System.out.println("\nApproach 4: Huffman Coding with Static Inner Class");
        huffmanCodingStaticInnerClass(text);

        // Approach 5: Using Lambda Expression
        System.out.println("\nApproach 5: Huffman Coding with Lambda Expression");
        huffmanCodingLambda(text);
    }
}

// Class to represent a node in the Huffman tree
class HuffmanNode {
    int data;
    char c;
    HuffmanNode left;
    HuffmanNode right;

    // Constructor for leaf node
    public HuffmanNode(int data, char c) {
        this.data = data;
        this.c = c;
        this.left = null;
        this.right = null;
    }

    // Constructor for internal node
    public HuffmanNode(int data, HuffmanNode left, HuffmanNode right) {
        this.data = data;
        this.c = '\0'; // Internal nodes don't have a character
        this.left = left;
        this.right = right;
    }
}

// Comparator for comparing nodes based on their data (frequency)
class HuffmanComparator implements Comparator<HuffmanNode> {
    public int compare(HuffmanNode x, HuffmanNode y) {
        return x.data - y.data;
    }
}
