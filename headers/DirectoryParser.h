#ifndef UNITYDIRECTORYREADER_DIRECTORYPARSER_H
#define UNITYDIRECTORYREADER_DIRECTORYPARSER_H
#include <string>
#include <vector>
#include <map>

class DirectoryParser{
public:
    void directoryWalker(const std::string& path);
    void setOutputDirectory(const std::string &directory);
    void writeUnusedScripts();

private:
    std::map <std::string, bool> usedScripts;
    std::vector <std::string> allScripts;
    std::string outputDirectory;

    void addUsedScriptsGui(const std::vector <std::string>& scriptsGui);

};

#endif //UNITYDIRECTORYREADER_DIRECTORYPARSER_H
