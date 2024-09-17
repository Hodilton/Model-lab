#ifndef IFILEHANDLER_H
#define IFILEHANDLER_H

#include <string>

template<typename Data>
class IFileHandler {
public:
    virtual void write(const std::string& path, const Data& data) = 0;
    virtual Data read(const std::string& path) = 0;
    virtual ~IFileHandler() = default;
};

#endif // !IFILEHANDLER_H