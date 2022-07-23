#include <stdio.h>
#include <stdlib.h>
#include "Rb_Tree.h"


// Основные //////////////////////////////////////////////////////////////
void InitRBTree(struct Rb_Tree *rbtree)
{
    rbtree->nil = malloc(SIZE_NODE);
    rbtree->root = malloc(SIZE_NODE);
    
    rbtree->nil->color = BLACK;
    rbtree->nil->key = 0;
    rbtree->nil->left = NULL;
    rbtree->nil->right = rbtree->root;
    rbtree->nil->p = NULL;

    rbtree->size = 0;
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

void RbInsert(struct Rb_Tree *rbtree, struct Node *z)
{
    if(rbtree->size == 0)
    {
        z->color = BLACK;
        z->left = z->right = z->p = rbtree->nil;
        rbtree->root = z;
        rbtree->nil->right = z;
        rbtree->size = 1;
    }
    else
    {
        struct Node *y = rbtree->nil;
        struct Node *x = rbtree->root;

        while(x != rbtree->nil)
        {
            y = x;
            if(z->key < x->key) x = x->left;
            else x = x->right;
        }

        z->p = y;
        if(y == rbtree->nil) rbtree->root = z;
        else if(z->key < y->key) y->left = z;
        else y->right = z;

        z->left = z->right = rbtree->nil;
        z->color = RED;
        RbInsertFixUp(rbtree, z);
        rbtree->size++;
    }
}

void RbInsertFixUp(struct Rb_Tree *rbtree, struct Node *z)
{
    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left)
        {
            struct Node *y = z->p->p->right;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    LeftRotate(rbtree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(rbtree, z->p->p);
            }
        }
        else
        {
            struct Node *y = z->p->p->left;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    RightRotate(rbtree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(rbtree, z->p->p);
            }
        }
    }

    rbtree->root->color = BLACK;
}

struct Node* find(struct Rb_Tree *rbtree, int key)
{

    struct Node *x = rbtree->root;
    while(x != rbtree->nil && key != x->key)
    {
        if(key < x->key) x = x->left;
        else x = x->right;
    }

    return x;
}

// Удаление элемента из дерева

void RbTransplant(struct Rb_Tree *rbtree, struct Node* u,struct Node *v)
{
    if(u->p == rbtree->nil) rbtree->root = v;
    else if(u == u->p->left) u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
}

struct Node* TreeMin(struct Node *nil,struct Node *x)
{
    while(x->left != nil) x = x->left;
    return x;
}

void RbDelete(struct Rb_Tree *rbtree, struct Node* z)
{
    struct Node *y = z;
    struct Node *x;
    enum Color y_original_color = y->color;
    
    if(z->left == rbtree->nil)
    {
        x = z->right;
        RbTransplant(rbtree, z, z->right);
    }
    else if(z->right == rbtree->nil)
    {
        x = z->left;
        RbTransplant(rbtree, z, z->left);
    }
    else
    {
        y = TreeMin(rbtree->nil,z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->p == z) x->p = y;
        else
        {
            RbTransplant(rbtree, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }

        RbTransplant(rbtree, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if(y_original_color == BLACK) RbDeleteFixUp(rbtree, x);
    free(z);
}


void RbDeleteFixUp(struct Rb_Tree *rbtree, struct Node* x)
{
    while(x != rbtree->root && x->color == BLACK)
    {
        if(x == x->p->left)
        {
            struct Node *w = x->p->right;
            if(w->color == RED)
            {
                w->color = BLACK;            // Случай 1
                x->p->color = RED;           // Случай 1
                LeftRotate(rbtree, x->p);    // Случай 1
                w = x->p->right;             // Случай 1
            }

            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;    // Случай 2
                x = x->p;          // Случай 2
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(rbtree, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(rbtree, x->p);
                x = rbtree->root;
            }
        }
        else
        {
            struct Node *w = x->p->left;
            if(w->color == RED)
            {
                w->color = BLACK;            // Случай 1
                x->p->color = RED;           // Случай 1
                RightRotate(rbtree, x->p);    // Случай 1
                w = x->p->left;             // Случай 1
            }

            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;    // Случай 2
                x = x->p;          // Случай 2
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(rbtree, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                RightRotate(rbtree, x->p);
                x = rbtree->root;
            }
        }
    }
    x->color = BLACK;
}



//////////////////////////////////////////////////////////////////////////

// Служебные ////////////////////////////////////////////////////////////
void PrintTree(struct Node* nil,struct Node const *root, int flag)
{
    if(root != nil)
    {
        PrintTree(nil,root->left, flag);
        if(flag)
            printf("color = %s parent = %d left = %d right = %d key = %d\n", root->color == RED ? "RED  " : "BLACK" , root->p->key  ,root->left->key, root->right->key, root->key);
        else
            printf("%d ", root->key);
        PrintTree(nil,root->right, flag);
    }
}


struct Node *MakeNode(int key)
{
    struct Node* node = malloc(SIZE_NODE);
    node->key = key;
    return node;
}

/////////////////////////////////////////////////////////////////////////