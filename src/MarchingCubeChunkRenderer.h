#pragma once
#include "Chunk.h"
#include "Error.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <map>
#include <vector>

// data required for rendring cube in right orientation.
struct CubeData {
  glm::mat4 transform;
  int modelID;
};

class MarchingCubeChunkRenderer {

private:
  Error error = Error("MarchingCubeChunkRenderer");

  // Noise cut off value.
  const static float noiseCutOff;

  // Chunks to render
  std::vector<Chunk> *chunks;

  // Here we will store a model corresponding to ease polygon of the marching
  // cubes algorithm plus maybe more if models become orientation specific:
  // https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.545.613
  std::vector<Model *> models;

  // this map will contain all combinations of cube data in order to render the
  // right model with the right translations
  const static std::map<int, CubeData> RenderMap;

  // Determine Cubes Model and translation.
  Model *genCubeModel(int x, int y, int z, Chunk &chunk);

public:
  MarchingCubeChunkRenderer(std::vector<Chunk> &chunks,
                            std::vector<Model *> models);
  void draw(ShaderLoader &shader);
};
