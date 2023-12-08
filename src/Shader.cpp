#include "Shader.h"
#include "../libs/glad/include/glad/glad.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  std::string vertexCode, fragmentCode;
  std::ifstream vShaderFile, fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure fail) {
    std::cerr << "shader: unable to read shader files.\n";
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  int success;
  char infoLog[512];

  unsigned int vertex{glCreateShader(GL_VERTEX_SHADER)};
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cerr << "Shader: unable to compile vertex shader.\n";
  }

  unsigned int fragment{glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cerr << "Shader: unable to compile fragment shader.\n";
  }

  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertex);
  glAttachShader(m_ID, fragment);
  glLinkProgram(m_ID);
  glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
    std::cerr << "Shader: unable to link shaders.\n";
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() { glDeleteProgram(m_ID); }

unsigned int Shader::getID() const { return m_ID; }

void Shader::use() { glUseProgram(m_ID); }

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()),
              static_cast<int>(value));
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
