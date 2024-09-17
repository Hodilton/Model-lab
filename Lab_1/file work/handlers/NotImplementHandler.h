#ifndef NOTIMPLEMENTHADLER_H
#define NOTIMPLEMENTHADLER_H

#include <fstream>

#include "./IFileHandler.h"

template<typename Data>
class NotImplementHandler : public IFileHandler<Data> {
public:
    void write(const std::string& path, const Data& data) override {
        return;
    }

    Data read(const std::string& path) override {
        return Data();
    }
};

#endif // !NOTIMPLEMENTHADLER_H