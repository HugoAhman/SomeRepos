#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int input;
    char inputLetter;
} player;

player players[4];

typedef struct int_node
{
    int playerNumber;
    struct int_node *next;
    struct int_node *head;
    char letter;
} int_node;

void show(struct int_node *text)
{
    while (text != NULL)
    {
        printf("%d", text->playerNumber);
        printf(" ");
        printf("%c", text->letter);
        printf("\n");
        printf("\n");

        text = text->next;
    }
}

int main()
{
    printf("We have 4 players here. What numbers do you want? Type below\n");
    scanf("%d", &players[0].input);
    printf("\n");
    printf("Type another\n");
    scanf("%d", &players[1].input);
    printf("\n");
    printf("Type another\n");
    scanf("%d", &players[2].input);
    printf("\n");
    printf("Type another\n");
    scanf("%d", &players[3].input);
    printf("\n");

    printf("What team character do you want? Type below\n");
    scanf("%c", &players[0].inputLetter);
    printf("\n");
    printf("Type another\n");
    scanf("%c", &players[1].inputLetter);
    printf("\n");
    printf("Type another\n");
    scanf("%c", &players[2].inputLetter);
    printf("\n");
    printf("Type another\n");
    scanf("%c", &players[3].inputLetter);
    printf("\n");

    struct int_node *first;
    struct int_node *second;
    struct int_node *third;
    struct int_node *fourth;

    first = (struct int_node *)malloc(sizeof(struct int_node));
    second = (struct int_node *)malloc(sizeof(struct int_node));
    third = (struct int_node *)malloc(sizeof(struct int_node));
    fourth = (struct int_node *)malloc(sizeof(struct int_node));

    first->playerNumber = players[0].input;
    second->playerNumber = players[1].input;
    third->playerNumber = players[2].input;
    fourth->playerNumber = players[3].input;

    first->letter = players[0].inputLetter;
    second->letter = players[1].inputLetter;
    third->letter = players[2].inputLetter;
    fourth->letter = players[3].inputLetter;

    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = first;

    second->head = first;
    third->head = first;
    fourth->head = first;

    show(first);

    return 0;
}
