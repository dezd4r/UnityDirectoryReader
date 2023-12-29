#include "../headers/DirectoryParser.h"
#include "../headers/SceneParser.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;


void DirectoryParser::directoryWalker(const std::string& path) {
    try {
        for (const auto & entry : fs::recursive_directory_iterator(path)) {
            if (fs::is_regular_file(entry)) { // Checking if it is a file
                if (entry.path().extension().string() == ".unity") {
                    std::cout << "Find .unity file: " + entry.path().filename().string() + "\n";
                    SceneParser sceneParser;
                    sceneParser.parse(entry.path().string());
                    sceneParser.writeResult(outputDirectory + entry.path().filename().string() + ".dump");
                    addUsedScriptsGui(sceneParser.getObjectsScriptsGui());
                }

                if (entry.path().extension().string() == ".cs.meta") {
                    std::ifstream file(entry.path().string());

                    if (!file.is_open()) {
                        std::cerr << "Failed to open file: " << entry.path().string() << std::endl;
                        throw std::runtime_error("Failed to open cs.meta file\n");
                    }

                    std::string word;
                    while (file >> word) {
                        if (word == "guid:") {
                            file >> word;
                            allScripts.push_back(word);
                            break;
                        }
                    }

                    file.close(); // Close the file when done
                }
            }
        }
    } catch (fs::filesystem_error & e) {
        std::cerr << e.what() << std::endl;
    }
}

void DirectoryParser::addUsedScriptsGui(const std::vector<std::string>& scriptsGui) {
    for (const std::string &scr: scriptsGui) {
        usedScripts[scr] = true;
    }
}

void DirectoryParser::setOutputDirectory(const std::string &directory) {
    outputDirectory = directory;
}

void DirectoryParser::writeUnusedScripts() {
    std::ofstream file(outputDirectory + "/unusedScripts");

    if (!file.is_open()) {
        std::cerr << "failed to create file\n";
        return;
    }

    for (const auto& script: allScripts){
        if (!usedScripts[script]) {
            file << script << '\n';
        }
    }

    file.close();
}