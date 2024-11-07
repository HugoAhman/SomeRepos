#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Svårare variant för att låta dig skriva in ett nummer igen om du har fel

    srand(time(0));

    int slumpnummer = rand() % 10 + 1;
    int input = -1;
    int guesses = 0;
    int currentHighscore = INT16_MAX;

    FILE *highscore = fopen("highscore.txt", "r");
    if (highscore != NULL)
    {
        fscanf(highscore, "Highscore: %d", &currentHighscore);
        fclose(highscore);
    }
    else
    {
        printf("Inga tidigare highscores hittade. Sätter normalt highscore.\n");
    }

    if (NULL == highscore)
    {
        printf("ERROR! Kunde inte öppna filen \n");
        return 0;
    }

    printf("Nuvarande highscoren är: %d\n", currentHighscore);

    while (slumpnummer != input)
    {
        guesses++;
        printf("Gissa nummret mellan 1 och 10\n");
        printf("\n");
        scanf("%d", &input);
        if (slumpnummer > input)
        {
            printf("Gissningen är för låg\n");
            printf("\n");
            continue;
        }
        else if (slumpnummer < input)
        {
            printf("Gissningen är för hög!\n");
            printf("\n");
            continue;
        }
    }

    printf("Du hade rätt!\n");

    if (guesses < currentHighscore)
    {
        printf("Nytt Highscore: %d", guesses);
        highscore = fopen("highscore.txt", "w");
        if (highscore != NULL)
        {
            fprintf(highscore, "Highscore: %d\n", guesses);
            fclose(highscore);
        }
        else
        {
            printf("ERROR! Kunde inte öppna för att skriva\n");
        }
    }
    else
    {
        printf("Inga nya highscores. Nuvarande highscore är fortfarande: %d\n", currentHighscore);
    }

    return 0;
}

// Enkel variant för att bara ge dig ett slumpnummer
/*
for (int i = 0; i < 1; i++){

    printf("Här är ett slumpnummer: %d\n", slumpnummer);
}
*/