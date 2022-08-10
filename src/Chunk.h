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

  // Pointer to the noise generator that generated this chunk
  FastNoise::SmartNode<> *fnGenerator;

  // Values that initialised the chunk
  TerrainInfo terrainInfo;

  // 3D vector of noise values
  std::vector<std::vector<std::vector<float>>> noise;

public:
  Chunk(FastNoise::SmartNode<> &noiseGenerator, TerrainInfo ti);

  float getNoise(int x, int y, int z);
  TerrainInfo getTerrainInfo();
};
