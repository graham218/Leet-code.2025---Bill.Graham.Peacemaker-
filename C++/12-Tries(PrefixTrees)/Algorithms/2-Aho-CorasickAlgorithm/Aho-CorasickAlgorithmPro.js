class AhoCorasickNode {
    constructor() {
        this.children = {};
        this.fail = null;
        this.output = [];
        this.endOfWord = false;
    }
}

// Approach 1: Basic Aho-Corasick Implementation
class BasicAhoCorasick {
    constructor() {
        this.root = new AhoCorasickNode();
    }

    addPattern(pattern) {
        let node = this.root;
        for (const char of pattern) {
            if (!node.children[char]) {
                node.children[char] = new AhoCorasickNode();
            }
            node = node.children[char];
        }
        node.endOfWord = true;
        node.output.push(pattern);
    }

    buildFailureLinks() {
        const queue = [];
        this.root.fail = this.root;

        // First level nodes fail to root
        for (const key in this.root.children) {
            const child = this.root.children[key];
            child.fail = this.root;
            queue.push(child);
        }

        // BFS to set failure links
        while (queue.length > 0) {
            const current = queue.shift();

            for (const key in current.children) {
                const child = current.children[key];
                let failNode = current.fail;

                while (failNode !== this.root && !failNode.children[key]) {
                    failNode = failNode.fail;
                }

                if (failNode.children[key]) {
                    child.fail = failNode.children[key];
                } else {
                    child.fail = this.root;
                }

                child.output = [...child.output, ...child.fail.output];
                queue.push(child);
            }
        }
    }

    search(text) {
        const results = {};
        let current = this.root;

        for (let i = 0; i < text.length; i++) {
            const char = text[i];

            while (current !== this.root && !current.children[char]) {
                current = current.fail;
            }

            if (current.children[char]) {
                current = current.children[char];
            }

            if (current.output.length > 0) {
                for (const pattern of current.output) {
                    if (!results[pattern]) {
                        results[pattern] = [];
                    }
                    results[pattern].push(i - pattern.length + 1);
                }
            }
        }

        return results;
    }
}

// Approach 2: Aho-Corasick with Case Insensitivity
class CaseInsensitiveAhoCorasick extends BasicAhoCorasick {
    addPattern(pattern) {
        super.addPattern(pattern.toLowerCase());
    }

    search(text) {
        return super.search(text.toLowerCase());
    }
}

// Approach 3: Aho-Corasick with Wildcard Support (single character)
class WildcardAhoCorasick extends BasicAhoCorasick {
    constructor(wildcardChar = '.') {
        super();
        this.wildcardChar = wildcardChar;
    }

    addPattern(pattern) {
        const addPatternWithWildcard = (node, remainingPattern, originalPattern) => {
            if (remainingPattern.length === 0) {
                node.endOfWord = true;
                node.output.push(originalPattern);
                return;
            }

            const char = remainingPattern[0];
            const remaining = remainingPattern.slice(1);

            if (char === this.wildcardChar) {
                // For wildcard, add all possible children
                for (const key in node.children) {
                    addPatternWithWildcard(node.children[key], remaining, originalPattern);
                }
                // And also add a new child if it doesn't exist
                const wildcardNode = new AhoCorasickNode();
                node.children[this.wildcardChar] = wildcardNode;
                addPatternWithWildcard(wildcardNode, remaining, originalPattern);
            } else {
                if (!node.children[char]) {
                    node.children[char] = new AhoCorasickNode();
                }
                addPatternWithWildcard(node.children[char], remaining, originalPattern);
            }
        };

        addPatternWithWildcard(this.root, pattern, pattern);
    }
}

// Approach 4: Aho-Corasick with Unicode Support
class UnicodeAhoCorasick extends BasicAhoCorasick {
    addPattern(pattern) {
        // Convert the pattern to an array of code points to handle Unicode properly
        const codePoints = Array.from(pattern).map(c => c.codePointAt(0));
        let node = this.root;

        for (const code of codePoints) {
            if (!node.children[code]) {
                node.children[code] = new AhoCorasickNode();
            }
            node = node.children[code];
        }

        node.endOfWord = true;
        node.output.push(pattern);
    }

    search(text) {
        const results = {};
        let current = this.root;
        const codePoints = Array.from(text).map(c => c.codePointAt(0));

        for (let i = 0; i < codePoints.length; i++) {
            const code = codePoints[i];

            while (current !== this.root && !current.children[code]) {
                current = current.fail;
            }

            if (current.children[code]) {
                current = current.children[code];
            }

            if (current.output.length > 0) {
                for (const pattern of current.output) {
                    if (!results[pattern]) {
                        results[pattern] = [];
                    }
                    results[pattern].push(i - Array.from(pattern).length + 1);
                }
            }
        }

        return results;
    }
}

// Approach 5: Aho-Corasick with Replacement Functionality
class ReplacingAhoCorasick extends BasicAhoCorasick {
    constructor(replacements = {}) {
        super();
        this.replacements = replacements;
    }

    addPattern(pattern, replacement) {
        super.addPattern(pattern);
        if (replacement) {
            this.replacements[pattern] = replacement;
        }
    }

    replace(text) {
        const matches = this.search(text);
        const patterns = Object.keys(matches).sort((a, b) => b.length - a.length);
        let result = text;

        for (const pattern of patterns) {
            const replacement = this.replacements[pattern] || '*'.repeat(pattern.length);
            const positions = matches[pattern];

            // We need to replace from the end to avoid position shifting issues
            const sortedPositions = [...positions].sort((a, b) => b - a);

            for (const pos of sortedPositions) {
                result = result.substring(0, pos) + replacement + result.substring(pos + pattern.length);
            }
        }

        return result;
    }
}

// Demo function to test all implementations
function demonstrateAhoCorasick() {
    console.log("=== Basic Aho-Corasick Implementation ===");
    const basicAC = new BasicAhoCorasick();
    basicAC.addPattern("he");
    basicAC.addPattern("she");
    basicAC.addPattern("his");
    basicAC.addPattern("hers");
    basicAC.buildFailureLinks();

    const text1 = "ushers";
    console.log(`Searching in "${text1}":`, basicAC.search(text1));

    console.log("\n=== Case Insensitive Aho-Corasick ===");
    const caseInsensitiveAC = new CaseInsensitiveAhoCorasick();
    caseInsensitiveAC.addPattern("HE");
    caseInsensitiveAC.addPattern("She");
    caseInsensitiveAC.buildFailureLinks();

    const text2 = "UShErs";
    console.log(`Searching in "${text2}":`, caseInsensitiveAC.search(text2));

    console.log("\n=== Wildcard Aho-Corasick ===");
    const wildcardAC = new WildcardAhoCorasick();
    wildcardAC.addPattern("h.");
    wildcardAC.addPattern("s.e");
    wildcardAC.buildFailureLinks();

    const text3 = "ushers";
    console.log(`Searching in "${text3}":`, wildcardAC.search(text3));

    console.log("\n=== Unicode Aho-Corasick ===");
    const unicodeAC = new UnicodeAhoCorasick();
    unicodeAC.addPattern("café");
    unicodeAC.addPattern("你好");
    unicodeAC.buildFailureLinks();

    const text4 = "I love café and 你好吗?";
    console.log(`Searching in "${text4}":`, unicodeAC.search(text4));

    console.log("\n=== Replacing Aho-Corasick ===");
    const replacingAC = new ReplacingAhoCorasick({
        "he": "HE",
        "she": "SHE",
        "hers": "HERS"
    });
    replacingAC.addPattern("he");
    replacingAC.addPattern("she");
    replacingAC.addPattern("his");
    replacingAC.addPattern("hers");
    replacingAC.buildFailureLinks();

    const text5 = "ushers and his hat";
    console.log(`Original: "${text5}"`);
    console.log(`Replaced: "${replacingAC.replace(text5)}"`);
}

// Run the demonstration
demonstrateAhoCorasick();