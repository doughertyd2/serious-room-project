#include "InputManager.hpp"



glm::vec2 InputManager::mousePosition;
std::unordered_map<unsigned int, bool> InputManager::keymap;
std::unordered_map<unsigned int, bool> InputManager::previousKeymap;
GLFWwindow* InputManager::window;

InputManager::InputManager(GLFWwindow* w){
  window = w;
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, mousePosCallback);
}

bool InputManager::processInput(){
  previousKeymap = keymap;
  glfwPollEvents();
  if (glfwWindowShouldClose(window)) {
      return true;
  }
  return false;
}

bool InputManager::isKeyPressed(unsigned int keyID){
  return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(unsigned int keyID){
  return (!isKeyDown(keyID) && wasKeyDown(keyID));
}


bool InputManager::isKeyDown(unsigned int keyID){
  auto it = keymap.find(keyID);
  if(it != keymap.end()){
    return it->second;
  }
  return false;
}

bool InputManager::wasKeyDown(unsigned int keyID){
  auto it = previousKeymap.find(keyID);
  if(it != previousKeymap.end()){
    return it->second;
  }
  return false;
}

void InputManager::setMousePosition(int x, int y){
  glfwSetCursorPos(window, x, y);
}

void InputManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
    mousePosition = glm::vec2(xpos, ypos);
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scanecode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyPressed(key);
    }
    else if (action == GLFW_RELEASE) {
        keyReleased(key);
    }
}


void InputManager::keyPressed(unsigned int keyID){
  keymap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID){
  keymap[keyID] = false;
}
