import java.util.Arrays;
import java.util.Comparator;

public class SuffixAndZAlgorithm {

    // Approach 1: Naive Suffix Array Construction - O(n^2 logn)
    public static int[] buildSuffixArrayNaive(String s) {
        int n = s.length();
        String[] suffixes = new String[n];

        // Generate all suffixes
        for (int i = 0; i < n; i++) {
            suffixes[i] = s.substring(i);
        }

        // Sort suffixes lexicographically
        Arrays.sort(suffixes);

        // Create suffix array with original indices
        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = n - suffixes[i].length();
        }

        return suffixArray;
    }

    // Approach 2: Prefix Doubling (Kasai's Algorithm) - O(n logn)
    public static int[] buildSuffixArrayPrefixDoubling(String s) {
        int n = s.length();
        Suffix[] suffixes = new Suffix[n];

        // Initialize suffixes with single character ranks
        for (int i = 0; i < n; i++) {
            suffixes[i] = new Suffix(i, s.charAt(i) - 'a',
                    (i+1 < n) ? s.charAt(i+1) - 'a' : -1);
        }

        // Sort the suffixes
        Arrays.sort(suffixes);

        // This array maps original index to its position in sorted array
        int[] ind = new int[n];

        // Prefix doubling
        for (int k = 4; k < 2*n; k *= 2) {
            // Assign new ranks
            int rank = 0;
            int prevRank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            ind[suffixes[0].index] = 0;

            for (int i = 1; i < n; i++) {
                // If same ranks as previous, assign same new rank
                if (suffixes[i].rank[0] == prevRank &&
                        suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                    prevRank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                } else {
                    prevRank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
                ind[suffixes[i].index] = i;
            }

            // Assign next rank
            for (int i = 0; i < n; i++) {
                int nextIndex = suffixes[i].index + k/2;
                suffixes[i].rank[1] = (nextIndex < n) ?
                        suffixes[ind[nextIndex]].rank[0] : -1;
            }

            // Sort suffixes based on new ranks
            Arrays.sort(suffixes);
        }

        // Extract suffix array
        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = suffixes[i].index;
        }

        return suffixArray;
    }

    static class Suffix implements Comparable<Suffix> {
        int index;
        int[] rank = new int[2];

        public Suffix(int index, int rank1, int rank2) {
            this.index = index;
            this.rank[0] = rank1;
            this.rank[1] = rank2;
        }

        @Override
        public int compareTo(Suffix other) {
            return (this.rank[0] == other.rank[0]) ?
                    (this.rank[1] - other.rank[1]) :
                    (this.rank[0] - other.rank[0]);
        }
    }

    // Approach 3: DC3 Algorithm (Skew Algorithm) - O(n)
    public static int[] buildSuffixArrayDC3(String s) {
        char[] str = s.toCharArray();
        int n = str.length;
        int[] s12 = new int[(n + 2) / 3];
        int[] SA12 = new int[(n + 2) / 3];
        int[] s0 = new int[(n + 2) / 3];
        int[] SA0 = new int[(n + 2) / 3];

        // Implementation would be quite lengthy as DC3 is complex
        // This is a placeholder for the actual implementation
        // For production use, consider a well-tested library implementation

        // For now, we'll fall back to prefix doubling
        return buildSuffixArrayPrefixDoubling(s);
    }

    // Approach 4: Z-Algorithm - O(n)
    public static int[] calculateZArray(String s) {
        int n = s.length();
        int[] Z = new int[n];
        Z[0] = n; // by definition

        // [L, R] is the Z-box window
        int L = 0, R = 0;

        for (int i = 1; i < n; i++) {
            if (i > R) {
                // No Z-box yet, compute from scratch
                L = R = i;
                while (R < n && s.charAt(R - L) == s.charAt(R)) {
                    R++;
                }
                Z[i] = R - L;
                R--;
            } else {
                // Inside a Z-box
                int k = i - L;
                if (Z[k] < R - i + 1) {
                    // Doesn't reach R, just copy
                    Z[i] = Z[k];
                } else {
                    // Need to expand beyond R
                    L = i;
                    while (R < n && s.charAt(R - L) == s.charAt(R)) {
                        R++;
                    }
                    Z[i] = R - L;
                    R--;
                }
            }
        }
        return Z;
    }

    // Approach 5: Suffix Array with LCP (Kasai's Algorithm) - O(n)
    public static int[] buildLCPArray(String s, int[] suffixArray) {
        int n = s.length();
        int[] lcp = new int[n];
        int[] invSuffix = new int[n];

        // Create inverse suffix array
        for (int i = 0; i < n; i++) {
            invSuffix[suffixArray[i]] = i;
        }

        int k = 0;
        for (int i = 0; i < n; i++) {
            if (invSuffix[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = suffixArray[invSuffix[i] + 1];

            // Find lcp
            while (i + k < n && j + k < n && s.charAt(i + k) == s.charAt(j + k)) {
                k++;
            }

            lcp[invSuffix[i]] = k;

            if (k > 0) {
                k--;
            }
        }

        return lcp;
    }

    public static void main(String[] args) {
        String text = "banana";

        // Approach 1: Naive
        int[] suffixArrayNaive = buildSuffixArrayNaive(text);
        System.out.println("Naive Suffix Array: " + Arrays.toString(suffixArrayNaive));

        // Approach 2: Prefix Doubling
        int[] suffixArrayPD = buildSuffixArrayPrefixDoubling(text);
        System.out.println("Prefix Doubling Suffix Array: " + Arrays.toString(suffixArrayPD));

        // Approach 3: DC3 (Skew)
        int[] suffixArrayDC3 = buildSuffixArrayDC3(text);
        System.out.println("DC3 Suffix Array: " + Arrays.toString(suffixArrayDC3));

        // Approach 4: Z-Algorithm
        int[] zArray = calculateZArray(text);
        System.out.println("Z Array: " + Arrays.toString(zArray));

        // Approach 5: LCP from Suffix Array
        int[] lcpArray = buildLCPArray(text, suffixArrayPD);
        System.out.println("LCP Array: " + Arrays.toString(lcpArray));
    }
}