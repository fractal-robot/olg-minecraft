#include "Chunck.h"
#include "../libs/glad/include/glad/glad.h"
#include "Block.h"
#include "GLFW/glfw3.h"
#include "Mesher.h"
#include "constants.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>

Chunck::Chunck() {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices,
               GL_STATIC_DRAW);

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

void Chunck::update() { Mesher::mesh(m_chunck, m_indices, m_vertices); }

void Chunck::render() const { glBindVertexArray(m_VAO); }

void Chunck::print() const {
  for (auto v : m_indices) {
    if (v != 0)
      std::cout << v << ' ';
  }

  std::cout << '\n' << '\n';

  for (auto v : m_vertices) {
    if (v != 0)
      std::cout << v << ' ';
  }
}
