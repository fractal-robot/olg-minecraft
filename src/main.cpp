#include "../libs/glad/include/glad/glad.h"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "Chunck.h"
#include "Shader.h"
#include "Texture2D.h"
#include "blockEnum.h"
#include "constants.h"
#include "debugger.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <math.h>

Camera camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebufferSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *, double xPos, double yPos) {
  camera.processMouseMovement(xPos, yPos);
};

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  camera.processKeyboard(window, deltaTime);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWwindow *window = glfwCreateWindow(
      constants::windowWidth, constants::windowHeight, "window", NULL, NULL);
  if (window == NULL) {
    std::cerr << "Unable to open window.\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Unable to initialize GLAD.\n";
    return EXIT_FAILURE;
  }

  glViewport(0, 0, constants::windowWidth, constants::windowHeight);
  glClearColor(1, 1, 1, 1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  debugger::initDebugger();

  Shader shader("../../res/shaders/shader.vert",
                "../../res/shaders/shader.frag");
  shader.use();

  Texture2D texture("../../res/textures/texture_atlas.png", true);
  glActiveTexture(GL_TEXTURE0);
  texture.bind();
  shader.setInt("tex", 0);

  Chunck chunck;
  chunck.update();

  glm::mat4 view;
  glm::mat4 projection{glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(constants::windowWidth) / constants::windowHeight,
      0.1f, 100.0f)};

  shader.setMatrix4("projection", projection);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = camera.getViewMatrix();
    shader.setMatrix4("view", view);

    glm::mat4 model{glm::mat4(1.0f)};
    shader.setMatrix4("model", model);

    chunck.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_FAILURE;
}
