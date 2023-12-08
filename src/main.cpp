
#include "../libs/glad/include/glad/glad.h"
#include "constants.h"
#include "debugger.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(
      constants::windowWidth, constants::windowHeight, "window", NULL, NULL);
  if (window == NULL) {
    std::cerr << "Unable to open window.\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

    std::cerr << "Unable to initialize GLAD.\n";
    return EXIT_FAILURE;
  }

  glViewport(0, 0, constants::windowHeight, constants::windowWidth);
  glClearColor(1, 1, 1, 1);

  debugger::initDebugger();

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_FAILURE;
}
