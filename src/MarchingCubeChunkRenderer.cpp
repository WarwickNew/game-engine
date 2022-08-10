#include "MarchingCubeChunkRenderer.h"

MarchingCubeChunkRenderer::MarchingCubeChunkRenderer(
    std::vector<Chunk> &chunks, std::vector<Model> models) {
  this->chunks = &chunks;
  this->models = models;
}

void MarchingCubeChunkRenderer::draw(ShaderLoader &shader) {
  for (int i = 0; i < chunks->size(); i++) {
    // Render Chunk
  }
}
