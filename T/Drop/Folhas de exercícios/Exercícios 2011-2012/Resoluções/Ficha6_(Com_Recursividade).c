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
	}
	else{
		if(t->elem > x) t->esq = insert(t->esq,x);
		else t->dir = insert(t->dir,x);
	}
	return t;
}

Tree extractMin(Tree t, int *x){
	if(t == NULL) return t;
	if(t->esq == NULL) { *x = t->elem; return t->dir; }
	else t->esq = extractMin(t->esq,x);
	return t;
}

int exists(Tree t, int x){
	if(t == NULL) return 0;
	if(t->elem == x) return 1;
	if(t->elem > x) return exists(t->esq,x);
	else return exists(t->esq,x);
}

int sum(Tree t, int *x){
	if(t == NULL){ return *x; }
	*x += t->elem;
	sum(t->dir,x);
	sum(t->esq,x);
	return *x;
}

int main(){
	Tree p = NULL;
	int x = 0;
	
	p = insert(p,10);
	p = insert(p,20);
	p = insert(p,5);
	
	//p = extractMin(p,&x);
	//printf("Existe: %d\n",exists(p,5));
	
	//printf("Soma: %d\n",sum(p,&x));
	
	//printf("%d\n",p->elem);
	//printf("%d\n",p->esq->elem);
	//printf("%d\n",p->dir->elem);
	
	return 0;
}
