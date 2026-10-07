#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


static void infoAdjacency(int** A, int N)
{
    int i, j, degree, found, edges = 0;

    for (i = 0; i < N; i++)
        for (j = i; j < N; j++)
            if (A[i][j] == 1) edges++;

    printf("\nРазмер графа |E| = %d\n", edges);

    printf("\nСтепени вершин:\n");
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
            if (i != j) degree += A[i][j];
        degree += 2 * A[i][i];
        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    printf("\nИзолированные вершины (степень 0): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
            if (i != j) degree += A[i][j];
        degree += 2 * A[i][i];
        if (degree == 0) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");

    printf("\nКонцевые вершины (степень 1): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < N; j++)
            if (i != j) degree += A[i][j];
        degree += 2 * A[i][i];
        if (degree == 1) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");

    printf("\nДоминирующие вершины (смежны со всеми %d): ", N - 1);
    found = 0;
    for (i = 0; i < N; i++)
    {
        int neighbors = 0;
        for (j = 0; j < N; j++)
            if (i != j && A[i][j] == 1) neighbors++;
        if (neighbors == N - 1) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");
    printf("\n");
}


static void infoIncidence(int** inc, int N, int edges)
{
    int i, j, degree, found;

    printf("\nРазмер графа |E| = %d\n", edges);

    printf("\nСтепени вершин:\n");
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++) degree += inc[i][j];
        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    printf("\nИзолированные вершины (степень 0): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++) degree += inc[i][j];
        if (degree == 0) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");

    printf("\nКонцевые вершины (степень 1): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        degree = 0;
        for (j = 0; j < edges; j++) degree += inc[i][j];
        if (degree == 1) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");

    printf("\nДоминирующие вершины (смежны со всеми %d): ", N - 1);
    found = 0;
    for (i = 0; i < N; i++)
    {
        int neighbors = 0;
        for (j = 0; j < N; j++)
        {
            int e, linked = 0;
            if (i == j) continue;
            for (e = 0; e < edges; e++)
            {
                if (inc[i][e] == 1 && inc[j][e] == 1) { linked = 1; break; }
            }
            if (linked) neighbors++;
        }
        if (neighbors == N - 1) { printf("v%d ", i + 1); found = 1; }
    }
    if (!found) printf("нет");
    printf("\n");
}

static void printSquare(int** M, int N)
{
    int i, j;
    printf("       ");
    for (j = 0; j < N; j++) printf("%4d", j + 1);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("v%-5d ", i + 1);
        for (j = 0; j < N; j++) printf("%4d", M[i][j]);
        printf("\n");
    }
}

static void printIncidence(int** inc, int N, int edges)
{
    int i, j;
    printf("       ");
    for (j = 0; j < edges; j++) printf("e%-3d", j + 1);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("v%-5d ", i + 1);
        for (j = 0; j < edges; j++) printf("%-4d", inc[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int N, p, loops;
    int i, j, edge, edges;
    int** A, ** inc;

    if (setlocale(LC_ALL, "Russian_Russia.1251") == NULL)
        setlocale(LC_ALL, "ru_RU.UTF-8");

    srand((unsigned)time(NULL));

    printf("Введите количество вершин N (>0): ");
    if (scanf("%d", &N) != 1 || N <= 0)
    {
        printf("Неверное N\n");
        return 1;
    }

    printf("Введите вероятность появления ребра в %% (0..100): ");
    if (scanf("%d", &p) != 1 || p < 0 || p > 100)
    {
        printf("Неверная вероятность\n");
        return 1;
    }

    printf("Учитывать петли? (1 - да, 0 - нет): ");
    if (scanf("%d", &loops) != 1) loops = 0;


    A = (int**)malloc((size_t)N * sizeof(int*));
    if (A == NULL) { printf("Ошибка памяти\n"); return 1; }
    for (i = 0; i < N; i++)
    {
        A[i] = (int*)calloc((size_t)N, sizeof(int));
        if (A[i] == NULL) { printf("Ошибка памяти\n"); return 1; }
    }


    for (i = 0; i < N; i++)
        for (j = i + 1; j < N; j++)
            if (rand() % 100 < p)
            {
                A[i][j] = 1;
                A[j][i] = 1;
            }

    if (loops)
    {
        for (i = 0; i < N; i++)
            if (rand() % 100 < p) A[i][i] = 1;
    }


    printf("\n МАТРИЦА СМЕЖНОСТИ \n");
    printSquare(A, N);

    printf("\n--- сведения по матрице смежности ---");
    infoAdjacency(A, N);

    edges = 0;
    for (i = 0; i < N; i++)
        for (j = i; j < N; j++)
            if (A[i][j] == 1) edges++;

    if (edges > 0)
    {
        inc = (int**)malloc((size_t)N * sizeof(int*));
        if (inc == NULL) { printf("Ошибка памяти\n"); return 1; }
        for (i = 0; i < N; i++)
        {
            inc[i] = (int*)calloc((size_t)edges, sizeof(int));
            if (inc[i] == NULL) { printf("Ошибка памяти\n"); return 1; }
        }

        edge = 0;
        for (i = 0; i < N; i++)
        {
            for (j = i; j < N; j++)
            {
                if (A[i][j] == 1)
                {
                    if (i == j)
                    {
                        inc[i][edge] = 2;
                    }
                    else
                    {
                        inc[i][edge] = 1;
                        inc[j][edge] = 1;
                    }
                    edge++;
                }
            }
        }


        printf("\n МАТРИЦА ИНЦИДЕНТНОСТИ \n");
        printIncidence(inc, N, edges);

        printf("\n--- сведения по матрице инцидентности ---");
        infoIncidence(inc, N, edges);


        for (i = 0; i < N; i++) free(inc[i]);
        free(inc);
    }
    else
    {
        printf("\nРёбер нет — матрица инцидентности пуста.\n");
    }

    for (i = 0; i < N; i++) free(A[i]);
    free(A);

    return 0;
}