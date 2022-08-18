#include "MarchingCubeChunkRenderer.h"

const float MarchingCubeChunkRenderer::noiseCutOff = 0.2f;

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
            // this->genCubeModel(x, y, z, *chunk);
            models.at(0)->setPosition(glm::vec3(x, y, z));
            models.at(0)->draw(shader);
          }
        }
      }
    }
  }
}

Model *MarchingCubeChunkRenderer::genCubeModel(int x, int y, int z,
                                               Chunk &chunk) {
  // Gen cube index. Based on figure 4 from:
  // https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.545.613
  bool bIndex[8] = {false};

  if (chunk.getNoise(x, y, z) > noiseCutOff)
    bIndex[7] = true;
  if (chunk.getNoise(x + 1, y, z) > noiseCutOff)
    bIndex[6] = true;
  if (chunk.getNoise(x + 1, y + 1, z) > noiseCutOff)
    bIndex[5] = true;
  if (chunk.getNoise(x, y + 1, z) > noiseCutOff)
    bIndex[4] = true;
  if (chunk.getNoise(x, y, z + 1) > noiseCutOff)
    bIndex[3] = true;
  if (chunk.getNoise(x + 1, y, z + 1) > noiseCutOff)
    bIndex[2] = true;
  if (chunk.getNoise(x + 1, y + 1, z + 1) > noiseCutOff)
    bIndex[1] = true;
  if (chunk.getNoise(x, y + 1, z + 1) > noiseCutOff)
    bIndex[0] = true;

  uint8_t index;
  for (int i = 0; i < 8; i++)
    index = index + (bIndex[i] * (pow(2, i)));

  return models.at(0);
}
