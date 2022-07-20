#include <stdio.h>
#include <stdlib.h>
#include "Rb_Tree.h"

void InitRBTree(struct Rb_Tree *rbtree)
{
    rbtree->nil = malloc(SIZE_NODE);
    rbtree->root = malloc(SIZE_NODE);
    
    rbtree->nil->color = BLACK;
    rbtree->nil->key = 0;
    rbtree->nil->left = NULL;
    rbtree->nil->right = rbtree->root;
    rbtree->nil->p = NULL;

    rbtree->root->p = rbtree->nil; // nil является родителем для корневого элемента
    rbtree->root->left = NULL;
    rbtree->root->right = NULL;
    rbtree->root->color = BLACK; // Корень дерева черный
    rbtree->root->key = 0; // Default value

    rbtree->size = 3;
}


// Операция левого поворота
void LeftRotate(struct Rb_Tree *rbtree, struct Node *x)
{

    // Условия в предположенни которых ведется работа со структурой 
    if(x->right == rbtree->nil) return;
    if(rbtree->root->p != rbtree->nil) return;

    
    struct Node *y = x->right; // Установка y
    x->right = y->left; // Превращение левого поддерва у в правое поддерево х
    
    //if(y->left != rbtree->nil) y->left->p = x; // Без установки 

    y->p = x->p; // Передача родителя х узлу у

    if(x->p == rbtree->nil) rbtree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;

    y->left = x; // Размещение х в качестве левого дочернего узла 
    x->p = y;
    
}

// Операция правого поворота
void RightRotate(struct Rb_Tree *rbtree, struct Node *x)
{
    if(x->right == rbtree->nil) return;
    if(rbtree->root->p != rbtree->nil) return;

    struct Node *y = x->left;
    x->left = y->right;

    //if(y->right != rbtree->nil) y->right->p = x;
    y->p = x->p;

    if(x->p == rbtree->nil) rbtree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->right = x;
    x->p = y;
}

void PrintTree(struct Node const *root, int flag)
{
    if(root != NULL)
    {
        PrintTree(root->left, flag);
        if(flag)
            printf("addres = %p left = %p right = %p key = %d\n", root ,root->left, root->right, root->key);
        else
            printf("%d ", root->key);
        PrintTree(root->right, flag);
    }
}

