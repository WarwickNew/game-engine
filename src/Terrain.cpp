#include "Terrain.h"

Terrain::Terrain() {
  TerrainInfo ti;
  ti.xRange[0] = 0;
  ti.xRange[1] = 16;
  ti.yRange[0] = 0;
  ti.yRange[1] = 16;
  ti.zRange[0] = 0;
  ti.zRange[1] = 16;
  ti.frequency = 0.2f;
  ti.seed = 0;

  chunks.push_back(Chunk(fnGenerator, ti));
}
