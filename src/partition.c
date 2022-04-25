#include <stdio.h>
#include <stdlib.h>

typedef struct subset
{
    int len;
    int *subset;
} Subset;

typedef struct answer
{
    int partition;
    Subset **subset;
    char *msg;
} Answer;

int accumulate(unsigned int *S, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += S[i];
    }
    return sum;
};

void clean(Answer *ans)
{
    for (int i = 0; i < 3; i++)
    {
        free(ans->subset[i]->subset);
        free(ans->subset[i]);
    }
    free(ans->subset);
    free(ans);
};

int isSubsetExists(unsigned int *S, int n, int a, int b, int c, int *subS)
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
    if (a - S[n] >= 0)
    {
        subS[n] = 1;
        A = isSubsetExists(S, n - 1, a - S[n], b, c, subS);
    }
    // case 2: the current item becomes part of the second subset
    int B = 0;
    if (!A && (b - S[n] >= 0))
    {
        subS[n] = 2;
        B = isSubsetExists(S, n - 1, a, b - S[n], c, subS);
    }
    // case 3: the current item becomes part of the third subset
    int C = 0;
    if ((!A && !B) && (c - S[n] >= 0))
    {
        subS[n] = 3;
        C = isSubsetExists(S, n - 1, a, b, c - S[n], subS);
    }
    // return true if we get a solution
    return A || B || C;
};

void partition(unsigned int *S, unsigned int n, unsigned int *subset1, unsigned int *subset2, unsigned int *subset3)
{
    int sum = accumulate(S, n);
    int arr[n];
    int result = (n >= 3) && !(sum % 3) && isSubsetExists(S, n - 1, (int)sum / 3, (int)sum / 3, (int)sum / 3, arr);
    Answer *answer = malloc(sizeof(Answer));
    answer->partition = result;
    answer->subset = calloc(3, sizeof(Subset *));
    if (result)
    {
        for (int i = 0; i < 3; i++)
        {
            answer->subset[i] = malloc(sizeof(Subset));
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == i + 1)
                {
                    answer->subset[i]->len++;
                }
            }
            answer->subset[i]->subset = calloc(answer->subset[i]->len, sizeof(int));

            int k = 0;
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == i + 1)
                {
                    answer->subset[i]->subset[k] = S[j];
                    if (i == 0)
                    {
                        subset1[k] = S[j];
                    }
                    if (i == 1)
                    {
                        subset2[k] = S[j];
                    }
                    if (i == 2)
                    {
                        subset3[k] = S[j];
                    }
                    k++;
                }
            }
        }
    }
}