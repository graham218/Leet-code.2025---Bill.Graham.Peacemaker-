import java.util.*;

// Main class implementing Bellman-Ford algorithm
public class BellmanFord {

    private int vertices;
    private List<Edge> edges;

    public BellmanFord(int vertices) {
        this.vertices = vertices;
        this.edges = new ArrayList<>();
    }

    public void addEdge(int source, int destination, int weight) {
        edges.add(new Edge(source, destination, weight));
    }

    // Core Bellman-Ford algorithm
    public void bellmanFord(int source) {
        int[] distance = new int[vertices];
        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[source] = 0;

        // Relax all edges |V| - 1 times
        for (int i = 1; i < vertices; i++) {
            for (Edge edge : edges) {
                if (distance[edge.source] != Integer.MAX_VALUE &&
                        distance[edge.source] + edge.weight < distance[edge.destination]) {
                    distance[edge.destination] = distance[edge.source] + edge.weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (Edge edge : edges) {
            if (distance[edge.source] != Integer.MAX_VALUE &&
                    distance[edge.source] + edge.weight < distance[edge.destination]) {
                System.out.println("Graph contains negative weight cycle");
                return;
            }
        }

        printSolution(distance);
    }

    private void printSolution(int[] distance) {
        System.out.println("Vertex Distance from Source");
        for (int i = 0; i < vertices; i++) {
            System.out.println(i + "\t\t" + distance[i]);
        }
    }

    // === Real-World Implementations ===

    // 1. Network Routing Optimization
    // Used to find the least-cost path for data packets.
    public static void networkRoutingExample() {
        BellmanFord graph = new BellmanFord(5);
        graph.addEdge(0, 1, 6);
        graph.addEdge(0, 2, 7);
        graph.addEdge(1, 3, 5);
        graph.addEdge(1, 2, 8);
        graph.addEdge(1, 4, -4);
        graph.addEdge(2, 3, -3);
        graph.addEdge(2, 4, 9);
        graph.addEdge(3, 1, -2);
        graph.addEdge(4, 0, 2);
        graph.addEdge(4, 3, 7);
        graph.bellmanFord(0);
    }

    // 2. Currency Arbitrage Detection
    // Used in finance to detect profit opportunities through exchange rates.
    public static void currencyArbitrageExample() {
        BellmanFord graph = new BellmanFord(3);
        // Log of exchange rates is used as weight (negated for detection)
        graph.addEdge(0, 1, -((int)(Math.log(0.9) * 1000)));
        graph.addEdge(1, 2, -((int)(Math.log(1.1) * 1000)));
        graph.addEdge(2, 0, -((int)(Math.log(1.2) * 1000)));
        graph.bellmanFord(0);
    }

    // 3. Social Network Influence Scoring
    // Determines shortest influence spread paths from an influencer node.
    public static void socialInfluenceExample() {
        BellmanFord graph = new BellmanFord(4);
        graph.addEdge(0, 1, 1);
        graph.addEdge(1, 2, 1);
        graph.addEdge(2, 3, 1);
        graph.addEdge(0, 3, 10);
        graph.bellmanFord(0);
    }

    // 4. Road Traffic Analysis System
    // Used to determine shortest time path between locations considering traffic.
    public static void roadTrafficExample() {
        BellmanFord graph = new BellmanFord(5);
        graph.addEdge(0, 1, 2);
        graph.addEdge(1, 2, 3);
        graph.addEdge(2, 3, 2);
        graph.addEdge(3, 4, 2);
        graph.addEdge(0, 4, 10);
        graph.bellmanFord(0);
    }

    // 5. Delivery Logistics Optimization
    // Determines optimal delivery routes under cost constraints.
    public static void logisticsOptimizationExample() {
        BellmanFord graph = new BellmanFord(6);
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 2, 2);
        graph.addEdge(1, 3, 5);
        graph.addEdge(2, 3, 8);
        graph.addEdge(3, 4, 6);
        graph.addEdge(4, 5, 3);
        graph.bellmanFord(0);
    }

    public static void main(String[] args) {
        System.out.println("--- Network Routing Optimization ---");
        networkRoutingExample();

        System.out.println("\n--- Currency Arbitrage Detection ---");
        currencyArbitrageExample();

        System.out.println("\n--- Social Influence Scoring ---");
        socialInfluenceExample();

        System.out.println("\n--- Road Traffic Analysis ---");
        roadTrafficExample();

        System.out.println("\n--- Delivery Logistics Optimization ---");
        logisticsOptimizationExample();
    }
}

// A class to represent a weighted edge in the graph
class Edge {
    int source, destination, weight;

    public Edge(int source, int destination, int weight) {
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }
}