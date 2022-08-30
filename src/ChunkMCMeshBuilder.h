#pragma once
#include "Error.h"
#include "Mesh.h"

// MC stands for Marching Cubes
class ChunkMCMeshBuilder {

private:
  Error error = Error("ChunkMCMeshBuilder");

  Mesh *chunkTerrain;

public:
  ChunkMCMeshBuilder();
  ~ChunkMCMeshBuilder();

  Mesh *getChunkMesh();
};
