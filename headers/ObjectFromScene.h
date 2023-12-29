#ifndef UNITYDIRECTORYREADER_OBJECTFROMSCENE_H
#define UNITYDIRECTORYREADER_OBJECTFROMSCENE_H

#include <string>
#include <vector>

class ObjectFromScene{
public:
    std::string getName();
    void setName(const std::string &newName);
    std::string getId();
    void setId(const std::string &newId);
    std::string getParent();
    void setParent(const std::string &newParent);
    std::vector<std::string> getChildrenId();
    void addChild(const std::string& childId);
    std::string getScriptGuid();
    void setScriptGuid(const std::string &newScript);
private:
    std::string id;
    std::string name;
    std::string parent;
    std::vector<std::string> childrenId;
    std::string scriptGuid;
};

#endif //UNITYDIRECTORYREADER_OBJECTFROMSCENE_H
