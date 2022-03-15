#pragma once
#ifndef Util_H
#define Util_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Util {
public:
    Util();
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int prog);
    static bool checkOpenGLError();
    static string readShaderSource(const char* filePath);
    static GLuint createShaderProgram();
    static GLuint loadTexture(const char* texImagePath);
};

#endif