cmake_minimum_required(VERSION 3.2)

project(RedBlackTree)

set(MAIN src/main)

set(RBTree src/lib/rb_tree)
set(RBTreeFacory src/lib/rb_tree_factory)

set(ASCENDING_NUMBERS ${CMAKE_SOURCE_DIR}/numbers_ascending.txt)
set(DESCENDING_NUMBERS ${CMAKE_SOURCE_DIR}/numbers_descending.txt)

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

add_executable(test_tree ${MAIN}.cpp)

add_library(rbtree_lib_base src/lib/rb_tree_base.h)

set_target_properties(rbtree_lib_base PROPERTIES LINKER_LANGUAGE CXX)

add_library(rbtree_lib ${RBTreeFacory}.cpp ${RBTree}.cpp ${RBTree}.h)

target_link_libraries(rbtree_lib PRIVATE rbtree_lib_base)

target_link_libraries(test_tree PRIVATE rbtree_lib)

add_custom_command(
    OUTPUT 
    ${ASCENDING_NUMBERS} 
    COMMAND ${CMAKE_COMMAND} -E touch ${ASCENDING_NUMBERS} && seq 0 50000 > ${ASCENDING_NUMBERS}
    )

add_custom_command(
    OUTPUT 
    ${DESCENDING_NUMBERS} 
    COMMAND ${CMAKE_COMMAND} -E touch ${DESCENDING_NUMBERS} && seq 50000 -1 0 > ${DESCENDING_NUMBERS}
    )

add_custom_target(generate_numbers ALL DEPENDS ${ASCENDING_NUMBERS} ${DESCENDING_NUMBERS})
