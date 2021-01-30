#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

struct edge {
int dest;
int weight;
struct edge *next;
};

typedef struct edge *GraphL[MAX];

typedef int GraphM[MAX][MAX];


void printGraphM(GraphM g, int size)
{
    int i, j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        if (g[i][j] != 0)
            printf ("1 ");
        else
            printf ("0 ");

        putchar('\n');
    }
}

void printGraphM_Weight(GraphM g, int size) // imprime vertices com peso
{
    int i, j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
            printf ("%d ",g[i][j]);
        putchar('\n');
    }
}

void printGraphL(GraphL gl, int size)
{
    int i;
    struct edge * aux = NULL;
    for(i=0; i<size; i++)
    {
        for (aux = gl[i]; aux; aux = aux->next)
            printf ("%d ",aux->dest);
            
        putchar('\n');
    }
}

void graphLtoM(GraphM gm, GraphL gl, int size)
{
    int i, j;
    struct edge * aux = NULL;
    
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
            gm[i][j] = 0;

    for(i=0; i<size; i++)
        for (aux = gl[i]; aux; aux = aux->next)
            gm[i][aux->dest] = aux->weight;
}

void graphMtoL(GraphL gl, GraphM gm, int size)
{
    int i, j;
    struct edge **ptr = NULL;
    for(i=0; i<size; i++)
    {
        ptr = &(gl[i]);
        for(j=0; j<size; j++)
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

int inDegreeM (GraphM g, int size, int v)
{
    int i, r = 0;
    for(i=0; i<size; i++)
        if (g[i][v] != 0)
            r++;
    return r;
}

int outDegreeM (GraphM g, int size,  int v)
{
    int i, r = 0;
    for(i=0; i<size; i++)
        if (g[v][i] != 0)
            r++;
    return r;

}

int inDegreeL (GraphL g, int size, int v)
{
    int i, r = 0;
    struct edge * aux = NULL;
    for(i=0; i<size; i++)
    {
        aux = g[i];
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

void printDegreeL (GraphL g, int size) // imprme graus de entrada e saida dos vertices do grafo
{
    int i, inDeg, outDeg;

    for(i=0; i<size; i++)
    {
        inDeg = inDegreeL(g,size,i);
        outDeg = outDegreeL(g,i);
        printf("Verice %d :: Grau Entrada %d :: Grau Saida %d\n",i, inDeg, outDeg);
    }
}

void df_visit(GraphL g, int v, int color[], int parent[]) // travessia em profundidade partindo do verice v
{
    color[v] = GRAY;
    printf ("%d GRAY\n", v);
    struct edge * aux; 
    for (aux = g[v]; aux; aux = aux->next )
        if(color[aux->dest] == WHITE)
        {
            parent[aux->dest] = v;
            df_visit (g, aux->dest, color, parent);
        }

    color[v] = BLACK;
    printf ("%d BLACK\n", v);

}

void dfs (GraphL g, int size) // função de topo que faz travessia em profundidade apartir de todos os vertices ainda não visitados
{
    int i, color[size], parent[size];
    for(i=0; i<size; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }

    for(i=0; i<size; i++)
        if (color[i] == WHITE)
            df_visit(g,i, color, parent);
}

void bf_visit(GraphL g, int v, int color[], int parent[]) // travessia em largura partindo do verice v
{
    int u, firstF = 0, lastF = 0, fringe[MAX];
    struct edge * aux;

    color[v] = GRAY;
    printf ("%d GRAY\n", v);
    fringe [lastF++] = v;
    while (lastF > firstF)
    {
        u = fringe[firstF++];
        for (aux = g[u]; aux; aux = aux->next)
            if (color[aux->dest] == WHITE)
            {
                color[aux->dest] = GRAY;
                parent[aux->dest] = u;
                fringe [lastF++] = aux->dest;
                printf ("%d GRAY\n", aux->dest);
            }
            
        color[u] = BLACK;
        printf ("%d BLACK\n", u);
    }
}

void bfs (GraphL g, int size) // função de topo que faz travessia em largura apartir de todos os vertices ainda não visitados
{
    int i, color[size], parent[size];
    for(i=0; i<size; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }

    for(i=0; i<size; i++)
        if (color[i] == WHITE)
            bf_visit(g,i, color, parent);
}


int minEdge (int color[], int dist[], int size) // calcula qual a aresta com menor peso
{
    int i, r;
    for(i=0; color[i] != GRAY; i++); 
    r = i; // encontrar um valor inicial para o r
    
    for(; i<size; i++)
        if (color[i] == GRAY && dist[i] < dist[r])
            r = i;
    return r;   
}

void calcPaths(GraphL g, int size, int source, int parent[]) // calcula caminhos menores partindo de v
{
    int i, fringe = 1, dist[size], color[size];
    struct edge * aux;

    for(i=0; i<size; i++)
    {
        color[i] = WHITE;
        parent[i] = -2;
    }

    color[source] = GRAY;
    parent[source] = -1;
    dist[source] = 0;
    
    while (fringe > 0)
    {
        fringe--;
        for (aux = g[source]; aux; aux = aux->next)
            if (color[aux->dest] == WHITE)
            {
                color[aux->dest] = GRAY;
                parent[aux->dest] = source;
                dist[aux->dest] = dist[source] + aux->weight;
                fringe++;
            }
            else    
                if (color[aux->dest] == GRAY && dist[aux->dest] > dist[source] + aux->weight)
                {
                    dist[aux->dest] = dist[source] + aux->weight;
                    parent[aux->dest] = source;
                }
        color[source] = BLACK;
        source = minEdge(color, dist, size);
    }
}


void showPathAux (GraphL g, int source, int destiny, int parent[])
{
    
    if(source != destiny)
    {
        showPathAux (g, source, parent[destiny], parent);
        printf ("%d ", destiny);
    }
    
    else
        printf("%d ",source );       
}

void showPath (GraphL g, int source, int destiny, int parent[]) // Imprime caminho 
{
    if (parent[destiny] == -2)
            printf ("%d nao alcancavel a partir de %d\n", destiny, source);
        else
        {
            printf("Caminho de %d para %d:\n", source, destiny);
            showPathAux (g, source, destiny, parent);
        }
}

void showPathReverse (GraphL g, int source, int destiny, int parent[]) // Imprime caminho ao contrario
{
    if (parent[destiny] == -2)
            printf ("%d nao alcancavel a partir de %d\n", destiny, source);
        else
        {
            printf("Caminho inverso de %d para %d:\n", source, destiny);
            while (source != destiny)
            {
                printf ("%d ", destiny);
                destiny = parent[destiny];
            }
            printf("%d ",source );
        }
} 


void shortestPath (GraphL g, int size, int source, int destiny)
{
    int parent[size];
    calcPaths(g, size, source, parent);
    showPath(g, source, destiny, parent);
    putchar('\n');
    showPathReverse(g, source, destiny, parent);

}






int main ()
{

    GraphM gm1 = {
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

    GraphL gl;
    graphMtoL (gl, gm1, 9 ); 
    //dfs(gl, 9);
    //printf ("\n---------------------------------\n");
    //bfs(gl, 9);
    //printf ("\n---------------------------------\n");
    shortestPath(gl, 9,  3, 5);
    printf ("\n---------------------------------\n");
    shortestPath(gl, 9, 3, 1);




    return 0;
}


