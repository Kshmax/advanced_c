#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
///=======================================
// Функция для сравнения двух чисел
// >1 - b>a
// 0  - b==a
// <1 - b<a
///=======================================
int compare (const void * a, const void * b)
{
  return (   *(int*)b - *(int*)a );
}

///=======================================
// Функция ищет M максимальных значений в массиве source размера N методом сортировки
// Возвращает указатель на массив максимальных чисел размера M или NULL в случае ошибки
///=======================================
int* findMax(int *source, int N, int M)
{
    // Валидация входных данных
    if(source == NULL ||
       !(0<N && N<INT_MAX) ||
       !(0<M && M<=N ))
    {
        return NULL;
    }
    // Выделение памяти для копии входного массива
    int *destination = (int*)malloc(N * sizeof(int));
    if(destination == NULL)
    {
        return NULL;
    }
    // Копирование массива
    for(int i = 0; i < N ; i++)
    {
        destination[i] = source[i];
    }
    // Сортировка массива по убыванию для получения M максимальных чисел на участке 0..M-1
    qsort(destination, N, sizeof(int), compare);
    // Урезаем массив до M с учетом проверки на ошибки
    int *destinationCut =  (int*)realloc(destination, M*sizeof(int));
    if(destinationCut == NULL )
    {
        if ( destination != NULL)
        {
            free(destination);
        }
        return NULL;
    }
    // Готовый результат
    return destinationCut;
}

///=======================================
// Принимает два указателя, в которые запишет размер и количество макс. значений
// N и M не должны быть NULL
// Возвращает считанный массив
// Гарантируется отказоустойчивость. Валидность данных не гарантируется
///=======================================
int *readData( long long *N, long long *M)
{
    // Проверка входных данных
    if( N == NULL ||
        M == NULL)
    {
        return NULL;
    }
    // Получаем поток, откуда читаем данные
    FILE *stream = stdin;
    if(stream == NULL)
        return NULL;

    // Читаем N
    if( fscanf(stream, "%lld", N) != 1 || !(0<=*N && *N<INT_MAX) )
    {
        return NULL;
    }

    // Выделяем память под массив
    int *src = (int*)malloc((*N)*sizeof(int));
    if(src == NULL)
    {
        return NULL;
    }
    // Читаем массив
    for(int i = 0; i < *N ; i++)
    {
        if ( fscanf(stream, "%d", src+i) != 1)
        {
            free(src);
            return NULL;
        }
    }
    // Читаем M
    if( fscanf(stream, "%lld", M) != 1)
    {
        free(src);
        return NULL;
    }
    return src;
}

///=========================
// Освобождает ранее использованную в программе память
///=========================
void freeAllocatedMemory(int *source, int *destination)
{
    free(source);
    free(destination);
}

int main()
{
    long long N=-1, M=-1;
    int *src  = NULL;
    int *dest = NULL;
    // Читаем данные, проверяем на успешность И
    // Ищем максимальное, проверяем на успешность.
    if ( (src  = readData(&N, &M))  != NULL &&
         (dest = findMax(src, N, M))  != NULL )
    {
        for( int i=0;i<M;i++)
        {
            printf("%d ", dest[i]);
        }
        freeAllocatedMemory(src, dest);
        return 0;
    }
    if(  M!=0 )
    {
        printf ("[error]");
    }
    freeAllocatedMemory(src, dest);
    return 0;
}
