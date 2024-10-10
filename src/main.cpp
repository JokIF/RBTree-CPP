#include "./lib/rb_tree.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#define PATH(path) std::string(PROJECT_ROOT_DIR) + '/' + path


inline void test_add_delete();
inline void time_test(std::string file_name);

int main()
{
    // test_add_delete();
    time_test("numbers_ascending.txt");
    time_test("numbers_descending.txt");

}

inline void time_test(std::string file_name)
{
    std::ifstream opened_file(PATH(file_name));
    std::string out_string;
    uint32_t key;
    std::chrono::_V2::system_clock::time_point t_start;
    std::chrono::_V2::system_clock::time_point t_end;
    uint32_t rand_key;
    RBTree* lookup_value;
    uint32_t level_tree;
    std::vector<uint32_t> key_arr;

    std::getline(opened_file, out_string);
    key = std::stoi(out_string);
    auto tree = FactoryRBTree::CreateFactoryRBTree(key, out_string);
    int i = 0;

    while(std::getline(opened_file, out_string))
    {
        i++;
        key = std::stoi(out_string);
        tree->add(key, out_string);
        key_arr.push_back(key);
        if (i % 5000 == 0)
        {
            rand_key = key_arr.at(rand() % key_arr.size());
            t_start = std::chrono::high_resolution_clock::now();
            lookup_value = tree->lookup(rand_key);
            t_end = std::chrono::high_resolution_clock::now();
            level_tree = lookup_value->get_level_On();
            std::cout 
                << "nodes: " << i << " level: " << level_tree << " lemma truth: " << lemma_truth(i, level_tree)  
                << "\tlookup key: " << rand_key << " value " << lookup_value->get_value() << "\n";

                // << " time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_start).count() 
                // << " microseconds\n";
        }
    }

    std::cout << '\n';
    tree->delete_tree();
}

inline void test_add_delete()
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

