#include <stdio.h>
#include <stdlib.h>

#define NE 0

#define MAX 100

typedef int WEIGHT;

struct edge {
  int dest;
  WEIGHT weight;
  struct edge *next;
};

typedef struct edge *GraphL[MAX];

typedef WEIGHT GraphM[MAX][MAX];

void printGraphM(GraphM g, int N)
{
    int i, j;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        if (g[i][j] != 0)
            printf ("1 ");
        else
            printf ("0 ");

        putchar('\n');
    }
}

void printGraphM_Weight(GraphM g, int N) // imprime vertices com peso
{
    int i, j;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
            printf ("%d ",g[i][j]);
        putchar('\n');
    }
}

void printGraphL(GraphL gl, int N)
{
    int i;
    struct edge * aux = NULL;
    for(i=0; i<N; i++)
    {
        aux = gl[i];
        while(aux)
        {
            printf ("%d ",aux->dest);
            aux = aux->next;
        }
        putchar('\n');
    }
}

void graphLtoM(GraphM gm, GraphL gl, int N)
{
    int i, j;
    struct edge * aux = NULL;
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            gm[i][j] = 0;

    for(i=0; i<N; i++)
    {
        aux = gl[i];
        while(aux)
        {
            gm[i][aux->dest] = aux->weight;
            aux = aux->next;
        }
    }
        
    
}
void graphMtoL(GraphL gl, GraphM gm, int N)
{
    int i, j;
    struct edge **ptr = NULL;
    for(i=0; i<N; i++)
    {
        ptr = &(gl[i]);
        for(j=0; j<N; j++)
        {
            if (gm[i][j] != 0)
            {
                *ptr = malloc (sizeof (struct edge));
                (*ptr)->dest = j+1;
                (*ptr)->weight = gm[i][j];
                ptr = &((*ptr)->next); 
            }      
        }
    }
}

int inDegreeM (GraphM gm, int N, int v)
{
    int i, r = 0;
    for(i=0; i<N; i++)
        if (gm[i][v-1] != 0)
            r++;
    return r;
}

int outDegreeM (GraphM gm, int v)
{
    int i, r = 0;
    for(i=0; i<MAX; i++)
        if (gm[v-1][i] != 0)
            r++;
    return r;

}
int inDegreeL (GraphL gl, int N, int v)
{
    int i, r = 0;
    struct edge * aux = NULL;
    for(i=0; i<N; i++)
    {
        aux = gl[i];
        while (aux && aux->dest < v)
            aux = aux->next;
        if (aux && aux->dest == v)
            r++;  
    }
    return r;
}
int outDegreeL (GraphL gl, int v)
{
    int r = 0;
    struct edge * aux = NULL;
    aux = gl[v-1];
    while (aux)
    {
        r++;
        aux = aux->next;
    }
    return r;
}

