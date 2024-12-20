#pragma once
#include "./rb_tree_base.h"
#include <stdint.h>
#include <string>

enum Color
{
    red,
    black
};

class RBTree : public virtual BaseRBTree
{
    public:
        friend class FactoryRBTree;
        RBTree(uint32_t key, std::string value, RBTree* parent=nullptr);
        ~RBTree();
        RBTree* lookup(uint32_t key_lookup) override;
        RBTree* min() override;
        RBTree* max() override;
        void add(uint32_t new_key, std::string new_value) override;
        void delete_node(uint32_t key_del) override;
        void delete_tree() override;
        std::string get_value() override;
        uint32_t get_level_On();

    private:
        void _get_level_On(RBTree* tree, uint32_t* level_tree_gl, uint32_t level_tree=0);
        void _delete_tree();
        void rotate_left();
        void rotate_right();
        void fix_tree_add();
        static void fix_tree_delete(RBTree* node, RBTree* node_parent=nullptr);
        RBTree* left = nullptr;
        RBTree* right = nullptr;
        Color color = red;
        RBTree* parent;
        RBTree** root;

        uint32_t key;
        std::string value;
};

class FactoryRBTree
{
    public:
        static RBTree* CreateFactoryRBTree(uint32_t key, std::string value);
};

bool lemma_truth(uint32_t node_amount, uint32_t level_tree);