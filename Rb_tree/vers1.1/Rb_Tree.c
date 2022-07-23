#include <stdio.h>
#include <stdlib.h>

#include "Rb_Tree.h"


void Init(struct RbTree *rbtree) 
{ 
    rbtree->size = 0; 
    rbtree->root = NULL;    
}




// Операция левого поворота
void LeftRotate(struct RbTree *rbtree, struct Node *x)
{

    // Условия в предположенни которых ведется работа со структурой 
    if(x->right == NULL) return;
    if(rbtree->root->p != NULL) return;

    
    struct Node *y = x->right; // Установка y
    x->right = y->left; // Превращение левого поддерва у в правое поддерево х
    
    if(y->left != NULL) y->left->p = x; // Без установки 

    y->p = x->p; // Передача родителя х узлу у

    if(x->p == NULL) rbtree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;

    y->left = x; // Размещение х в качестве левого дочернего узла 
    x->p = y;
    
}

// Операция правого поворота
void RightRotate(struct RbTree *rbtree, struct Node *x)
{
    if(x->right == NULL) return;
    if(rbtree->root->p != NULL) return;

    struct Node *y = x->left;
    x->left = y->right;

    if(y->right != NULL) y->right->p = x;
    y->p = x->p;

    if(x->p == NULL) rbtree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->right = x;
    x->p = y;
}


void Insert(struct RbTree *rbtree, struct Node *z)
{
    struct Node *x = rbtree->root;
    struct Node *y =  NULL;
    while(x != NULL)
    {
        y = x;
        if(z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->p = y;

    if(y != NULL)
    {
        if(z->key > y->key) y->right = z;
        else y->left =z;
    }
    else
    {
        z->p = NULL;
        rbtree->root = z;
    }
    InsertFixUp(rbtree, z);

}





void InsertFixUp(struct RbTree *rbtree, struct Node *z)
{
    
    while(z != rbtree->root && z->p->color == RED)
    {
        if(z->p->p->left == z->p)
        {   
            struct Node *y = z->p->p->right;
            if(y != NULL && y->color == RED)
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
            if(y != NULL && y->color == RED)
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



void Transplant(struct RbTree *rbtree, struct Node *u, struct Node *v)
{
    if(v == NULL) return;
    if(u == NULL) return;
    if(u->p == NULL) rbtree->root = v;
    else if(u == u->p->left) u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
}


struct Node* TreeMin(struct Node *x)
{
    while(x->left != NULL) x = x->left;
    return x;
}



void Delete(struct RbTree *rbtree, struct Node *node)
{
    struct Node *child, *parent;
    enum Color color;

    if(node->left != NULL && node->right != NULL)
    {
        struct Node *replace = node;
        // Find min element
        replace = node->right;
        while(replace->left != NULL)
            replace = replace->left;
        
        if(node->p != NULL)
        {
            if(node->p->left == node)
                node->p->left = replace;
            else node->p->right = replace;
        }
        else
            rbtree->root = replace;
        
        child = replace->right;
        parent = replace->p;
        color = replace->color;

        if(parent == node)
            parent = replace;
        else
        {
            if(child != NULL)
                child->p = parent;
            
            parent->left = child;
            replace->right = node->right;
            node->right->p = replace;
        }

        replace->p = node->p;
        replace->color = node->color;
        replace->left = node->left;
        node->left->p = replace;

        if(color == BLACK)
            DeleteFixUp(rbtree, child, parent);
        
        free(node);
        return;
    }

    if(node->left != NULL)
        child = node->left;
    else 
        child = node->right;
    
    parent = node->p;
    color = node->color;

    if(child)
    {
        child->p = parent;
    }

    if(parent)
    {
        if(node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
    else
    {
        rbtree->root = child;
    }

    if(color == BLACK)
        DeleteFixUp(rbtree, child, parent);

    free(node);
}

void DeleteFixUp(struct RbTree *rbtree, struct Node *node, struct Node *parent)
{
    struct Node *otherNode;

    while((!node) || node->color == BLACK && node != rbtree->root)
    {
        if(parent->left == node)
        {
            otherNode = parent->right;
            if(otherNode->color == RED)
            {
                otherNode->color = BLACK;
                parent->color = RED;
                LeftRotate(rbtree, parent);
                otherNode = parent->right;
            }
            else
            {
                if(!(otherNode->right) || otherNode->right->color == BLACK)
                {
                    otherNode->left->color = BLACK;
                    otherNode->color = RED;
                    RightRotate(rbtree, otherNode);
                    otherNode = parent->right;
                }

                otherNode->color = parent->color;
                parent->color = BLACK;
                otherNode->right->color = BLACK;
                LeftRotate(rbtree, parent);
                //node = rbtree->root;
                break;
            }
        }
        else
        {
            otherNode = parent->left;
            if(otherNode->color == RED)
            {
                otherNode->color = BLACK;
                parent->color = RED;
                RightRotate(rbtree, parent);
                otherNode = parent->left;
            }
            else
            {
                if(!(otherNode->left) || otherNode->left->color == BLACK)
                {
                    otherNode->right->color = BLACK;
                    otherNode->color = RED;
                    LeftRotate(rbtree, otherNode);
                    otherNode = parent->left;
                }

                otherNode->color = parent->color;
                parent->color = BLACK;
                otherNode->left->color = BLACK;
                RightRotate(rbtree, parent);
                //node = rbtree->root;
                break;
            }
        }
    }
    if(node)
        node->color = BLACK;
}

struct Node* find(struct RbTree *rbtree, int key)
{

    struct Node *x = rbtree->root;
    while(x != NULL && key != x->key)
    {
        if(key < x->key) x = x->left;
        else x = x->right;
    }

    return x;
}

void Print(struct Node *root, int OutputMode)
{
    if(root == NULL) return;

    Print(root->left, OutputMode);
    if(OutputMode)
        printf("elem = %d  parent = %d  right = %d left = %d  color = %s\n", 
        root->key,
        root->p == NULL? 0 : root->p->key,
        root->right == NULL ? 0: root->right->key, 
        root->left == NULL  ? 0: root->left->key,
        root->color == RED? "RED" : "BLACK");
    else
        printf("| %d |", root->key);
    Print(root->right, OutputMode);
}

struct Node* MakeNode(int k)
{
    struct Node *node = malloc(sizeof(struct Node));
    node->key = k;
    node->left = NULL;
    node->right = NULL;
    node->color = RED;

    return node;
}
