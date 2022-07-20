#include<stdio.h>
#include "Rb_Tree.h"

int main(){
    

    int OutputMode = 1;
    struct Rb_Tree rbtree;
    
    InitRBTree(&rbtree);

    rbtree.root->key = 5;

    // Создадим два листа 


    // Т.к нет операции Insert приходится производить данную инициализацию
    struct Node node1_left = {.color = BLACK, .key = 100, .p = NULL, .left = NULL, .right = NULL};
    struct Node node1_right = {.color = BLACK, .key = 170, .p = NULL, .left = NULL, .right = NULL};

    struct Node node2_left = {.color = BLACK, .key = 45, .p = NULL, .left = NULL, .right = NULL};
    struct Node node2_right = {.color = BLACK, .key = 89, .p = NULL, .left = NULL, .right = NULL};
    
    

    struct Node node1 = {.color = RED, .key = 10, .p = rbtree.root, .left = &node1_left, .right = &node1_right};
    struct Node node2 = {.color = RED, .key = 17, .p = rbtree.root, .left = &node2_left, .right = &node2_right};
    


    rbtree.root->left = &node1;
    rbtree.root->right = &node2;

    PrintTree(rbtree.root, OutputMode);

    LeftRotate(&rbtree, rbtree.root->right);
    RightRotate(&rbtree, rbtree.root->right);
    printf("\n After Left Rotate: \n");
    PrintTree(rbtree.root, OutputMode);

    return 0;
}
