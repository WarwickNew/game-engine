#pragma once
#include "Chunk.h"
#include "Error.h"
#include "MarchingCubeChunkRenderer.h"
#include "Model.h"
#include "ShaderLoader.h"
#include "helpers/RootDir.h"
#include <FastNoise/FastNoise.h>
#include <vector>

class Terrain {
private:
  Error error = Error("Terrain");

  // Favourite noise generated values using the NoiseTool for now:
  FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(
      "DgAIAAAAAAAAQBkAAwAAAIA/AQcAAAAAAD8AAAAAAAAAAABA");

  // Currently used chunks
  std::vector<Chunk> chunks;

  std::vector<Model *> models;

  MarchingCubeChunkRenderer *renderer;

public:
  Terrain();

  void draw(ShaderLoader &shader);

  ~Terrain();
};
