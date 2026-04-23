#include "binary_tree.h"
#include "node.h"

int main(){
    BinaryTree tree;
    tree.build_expression_tree();
    tree.print_tree();
    tree.replace_multi(tree.get_root());
    tree.print_tree();
    return 0;
}