#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

void Mesh::setupMesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, Normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, TexCoords));

  glBindVertexArray(0);
}

void Mesh::draw(ShaderLoader &shader) {
  unsigned int diffuseNr = 1;
  unsigned int rmaNr = 1;
  unsigned int normalNr = 1;
  for (unsigned int i = 0; i < textures.size(); i++) {
    // activate proper texture unit before binding
    glActiveTexture(GL_TEXTURE0 + i);
    // retrieve texture number (the N in diffuse_textureN)
    std::string number;
    std::string name = textures[i].type;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_rma")
      number = std::to_string(rmaNr++);
    else if (name == "texture_normal")
      number = std::to_string(normalNr++);

    shader.setInt((name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
    // error.log(std::to_string(i));
  }
  glActiveTexture(GL_TEXTURE0);

  // draw mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::unloadTextures() {
  for (int i = 0; i < textures.size(); i++) {
    glDeleteTextures(1, &textures[i].id);
  }
}

// Until I have a firmer grasp on memory management, textures should only be
// managed by the Model class
Mesh::~Mesh() { // this->unloadTextures();
  // error.log("Mesh destructor called");
}
