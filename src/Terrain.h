#pragma once
#include "Chunk.h"
#include "Error.h"
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

public:
  Terrain();
};
