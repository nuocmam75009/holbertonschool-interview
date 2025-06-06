#include "lists.h"

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to pointer of first node of listint_t list
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow = *head;
    listint_t *fast = *head;
    listint_t *prev = NULL;
    listint_t *temp;
    int is_pal = 1;

    /* Empty list is considered a palindrome */
    if (*head == NULL || (*head)->next == NULL)
        return (1);

    /* Find the middle of the list using slow and fast pointers */
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        temp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = temp;
    }

    /* If the list has odd number of elements, skip the middle element */
    if (fast != NULL)
        slow = slow->next;

    /* Compare the first half with the second half */
    while (slow != NULL)
    {
        if (prev->n != slow->n)
        {
            is_pal = 0;
            break;
        }
        prev = prev->next;
        slow = slow->next;
    }

    /* Restore the original list */
    while (prev != NULL)
    {
        temp = prev->next;
        prev->next = slow;
        slow = prev;
        prev = temp;
    }

    return (is_pal);
}
