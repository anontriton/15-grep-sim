#include <iostream>
#include "FileManager.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << std::endl;
        return 1;
    }

    FileManager fileManager(argv[1], argv[2]);
    fileManager.processQueries();

    return 0;
}
