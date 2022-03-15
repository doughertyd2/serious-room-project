#include "Camera.hpp"

Camera::Camera(int w, int h){
  projection = glm::perspective(glm::radians(110.0f), w/(float)h, 0.1f, 1000.0f);
  position = glm::vec3(0.0f, 40.0f, 0.0f);
}

void Camera::update(InputManager& manager){

  glm::vec2 mousePos = manager.mousePosition;
  glm::vec2 center = glm::vec2(400, 300);
  glm::vec2 delta = center - mousePos;
  manager.setMousePosition(400, 300);

  pitch += delta.y * 0.1f;
  yaw -= delta.x * 0.1f;

  if(pitch > 89.0f) pitch = 89.0f;
  if(pitch < -89.0f) pitch = -89.0f;

  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  //Movement
  glm::vec3 forward = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
  glm::vec3 side = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
  if(manager.isKeyDown(GLFW_KEY_W)){
    position += forward * 0.35f;
  }
  if(manager.isKeyDown(GLFW_KEY_S)){
    position -= forward * 0.35f;
  }
  if(manager.isKeyDown(GLFW_KEY_A)){
    position -= side * 0.35f;
  }
  if(manager.isKeyDown(GLFW_KEY_D)){
    position += side * 0.35f;
  }
  if(manager.isKeyDown(GLFW_KEY_SPACE)){
    position += glm::vec3(0, 1, 0) * 0.1f;
  }
  if(manager.isKeyDown(GLFW_KEY_LEFT_SHIFT)){
    position -= glm::vec3(0, 1, 0) * 0.1f;
  }

  view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));

  model = glm::translate(glm::mat4(1.0f), position);

}
