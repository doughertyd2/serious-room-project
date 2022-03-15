#ifndef CAMERA_H
#define CAMERA_H

#include "InputManager.hpp"
#include <glm/gtc/matrix_transform.hpp>

struct Camera {

  Camera(int w, int h);
  void update(InputManager& manager);

public:
	float pitch = 0.0f;
	float yaw = 0.0f;
	glm::vec3 direction;
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

};

#endif
