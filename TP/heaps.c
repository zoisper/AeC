#include <stdio.h>



void swap (int v[], int a, int b)
{
    int aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void showArray (int v[], int N)
{
    int i;
    for(i=0; i <N; i++)
        printf ("%d ",v[i]);
}

//minHeaps

void minBubbleUp (int h[], int N)
{
    int i = N-1, j = (i-1)/2;
    while(i > 0 && h[i] < h[j])
    {
        swap (h, i, j);
        i = j;
        j = (i-1)/2;
    }
}

void minBubbleDown (int h[], int N)
{
    int p, x = 0, controlo = 1;
    while (2 * x + 2 < N && controlo)
    {
        if (h[2*x+1] < h[2*x+2])
            p = 2*x+1;
        else
            p = 2*x+2;
        if (h[x] > h[p])
        {
            swap (h, x, p);
            x = p;
        }
        else
            controlo = 0;  
    }
    if (2*x+1 < N && h[2*x+1] < h[x])
        swap(h, x, 2*x+1 );
}

void decHeapSort (int h[], int N) // oredena array por ordem decrescente
{
    int i;
    for(i=1; i<N; i++)
        minBubbleUp (h,i);
    
    for(i=N-1; i>0; i--)
    {
        swap(h,0,i);
        minBubbleDown (h, i);
    }
}

//maxHeaps

void maxBubbleUp (int h[], int N)
{
    int i = N-1, j = (i-1)/2;
    while(i > 0 && h[i] > h[j])
    {
        swap (h, i, j);
        i = j;
        j = (i-1)/2;
    }
}

void maxBubbleDown (int h[], int N)
{
    int p, x = 0, controlo = 1;
    while (2 * x + 2 < N && controlo)
    {
        if (h[2*x+1] > h[2*x+2])
            p = 2*x+1;
        else
            p = 2*x+2;
        if (h[x] < h[p])
        {
            swap (h, x, p);
            x = p;
        }
        else
            controlo = 0;  
    }
    if (2*x+1 < N && h[2*x+1] > h[x])
        swap(h, x, 2*x+1 );
}

void incHeapSort (int h[], int N) // oredena array por ordem crescente
{
    int i;
    for(i=1; i<N; i++)
        maxBubbleUp (h,i);
    
    for(i=N-1; i>0; i--)
    {
        swap(h,0,i);
        maxBubbleDown (h, i);
    }
}
