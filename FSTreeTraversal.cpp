#include "FSTree.h"
#include <iostream>
#include <string>

// recursive function to traverse the tree and print file path
void traversePrint(DirNode *node, const std::string &currPath) {
    // base case, if the node has files then print their paths
    if (node->hasFiles()) {
        for (int i = 0; i < node->numFiles(); ++i) {
            std::cout << currPath << "/" << node->getFile(i) << std::endl;
        }
    }

    // recursively traverse subdirectories
    if (node->hasSubDir()) {
        for (int i = 0; i < node->numSubDirs(); ++i) {
           traversePrint(node->getSubDir(i),
                         currPath + "/" + node->getSubDir(i)->getName());
        }
    }
}


/*
int main(int argc, char *argv[]) {
    // check for the correct number of command line arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " Directory" << std::endl;
        return EXIT_FAILURE;
    }

    // get the directory path from provided argument
    std::string directory = argv[1];

    // create FSTree object w/ the specified root directory
    FSTree tree(directory);

    // call traversePrint to traverse tree and print the full file paths
    traversePrint(tree.getRoot(), directory);

    return 0;
}
*/