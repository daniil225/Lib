#ifndef RB_TREE_
#define RB_TREE_


enum Color
{
    BLACK,
    RED
};

struct Node
{
    struct Node *p;
    struct Node *left;
    struct Node *right;
    enum Color color;
    int key;
};

struct RbTree
{
    struct Node *root;
    int size;
};

void Init(struct RbTree *rbtree);


void LeftRotate(struct RbTree *rbtree, struct Node *x);
void RightRotate(struct RbTree *rbtree, struct Node *x);

void Insert(struct RbTree *rbtree, struct Node *z);
void InsertFixUp(struct RbTree *rbtree, struct Node *z);

void Transplant(struct RbTree *rbtree, struct Node *u, struct Node *v);
struct Node* TreeMin(struct Node *x);

void Delete(struct RbTree *rbtree, struct Node *z);

void DeleteFixUp(struct RbTree *rbtree,struct Node *child, struct Node *parent);

struct Node* find(struct RbTree *rbtree, int key);

struct Node* MakeNode(int k);

void Print(struct Node *root, int OutputMode);

#endif