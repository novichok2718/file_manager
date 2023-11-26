#include <stdlib.h>

struct node
{
    struct node *parent;
    struct LinkedList *child;
    char *nodeValue;
    char *absolutePath;
    int is_dir;
} typedef node;

// Linked list struct
struct ListItem
{
    node *node;
    struct ListItem *prev;
    struct ListItem *next;
} typedef ListItem;

struct LinkedList
{
    int size;
    ListItem *head;
    ListItem *tail;
} typedef LinkedList;

// implementation of Linked list
LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ListItem *createListItem()
{
    ListItem *item = (ListItem *)malloc(sizeof(ListItem));
    item->node = (node *)malloc(sizeof(node));
    item->node->absolutePath = NULL;
    item->node->child = NULL;
    item->node->is_dir = 1;
    item->node->parent = NULL;
    item->node->nodeValue = NULL;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

void pushBack(LinkedList *list, node *node)
{
    ListItem *item = (ListItem *)malloc(sizeof(ListItem));
    if (!item)
    {
        exit(1);
    }
    item->node = node;
    item->next = NULL;
    item->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = item;
    }
    list->tail = item;
    if (!list->head)
    {
        list->head = item;
    }
    ++list->size;
}

node *popBack(LinkedList *list)
{
    if (!list->tail)
    {
        exit(2);
    }
    ListItem *item = list->tail;
    list->tail = list->tail->prev;
    if (list->tail)
    {
        list->tail->next = NULL;
    }
    if (item == list->head)
    {
        list->head = NULL;
    }
    return item->node;
}

void deleteLinkedList(LinkedList **list)
{
    ListItem *item = (*list)->head;
    ListItem *next = NULL;
    while (item)
    {
        next = item->next;
        free(item->node->absolutePath);
        free(item->node->nodeValue);
        free(item->node->child);
        free(item->node->parent);
        free(item->node);
        item->node = NULL;
        item = next;
    }
    free(*list);
    (*list) = NULL;
}

node *is_contains(LinkedList *list, char *nodeValue, int isDir)
{
    ListItem *item = list->head;
    while (item)
    {
        if (!strcmp(item->node->nodeValue, nodeValue) && item->node->is_dir == isDir)
        {
            return item->node;
        }
        item = item->next;
    }
    return NULL;
}
