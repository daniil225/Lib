#include<stdio.h>
#include "Rb_Tree.h"

int main(){
    

    int OutputMode = 1;
    struct Rb_Tree rbtree;
    
    InitRBTree(&rbtree);

    for(int i = -5; i < 15; i++)
    {
        if(i != 0)
            RbInsert(&rbtree, MakeNode(i));
    }
        


    //RbDelete(&rbtree, find(&rbtree, 1));

    //RbDelete(&rbtree, find(&rbtree, 0));

    printf("%d\n", find(&rbtree, 4)->key);
    PrintTree(rbtree.nil,rbtree.root, OutputMode);

    return 0;
}
