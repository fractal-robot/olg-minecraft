#include "Camera.h"
#include "../libs/glm/glm.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "constants.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_position(position), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_worldUp(up), m_yaw(yaw), m_pitch(pitch) {
  updateCameraVectors();
};

void Camera::processKeyboard(GLFWwindow *window, float deltaTime) {

  glm::vec3 front(m_front.x, 0, m_front.z);
  front = glm::normalize(front);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    m_position += constants::cameraSpeed * deltaTime * front;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    m_position -= constants::cameraSpeed * deltaTime * front;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    m_position -= glm::normalize(glm::cross(front, m_up)) *
                  constants::cameraSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    m_position += glm::normalize(glm::cross(front, m_up)) *
                  constants::cameraSpeed * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    m_position.y += constants::cameraAltitudeSpeed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    m_position.y -= constants::cameraAltitudeSpeed * deltaTime;
}

void Camera::processMouseMovement(float xPos, float yPos) {
  float xOffset = xPos - m_lastX;
  float yOffset = m_lastY - yPos;

  m_lastX = xPos;
  m_lastY = yPos;

  xOffset *= constants::cameraSensivity;
  yOffset *= constants::cameraSensivity;

  m_yaw += xOffset;
  m_pitch += yOffset;

  if (m_pitch > 89.0f)
    m_pitch = 89.0f;
  if (m_pitch < -89.0f)
    m_pitch = -89.0f;

  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::updateCameraVectors() {

  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);

  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));
}
