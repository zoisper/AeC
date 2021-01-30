#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NE 0


struct edge {
int dest;
int weight;
struct edge *next;
};

typedef struct edge *GraphL[MAX];

typedef int GraphM[MAX][MAX];


void printGraphM(GraphM g, int size) // imprime Grafo Matriz
{
    int i, j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
            printf ("%d ", g[i][j]);
        

        putchar('\n');
    }
}


void printGraphL(GraphL g, int size) // Imprime Grafo Lista
{
    int i;
    struct edge * aux = NULL;
    for(i=0; i<size; i++)
    {
        printf ("%d ",i);
        for (aux = g[i]; aux; aux = aux->next)
            printf ("--> (%d,%d) ",aux->dest, aux->weight);
            
        putchar('\n');
    }
}

void graphLtoM(GraphM gm, GraphL gl, int size) // converte grafo lista para matriz
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

void graphMtoL(GraphL gl, GraphM gm, int size) // converte grafo matriz para lista
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

int inDegreeM (GraphM g, int size, int v) // calcula grau de entrada do vertice v em grafo matriz
{
    int i, r = 0;
    for(i=0; i<size; i++)
        if (g[i][v] != 0)
            r++;
    return r;
}

int outDegreeM (GraphM g, int size, int v) // calcula grau de saida do vertice v em grafo matriz
{
    int i, r = 0;
    for(i=0; i<size; i++)
        if (g[v][i] != 0)
            r++;
    return r;

}

int inDegreeL (GraphL g, int size, int v) // calcula grau de entrada do vertice v em grafo lista
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
int outDegreeL (GraphL g, int v) // calcula grau de saida do vertice v em grafo lista
{
    int r = 0;
    struct edge * aux = NULL;
    aux = g[v];
    while (aux)
    {
        r++;
        aux = aux->next;
    }
    return r;
}

void printDegreeL (GraphL g, int size) // imprime graus de entrada e saida dos vertices do grafo
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

void calcPaths(GraphL g, int size, int source, int parent[]) // calcula caminhos menores partindo do vertice source
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


void showPathAux (GraphL g, int source, int destiny, int parent[]) // função auxiliar para imprimir caminhos do vertice source para o vertice destiny
{
    
    if(source != destiny)
    {
        showPathAux (g, source, parent[destiny], parent);
        printf ("%d ", destiny);
    }
    
    else
        printf("%d ",source );       
}

void showPath (GraphL g, int source, int destiny, int parent[]) // Imprime caminho do vertice source para o vertice destiny
{
    if (parent[destiny] == -2)
            printf ("%d nao alcancavel a partir de %d\n", destiny, source);
        else
        {
            printf("Caminho de %d para %d:\n", source, destiny);
            showPathAux (g, source, destiny, parent);
        }
}

void showPathReverse (GraphL g, int source, int destiny, int parent[]) // Imprime caminho invertido do vertice source para o vertice destiny
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

void shortestPath (GraphL g, int size, int source, int destiny) // calcula e imprime caminho mais curto do source para o vertice destiny 
{
    int parent[size];
    calcPaths(g, size, source, parent);
    showPath(g, source, destiny, parent);
    putchar('\n');
    showPathReverse(g, source, destiny, parent);
}


void prim (GraphL gl, int size, int source, GraphM gm) // calcula a arvore geradora minima do grafo
{
    int i, v, len = 0, edges = size , fringe[size], color[size], parent[size];
    struct edge * aux;
    for(i=0; i<size; i++)
    {
        fringe[i] = 0;
        color[i] = WHITE;
        parent[i] = -2;    
    }
    color[source] = GRAY;
    parent[source] = source;
    v = source;
    len++;

    while(edges>0 && len>0)
    {
        
        for(aux = gl[v]; aux; aux = aux->next)
        {
            if(color[aux->dest] == WHITE)
            {
                color[aux->dest] = GRAY;
                parent[aux->dest] = v;
                fringe[aux->dest] = aux->weight;
                len++;
            }
            else    
                if (color[aux->dest] == GRAY && fringe[aux->dest] > aux->weight)
                {
                    parent[aux->dest] = v;
                    fringe[aux->dest] = aux->weight;
                }
        }
        color[v] = BLACK;
        v = minEdge(color, fringe, len);
        edges--;
        len--;
    }

    if(len == 0 && edges>0)
        printf("Grafo não ligado\n");
    for(i=0; i<size; i++)
        gm[parent[i]][i] = fringe[i];
}

void FloydWarshall (GraphM g, GraphM d, int size, int paths[MAX][MAX])
{
    int i, j, k;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            d[i][j] = g[i][j];
                paths[i][j] = -1;
        }

    for(k=0; k<size; k++)
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
            {
                if(d[i][k] > 0 && d[k][j] > 0 && d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    paths[i][j] = k; 
                }
            }
} 

void showPathFloydWashal (int paths[MAX][MAX], int source, int destiny)
{
    {
        while (destiny != -1)
        {
            printf("%d ", destiny);
            destiny = paths[source][destiny];
        }
        printf("%d ", source);
    }
}





int main ()
{

    
    GraphM gm1 = {
    {NE,  2, NE, NE, NE,  7,  3, NE, NE},
    { 2, NE,  4, NE, NE, NE,  6, NE, NE},
    {NE,  4, NE,  2, NE, NE, NE,  2, NE},
    {NE, NE,  2, NE,  1, NE, NE,  8, NE},
    {NE, NE, NE,  1, NE,  6, NE, NE,  2},
    { 7, NE, NE, NE,  6, NE, NE, NE,  5},
    { 3,  6, NE, NE, NE, NE, NE,  3,  1},
    {NE, NE,  2,  8, NE, NE,  3, NE,  4},
    {NE, NE, NE, NE,  2,  5,  1,  4, NE}
    };   

    //printGraphM(gm1, 9);

    GraphL gl;
    graphMtoL (gl, gm1, 9 ); 

    printGraphM(gm1, 9);
    //dfs(gl, 9);
    //printf ("\n---------------------------------\n");
    //bfs(gl, 9);
    //printf ("\n---------------------------------\n");
    //shortestPath(gl, 9,  3, 5);
    printf ("\n---------------------------------\n");
    //shortestPath(gl, 9, 3, 1);
    //GraphM gm2;
    //prim(gl, 9, 2, gm2);

    //printGraphM(gm2, 9);
    GraphM gm2;
    int P[MAX][MAX];

    FloydWarshall(gm1, gm2, 9, P);
    showPathFloydWashal(P, 0, 1);
    //printf("%d", P[0][1]);




    return 0;
}


