#include "Model.h"

Model::Model(Mesh mesh) { this->meshes.push_back(mesh); }
Model::Model(std::vector<Mesh> meshes) { this->meshes = meshes; }

void Model::draw(ShaderLoader &shader) {
  for (unsigned int i = 0; i < this->meshes.size(); i++)
    this->meshes[i].draw(shader);
}
