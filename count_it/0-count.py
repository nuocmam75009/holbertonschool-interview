#!/usr/bin/python3
"""Recursive Reddit hot articles keyword counter."""
import requests


def count_words(subreddit, word_list, counts=None, after=None):
    """
    Recursively query Reddit hot articles and count keyword occurrences.

    Args:
        subreddit: name of the subreddit to query
        word_list: list of keywords to count (case-insensitive)
        counts: dict accumulating counts across recursive calls
        after: pagination token for the next page
    """
    if counts is None:
        counts = {}
        for word in word_list:
            key = word.lower()
            counts[key] = counts.get(key, 0)

    url = "https://www.reddit.com/r/{}/hot.json".format(subreddit)
    headers = {"User-Agent": "count_words/1.0"}
    params = {"limit": 100}
    if after:
        params["after"] = after

    response = requests.get(url, headers=headers,
                            params=params, allow_redirects=False)

    if response.status_code != 200:
        return

    data = response.json().get("data", {})
    children = data.get("children", [])

    for post in children:
        title = post.get("data", {}).get("title", "").lower()
        words = title.split()
        for word in words:
            cleaned = ''.join(c for c in word if c.isalnum())
            if cleaned in counts:
                counts[cleaned] += 1

    next_after = data.get("after")
    if next_after:
        count_words(subreddit, word_list, counts, next_after)
    else:
        results = [(k, v) for k, v in counts.items() if v > 0]
        for word, count in sorted(results, key=lambda x: (-x[1], x[0])):
            print("{}: {}".format(word, count))
