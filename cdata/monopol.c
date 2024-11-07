#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int bank_money = 14580;

typedef struct
{
    int money;
    int position;
} player;

player players[4] = {
    {.money = 1500,
     .position = 0},
    {.money = 1500,
     .position = 0},
    {.money = 1500,
     .position = 0},
    {.money = 1500,
     .position = 0}};

typedef enum
{
    go,
    cards,
    freePark,
    goToJail,
    jail,
    plots,
    tax
} SpaceType;

typedef struct
{
    SpaceType type;
    char property_name[64];
    int price;
    int rent;
    int owner; // -1 Means no owner. 0-3 Shows which user owns it.
} BoardSpace;

int ownedPlot = 1;
int youGotInJail;

BoardSpace spaces[40] = {
    {.type = go, .owner = -1},
    {.type = plots, .property_name = "Mediterranean Avenue", .price = 60, .rent = 2, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Baltic Avenue", .price = 60, .rent = 4, .owner = -1},
    {.type = tax, .owner = -1},
    {.type = plots, .property_name = "Reading Railroad", .price = 200, .rent = 25, .owner = -1},
    {.type = plots, .property_name = "Oriental Avenue", .price = 100, .rent = 6, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Vermont Avenue", .price = 100, .rent = 6, .owner = -1},
    {.type = plots, .property_name = "Connecticut Avenue", .price = 120, .rent = 8, .owner = -1},
    {.type = jail, .owner = -1},
    {.type = plots, .property_name = "St. Charles place", .price = 140, .rent = 10, .owner = -1},
    {.type = plots, .property_name = "Electric Company", .price = 150, .rent = 28, .owner = -1},
    {.type = plots, .property_name = "State Avenue", .price = 140, .rent = 10, .owner = -1},
    {.type = plots, .property_name = "Virginia Avenue", .price = 160, .rent = 12, .owner = -1},
    {.type = plots, .property_name = "Pennsylvania Railroad", .price = 200, .rent = 25, .owner = -1},
    {.type = plots, .property_name = "St. James Place", .price = 180, .rent = 14, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Tennessee Avenue", .price = 180, .rent = 14, .owner = -1},
    {.type = plots, .property_name = "New York Avenue", .price = 200, .rent = 16, .owner = -1},
    {.type = freePark, .owner = -1},
    {.type = plots, .property_name = "Kentucky Avenue", .price = 220, .rent = 18, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Indiana Avenue", .price = 220, .rent = 18, .owner = -1},
    {.type = plots, .property_name = "Illinois Avenue", .price = 240, .rent = 20, .owner = -1},
    {.type = plots, .property_name = "B. & O. Railroad", .price = 200, .rent = 25, .owner = -1},
    {.type = plots, .property_name = "Atlantic Avenue", .price = 260, .rent = 22, .owner = -1},
    {.type = plots, .property_name = "Ventnor Avenue", .price = 260, .rent = 22, .owner = -1},
    {.type = plots, .property_name = "Water Works", .price = 150, .rent = 28, .owner = -1},
    {.type = plots, .property_name = "Marvin Gardens", .price = 280, .rent = 24, .owner = -1},
    {.type = goToJail, .owner = -1},
    {.type = plots, .property_name = "Pacific Avenue", .price = 300, .rent = 26, .owner = -1},
    {.type = plots, .property_name = "North Carolina Avenue", .price = 300, .rent = 26, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Pennsylvania Avenue", .price = 320, .rent = 28, .owner = -1},
    {.type = plots, .property_name = "Short Line", .price = 200, .rent = 25, .owner = -1},
    {.type = cards, .owner = -1},
    {.type = plots, .property_name = "Park Place", .price = 350, .rent = 35, .owner = -1},
    {.type = tax, .owner = -1},
    {.type = plots, .property_name = "Boardwalk", .price = 400, .rent = 50, .owner = -1},
};

void takeTurn(int playerIndex, int playerAmount)
{
    int dieRoll = (rand() % 5) + 1 + (rand() % 5) + 1;
    printf("Player %d threw the dices and got %d\n", playerIndex + 1, dieRoll);
    printf("\n");

    players[playerIndex].position = (players[playerIndex].position + dieRoll) % 40;
    printf("Player %d is now standing on %d\n", playerIndex + 1, players[playerIndex].position);

    switch (spaces[players[playerIndex].position].type)
    {
    case go:
        players[playerIndex].money += 200;
        printf("You received $200 for passing GO!\n");
        break;

    case plots:
        if (spaces[players[playerIndex].position].owner == -1)
        { // If no one owns the plot this code runs
            int buyPlot;
            printf("You landed on %s.\n", spaces[players[playerIndex].position].property_name);
            printf("The price is: $%d\n", spaces[players[playerIndex].position].price);
            printf("Do you want to buy this plot? (1 for Yes, 0 for No): ");
            scanf("%d", &buyPlot);
            printf("\n");
            if (buyPlot == 1)
            {
                if (players[playerIndex].money >= spaces[players[playerIndex].position].price)
                {
                    players[playerIndex].money -= spaces[players[playerIndex].position].price;
                    spaces[players[playerIndex].position].owner = playerIndex; // Mark plot as bought by the current player
                    printf("You bought %s. Your balance is now $%d.\n", spaces[players[playerIndex].position].property_name, players[playerIndex].money);
                }
                else
                {
                    printf("You don't have enough money to buy this plot.\n");
                }
            }
            else
            {
                printf("You chose not to buy %s.\n", spaces[players[playerIndex].position].property_name);
            }
        }
        else
        {
            // Rent paying code
            int owner = spaces[players[playerIndex].position].owner;
            if (owner != playerIndex)
            {
                players[playerIndex].money -= spaces[players[playerIndex].position].rent;
                players[owner].money += spaces[players[playerIndex].position].rent;
                printf("This plot is owned by Player %d. You paid $%d in rent. Your balance is now $%d.\n", owner + 1, spaces[players[playerIndex].position].rent, players[playerIndex].money);
            }
            else
            {
                printf("You own this plot.\n");
            }
        }
        break;

    case cards:
        printf("You landed on a drawable card tile but unfortunately all cards are already drawn :( \n");
        break;

    case freePark:
        printf("You are just visiting Free Parking.\n");
        break;

    case goToJail:
        players[playerIndex].position = 10;
        youGotInJail = 1;
        printf("You are going to jail!\n");
        break;

    case jail:
        if (youGotInJail == 1)
        {
            players[playerIndex].money -= 200;
            printf("You paid $200 to get out of jail. Your balance is now $%d.\n", players[0].money);
        }
        else
        {
            printf("You are just visiting jail. Don't sweat about it!\n");
        }

        break;

    case tax:
        players[playerIndex].money -= 200;
        printf("Player %d had to pay $200 in taxes. Your balance is now $%d.\n", playerIndex + 1, players[playerIndex].money);
        break;
    }

    printf("\n");
    for (int i = 0; i < playerAmount; i++)
    {
        printf("Player %d -- Money: %d, Position: %d\n", i + 1, players[i].money, players[i].position);
    }
    printf("\n");
}

int main()
{

    srand(time(0));

    int playeramount;
    printf("The maximum amount is 4 players\n");
    printf("Enter the amount of players: ");
    scanf("%d", &playeramount);
    if (playeramount > 4)
    {
        printf("Too many players\n");
        exit(1);
    }
    if (playeramount < 1)
    {
        printf("Too few players\n");
        exit(1);
    }

    for (int i = 0; i < playeramount; i++)
    {
        players[i].money = 1500;
        players[i].position = 0;
    }

    int turn = 0;
    while (playeramount != 1) // Need to create something to put here to end the infinte loop
    {
        printf("It's now player %d's turn!\n", turn + 1);
        printf("\n");
        takeTurn(turn, playeramount);
        turn = (turn + 1) % playeramount;
    }
    if (playeramount == 1)
    {
        printf("You won the game!");
    }

    return 0;
}