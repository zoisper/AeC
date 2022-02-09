#include<stdio.h>
#include<stdlib.h>


typedef enum balancefactor { LH , EH , RH } BalanceFactor;

typedef struct treeNode {
BalanceFactor bf;
int entry;
struct treeNode *left;
struct treeNode *right;
} *Tree;


Tree rotateLeft(Tree t)
{
    Tree r = t->right;
    t->right = r->left;
    r->left = t;
    return r;
    
    
}

Tree rotateRight(Tree t)
{
    Tree r = t->left;
    t->left = r->right;
    r->right = t;
    return r;
}

Tree balanceRight(Tree t)
{
    if (t->right->bf == RH)
    {
        t = rotateLeft(t);
        t->left->bf = EH;
    }
    else
    {
        t->right = rotateRight (t->right);
        t = rotateLeft (t);
        if (t->bf == EH)
        {
            t->left->bf = EH;
            t->right->bf = EH;
        }
        else
            if (t->bf == RH)
            {
                t->left->bf = LH;
                t->right->bf = EH;
            }
            else
            {
                t->left->bf = EH;
                t->right->bf = RH;
            }
    }
    t->bf = EH;
    return t;
}

Tree balanceLeft(Tree t)
{
    if (t->left->bf == LH)
    {
        t = rotateRight(t);
        t->right->bf = EH;
    }
    else
    {
        t->left = rotateLeft (t->left);
        t = rotateRight (t);
        if (t->bf == EH)
        {
            t->left->bf = EH;
            t->right->bf = EH;
        }
        else
            if (t->bf == LH)
            {
                t->left->bf = EH;
                t->right->bf = RH;
            }
            else
            {
                t->left->bf = LH;
                t->right->bf = EH;
            }
    }
    t->bf = EH;
    return t;
}

Tree insertTreeAux(Tree t, int e, int *cresceu)
{
    if (!t)
    {
        t = malloc (sizeof (struct treeNode));
        t->entry = e;
        t->bf = EH;
        t->left = NULL;
        t->right = NULL;
        *cresceu = 1;
    }
    else
        if (t->entry < e)
        {
            t->left = insertTreeAux (t->left, e, cresceu);
            if (*cresceu)
            {
                if (t->bf == EH)
                    t->bf = LH;
                else
                    if (t->bf == RH)
                    {
                        t->bf = EH;
                        *cresceu = 0;
                    }
                    else
                    {
                        t = balanceLeft (t);
                        *cresceu = 0;
                    }
            }
        }
        else
        {
            t->right = insertTreeAux (t->right, e, cresceu);
            if (*cresceu)
            {
                if (t->bf == EH)
                    t->bf = RH;
                else
                    if (t->bf == LH)
                    {
                        t->bf = EH;
                        *cresceu = 0;
                    }
                    else
                    {
                        t = balanceRight (t);
                        *cresceu = 0;
                    }
            }
        }
    return t;
}

Tree insertTree(Tree t, int e)
{
    int c = 0;
    t = insertTreeAux (t, e, &c);
    return t;
}

void showTree (Tree t) // imprime a arvore
{
    if (t)
    {
        showTree (t->left);
        printf ("%d ", t->entry);
        showTree (t->right); 
    }
}

int treeHeight (Tree t) // calcula altura da arvore
{
    if (! t)
        return 0;
    else
    {
        int l = treeHeight (t->left);
        int r = treeHeight (t->right);
        if (l > r)
            return l + 1;
        else
            return r + 1;
    }
}

int isAVLTree (Tree t) // verifica se é uma arvore AVL
{
    if (!t)
        return 1;
    else
    {
        int l = treeHeight (t->left);
        int r = treeHeight (t->right);
        
        if (l - r > 1 || l - r < -1 )
            return 0;
        else
            if (l == r && t->bf != EH)
                return 0;
            else
                if (l > r && t->bf != LH)
                    return 0;
                else
                    if ( r > l && t->bf != RH)
                        return 0;
                    else
                        return isAVLTree (t->left) && isAVLTree (t->right);
    }
}
