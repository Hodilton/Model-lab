#ifndef FILEHANDLERFACTORY_H
#define FILEHANDLERFACTORY_H

#include "../handlers/IFileHandler.h"

#include "../handlers/JsonHandler.h"
#include "../handlers/NotImplementHandler.h"

template<typename Data>
class FileHandlerFactory {
public:
    static std::unique_ptr<IFileHandler<Data>> createHandler(const std::string& extension) {
        if (extension == "json") {
            return std::unique_ptr<IFileHandler<Data>>(new JsonHandler<Data>());
        }
        else {
            return std::unique_ptr<IFileHandler<Data>>(new NotImplementHandler<Data>());;
        }
    }
};

#endif // !FILEHANDLERFACTORY_H