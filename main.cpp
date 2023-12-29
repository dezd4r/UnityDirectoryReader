#include "headers/DirectoryParser.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        throw std::runtime_error("wrong number of arguments");
    }

    std::string inputDirectory(argv[1]);
    std::string outputDirectory(argv[2]);

    DirectoryParser directoryParser;

    directoryParser.setOutputDirectory(outputDirectory);
    directoryParser.directoryWalker(inputDirectory);
    directoryParser.writeUnusedScripts();
}
