#include <stdlib.h>
#include <stdio.h>

/**
 * struct heap_s - Binary heap node structure
 * @value: Value stored in the node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 */
typedef struct heap_s
{
    int value;
    struct heap_s *left;
    struct heap_s *right;
} heap_t;

/**
 * get_last_node_and_parent - Gets the last level-order node and its parent
 * @root: Pointer to the root of the heap
 * @parent: Pointer to store the parent of the last node
 *
 * Return: Pointer to the last node, or NULL if heap is empty
 */
static heap_t *get_last_node_and_parent(heap_t *root, heap_t **parent)
{
    heap_t **queue;
    heap_t **parent_queue;
    int front = 0, rear = 0;
    heap_t *current, *current_parent, *last = NULL;

    if (!root)
        return (NULL);

    *parent = NULL;

    /* Allocate queues for level-order traversal */
    queue = malloc(sizeof(heap_t *) * 1000); /* Assuming max 1000 nodes */
    parent_queue = malloc(sizeof(heap_t *) * 1000);
    if (!queue || !parent_queue)
    {
        free(queue);
        free(parent_queue);
        return (NULL);
    }

    queue[rear] = root;
    parent_queue[rear] = NULL;
    rear++;

    while (front < rear)
    {
        current = queue[front];
        current_parent = parent_queue[front];
        front++;

        last = current;
        *parent = current_parent;

        if (current->left)
        {
            queue[rear] = current->left;
            parent_queue[rear] = current;
            rear++;
        }
        if (current->right)
        {
            queue[rear] = current->right;
            parent_queue[rear] = current;
            rear++;
        }
    }

    free(queue);
    free(parent_queue);
    return (last);
}

/**
 * heapify_down - Restores the max heap property after extraction
 * @root: Pointer to the root of the heap
 */
static void heapify_down(heap_t *root)
{
    heap_t *largest = root;

    if (!root)
        return;

    /* Compare with left child */
    if (root->left && root->left->value > largest->value)
        largest = root->left;

    /* Compare with right child */
    if (root->right && root->right->value > largest->value)
        largest = root->right;

    /* If largest is not root, swap and continue heapifying */
    if (largest != root)
    {
        int temp_value = root->value;
        root->value = largest->value;
        largest->value = temp_value;
        heapify_down(largest);
    }
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: Value stored in the root node, or 0 if function fails
 */
int heap_extract(heap_t **root)
{
    heap_t *last_node, *parent;
    int root_value;

    if (!root || !*root)
        return (0);

    /* Store the root value to return */
    root_value = (*root)->value;

    /* If heap has only one node */
    if (!(*root)->left && !(*root)->right)
    {
        free(*root);
        *root = NULL;
        return (root_value);
    }

        /* Find the last level-order node and its parent */
    last_node = get_last_node_and_parent(*root, &parent);
    if (!last_node)
        return (0);

    /* Replace root value with last node value */
    (*root)->value = last_node->value;

    /* Remove the last node */
    if (*root == last_node)
    {
        /* Root is the last node (shouldn't happen with above check) */
        free(*root);
        *root = NULL;
    }
    else
    {
        /* Remove the last node from its parent */
        if (parent->left == last_node)
            parent->left = NULL;
        else if (parent->right == last_node)
            parent->right = NULL;

        free(last_node);

        /* Restore heap property */
        heapify_down(*root);
    }

    return (root_value);
}
