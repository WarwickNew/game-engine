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

  // Create models for chunk renderer to use.
  models = {
      new Model(ROOT_DIR "data/game-models/1/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/2/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/3/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/4/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/5/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/6/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/7/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/8/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/9/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/10/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/11/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/12/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/13/MetalFloor.obj"),
      new Model(ROOT_DIR "data/game-models/14/MetalFloor.obj"),
  };
  // Resize models to fit in coordinate system.
  for (int i = 0; i < models.size(); i++) {
    models.at(i)->resize(glm::vec3(0.5f));
  }

  // Create chunk renderer.
  renderer = new MarchingCubeChunkRenderer(this->chunks, models);
}

Terrain::~Terrain() {
  // Since we created our renderer member in our constructer and defined it in
  // the header file it has to be a nullptr before being updated to the created
  // object, which means it's lifecycle needs to be managed by this class.
  delete renderer;
  // Creating models here for OpenGL purposes means that we can't duplicate the
  // data, so we need to delete them after creating them as pointers.
  for (int i = 0; i < models.size(); i++) {
    delete models.at(i);
  }
}

void Terrain::draw(ShaderLoader &shader) {
  if (renderer != nullptr)
    renderer->draw(shader);
  else
    error.warn("Terrain attempted to draw with no chunk renderer!");
}
