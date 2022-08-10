#include "Chunk.h"

Chunk::Chunk(FastNoise::SmartNode<> &noiseGenerator, TerrainInfo ti) {
  this->terrainInfo = ti;
  this->fnGenerator = &noiseGenerator;

  // Create location to store noise values temporarily.
  std::vector<float> noiseOutput((ti.xRange[1] - ti.xRange[0]) *
                                 (ti.yRange[1] - ti.yRange[0]) *
                                 (ti.zRange[1] - ti.zRange[0]));

  // Generate noise to the outputs dimentions
  noiseGenerator->GenUniformGrid3D(
      noiseOutput.data(), ti.xRange[0], ti.yRange[0], ti.zRange[0],
      ti.xRange[1] - ti.xRange[0], ti.yRange[1] - ti.yRange[0],
      ti.zRange[1] - ti.zRange[0], ti.frequency, ti.seed);

  // Place noise into 3D vector array for easy access.
  int index = 0;
  std::vector<std::vector<float>> yArray;
  std::vector<float> xArray;
  for (int z = 0; z < ti.zRange[1] - ti.zRange[0]; z++) {
    for (int y = 0; y < ti.yRange[1] - ti.yRange[0]; y++) {
      for (int x = 0; x < ti.xRange[1] - ti.xRange[0]; x++) {
        error.log(std::to_string(x) + " " + std::to_string(y) + " " +
                  std::to_string(z) + ": " +
                  std::to_string(noiseOutput[index]));
        xArray.push_back(noiseOutput[index++]);
      }
      yArray.push_back(xArray);
      xArray.clear();
    }
    this->noise.push_back(yArray);
    yArray.clear();
  }
}

float Chunk::getNoise(int x, int y, int z) { return this->noise[x][y][z]; }
TerrainInfo Chunk::getTerrainInfo() { return this->terrainInfo; }
