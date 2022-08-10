#pragma once
#include "Chunk.h"
#include "Error.h"
#include "Model.h"
#include <vector>

class MarchingCubeChunkRenderer {

private:
  Error error = Error("MarchingCubeChunkRenderer");

  // Chunks to render
  std::vector<Chunk> *chunks;

  // Here we will store a model corresponding to ease polygon of the marching
  // cubes algorithm plus maybe more if models become orientation specific:
  // https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.545.613
  std::vector<Model> models;

public:
  MarchingCubeChunkRenderer(std::vector<Chunk> &chunks,
                            std::vector<Model> models);
  void draw(ShaderLoader &shader);
};
