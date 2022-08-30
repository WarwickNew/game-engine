#pragma once
#include "Error.h"
#include "Mesh.h"

// MC stands for Marching Cubes
class ChunkMCMeshBuilder {

private:
  Error error = Error("ChunkMCMeshBuilder");

  Mesh *chunkTerrain;

  // Marching Cube data from:
  // http://paulbourke.net/geometry/polygonise/
  static const int edgeTable[256];
  static const int triTable[256][16];

public:
  ChunkMCMeshBuilder();
  ~ChunkMCMeshBuilder();

  Mesh *getChunkMesh();
};
