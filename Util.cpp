//Computer Graphics Programming in OpenGL with C++
//by V.Scott Gordonand John Clevenger

#include "Util.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Util::Util() {}

void Util::printShaderLog(GLuint shader) {
    int len = 0;
    int cw = 0; //characters written
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &cw, log);
        cout << "Shader info log: " << log << endl;
        free(log);
    }
}

void Util::printProgramLog(int prog) {
    int len = 0;
    int cw = 0; //characters written
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &cw, log);
        cout << "Program info log: " << log << endl;
        free(log);
    }
}

bool Util::checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

string Util::readShaderSource(const char* filePath) {
    string content;
    ifstream fileStream(filePath, ios::in);
    string line = "";

    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint Util::createShaderProgram() {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    string verShaderStr = readShaderSource("vertShader.glsl");
    string fragShaderStr = readShaderSource("fragShader.glsl");
    const char* vshaderSource = verShaderStr.c_str();
    const char* fshaderSource = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);  //tell it to create a vertex shader and fragment shader (initially empty)
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);  //returns an integer id for each shader

    //second parameter is the number of strings in the shader source code
    //if thats greater than 1, the third paramater has to be a pointer to an array of strings
    glShaderSource(vShader, 1, &vshaderSource, NULL);  //loads GLSL code from the strings into the empty objects
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    //compile shaders
    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "Vert compilation failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "Frag compilation failed" << endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();  //creates a program, which is a series of compiled shaders
    glAttachShader(vfProgram, vShader);   //attach shaders
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);  //request the GLSL compiler ensure the shaders are compatable
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "Link failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

GLuint Util::loadTexture(const char* texImagePath) {
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0)
        cout << "Could not find texture file " << texImagePath << endl;
    return textureID;
}