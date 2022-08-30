#include "ChunkMCMeshBuilder.h"

ChunkMCMeshBuilder::ChunkMCMeshBuilder() : chunkTerrain(nullptr) {
  // Data to create the Mesh
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // TODO: Build/load Mesh data here, it's better practice to place this in a
  // function but fuck it.

  // Create the Mesh
  this->chunkTerrain = new Mesh(vertices, indices, textures);
}

ChunkMCMeshBuilder::~ChunkMCMeshBuilder() { delete this->chunkTerrain; }

Mesh *ChunkMCMeshBuilder::getChunkMesh() { return chunkTerrain; }
