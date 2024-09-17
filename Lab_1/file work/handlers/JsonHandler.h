#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <fstream>

#include "./IFileHandler.h"
#include <./json/json.hpp>

using json = nlohmann::json;

template<typename Data>
class JsonHandler : public IFileHandler<Data> {
public:
    void write(const std::string& path, const Data& data) override {
        std::ofstream file(path);

        if (!file.is_open()) {
            return;
        }

        json jsonData = data;
        file << jsonData.dump(4);

        file.close();
    }

    Data read(const std::string& path) override {
        std::ifstream file(path);

        if (!file.is_open()) {
            return Data();
        }

        json jsonData;
        file >> jsonData;
        Data data = jsonData.get<Data>();

        return data;
    }
};

#endif // !JSONHANDLER_H