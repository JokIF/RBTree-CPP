#include "./rb_tree.h"
#include <string>
#include <stdint.h>


RBTree::RBTree(uint32_t key, std::string value, RBTree* parent) : value(value), key(key), parent(parent) 
{
    if (parent != nullptr)
    {
        root = parent->root;
    }
}

void RBTree::add(uint32_t new_key, std::string new_value)
{
    RBTree* tree = *this->root;
    RBTree* parent_tree;
    while (tree != nullptr)
    {
        parent_tree = tree;
        if (tree->key < new_key) tree = tree->right;
        else if (tree->key > new_key) tree = tree->left;
        else
            return;
    }
    
    RBTree* node = new RBTree(new_key, new_value, parent_tree);

    if (node->parent->key < new_key)
        node->parent->right = node;
    else
        node->parent->left = node;

    node->fix_tree_add();
}

void RBTree::fix_tree_add()
{
    RBTree* uncle;
    if (this->parent == nullptr)
    {
        this->color = black;
        return;
    }
    if (this->parent->color == red)
    {
        if (this->parent == this->parent->parent->left)
        {
            uncle = this->parent->parent->right;
            if (uncle != nullptr && uncle->color == red)
            {
                this->parent->color = black;
                uncle->color = black;
                this->parent->parent->color = red;
                this->parent->parent->fix_tree_add();
            }
            else
            {
                RBTree* temp = this;
                if (this == this->parent->right)
                {
                    this->parent->rotate_left();
                    temp = this->left;
                }
                // if (temp->parent)
                temp->parent->color = black;
                temp->parent->parent->color = red;
                temp->parent->parent->rotate_right();
            }
        }

        else if (this->parent == this->parent->parent->right)
        {
            uncle = this->parent->parent->left;
            if (uncle != nullptr && uncle->color == red)
            {
                this->parent->color = black;
                uncle->color = black;
                this->parent->parent->color = red;
                this->parent->parent->fix_tree_add();
            }
            else
            {
                RBTree* temp = this;
                if (this == this->parent->left)
                {
                    this->parent->rotate_right();
                    temp = this->right;
                }
                // if (temp->parent)
                temp->parent->color = black;
                temp->parent->parent->color = red;
                temp->parent->parent->rotate_left();
            }
        }
    }
    (*this->root)->color = black;
}

void RBTree::rotate_left()
{
    RBTree* temp = this->right;
    this->right = temp->left;
    if (temp->left != nullptr)
        temp->left->parent = this;
    temp->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this == this->parent->left)
            this->parent->left = temp;
        else
            this->parent->right = temp;
    }
    temp->left = this;
    this->parent = temp;
    if (*this->root == this)
        *this->root = temp;
}

void RBTree::rotate_right()
{
    RBTree* temp = this->left;
    this->left = temp->right;
    if (temp->right != nullptr)
        temp->right->parent = this;
    temp->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this == this->parent->left)
            this->parent->left = temp;
        else
            this->parent->right = temp;
    }
    this->parent = temp;
    temp->right = this;
    if (*this->root == this)
        *this->root = temp;
}

RBTree* RBTree::lookup(uint32_t key_lookup)
{
    RBTree* tree = *this->root;
    while (tree != nullptr && tree->key != key_lookup)
    {
        if (tree->key < key_lookup) tree = tree->right;
        else if (tree->key > key_lookup) tree = tree->left;
    }
    return tree;
}

RBTree* RBTree::min()
{
    RBTree* min_node = this;
    while (min_node->left != nullptr)
        min_node = min_node->left;
    return min_node;
}

RBTree* RBTree::max()
{
    RBTree* max_node = this;
    while (max_node->right != nullptr)
        max_node = max_node->right;
    return max_node;
}


RBTree::~RBTree()
{
    auto transplant = [](RBTree* node, RBTree* in_node)
    {
        if (*node->root == node) *node->root = in_node;
        else if (node == node->parent->left) node->parent->left = in_node;
        else node->parent->right = in_node;
        if (in_node != nullptr)
            in_node->parent = node->parent;
    };

    if (this->left == nullptr)
        transplant(this, this->right);
    else if (this->right == nullptr)
        transplant(this, this->left);
    else
    {
        RBTree* temp_gr = this->right->min();
        RBTree* fix_node = temp_gr->right;
        // temp_gr_color = temp_gr->color;
        if (temp_gr->parent == this)
        {
            if (fix_node != nullptr) fix_node->parent = temp_gr;
        }
        else
        {
            transplant(temp_gr, temp_gr->right);
            temp_gr->right = this->right;
            temp_gr->right->parent = temp_gr;
        }
        transplant(this, temp_gr);
        temp_gr->left = this->left;
        temp_gr->left->parent = temp_gr;
        temp_gr->color = this->color;
    }
}

void RBTree::fix_tree_delete(RBTree* node, RBTree* node_parent)
{
    RBTree* parent;
    RBTree* temp;
    while (node == nullptr || node != *node->root && node->color == black)
    {
        if (node == nullptr) parent = node_parent;
        else parent = node->parent;
        if (node == parent->left)
        {
            temp = parent->right;
            if (temp->color == red)
            {
                temp->color = black;
                parent->color = red;
                parent->rotate_left();
                temp = parent->right;
            }
            if ((temp->left == nullptr || temp->left->color == black) && (temp->right == nullptr ||temp->right->color == black))
            {
                temp->color = red;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (temp->right == nullptr || temp->right->color == black)
                {
                    if (temp->left != nullptr) temp->left->color = black;
                    temp->color = red;
                    temp->rotate_right();
                    temp = parent->right;
                }
                temp->color = parent->color;
                parent->color = black;
                if (temp->right != nullptr) temp->right->color = black;
                parent->rotate_left();
            }
        }
        else if (node == parent->right)
        {
            temp = parent->left;
            if (temp->color == red)
            {
                temp->color = black;
                parent->color = red;
                parent->rotate_right();
                temp = parent->left;
            }
            if ((temp->left == nullptr || temp->left->color == black) && (temp->right == nullptr ||temp->right->color == black))
            {
                temp->color = red;
                node = parent;
            }
            else
            {
                if (temp->left == nullptr || temp->left->color == black)
                {
                    if (temp->right != nullptr) temp->right->color = black;
                    temp->color = red;
                    temp->rotate_left();
                    temp = parent->left;
                }
                temp->color = parent->color;
                parent->color = black;
                if (temp->left != nullptr) temp->left->color = black;
                parent->rotate_right();
                node = temp->parent;
            }
        }
    }
    if (node != nullptr) node->color = black;
}


void RBTree::delete_node(uint32_t key_del)
{
    RBTree* node_del = this->lookup(key_del);
    RBTree* fix_node;
    RBTree* fix_node_parent;

    if (node_del->left == nullptr && node_del->right == nullptr)
    {
        fix_node = nullptr;
        fix_node_parent = node_del->parent;
    }
    else if (node_del->left == nullptr)
        fix_node = node_del->right;
    else if (node_del->right == nullptr)
        fix_node = node_del->left;
    else
    {
        RBTree* min_right_node = node_del->right->min();
        if (min_right_node->parent == node_del)
        {
            fix_node_parent = min_right_node;
            fix_node = fix_node_parent->right;    
        }
        else
        {
            fix_node_parent = min_right_node->parent;
            fix_node = min_right_node->right;
        }
    }
    
    delete node_del;
    fix_tree_delete(fix_node, fix_node_parent);
}

void RBTree::delete_tree()
{
    RBTree* tree = *this->root;
    if (tree->left != nullptr) tree->left->_delete_tree();
    if (tree->right != nullptr) tree->right->_delete_tree();
    RBTree** del_root = tree->root;
    delete tree;
    delete del_root;
}

void RBTree::_delete_tree()
{
    if (this->left != nullptr) this->left->_delete_tree();
    if (this->right != nullptr) this->right->_delete_tree();
    delete this;
}

std::string RBTree::get_value()
{
    return this->value;
}