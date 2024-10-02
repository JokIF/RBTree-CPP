#include "./lib/rb_tree.h"
#include <iostream>


void foo(RBTree* tree);

int main()
{
    auto tree = FactoryRBTree::CreateFactoryRBTree(14, "ROOTFIRST");
    tree->add(14, "14");
    tree->add(18, "18");
    tree->add(4, "4");
    tree->add(21, "21");
    tree->add(3, "3");
    tree->add(11, "11");
    tree->add(13, "13");
    tree->add(17, "17");
    tree->add(20, "20");
    tree->add(5, "5");
    tree->add(6, "6");
    tree->delete_node(4);
    tree->delete_node(5);
    tree->delete_node(6);
    tree->add(4, "4");
    tree->delete_node(11);
    tree->delete_node(4);
    tree->delete_node(13);
    tree->delete_node(3);

    tree->delete_tree();
}
