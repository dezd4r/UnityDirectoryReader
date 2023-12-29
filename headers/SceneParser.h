#ifndef UNITYDIRECTORYREADER_SCENEPARSER_H
#define UNITYDIRECTORYREADER_SCENEPARSER_H

#include <vector>
#include <map>
#include "ObjectFromScene.h"

class SceneParser {
public:
    void parse(std::string path);
    void writeResult(std::string fileOutput);
    std::vector<std::string> getObjectsScriptsGui();

private:
    std::map <std::string, ObjectFromScene> sceneObjects; // id -> object
    std::map <std::string, std::vector<ObjectFromScene>> dependsTree; // parent -> children
    std::map <std::string, bool> usedObjects; // id -> used or not
    std::vector <std::string> withoutParents; // id
    std::vector <std::string> usedScriptsGui;

    void writeTree(std::ofstream &file, int level, const std::string &parent);
};

#endif //UNITYDIRECTORYREADER_SCENEPARSER_H
