//Computer Graphics Programming in OpenGL with C++
//by V.Scott Gordonand John Clevenger

#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
#include "ImportedModel.h"
#include "ModelImporter.h"

using namespace std;

// ------------ Imported Model class
ImportedModel::ImportedModel(const char* filePath) {
	ModelImporter modelImporter = ModelImporter();
	modelImporter.parseOBJ(filePath); // uses modelImporter to get vertex information
	numVertices = modelImporter.getNumVertices();
	std::vector<float> verts = modelImporter.getVertices();
	std::vector<float> tcs = modelImporter.getTextureCoordinates();
	std::vector<float> normals = modelImporter.getNormals();
	for (int i = 0; i < numVertices; i++) {
		vertices.push_back(glm::vec3(verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2]));
		texCoords.push_back(glm::vec2(tcs[i * 2], tcs[i * 2 + 1]));
		normalVecs.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
	}
}

int ImportedModel::getNumVertices() { return numVertices; } // accessors
std::vector<glm::vec3> ImportedModel::getVertices() { return vertices; }
std::vector<glm::vec2> ImportedModel::getTextureCoords() { return texCoords; }
std::vector<glm::vec3> ImportedModel::getNormals() { return normalVecs; }