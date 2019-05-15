#include <fstream>
#include <sstream>
#include "obj.h"

OBJ::OBJ(const std::string &file) {
    std::map<int, std::array<float, 3>> normalMap, positionMap;
    auto normalIndex = 1, positionIndex = 1;
    std::ifstream stream{file};
    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream lineStream{line};
        std::string type;
        lineStream >> type;
        if (type == "f") {
            std::string vertex1;
            std::string vertex2;
            std::string vertex3;
            lineStream >> vertex1 >> vertex2 >> vertex3;
            parseVertex(normalMap, positionMap, vertex1);
            parseVertex(normalMap, positionMap, vertex2);
            parseVertex(normalMap, positionMap, vertex3);
        }
        else if (type == "v") {
            float x, y, z;
            lineStream >> x >> y >> z;
            positionMap[positionIndex++] = {x, y, z};
        }
        else if (type == "vn") {
            float x, y, z;
            lineStream >> x >> y >> z;
            normalMap[normalIndex++] = {x, y, z};
        }
    }
}

void OBJ::parseVertex(
    std::map<int, std::array<float, 3>> &normalMap,
    std::map<int, std::array<float, 3>> &positionMap,
    const std::string &vertex
) {
    std::istringstream stream{vertex};
    std::string index;
    std::getline(stream, index, '/');
    for (auto &value : positionMap[stoi(index)]) {
        positionData.push_back(value);
    }
    if (std::getline(stream, index, '/')) {
        //textureData
    }
    if (std::getline(stream, index, '/')) {
        for (auto &value : normalMap[stoi(index)]) {
            normalData.push_back(value);
        }
    }
}