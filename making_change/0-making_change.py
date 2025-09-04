#!/usr/bin/python3
"""
Contains the function makeChange(coins, total)
"""

def makeChange(coins, total):
    """
    Make change given a certain total while using the minimum amount of coins
    Args:
        coins: list of integers representing coin denominations
        total: integer representing total amount of change to make
    Returns:
        Integer representing the smallest amount of coin to make the given total to change.
        If total cannot be made with given coins, it returns -1.
    """
    if total <= 0:
        return 0
    dp = [float('inf') * (total + 1)]
    dp[0] = 0

    for coin in coins:
        for i in range(coin, total + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)

    return dp[total] if dp[total] != float('inf') else -1

