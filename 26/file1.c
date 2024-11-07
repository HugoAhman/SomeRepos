#include <stdio.h>

int main()
{
    const char *name = "Hugo";
    int age = 18;

    FILE *my_file = fopen("myfile.txt", "w");
    if (NULL == my_file)
    {
        printf("ERROR! Could not open file! \n");
        return 0;
    }

    fprintf(my_file, "Name: %s Age: %d\n", name, age);
    fclose(my_file);

    my_file = fopen("myfile.txt", "r");
    char mychar[65];
    fscanf(my_file, "Name: %64s Age: %d\n", mychar, &age);
    fclose(my_file);

    printf("%s %d", mychar, age);
    return 0;
}