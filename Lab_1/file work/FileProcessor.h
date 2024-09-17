#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>

#include "./path/PathParams.h"
#include "./factories/FileHandlerFactory.h"

template<typename Data>
class FileProcessor {
public:
    static Data readFile(const PathParams& pathParams) {
        std::string fullPath = pathParams.getFullPath();

        auto handler = FileHandlerFactory<Data>::createHandler(pathParams.getExtension());

        return handler->read(fullPath);
    }

    static void writeFile(const PathParams& pathParams, const Data& data) {
        std::string fullPath = pathParams.getFullPath();

        auto handler = FileHandlerFactory<Data>::createHandler(pathParams.getExtension());

        handler->write(fullPath, data);
    }
};

#endif // !FILEPROCESSOR_H