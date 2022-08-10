#include "Terrain.h"

Terrain::Terrain() : renderer(nullptr) {
  // Create chunk
  TerrainInfo ti;
  ti.xRange[0] = 0;
  ti.xRange[1] = 16;
  ti.yRange[0] = 0;
  ti.yRange[1] = 16;
  ti.zRange[0] = 0;
  ti.zRange[1] = 16;
  ti.frequency = 0.2f;
  ti.seed = 0;

  chunks.push_back(Chunk(fnGenerator, ti));

  // Create chunks renderer.
  std::vector<Model> models = {
      Model(ROOT_DIR "data/models/wooden_boxbarrel/wooden_box_and_barrel.obj")};

  renderer = new MarchingCubeChunkRenderer(this->chunks, models);
}

Terrain::~Terrain() {
  // Since we created our renderer member in our constructer it has to be a
  // nullptr before being updated to the created object, which means it's
  // lifecycle needs to be managed by this class.
  delete renderer;
}

void Terrain::draw(ShaderLoader &shader) {
  if (renderer != nullptr)
    renderer->draw(shader);
  else
    error.warn("Terrain attempted to draw with no chunk renderer!");
}
