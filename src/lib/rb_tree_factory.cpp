#include "./rb_tree.h"


RBTree* FactoryRBTree::CreateFactoryRBTree(uint32_t key, std::string value)
{
    RBTree **root = new RBTree*;
    *root = new RBTree(key, value);
    (*root)->color = black;
    (*root)->root = root; 
    return *root;
}