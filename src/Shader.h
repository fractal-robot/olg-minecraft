#pragma once

#include "../libs/glm/mat4x4.hpp"
#include <string>
class Shader {
public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();

  unsigned int getID() const;
  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMatrix4(const std::string &name, const glm::mat4 &value) const;

private:
  unsigned int m_ID;
};
