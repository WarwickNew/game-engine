#pragma once
#include "Error.h"
#include "Mesh.h"
#include "ShaderLoader.h"
#include <SDL2/SDL_image.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
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

  // Load in models using assimp
  void loadModel(std::string path);
  // process assimps node structure
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *material,
                                            aiTextureType type,
                                            std::string typeName);

  void unloadTextures();

  std::string directory;
  unsigned int loadTextureFromFile(std::string texture, std::string directory);
  std::vector<Texture> textures_loaded;

public:
  // Create a model from file
  Model(std::string path);
  // Used to create a mesh out of a single mesh.
  Model(Mesh mesh);
  // Used to create a mesh out of multiple meshes.
  Model(std::vector<Mesh> meshes);

  // Render the model
  void draw(ShaderLoader &shader);

  // Translate the model
  void translate(glm::vec3 translation);

  ~Model();
};
