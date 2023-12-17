#include "Chunck.h"
#include "../libs/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "Mesher.h"
#include "constants.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>

Chunck::Chunck() {
  m_vertices.reserve(constants::chunckSize * constants::chunckSize *
                     constants::chunckSize * 6 * 4 * 5);
  m_indices.reserve(constants::chunckSize * constants::chunckSize *
                    constants::chunckSize * 36);

  update();

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  glBufferData(GL_ARRAY_BUFFER, std::size(m_vertices) * sizeof(float),
               m_vertices.data(), GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::size(m_indices) * sizeof(float),
               m_indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Chunck::~Chunck() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteBuffers(1, &m_EBO);
}

void Chunck::update() { Mesher::mesh(m_chunck, m_vertices, m_indices); }

void Chunck::render() const {
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, std::size(m_indices), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
