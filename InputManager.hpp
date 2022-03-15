#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct InputManager {

  InputManager(GLFWwindow* w);
  bool processInput();
  bool isKeyPressed(unsigned int keyID);
  bool isKeyReleased(unsigned int keyID);

  static bool isKeyDown(unsigned int keyID);
  static bool wasKeyDown(unsigned int keyID);

  static void keyPressed(unsigned int keyID);
  static void keyReleased(unsigned int keyID);

  static glm::vec2 mousePosition;
  static void setMousePosition(int x, int y);

  static std::unordered_map<unsigned int, bool> keymap;
  static std::unordered_map<unsigned int, bool> previousKeymap;
  static GLFWwindow* window;

  static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
  static void keyCallback(GLFWwindow* window, int key, int scanecode, int action, int mods);

};

#endif
