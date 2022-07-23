#include <stdio.h>

#include "Rb_Tree.h"

int main()
{
    int Outputmode = 1;

    struct RbTree rbtree;
    Init(&rbtree);

    for(int i = -10; i < 10; i++)
    {
        if(i != 0)
            Insert(&rbtree, MakeNode(i));
    }
    /*elem = -7  parent = -3  right = -5 left = -9  color = RED*/
    Delete(&rbtree, find(&rbtree, -7));
    Print(rbtree.root, Outputmode);

    return 0;
}