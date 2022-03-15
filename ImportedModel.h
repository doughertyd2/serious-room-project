#include <vector>

class ImportedModel {
    private:
        int numVertices;

    public:
        ImportedModel(const char * filePath);

        int getNumVertices();
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec2> getTextureCoords();
        std::vector<glm::vec3> getNormals();

        std::vector < glm::vec3 > vertices;
        std::vector < glm::vec2 > texCoords;
        std::vector < glm::vec3 > normalVecs;
};
