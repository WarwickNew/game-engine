#include "Model.h"

Model::Model(char *path) {}
Model::Model(Mesh mesh) { this->meshes.push_back(mesh); }
Model::Model(std::vector<Mesh> meshes) { this->meshes = meshes; }

void Model::draw(ShaderLoader &shader) {
  for (unsigned int i = 0; i < this->meshes.size(); i++) {
    shader.setMat4("Model", this->model);
    this->meshes[i].draw(shader);
  }
}

void Model::translate(glm::vec3 translation) {
  // set worldspace postition
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans, translation);
  this->position = trans * this->position;

  // set model transform
  this->model = glm::translate(glm::mat4(1.0f), glm::vec3(this->position));
}

void Model::loadModel(char *path) {}
