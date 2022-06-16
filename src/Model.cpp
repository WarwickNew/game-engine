#include "Model.h"

Model::Model(std::string path) { loadModel(path); }
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
void Model::resize(glm::vec3 scale) {
  // set worldspace postition
  glm::mat4 transMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(this->position));
  this->scale = scale;

  // set model transform
  this->model = glm::scale(transMatrix, glm::vec3(this->scale));
}
void Model::rotate(float angle, glm::vec3 axis) {
  this->model = glm::rotate(this->model, angle, axis);
}

void Model::loadModel(std::string path) {
  // Attempt to import model data using assimp
  Assimp::Importer import;
  const aiScene *scene =
      import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  // Check the model got imported correctly
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    error.crash("Assimp failed to load model data", import.GetErrorString());
    return;
  }
  directory = path.substr(0, path.find_last_of('/')) + '/';
  processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene) {
  // if the node has meshes process them
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }
  // Now process any nodes that this node contains
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}
// transform assimps mesh format to our own custom one
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indecies;
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    // process vertex postions and add to our mesh
    vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                mesh->mVertices[i].z);
    vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                              mesh->mNormals[i].z);
    // Handle texture coords
    if (mesh->mTextureCoords[0]) {
      vertex.TexCoords =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    } else
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }
  // Handle indeces
  // Loop through the meshes faces to get the correct order
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // loop through and add each face's indecies
    for (unsigned int faceIndicie = 0; faceIndicie < face.mNumIndices;
         faceIndicie++) {
      indecies.push_back(face.mIndices[faceIndicie]);
    }
  }
  // Handle Assimps material format
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }
  return Mesh(vertices, indecies, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *material,
                                                 aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
    aiString str;
    material->GetTexture(type, i, &str);
    bool skip = false;

    // check we're not loading in a texture we already have
    for (unsigned int loadedtex = 0; loadedtex < textures_loaded.size();
         loadedtex++) {

      if (std::strcmp(textures_loaded[loadedtex].path.data(), str.C_Str()) ==
          0) {
        textures.push_back(textures_loaded[loadedtex]);
        skip = true;
        break;
      }
    }
    // If the texture isn't already loaded load it here
    if (!skip) {
      Texture texture;
      texture.id = loadTextureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      // Store the texture in the models loaded texture bank so we can check if
      // we've already loaded it
      textures_loaded.push_back(texture);
    }
  }
  return textures;
}

unsigned int Model::loadTextureFromFile(std::string file,
                                        std::string directory) {
  // Use sdl2_image to load the texture.
  unsigned int texture;
  SDL_Surface *image = IMG_Load((directory + file).c_str());
  if (image == nullptr) {
    error.crash("SDL2_image was unable to load a texture", IMG_GetError());
  }

  // Generate the texture and put its reference id in the texture variable
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set some textue defaults
  float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  // Handle different SDL Surface data types
  int mode = GL_RGB;
  if (image->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }

  // Put image data into texture we've just generated
  glTexImage2D(GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode,
               GL_UNSIGNED_BYTE, image->pixels);
  // Whilst we're here we might as well generate mipmaps
  glGenerateMipmap(GL_TEXTURE_2D);
  // remove image surface now it's no longer needed to create texture
  SDL_FreeSurface(image);
  image = nullptr;

  return texture;
}

void Model::unloadTextures() {
  for (int i = 0; i < textures_loaded.size(); i++) {
    glDeleteTextures(1, &textures_loaded[i].id);
  }
}

Model::~Model() { this->unloadTextures(); }
