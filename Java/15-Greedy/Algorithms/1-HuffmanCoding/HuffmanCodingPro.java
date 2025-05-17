// Node class for Huffman tree
class HuffmanNode {
    int frequency;
    char character;
    HuffmanNode left;
    HuffmanNode right;

    HuffmanNode(char character, int frequency) {
        this.character = character;
        this.frequency = frequency;
        this.left = null;
        this.right = null;
    }

    HuffmanNode(int frequency, HuffmanNode left, HuffmanNode right) {
        this.character = '\0'; // internal node
        this.frequency = frequency;
        this.left = left;
        this.right = right;
    }
}

// Comparator for PriorityQueue
class FrequencyComparator implements Comparator<HuffmanNode> {
    public int compare(HuffmanNode n1, HuffmanNode n2) {
        return Integer.compare(n1.frequency, n2.frequency);
    }
}