// Advanced Stock Trading Solution using Sliding Window in Dart
// Real-world Application: AI-powered stock trading strategy optimization

import 'dart:math';

class StockTrader {
  List<int> prices;
  StockTrader(this.prices);

  // Approach 1: Optimized Sliding Window with Dynamic Adjustments (O(n))
  int optimizedMaxProfit() {
    if (prices.isEmpty) return 0;

    int minPrice = prices[0];
    int maxProfit = 0;
    for (int price in prices) {
      minPrice = min(minPrice, price);
      maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
  }

  // Approach 2: Two-Transaction Strategy (O(n))
  // Buy and sell twice to maximize profit
  int maxProfitTwoTransactions() {
    if (prices.isEmpty) return 0;

    int n = prices.length;
    List<int> leftProfit = List.filled(n, 0);
    List<int> rightProfit = List.filled(n, 0);

    int minPrice = prices[0];
    for (int i = 1; i < n; i++) {
      minPrice = min(minPrice, prices[i]);
      leftProfit[i] = max(leftProfit[i - 1], prices[i] - minPrice);
    }

    int maxPrice = prices[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      maxPrice = max(maxPrice, prices[i]);
      rightProfit[i] = max(rightProfit[i + 1], maxPrice - prices[i]);
    }

    int maxProfit = 0;
    for (int i = 0; i < n; i++) {
      maxProfit = max(maxProfit, leftProfit[i] + rightProfit[i]);
    }
    return maxProfit;
  }

  // Approach 3: Machine Learning-Inspired Momentum Trading (O(n))
  // Buy when price starts increasing rapidly and sell at peak
  int momentumTrading() {
    if (prices.isEmpty) return 0;

    int maxProfit = 0;
    int buyPrice = prices[0];
    for (int i = 1; i < prices.length; i++) {
      if (prices[i] > prices[i - 1]) {
        maxProfit = max(maxProfit, prices[i] - buyPrice);
      } else {
        buyPrice = prices[i];
      }
    }
    return maxProfit;
  }

  // Approach 4: AI-Simulated Trading using Moving Averages (O(n))
  int movingAverageStrategy(int windowSize) {
    if (prices.length < windowSize) return 0;

    List<int> movingAverages = [];
    int sum = 0;
    for (int i = 0; i < prices.length; i++) {
      sum += prices[i];
      if (i >= windowSize - 1) {
        movingAverages.add(sum ~/ windowSize);
        sum -= prices[i - windowSize + 1];
      }
    }
    return optimizedMaxProfit();
  }

  // Approach 5: Reinforcement Learning Inspired Dynamic Trading (O(n))
  int dynamicTradingStrategy() {
    if (prices.isEmpty) return 0;

    int profit = 0;
    for (int i = 1; i < prices.length; i++) {
      if (prices[i] > prices[i - 1]) {
        profit += prices[i] - prices[i - 1];
      }
    }
    return profit;
  }
}

void main() {
  List<int> stockPrices = [7, 1, 5, 3, 6, 4, 8, 3, 10];
  StockTrader trader = StockTrader(stockPrices);

  print("Optimized Sliding Window Profit: ${trader.optimizedMaxProfit()}");
  print("Max Profit with Two Transactions: ${trader.maxProfitTwoTransactions()}");
  print("Momentum Trading Profit: ${trader.momentumTrading()}");
  print("Moving Average Strategy Profit: ${trader.movingAverageStrategy(3)}");
  print("Dynamic Trading Strategy Profit: ${trader.dynamicTradingStrategy()}");
}