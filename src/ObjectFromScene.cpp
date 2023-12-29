#include <utility>

#include "../headers/ObjectFromScene.h"

std::string ObjectFromScene::getId() {
    return id;
}

std::string ObjectFromScene::getParent() {
    return parent;
}

std::vector<std::string> ObjectFromScene::getChildrenId() {
    return childrenId;
}

void ObjectFromScene::addChild(const std::string& childId) {
    childrenId.push_back(childId);
}

void ObjectFromScene::setId(const std::string &newId) {
    id = newId;
}

void ObjectFromScene::setParent(const std::string &newParent) {
    parent = newParent;
}

void ObjectFromScene::setName(const std::string &newName) {
    name = newName;
}

std::string ObjectFromScene::getName() {
    return name;
}

std::string ObjectFromScene::getScriptGuid() {
    return scriptGuid;
}

void ObjectFromScene::setScriptGuid(const std::string &newScript) {
    scriptGuid = newScript;
}

