#pragma once
#include "Error.h"
#include <FastNoise/FastNoise.h>
#include <vector>

class Terrain {
private:
  Error error = Error("Terrain");

  // Favourite noise generated values using the NoiseTool for now:
  FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(
      "DgAIAAAAAAAAQBkAAwAAAIA/AQcAAAAAAD8AAAAAAAAAAABA");

public:
  Terrain();
};
