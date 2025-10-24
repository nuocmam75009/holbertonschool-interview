#!/usr/bin/python3

def isWinner(x, nums):
    """
    Determines the winner of the prime game.

    Args:
        x: number of rounds
        nums: array of n values for each round

    Returns:
        name of the player that won the most rounds, or None if tied
    """
    if not nums or x == 0:
        return None

    maria_wins = 0
    ben_wins = 0

    for n in nums:
        if n < 2:  # No primes available for n < 2
            ben_wins += 1
            continue

        # Get all primes up to n
        primes = get_primes_up_to(n)

        # Simulate the game
        winner = simulate_game(n, primes)

        if winner == "Maria":
            maria_wins += 1
        else:
            ben_wins += 1

    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    else:
        return None


def get_primes_up_to(n):
    """Get all prime numbers up to n using Sieve of Eratosthenes."""
    if n < 2:
        return []

    # Create a boolean array "prime[0..n]" and initialize all entries as true
    prime = [True] * (n + 1)
    prime[0] = prime[1] = False

    for p in range(2, int(n ** 0.5) + 1):
        if prime[p]:
            # Update all multiples of p
            for i in range(p * p, n + 1, p):
                prime[i] = False

    # Collect all primes
    primes = []
    for i in range(2, n + 1):
        if prime[i]:
            primes.append(i)

    return primes


def simulate_game(n, primes):
    """
    Simulate the game with optimal play.
    The key insight is that this game is equivalent to a Nim game
    where each prime number represents a "pile" of size 1.
    """
    if not primes:
        return "Ben"  # Maria cannot move

    # Create a set of available numbers
    available = set(range(1, n + 1))

    # Simulate optimal play
    current_player = "Maria"

    while True:
        # Find available primes
        available_primes = [p for p in primes if p in available]

        if not available_primes:
            # Current player cannot move, other player wins
            return "Ben" if current_player == "Maria" else "Maria"

        # For optimal play, we need to consider the game state
        # This is a variant of Nim game where each prime is a "pile"
        # The key insight is that this game is equivalent to a Nim game
        # where the "piles" are the prime numbers

        # Calculate the XOR of all available primes (Nim sum)
        nim_sum = 0
        for prime in available_primes:
            nim_sum ^= prime

        # If nim_sum is 0, we're in a losing position
        # Otherwise, we can make a winning move
        if nim_sum == 0:
            # In losing position, any move will do
            chosen_prime = available_primes[0]
        else:
            # Find a move that makes nim_sum 0
            chosen_prime = None
            for prime in available_primes:
                # Check if removing this prime makes nim_sum 0
                new_nim_sum = nim_sum ^ prime
                if new_nim_sum == 0:
                    chosen_prime = prime
                    break

            if chosen_prime is None:
                chosen_prime = available_primes[0]

        # Make the move - remove the prime and all its multiples
        for i in range(chosen_prime, n + 1, chosen_prime):
            available.discard(i)

        # Switch players
        current_player = "Ben" if current_player == "Maria" else "Maria"
