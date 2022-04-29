#pragma once
#include "Error.h"
#include "Mesh.h"
#include "ShaderLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Model {
private:
  Error error = Error("Model");

  // All the meshes that make up the model
  std::vector<Mesh> meshes;

  // Model position/scale/more matrix
  glm::mat4 model = glm::mat4(1.0f);

  // Position
  glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

  void loadModel(char *path);

public:
  // Create a model from file
  Model(char *path);
  // Used to create a mesh out of a single mesh.
  Model(Mesh mesh);
  // Used to create a mesh out of multiple meshes.
  Model(std::vector<Mesh> meshes);

  // Render the model
  void draw(ShaderLoader &shader);

  // Translate the model
  void translate(glm::vec3 translation);
};
