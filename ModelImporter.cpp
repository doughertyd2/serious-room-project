//Computer Graphics Programming in OpenGL with C++
//by V.Scott Gordonand John Clevenger

#include "ModelImporter.h"
#include <fstream>
#include <sstream>
#include <glm\glm.hpp>
using namespace std;


ModelImporter::ModelImporter() {}
void ModelImporter::parseOBJ(const char* filePath) {
	float x, y, z;
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		if (line.compare(0, 2, "v ") == 0) { // vertex position ("v" case)
			stringstream ss(line.erase(0, 1));
			ss >> x; ss >> y; ss >> z; // extract the vertex position values
			vertVals.push_back(x);
			vertVals.push_back(y);
			vertVals.push_back(z);
		}
		if (line.compare(0, 2, "vt") == 0) { // texture coordinates ("vt" case)
			stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; // extract texture coordinate values
			stVals.push_back(x);
			stVals.push_back(y);
		}
		if (line.compare(0, 2, "vn") == 0) { // vertex normals ("vn" case)
			stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; ss >> z; // extract the normal vector values
			normVals.push_back(x);
			normVals.push_back(y);
			normVals.push_back(z);
		}
		if (line.compare(0, 2, "f ") == 0) { // triangle faces ("f" case)
			string oneCorner, v, t, n;
			stringstream ss(line.erase(0, 2));
			for (int i = 0; i < 3; i++) {
				getline(ss, oneCorner, ' '); // extract triangle face references
				stringstream oneCornerSS(oneCorner);
				getline(oneCornerSS, v, '/');
				getline(oneCornerSS, t, '/');
				getline(oneCornerSS, n, '/');
				int vertRef = (stoi(v) - 1) * 3; // "stoi" converts string to integer
				int tcRef = (stoi(t) - 1) * 2;
				int normRef = (stoi(n) - 1) * 3;
				triangleVerts.push_back(vertVals[vertRef]); // build vector of vertices
				triangleVerts.push_back(vertVals[vertRef + 1]);
				triangleVerts.push_back(vertVals[vertRef + 2]);
				textureCoords.push_back(stVals[tcRef]); // build vector of texture coords
				textureCoords.push_back(stVals[tcRef + 1]);
				normals.push_back(normVals[normRef]); //… and normals
				normals.push_back(normVals[normRef + 1]);
				normals.push_back(normVals[normRef + 2]);
			}
		}
	}
}
int ModelImporter::getNumVertices() { return (triangleVerts.size() / 3); } // accessors
std::vector<float> ModelImporter::getVertices() { return triangleVerts; }
std::vector<float> ModelImporter::getTextureCoordinates() { return textureCoords; }
std::vector<float> ModelImporter::getNormals() { return normals; }