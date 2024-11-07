#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int capacity;
    int occupied;
} darray_ints;

void darray_int_init(darray_ints *array, int desired_capacity)
{
    // array->data = malloc(array->capacity)
    array->data = (int *)malloc(desired_capacity * sizeof(int));
    if (array->data == NULL)
    {
        printf("Minne kunde inte allokeras\n");
        exit(1);
    }
    array->capacity = desired_capacity;
    array->occupied = 0;
}

void darray_int_push(darray_ints *array, int number)
{
    // array->occupied++;
    // finns det plats? jämför array->occupied med array->capacity
    // om du måste, så kommer du vilja anropa array->data = realloc(array->capcity * 2)
}

void darray_int_free(darray_ints *array)
{
}

int main()
{
    darray_ints my_array;
    darray_int_init(&my_array, 8);

    darray_int_push(&my_array, 5);
    darray_int_push(&my_array, 7);
    darray_int_push(&my_array, 11);

    darray_print(&my_array);

    darray_int_free(&my_array);
    return 0;
}