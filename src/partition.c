#include <stdio.h>
#include <stdlib.h>

typedef struct subset
{
    int len;
    int *subset;
} Subset;

typedef struct data
{
    int partition;
    Subset **subset;
    char *msg;
} Data;

int isSubsetExists(unsigned int *Vector, int n, int a, int b, int c, int *subS)
{
    if (a == 0 && b == 0 && c == 0)
    {
        return 1;
    }
    if (n < 0)
    {
        return 0;
    }
    // case 1: the current item becomes part of the first subset
    int A = 0;
    if (a - Vector[n] >= 0)
    {
        subS[n] = 1;
        A = isSubsetExists(Vector, n - 1, a - Vector[n], b, c, subS);
    }
    // case 2: the current item becomes part of the second subset
    int B = 0;
    if (!A && (b - Vector[n] >= 0))
    {
        subS[n] = 2;
        B = isSubsetExists(Vector, n - 1, a, b - Vector[n], c, subS);
    }
    // case 3: the current item becomes part of the third subset
    int C = 0;
    if ((!A && !B) && (c - Vector[n] >= 0))
    {
        subS[n] = 3;
        C = isSubsetExists(Vector, n - 1, a, b, c - Vector[n], subS);
    }
    // return true if we get a solution
    return A || B || C;
};

void partition(unsigned int *Vector, unsigned int n, unsigned int *a, unsigned int *b, unsigned int *c)
{
    int arr[n];
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += Vector[i];
    }
    int result = (n >= 3) && !(sum % 3) && isSubsetExists(Vector, n - 1, (int)sum / 3, (int)sum / 3, (int)sum / 3, arr);
    Data *data = malloc(sizeof(Data));
    data->partition = result;
    data->subset = calloc(3, sizeof(Subset *));
    if (result)
    {
        for (int i = 0; i < 3; i++)
        {
            data->subset[i] = malloc(sizeof(Subset));
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == i + 1)
                {
                    data->subset[i]->len++;
                }
            }
            data->subset[i]->subset = calloc(data->subset[i]->len, sizeof(int));
            int k = 0;
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == i + 1)
                {
                    data->subset[i]->subset[k] = Vector[j];
                    if (i == 0)
                    {
                        a[k] = Vector[j];
                    }
                    if (i == 1)
                    {
                        b[k] = Vector[j];
                    }
                    if (i == 2)
                    {
                        c[k] = Vector[j];
                    }
                    k++;
                }
            }
        }
    }
}