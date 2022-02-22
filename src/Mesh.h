#pragma once
#include "Error.h"
#include "ShaderLoader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

// Define some useful structures to be used in the mesh object
struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};
struct Texture {
  unsigned int id;
  std::string type;
};

class Mesh {
private:
  Error error = Error("Mesh");

  unsigned int VAO, VBO, EBO;
  void setupMesh();

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  void Draw(ShaderLoader &shader);

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<Texture> textures);
};
