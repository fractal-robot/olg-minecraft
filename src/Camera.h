#pragma once

#include "../libs/glm/glm.hpp"
#include <GLFW/glfw3.h>

class Camera {

public:
  glm::vec3 position;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90,
         float pitch = 0);

  void processKeyboard(GLFWwindow *window, float deltaTime);
  void processMouseMovement(float xOffset, float yOffset);

  glm::mat4 getViewMatrix() const;

private:
  void updateCameraVectors();

  enum m_cameraMovement {
    forward,
    backward,
    left,
    right,
  };

  glm::vec3 m_front, m_up, m_right;
  glm::vec3 m_worldUp;

  float m_yaw, m_pitch;

  float m_lastX = 400, m_lastY = 300;
};
