#pragma once
#include "Chunk.h"
#include "Error.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>

// MC stands for Marching Cubes
class ChunkMCMeshBuilder {
private:
  // Structs for organising data
  struct triangle {
    glm::vec3 verticie[3];
  };
  struct gridCube {
    glm::vec3 vert[8];
    float nVal[8];
  };

  // All polygonised tris
  std::vector<triangle> triangles;

  Error error = Error("ChunkMCMeshBuilder");

  Mesh *chunkTerrain;

  // Reference to chunk to chunk
  Chunk *chunk;

  // Marching Cube data from:
  // http://paulbourke.net/geometry/polygonise/
  static const int edgeTable[256];
  static const int triTable[256][16];

  // Functions to create the base mesh
  // special thanks to this page: http://paulbourke.net/geometry/polygonise/
  void generateMesh();
  void polygonise(gridCube cube, float noiseCutoff);
  glm::vec3 vertexInterp(float noiseCutoff, glm::vec3 p1, glm::vec3 p2,
                         float n1, float n2);

public:
  ChunkMCMeshBuilder(Chunk &chunk);
  ~ChunkMCMeshBuilder();

  Mesh *getChunkMesh();
};
