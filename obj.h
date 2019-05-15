#include <array>
#include <map>
#include <string>
#include <vector>

struct OBJ {

    std::vector<float> normalData, positionData;

    OBJ(const std::string &file);

private:

    void parseVertex(
        std::map<int, std::array<float, 3>> &normalMap,
        std::map<int, std::array<float, 3>> &positionMap,
        const std::string &vertex
    );

};