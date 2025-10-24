#include <stdio.h>
#include <stdlib.h>
#include "0-heap_extract.c"

/**
 * print_heap - Prints the heap in level-order
 * @root: Pointer to the root of the heap
 */
void print_heap(heap_t *root)
{
    heap_t **queue;
    int front = 0, rear = 0;
    heap_t *current;

    if (!root)
    {
        printf("Empty heap\n");
        return;
    }

    queue = malloc(sizeof(heap_t *) * 100);
    queue[rear++] = root;

    printf("Heap (level-order): ");
    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current->value);

        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }
    printf("\n");

    free(queue);
}

/**
 * create_heap_node - Creates a new heap node
 * @value: Value to store in the node
 *
 * Return: Pointer to the new node
 */
heap_t *create_heap_node(int value)
{
    heap_t *node = malloc(sizeof(heap_t));
    if (node)
    {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return (node);
}

/**
 * main - Test the heap_extract function
 *
 * Return: 0 on success
 */
int main(void)
{
    heap_t *root = NULL;
    int extracted_value;

    /* Create a max heap:
     *       10
     *      /  \
     *     8    9
     *    / \  /
     *   5  6 7
     */

    root = create_heap_node(10);
    root->left = create_heap_node(8);
    root->right = create_heap_node(9);
    root->left->left = create_heap_node(5);
    root->left->right = create_heap_node(6);
    root->right->left = create_heap_node(7);

    printf("Original heap:\n");
    print_heap(root);

    /* Extract root (should be 10) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Extract root again (should be 9) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Extract root again (should be 8) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Extract root again (should be 7) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Extract root again (should be 6) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Extract root again (should be 5) */
    extracted_value = heap_extract(&root);
    printf("Extracted value: %d\n", extracted_value);
    printf("Heap after extraction:\n");
    print_heap(root);

    /* Try to extract from empty heap */
    extracted_value = heap_extract(&root);
    printf("Extracted value from empty heap: %d\n", extracted_value);

    return (0);
}