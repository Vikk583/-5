#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 8
#define MAX_EDGES (N * (N - 1) / 2)

int main(void)
{
    int A[N][N];
    int incidence[N][MAX_EDGES];

    int i, j;
    int edges = 0;
    int edge = 0;
    int degree;
    int found;

    if (setlocale(LC_ALL, "Russian_Russia.1251") == NULL)
    {
        if (setlocale(LC_ALL, "ru_RU.UTF-8") == NULL)
        {

        }
    }

    srand((unsigned)time(NULL));


    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = 0;
        }
    }

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            A[i][j] = rand() % 2;
            A[j][i] = A[i][j];
        }
    }

    printf("МАТРИЦА СМЕЖНОСТИ\n");

    printf("       ");
    for (i = 0; i < N; i++)
    {
        printf("%4d", i + 1);
    }
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("v%-4d ", i + 1);
        for (j = 0; j < N; j++)
        {
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    edges = 0;
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (A[i][j] == 1)
            {
                edges++;
            }
        }
    }

    printf("\nРазмер графа |E| = %d\n", edges);

    printf("\nСтепени вершин:\n");
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }
        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    printf("\nИзолированные вершины (степень 0): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }
        if (degree == 0)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }

    printf("\nКонцевые вершины (степень 1): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }
        if (degree == 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }

    printf("\nДоминирующие вершины (степень %d): ", N - 1);
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }
        if (degree == N - 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }
    printf("\n");

    //инцидентность
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < MAX_EDGES; j++)
        {
            incidence[i][j] = 0;
        }
    }

    edge = 0;
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (A[i][j] == 1)
            {
                if (edge >= MAX_EDGES)
                {
                    printf("Ошибка: превышено MAX_EDGES!\n");
                    return 1;
                }
                incidence[i][edge] = 1;
                incidence[j][edge] = 1;
                edge++;
            }
        }
    }

    printf("МАТРИЦА ИНЦИДЕНТНОСТИ\n");

    printf("       ");
    for (j = 0; j < edges; j++)
    {
        printf("e%-3d", j + 1);
    }
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("v%-4d ", i + 1);
        for (j = 0; j < edges; j++)
        {
            printf("%-4d", incidence[i][j]);
        }
        printf("\n");
    }


    printf("\nРазмер графа |E| = %d\n", edges);

    printf("\nСтепени вершин:\n");
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++)
        {
            degree += incidence[i][j];
        }
        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    printf("\nИзолированные вершины (степень 0): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++)
        {
            degree += incidence[i][j];
        }
        if (degree == 0)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }

    printf("\nКонцевые вершины (степень 1): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++)
        {
            degree += incidence[i][j];
        }
        if (degree == 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }

    printf("\nДоминирующие вершины (степень %d): ", N - 1);
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++)
        {
            degree += incidence[i][j];
        }
        if (degree == N - 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("нет");
    }
    printf("\n");

    return 0;
}