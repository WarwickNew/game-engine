#pragma once
#include "Error.h"
#include "Mesh.h"
#include "ShaderLoader.h"
#include <vector>

class Model {
private:
  Error error = Error("Model");

  std::vector<Mesh> meshes;

public:
  // Used to create a mesh out of a single mesh.
  Model(Mesh mesh);
  // Used to create a mesh out of multiple meshes.
  Model(std::vector<Mesh> meshes);
  void draw(ShaderLoader &shader);
};
