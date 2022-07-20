#ifndef RB_TREE_H_
#define RB_TREE_H_


#define SIZE_NODE 40

enum Color
{
    BLACK, // 0
    RED // 1
};

struct Node
{
    enum Color color;
    struct Node *p;
    struct Node *left;
    struct Node *right;
    int key;
};


struct Rb_Tree
{
    struct Node *nil; // Представляет собой точно такое же элемент с теми же атрибутами что и обычный элемент дерева color = BLACK
    // А все остальные атрибуты имеют произвольное значение
    // left == NULL right - указатель на root
    struct Node *root;
    int size;
};

 void InitRBTree(struct Rb_Tree *rbtree);



//////////////////////////////////////////////////////////////////////////////////////////////
// Достаточно проблемно понимается сама суть операции, однако является довольно элементарной 
// Поэтому подробный разбор находится в файле Help_to_understend.pdf
// В файле представлено подробное описание каждого шага алгоритма 

// Левый поворот дерева
void LeftRotate(struct Rb_Tree *rbtree, struct Node *x);
// Правый поворот дерева
void RightRotate(struct Rb_Tree *rbtree, struct Node *x);
//////////////////////////////////////////////////////////////////////////////////////////////



// param: int flag
// 0 - Вывод элементов дерева в порядке (левое-корень-правое) без подробной распечатки адресов всех элементов
// 1 - ---------------------------||------------------------- c подробным выводом всех адресов элементов дерева
void PrintTree(struct Node const *rbtree, int flag);

// Операция вставки элемента в дерево

#endif