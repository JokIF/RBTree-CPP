#pragma once
#include <stdint.h>
#include <string>


class BaseRBTree
{
    public:
        BaseRBTree() {};
        virtual ~BaseRBTree() {};
        virtual BaseRBTree* lookup(uint32_t key_lookup) = 0;
        virtual void add(uint32_t new_key, std::string new_value) = 0;
        virtual BaseRBTree* min() = 0;
        virtual BaseRBTree* max() = 0;
        virtual void delete_node(uint32_t key_del) = 0;
        virtual void delete_tree() = 0;
        virtual std::string get_value() = 0;
};