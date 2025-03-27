'''
Advanced Sliding Window: Best Time to Buy and Sell Stock - Real-World Implementations

Problem Statement:
Implement real-world use cases for stock trading using dynamic sliding window techniques.
'''

# 1. Moving Average Crossover Strategy (O(n))
def moving_average_crossover(prices, short_window=5, long_window=20):
    """
    Implements a moving average crossover strategy.  It calculates short-term and long-term moving averages
    and generates buy/sell signals when the short-term average crosses the long-term average.
    This strategy helps identify trend changes.

    Args:
        prices (list): A list of stock prices for each day.
        short_window (int): The time window for the short-term moving average (e.g., 5 days).
        long_window (int): The time window for the long-term moving average (e.g., 20 days).

    Returns:
        list: A list of trading signals ("BUY", "SELL", or "HOLD") for each day, starting from the long_window day.
    """
    signals = []  # Initialize a list to store trading signals.
    short_ma, long_ma = [], []  # Initialize lists to store short-term and long-term moving averages.

    for i in range(len(prices)):
        # Calculate the short-term moving average.  The window expands until it reaches short_window.
        short_ma.append(sum(prices[max(0, i - short_window + 1):i + 1]) / min(i + 1, short_window))
        # Calculate the long-term moving average.  The window expands until it reaches long_window.
        long_ma.append(sum(prices[max(0, i - long_window + 1):i + 1]) / min(i + 1, long_window))

        # Generate trading signals:
        # A "BUY" signal is generated when the short-term MA crosses above the long-term MA.
        # A "SELL" signal is generated when the short-term MA crosses below the long-term MA.
        # "HOLD" is used when there is no crossover.
        if i >= long_window and short_ma[-1] > long_ma[-1]:
            signals.append("BUY")
        elif i >= long_window and short_ma[-1] < long_ma[-1]:
            signals.append("SELL")
        else:
            signals.append("HOLD")
    return signals

# 2. RSI-Based Trading Strategy (O(n))
def rsi_trading_strategy(prices, window=14, overbought=70, oversold=30):
    """
    Implements a Relative Strength Index (RSI) based trading strategy.  RSI measures the magnitude of recent price changes
    to evaluate overbought or oversold conditions in the price of a stock.

    Args:
        prices (list): A list of stock prices for each day.
        window (int): The time window for calculating RSI (e.g., 14 days).
        overbought (int): The RSI level above which the stock is considered overbought (e.g., 70).
        oversold (int): The RSI level below which the stock is considered oversold (e.g., 30).

    Returns:
        list: A list of trading signals ("BUY", "SELL", or "HOLD") based on RSI values.
    """
    gains, losses, rsi = [], [], []  # Initialize lists to store gains, losses, and RSI values.
    for i in range(1, len(prices)):
        # Calculate daily price changes.
        diff = prices[i] - prices[i - 1]
        gains.append(max(0, diff))  # Store gains (positive changes).
        losses.append(max(0, -diff))  # Store losses (negative changes).

        # Calculate RSI:
        if i >= window:
            # Calculate average gain and average loss over the specified window.
            avg_gain = sum(gains[-window:]) / window
            avg_loss = sum(losses[-window:]) / window
            # Calculate the Relative Strength (RS).
            rs = avg_gain / avg_loss if avg_loss != 0 else float('inf')
            # Calculate the RSI.
            rsi.append(100 - (100 / (1 + rs)))
        else:
            rsi.append(50)  # Neutral signal for the initial period before enough data is available.

    # Generate trading signals based on RSI:
    # "BUY" when RSI is below oversold level.
    # "SELL" when RSI is above overbought level.
    # "HOLD" otherwise.
    return ["BUY" if val < oversold else "SELL" if val > overbought else "HOLD" for val in rsi]

# 3. Volume-Weighted Average Price (VWAP) (O(n))
def vwap(prices, volumes):
    """
    Calculates the Volume-Weighted Average Price (VWAP).  VWAP is a trading benchmark that measures the average price
    a stock traded at over a given period, weighted by volume.  It's used to assess the efficiency of trades.

    Args:
        prices (list): A list of stock prices for each transaction period.
        volumes (list): A list of trading volumes for each transaction period, corresponding to the prices.

    Returns:
        list: A list of VWAP values calculated cumulatively for each period.
    """
    cum_price_volume, cum_volume = 0, 0  # Initialize cumulative price-volume and cumulative volume.
    vwap_values = []  # Initialize a list to store VWAP values.
    for i in range(len(prices)):
        # Calculate the cumulative price-volume.
        cum_price_volume += prices[i] * volumes[i]
        # Calculate the cumulative volume.
        cum_volume += volumes[i]
        # Calculate and append the VWAP for the current period.
        vwap_values.append(cum_price_volume / cum_volume)
    return vwap_values

# 4. Order Book Liquidity Analysis (O(n))
def liquidity_analysis(order_book):
    """
    Analyzes the liquidity of a stock by calculating the bid-ask spread from the order book.
    A narrow bid-ask spread indicates high liquidity, meaning that the asset can be bought and sold quickly
    without causing a significant change in price.

    Args:
        order_book (list): A list of order book snapshots.  Each snapshot is a dictionary with "bids" and "asks" lists,
                           containing the prices at which buyers want to buy and sellers want to sell.
                           e.g., [{"bids": [98, 99, 100], "asks": [101, 102, 103]}]

    Returns:
        list: A list of bid-ask spreads for each order book snapshot.
    """
    bid_ask_spread = []  # Initialize a list to store bid-ask spreads.
    for order in order_book:
        # Get the highest bid price.  Use default=0 to handle cases where there are no bids.
        highest_bid = max(order["bids"], default=0)
        # Get the lowest ask price.  Use default=float('inf') to handle cases where there are no asks.
        lowest_ask = min(order["asks"], default=float('inf'))
        # Calculate the bid-ask spread.  If there are no asks, the spread is 0.
        bid_ask_spread.append(lowest_ask - highest_bid if lowest_ask != float('inf') else 0)
    return bid_ask_spread

# 5. Breakout Trading Strategy (O(n))
def breakout_strategy(prices, window=20):
    """
    Implements a breakout trading strategy.  It identifies potential buying opportunities when the price moves above
    a recent high (resistance level) or selling opportunities when the price moves below a recent low (support level).

    Args:
        prices (list): A list of stock prices for each day.
        window (int): The time window to determine the recent high and low prices (e.g., 20 days).

    Returns:
        list: A list of trading signals ("BUY", "SELL", or "HOLD") for each day, starting from the window day.
    """
    signals = []  # Initialize a list to store trading signals.
    for i in range(len(prices)):
        # Check for a breakout above the recent high.
        if i >= window and prices[i] > max(prices[i-window:i]):
            signals.append("BUY")
        # Check for a breakout below the recent low.
        elif i >= window and prices[i] < min(prices[i-window:i]):
            signals.append("SELL")
        else:
            signals.append("HOLD")  # Hold if no breakout occurs.
    return signals

# 6. Algorithmic Trend Following Strategy (O(n))
def trend_following_strategy(prices, momentum_window=10):
    """
    Implements a trend-following strategy.  It generates buy signals when the price is trending upwards
    and sell signals when the price is trending downwards, based on price momentum over a specified window.

    Args:
        prices (list): A list of stock prices for each day.
        momentum_window (int): The time window to measure price momentum (e.g., 10 days).

    Returns:
        list: A list of trading signals ("BUY", "SELL", or "HOLD") for each day, starting from the momentum_window day.
    """
    signals = []  # Initialize the signals list.
    for i in range(len(prices)):
        # Check for an upward trend.
        if i >= momentum_window and prices[i] > prices[i - momentum_window]:
            signals.append("BUY")
        # Check for a downward trend.
        elif i >= momentum_window and prices[i] < prices[i - momentum_window]:
            signals.append("SELL")
        else:
            signals.append("HOLD")  # Hold if no clear trend.
    return signals

# Test Cases
prices = [100, 102, 105, 101, 99, 98, 110, 115, 120, 125]
volumes = [1000, 1200, 1500, 1300, 1100, 1000, 1800, 1900, 2000, 2100]
order_book = [{"bids": [98, 99, 100], "asks": [101, 102, 103]} for _ in prices]

print("Moving Average Crossover:", moving_average_crossover(prices))
print("RSI Strategy:", rsi_trading_strategy(prices))
print("VWAP:", vwap(prices, volumes))
print("Liquidity Analysis:", liquidity_analysis(order_book))
print("Breakout Strategy:", breakout_strategy(prices))
print("Trend Following:", trend_following_strategy(prices))
