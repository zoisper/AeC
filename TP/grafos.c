#include <stdio.h>
#include <stdlib.h>

#define NE 0
#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef int WEIGHT;

struct edge {
  int dest;
  WEIGHT weight;
  struct edge *next;
};

typedef struct edge *GraphL[MAX];

typedef WEIGHT GraphM[MAX][MAX];

typedef struct queue {
int inicio, tamanho;
int valores [MAX];
} QUEUE;


int color[MAX];
int parent[MAX];

void initQueue (QUEUE *q)
{
    q->inicio = 0;
    q->tamanho = 0;
}

int isEmptyQ (QUEUE *q)
{
    return q->tamanho == 0;
}

void enqueue (QUEUE *q, int x)
{
    if (q->tamanho < MAX)
    {
        q->valores[(q->inicio + q->tamanho) % MAX] = x;
        q->tamanho++; 
    }
}

int dequeue (QUEUE *q)
{
    int r = q->valores[q->inicio];
    q->tamanho--;
    q->inicio = (q->inicio + 1) % MAX; 
    return r;
}

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
                (*ptr)->dest = j;
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
        if (gm[i][v] != 0)
            r++;
    return r;
}

int outDegreeM (GraphM gm, int v)
{
    int i, r = 0;
    for(i=0; i<MAX; i++)
        if (gm[v][i] != 0)
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
    aux = gl[v];
    while (aux)
    {
        r++;
        aux = aux->next;
    }
    return r;
}

void printDegreeL (GraphL gl, int N) // imprme graus de entrada e saida dos vertices do grafo
{
    int i, inDeg, outDeg;

    for(i=0; i<N; i++)
    {
        inDeg = inDegreeL(gl,N,i);
        outDeg = outDegreeL(gl,i);
        printf("Verice %d :: Grau Entrada %d :: Grau Saida %d\n",i, inDeg, outDeg);
    }
}


void df_visit(GraphL g, int s)
{
    color[s] = GRAY;
    printf ("%d GRAY\n", s);
    struct edge * aux = g[s];
    while (aux)
    {
        if(color[aux->dest] == WHITE)
        {
            parent[aux->dest] = s;
            df_visit (g, aux->dest);
        }
        aux = aux->next; 
    }
    color[s] = BLACK;
    printf ("%d BLACK\n", s);

}


void dfs (GraphL g, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }

    for(i=0; i<n; i++)
        if (color[i] == WHITE)
            df_visit(g,i);
}

void bf_visit(GraphL g, int s)
{
    QUEUE q;
    initQueue (&q);
    color[s] = GRAY;
    printf ("%d GRAY\n", s);
    parent[s] = 0;
    enqueue(&q, s);
    while (! isEmptyQ (&q))
    {
        int u = dequeue (&q);
        struct edge * aux = g[u];
        while (aux)
        {
            if (color[aux->dest] == WHITE)
            {
                color[aux->dest] = GRAY;
                printf ("%d GRAY\n", aux->dest);
                parent[aux->dest] = u;
                enqueue (&q, aux->dest);
            }
            aux = aux->next;
        }
        color[u] = BLACK;
        printf ("%d BLACK\n", u);
    }


    
}

void bfs (GraphL g, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }

    for(i=0; i<n; i++)
        if (color[i] == WHITE)
            bf_visit(g,i);
    
}


int main ()
{
    GraphM gm3 = {
    {0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 1, 0, 0},
    }; 
    
    //printGraphM (gm3, n3);
    //putchar('\n');

    GraphL gl3;
    int n3 = 9;
    graphMtoL(gl3, gm3, n3);

    //printGraphL(gl3, n3);
    //putchar('\n');
   
    //printDegreeL (gl3, n3);
    //putchar('\n');

    printf("Depth-first traversal:\n");
    dfs(gl3, n3);
    putchar('\n');


    printf("Breadth-first traversal:\n");
    bfs(gl3, n3);
    putchar('\n');


    return 0;
     
}
