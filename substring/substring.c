#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * word_index - finds the index of a word in the words array
 * @word: the word to look up
 * @words: the array of words
 * @nb_words: number of words in the array
 * @word_len: length of each word
 *
 * Return: index of the word, or -1 if not found
 */
static int word_index(char const *word, char const **words,
		int nb_words, int word_len)
{
	int i;

	for (i = 0; i < nb_words; i++)
	{
		if (strncmp(word, words[i], word_len) == 0)
			return (i);
	}
	return (-1);
}

/**
 * check_window - checks whether s[start] is the start of a valid substring
 * @s: the string to scan
 * @start: starting index in s
 * @words: array of words
 * @nb_words: number of words
 * @word_len: length of each word
 *
 * Return: 1 if valid, 0 otherwise
 *
 * Uses frequency counts indexed by the first occurrence of each word,
 * so duplicate words in the words array are handled correctly.
 */
static int check_window(char const *s, int start, char const **words,
		int nb_words, int word_len)
{
	int *need;
	int *found;
	int i;
	int canonical;
	int idx;
	int result;

	need = calloc(nb_words, sizeof(int));
	found = calloc(nb_words, sizeof(int));
	if (!need || !found)
	{
		free(need);
		free(found);
		return (0);
	}

	for (i = 0; i < nb_words; i++)
	{
		canonical = word_index(words[i], words, nb_words, word_len);
		need[canonical]++;
	}

	result = 1;
	for (i = 0; i < nb_words && result; i++)
	{
		idx = word_index(s + start + i * word_len, words, nb_words, word_len);
		if (idx == -1)
		{
			result = 0;
			break;
		}
		found[idx]++;
		if (found[idx] > need[idx])
			result = 0;
	}

	free(need);
	free(found);
	return (result);
}

/**
 * find_substring - finds all starting indices of valid substrings in s
 * @s: the string to scan
 * @words: array of words to concatenate
 * @nb_words: number of words
 * @n: stores the number of indices found
 *
 * Return: allocated array of indices, or NULL if none found
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	int word_len;
	int s_len;
	int window_len;
	int max_starts;
	int *indices;
	int count;
	int i;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return (NULL);

	word_len = (int)strlen(words[0]);
	s_len = (int)strlen(s);
	window_len = nb_words * word_len;
	max_starts = s_len - window_len + 1;

	if (max_starts <= 0)
		return (NULL);

	indices = malloc(sizeof(int) * max_starts);
	if (!indices)
		return (NULL);

	count = 0;
	for (i = 0; i < max_starts; i++)
	{
		if (check_window(s, i, words, nb_words, word_len))
			indices[count++] = i;
	}

	*n = count;
	if (count == 0)
	{
		free(indices);
		return (NULL);
	}
	return (indices);
}
