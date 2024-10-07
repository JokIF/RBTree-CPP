#include <stdint.h>
#include <string>

enum Color
{
    red,
    black
};

class RBTree
{
    public:
        friend class FactoryRBTree;
        RBTree(uint32_t key, std::string value, RBTree* parent=nullptr);
        ~RBTree();
        RBTree* lookup(uint32_t key_lookup);
        void add(uint32_t new_key, std::string new_value);
        RBTree* min();
        void delete_node(uint32_t key_del);
        void delete_tree();
        std::string get_value();
        RBTree* max();

    private:
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