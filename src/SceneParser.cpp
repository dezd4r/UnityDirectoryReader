#include "../headers/SceneParser.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

void SceneParser::parse(std::string path) {
    std::ifstream file(path);
    if (file) std::cout << "opening file " + path + "\n";
    YAML::Node scene = YAML::Load(file);


    for (const YAML::Node& node : scene) {
        if (node.Tag() == "!u!1") {
            ObjectFromScene newObject;
            std::cout << "Found a GameObject" + node["m_Name"].as<std::string>();
            newObject.setName(node["m_Name"].as<std::string>());
            for (const YAML::Node& component : node["components"]) {
                if (component.Tag() == "!u!114") {  // Define this to identify MonoBehaviour components
                    std::string scriptGuid = component["m_Script"]["scriptGuid"].as<std::string>();
                    newObject.setScriptGuid(scriptGuid);
                }

                if (component.Tag() == "!u!4") {
                    if (component["m_GameObject"]) {
                        newObject.setId(component["m_GameObject"]["fileID"].as<std::string>());
                    }

                    if (component["m_Father"]) {
                        newObject.setParent(component["m_Father"]["fileID"].as<std::string>());
                    }

                    if (component["m_Children"]) {
                        for (const YAML::Node& child : component["m_Children"]){
                            newObject.addChild(child["fileID"].as<std::string>());
                        }
                        newObject.setParent(component["m_Father"]["fileID"].as<std::string>());
                    }
                }
            }
            if (newObject.getParent().empty()) {
                withoutParents.push_back(newObject.getId());
            }
            sceneObjects[newObject.getId()] = newObject;
            usedObjects[newObject.getId()] = false;
            dependsTree[newObject.getParent()].push_back(newObject);
            usedScriptsGui.push_back(newObject.getScriptGuid()); //!!!
        }
    }
}

void SceneParser::writeResult(std::string fileOutput) {
    std::ofstream file(fileOutput);

    if (!file.is_open()) {
        std::cerr << "failed to create file\n";
        return;
    }

    for (const auto& parent: withoutParents){
        if (!usedObjects[parent]) {
            writeTree(file, 0, parent);
        }
    }
    file.close();
}

std::vector<std::string> SceneParser::getObjectsScriptsGui() {
    return usedScriptsGui;
}

void SceneParser::writeTree(std::ofstream &file, int level, const std::string &parent) {
    for (int i = 0; i < level; i++) {
        file << "-";
    }

    file << sceneObjects[parent].getName();
    usedObjects[parent] = true;

    for (auto obj : dependsTree[parent]) {
        writeTree(file, level + 1, obj.getId());
    }

    file << '\n';

}
