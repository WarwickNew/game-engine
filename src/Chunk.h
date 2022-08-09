#pragma once
#include "Error.h"
#include <FastNoise/FastNoise.h>
#include <vector>

struct TerrainInfo {
  int xRange[2];
  int yRange[2];
  int zRange[2];
  float frequency;
  int seed;
};

class Chunk {
private:
  Error error = Error("Chunk");

  // Favourite noise generated values using the NoiseTool for now:
  FastNoise::SmartNode<> *fnGenerator;

public:
  Chunk(FastNoise::SmartNode<> &noiseGenerator, TerrainInfo ti);
};
