#include "Chunk.h"

Chunk::Chunk(FastNoise::SmartNode<> &noiseGenerator, TerrainInfo ti) {
  this->fnGenerator = &noiseGenerator;
  // Create location to store noise values.
  std::vector<float> noiseOutput((ti.xRange[1] - ti.xRange[0]) *
                                 (ti.yRange[1] - ti.yRange[0]) *
                                 (ti.zRange[1] - ti.zRange[0]));

  // Generate noise to the outputs dimentions
  noiseGenerator->GenUniformGrid3D(
      noiseOutput.data(), ti.xRange[0], ti.yRange[0], ti.zRange[0],
      ti.xRange[1] - ti.xRange[0], ti.yRange[1] - ti.yRange[0],
      ti.zRange[1] - ti.zRange[0], ti.frequency, ti.seed);

  // do stuff with values
  int index = 0;
  for (int z = 0; z < 16; z++) {
    for (int y = 0; y < 16; y++) {
      for (int x = 0; x < 16; x++) {
        error.log(std::to_string(x) + " " + std::to_string(y) + " " +
                  std::to_string(z) + ": " +
                  std::to_string(noiseOutput[index++]));
      }
    }
  }
}
