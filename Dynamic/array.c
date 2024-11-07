#include <stdio.h>
#include <stdlib.h>

int add_at_end(int a[], int b[], int n, int freePos, int data)
{
    int i;
    for (i = 0; i < n; i++)
    {
        b[i] = a[i];
    }

    b[freePos] = data;
    freePos++;
    return freePos;
}
int main()
{
    int a[10];
    int i, n, freePos;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int size = sizeof(a) / sizeof(a[0]);
    freePos = n;
    if (n == size)
    {
        int b[size + 2];
        freePos = add_at_end(a, b, size, freePos, 65);
        for (i = 0; i < freePos; i++)
        {
            printf("%d ", b[i]);
        }
    }
    return 0;
}

/*
int arr[] = {45, 98, 3};
int n, i;
n = sizeof(arr) / sizeof(int);
for (i = 0; i < n; i++)
{

    printf("%d\n", arr[i]);
}
printf("Count: %d\n", n);
return 0;
*/