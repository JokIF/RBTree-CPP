cmake_minimum_required(VERSION 3.2)

project(RedBlackTree)

set(MAIN src/main)

set(RBTree src/lib/rb_tree)
set(RBTreeFacory src/lib/rb_tree_factory)

add_executable(test_tree ${MAIN}.cpp)

add_library(rbtree_lib_base src/lib/rb_tree_base.h)

set_target_properties(rbtree_lib_base PROPERTIES LINKER_LANGUAGE CXX)

add_library(rbtree_lib ${RBTreeFacory}.cpp ${RBTree}.cpp ${RBTree}.h)

target_link_libraries(rbtree_lib PRIVATE rbtree_lib_base)

target_link_libraries(test_tree PRIVATE rbtree_lib)