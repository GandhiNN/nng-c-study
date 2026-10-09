#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * CONTACT BOOK - a concrete program using EVERYTHING so far:
 *  structs, ->, self-referential nodes, malloc/free, strings (with '\0'),
 *  pointers as function arguments, NULL, and pointer traversal.
 * 
 * It stores contacts in a singly linked list. Each node holds the name in 
 * a FIXED char array (option 1): simple, one allocation per node, names
 * capped at NAME_MAX-1 characters.
 *
*/

#define NAME_MAX 32 /* max name length incl. the '\0' */
#define PHONE_MAX 16

struct Contact {
    char name[NAME_MAX];    /* fixed array: no separate malloc for the name */
    char phone[PHONE_MAX];
    struct Contact *next;   /* self-reference: pointer to the next contact */
};

/* --- helpers --- */

/* Safely copy a string into a fixed buffer, always NUL-terminating.
   This is the string + buffer-size care from the memory lessons. */
static void copyField(char *dst, size_t cap, const char *src)
{
    strncpy(dst, src, cap - 1);
    dst[cap - 1] = '\0';    /* guarantee termination even if truncated */
}

/* Allocate one contact node on the heap. */
static struct Contact *makeContact(const char *name, const char *phone)
{
    struct Contact *c = malloc(sizeof(struct Contact));
    if (c == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    copyField(c->name, NAME_MAX, name);
    copyField(c->phone, PHONE_MAX, phone);
    c->next = NULL;
    return c;
}

/* --- list operations --- */

/* Add to the front. Returns the new head (pointer-returning pattern) */
struct Contact *addContact(struct Contact *head, const char *name, const char *phone)
{
    struct Contact *c = makeContact(name, phone);
    c->next = head;
    return c;
}

/* Find a contact by name. Returns a pointer to it, or NULL if not found.
   Returning NULL for "not found" is the pattern from the NULL lesson */
struct Contact *findContact(struct Contact *head, const char *name)
{
    for (struct Contact *p = head; p != NULL; p = p->next)
        if (strcmp(p->name, name) == 0) /* strcmp == 0 means equal */
            return p;
    return NULL;
}

/* Delete the first contact matching 'name'. Returns the (possibly new) head. 
   Uses a 'prev' pointer so we can relink around the removed node. */
struct Contact *deleteContact(struct Contact *head, const char *name)
{
    struct Contact *prev = NULL;
    for (struct Contact *p = head; p != NULL; prev = p, p = p->next) {
        if (strcmp(p->name, name) == 0) {
            if (prev == NULL)
                head = p->next; /* removing the head node */
            else
                prev->next = p->next; /* skip p in the chain */
            free(p);    /* release the removed node */
            printf("deleted: %s\n", name);
            return head;
        }
    }
    printf("not found (nothing deleted): %s\n", name);
    return head;
}

/* Print the whole book by walking the chain to NULL. */
void printBook(const struct Contact *head)
{
    printf("--- contacts ---\n");
    if (head == NULL) {
        printf("(empty)\n");
        return;
    }
    for (const struct Contact *p = head; p != NULL; p = p->next)
        printf("%-20s %s\n", p->name, p->phone);
}

/* Free every node (save next before freeing current) */
void freeBook(struct Contact *head)
{
    struct Contact *p = head;
    while (p != NULL) {
        struct Contact *next = p->next;
        free(p);
        p = next;
    }
}

/* --- demo --- */

int main(void)
{
    struct Contact *book = NULL; /* empty book = NULL head */

    book = addContact(book, "Alice", "555-0001");
    book = addContact(book, "Bob", "555-0002");
    book = addContact(book, "Carol", "555-0003");
    printBook(book);

    /* Look someone up */
    printf("\nlooking up Bob...\n");
    struct Contact *hit = findContact(book, "Bob");
    if (hit != NULL)
        printf("found: %s -> %s\n", hit->name, hit->phone);
    else
        printf("Bob not found\n");

    /* Look up someone who isn't there */
    printf("\nlooking up Dave...\n");
    if (findContact(book, "Dave") == NULL)
        printf("Dave not found (findContact returned NULL)\n");

    /* Delete and reprint */
    printf("\n");
    book = deleteContact(book, "Alice"); /* deletes the tail-most added */
    book = deleteContact(book, "Zoe"); /* not present */
    printf("\n");
    printBook(book);

    /* Clean up all remaining nodes. */
    freeBook(book);
    book = NULL;
    printf("\nbook freed.\n");

    return 0;
}