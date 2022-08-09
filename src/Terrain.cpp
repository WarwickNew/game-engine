#include "Terrain.h"

Terrain::Terrain() {
  // Create location to store noise values.
  std::vector<float> noiseOutput(16 * 16 * 16);

  // Generate noise to the outputs dimentions
  this->fnGenerator->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16,
                                      0.2f, 0);

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
