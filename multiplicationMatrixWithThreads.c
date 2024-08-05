/*
İki matrisi çarp ve her thread bir matris hücresinin hesaplanmasını sağlar.
Mutex kullanarak ortak kaynakların senkronizasyonunu sağla.
*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int row;
    int col;
    int colsA;
    int common_dim;
    int** firstMatrix;
    int** secondMatrix;
    int** resultMatrix;
} thread_data_t;

int** allocMatrix(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int*)malloc(cols * sizeof(int));
    return matrix;
}

void fillMatrixRandomly(int rows, int cols, int** matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    
}

void* computeCell(void* arg)
{
    thread_data_t* data = (thread_data_t*)arg;
    int sum = 0;

    for (int k = 0; k < data->common_dim; k++)
    {
        sum += data->firstMatrix[data->row][k] * data->secondMatrix[k][data->col];
    }
    pthread_mutex_lock(&mutex);
    data->resultMatrix[data->row][data->col] = sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}


void printMatrix(int rows, int cols, int** matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void freeMatrix(int** matrix, int rows)
{
    for(int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}


int main()
{
    srand(time(0));

    int rowsA, colsA, rowsB, colsB;

    printf("Enter the number of rows and columns for the first matrix: ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter the number of rows and columns for the second matrix: ");
    scanf("%d %d", &rowsB, &colsB);

    if (colsA != rowsB)
    {
        printf("Matrix multiplication is not possible with the given dimensions.\n Columns for the first matrix and rows for the second matrix has to be equal.");
        return 1;
    }

    int** firstMatrix = allocMatrix(rowsA, colsA);
    int** secondMatrix = allocMatrix(rowsB, colsB);
    int** resultMatrix = allocMatrix(rowsA, colsB);

    
    fillMatrixRandomly(rowsA, colsA, firstMatrix);
    fillMatrixRandomly(rowsB, colsB, secondMatrix);
    
    printf("First matrix is: \n");
    printMatrix(rowsA, colsA, firstMatrix);
    printf("Second matrix is: \n");
    printMatrix(rowsB, colsB, secondMatrix);

    pthread_t threads[rowsA * colsB];
    thread_data_t thread_data[rowsA * colsB];

    int thread_index = 0;
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            thread_data[thread_index].row = i;
            thread_data[thread_index].col = j;
            thread_data[thread_index].colsA = colsA;
            thread_data[thread_index].common_dim = colsA;
            thread_data[thread_index].firstMatrix = firstMatrix;
            thread_data[thread_index].secondMatrix = secondMatrix;
            thread_data[thread_index].resultMatrix = resultMatrix;

            pthread_create(&threads[thread_index], NULL, computeCell, (void*)&thread_data[thread_index]);
            thread_index++;
        }
    }
    for (int i = 0; i < rowsA * colsB; i++)
        pthread_join(threads[i], NULL);
    
    printf("Result matrix is: \n");
    printMatrix(rowsA, colsB, resultMatrix);

    freeMatrix(firstMatrix, rowsA);
    freeMatrix(secondMatrix, rowsB);
    freeMatrix(resultMatrix, rowsA);

    pthread_mutex_destroy(&mutex);

    return 0;
}