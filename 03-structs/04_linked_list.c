#include <stdio.h>
#include <stdlib.h>

/*
 * LESSON: the LINKED LIST -- where pointers + structs + malloc all meet.
 *
 * A linked list is a chain of nodes. Each node holds:
 *      - a value
 *      - a POINTER to the next node (or NULL if it's the last one)
 * 
 * You only keep the address of the FIRST node ("head"). To reach any
 * other node you follow the 'next' pointers until you hit NULL.
 * 
 *      head -> [10|*] -> [20|*] -> [30|NULL]
 * 
 * THE KEY IDEA: 'next' is a POINTER to a Node, not a Node itself.
 * A pointer is a fixed-size address, so the struct's size is known even
 * though the chain can be any length. (A plain 'struct Node next;' would
 * be infinitely large and will not compile.)
 *
*/ 

struct Node {
    int value;
    struct Node *next;  /* pointer to the next node, or NULL at the end */
};

/* Make one node on the heap: store the value, point next at NULL for now. */
struct Node *makeNode(int value)
{
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->value = value;
    n->next = NULL;
    return n;   /* hand back the address of the new node */
}

/* Add a node to the FRONT of the list and return the new head.
   New node's 'next' points at the old head; the new node becomes head. */
struct Node *pushFront(struct Node *head, int value)
{
    struct Node *n = makeNode(value);
    n->next = head;     /* link the rest of the list behind the new node */
    return n;           /* new node is the new head */
}

/* Walk the chain from head to NULL, printing each value. */
void printList(const struct Node *head)
{
    printf("head ->");
    for (const struct Node *p = head; p != NULL; p = p->next)
        printf("[%d] -> ", p->value);
    printf("NULL\n");
}

/* Count the nodes by following 'next' until NULL */
int length(const struct Node *head)
{
    int count = 0;
    for (const struct Node *p = head; p != NULL; p = p->next)
        count++;
    return count;
}

/* Free every node. Must grab 'next' BEFORE freeing the current node,
   otherwise we'd be reading freed memory to find the next one. */
void freeList(struct Node *head)
{
    struct Node *p = head;
    while (p != NULL) {
        struct Node *next = p->next;    /* save next FIRST */
        free(p);                        /* now it's safe to free p */
        p = next;
    }
}

int main(void)
{
    struct Node *head = NULL;   /* empty list is just a NULL head */

    /* Build head -> [30] -> [20] -> [10] -> NULL (pushFront reverses order). */
    head = pushFront(head, 10);
    head = pushFront(head, 20);
    head = pushFront(head, 30);

    printList(head);
    printf("length = %d\n", length(head));

    /* Reach into the chain by following pointers. */
    printf("\nhead->value               = %d\n", head->value);
    printf("head->next->value           = %d\n", head->next->value);
    printf("head->next->next->value     = %d\n", head->next->next->value);

    /* Always clean up every malloc'd node */
    freeList(head);
    head = NULL;
    printf("\nlist freed.\n");

    return 0;
}