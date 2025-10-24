#include "regex.h"

/**
 * regex_match - matches a pattern against a string
 * @str: the string to match
 * @pattern: the pattern to match against
 *
 * Return: 1 if pattern matches string, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
    /* Handle empty pattern */
    if (!pattern || !*pattern)
        return (!str || !*str);

    /* Handle empty string */
    if (!str || !*str)
    {
        /* Pattern can only match empty string if it's all * patterns */
        while (*pattern)
        {
            if (pattern[1] == '*')
                pattern += 2;
            else
                return (0);
        }
        return (1);
    }

    /* Check if next character in pattern is * */
    if (pattern[1] == '*')
    {
        /* Try matching zero occurrences of the character before * */
        if (regex_match(str, pattern + 2))
            return (1);

        /* Try matching one or more occurrences */
        if ((*pattern == '.' || *pattern == *str) &&
            regex_match(str + 1, pattern))
            return (1);

        return (0);
    }

    /* Handle single character match */
    if (*pattern == '.' || *pattern == *str)
        return (regex_match(str + 1, pattern + 1));

    return (0);
}
