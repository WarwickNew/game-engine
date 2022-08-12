#include "MarchingCubeChunkRenderer.h"

MarchingCubeChunkRenderer::MarchingCubeChunkRenderer(
    std::vector<Chunk> &chunks, std::vector<Model *> models) {
  this->chunks = &chunks;
  this->models = models;
}

void MarchingCubeChunkRenderer::draw(ShaderLoader &shader) {
  for (int i = 0; i < chunks->size(); i++) {
    Chunk *chunk = &chunks->at(i);
    TerrainInfo ti = chunk->getTerrainInfo();
    // TerrainInfo ti = this->chunks[i].getTerrainInfo();
    // Render Chunk
    for (int x = ti.xRange[0]; x < ti.xRange[1]; x++) {
      for (int y = ti.yRange[0]; y < ti.yRange[1]; y++) {
        for (int z = ti.zRange[0]; z < ti.zRange[1]; z++) {
          if (chunk->getNoise(x, y, z) > 0.2f) {
            models.at(0)->setPosition(glm::vec3(x, y, z));
            models.at(0)->draw(shader);
          }
        }
      }
    }
  }
}
