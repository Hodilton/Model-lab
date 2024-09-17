#ifndef PATHPARAMS_H
#define PATHPARAMS_H

#include <string>

class PathParams {
private:
    std::string folderPath;
    std::string fileName;
    std::string extension;

public:
    PathParams(const std::string& folderPath, const std::string& fileName, const std::string& extension)
        : folderPath(folderPath), fileName(fileName), extension(extension) {}

    std::string getFullPath() const {
        return folderPath + "/" + fileName + "." + extension;
    }

    std::string getFolderPath() const { return folderPath; }
    std::string getFileName() const { return fileName; }
    std::string getExtension() const { return extension; }
};

#endif // !PATHPARAMS_H