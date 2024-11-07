#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
} node;

void count_of_nodes(struct node *head)
{
    int count = 0;
    if (head == NULL)
    {
        printf("Linked list is empty");
    }
    struct node *ptr = NULL;
    ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->link;
    }
    printf("Count: %d\n", count);
}

void print_data(struct node *head)
{
    if (head == NULL)
    {
        printf("Linked list is empty\n");
    }
    struct node *ptr = NULL;
    ptr = head;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->data);
        ptr = ptr->link;
    }
}

struct node *add_at_end(struct node *ptr, int data)
{

    struct node *temp = malloc(sizeof(struct node));

    temp->data = data;
    temp->link = NULL;

    ptr->link = temp;
    return temp;
}

int main()
{
    struct node *head = malloc(sizeof(struct node));
    head->data = 45;
    head->link = NULL;

    struct node *ptr = head;
    ptr = add_at_end(ptr, 98);
    ptr = add_at_end(ptr, 3);
    ptr = add_at_end(ptr, 67);

    ptr = head;

    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }

    count_of_nodes(head);

    print_data(head);

    return 0;
}

/* Manuell skrivning av alla nummer // Jobbigt när det ökar ser fult ut och tar massa data
    struct node *head = malloc(sizeof(struct node));
    head->data = 45;
    head->link = NULL;

    struct node *current = malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;

    current = malloc(sizeof(struct node));
    current->data = 3;
    current->link = NULL;
    head->link->link = current;

    printf("%d %d\n", head->data, current->data);
    */