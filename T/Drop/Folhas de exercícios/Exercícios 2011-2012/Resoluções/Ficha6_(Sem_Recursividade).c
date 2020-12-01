#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int elem;
	struct node *esq;
	struct node *dir;
} Node, *Tree;

Tree insert(Tree t, int x){
	if(t == NULL){
		t = (Tree)malloc(sizeof(Node));
		t->elem = x;
		t->esq = NULL;
		t->dir = NULL;
		return t;
	}
	Tree aux = t;
	Tree anterior = NULL;
	while(t != NULL){
		anterior = t;
		if(t->elem == x) return t;
		if(t->elem > x) t = t->esq;
		else t = t->dir;
	}	
	t = (Tree)malloc(sizeof(Node));
	t->elem = x;
	t->esq = NULL;
	t->dir = NULL;	
	if(anterior->elem > x) anterior->esq = t;
	else anterior->dir = t;	
	return aux;
}

Tree extractMin(Tree t, int *x){
	Tree aux = t;
	if(t == NULL) { *x = 0; return 0; }
	while(t->esq->esq != NULL) t = t->esq;
	*x = t->esq->elem;
	if(t->esq->dir != NULL) t->esq = t->dir;
	return aux;
}

int exists(Tree t, int x){
	if(t == NULL) return 0;
	while(t != NULL){
		if(t->elem == x) return 1;
		if(t->elem > x) t = t->esq;
		else t = t->dir;
	}
	return 0;
}

int sum(Tree t, int *x);

int main(){	
	Tree p = NULL;
	int x = 0;
	
	p = insert(p,10);
	p = insert(p,20);
	p = insert(p,5);
	
	p = extractMin(p,&x);
	
	//printf("%d\n",x);
	
	//printf("%d\n",exists(p,10));
	
	//printf("%d\n",p->elem);
	//printf("%d\n",p->dir->elem);
	//printf("%d\n",p->esq->elem);
	
	return 0;
}
