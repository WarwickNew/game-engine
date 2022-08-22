#pragma once

#include "MarchingCubeChunkRenderer.h"

const std::map<int, CubeData> MarchingCubeChunkRenderer::RenderMap = {
    {0, {glm::mat4(0.0f), 0}},
    {1,
     {glm::mat4({-1.000000, -0.000000, -0.000000, 0.000000},
                {0.000000, -1.000000, 0.000000, 0.000000},
                {0.000000, 0.000000, 1.000000, 0.000000},
                {0.000000, 0.000000, 0.000000, 1.000000}),
      1}},
    {2,
     {glm::mat4({-1.000000, -0.000000, 1.000000, 0.000000},
                {0.000000, -1.000000, -0.000000, 0.000000},
                {1.000000, 0.000000, -0.000000, 0.000000},
                {0.000000, 0.000000, 0.000000, 1.000000}),
      1}},
    {3, {glm::mat4(0.0f), 0}},
    {4, {glm::mat4(0.0f), 0}},
    {5, {glm::mat4(0.0f), 0}},
    {6, {glm::mat4(0.0f), 0}},
    {7, {glm::mat4(0.0f), 0}},
    {8, {glm::mat4(0.0f), 0}},
    {9, {glm::mat4(0.0f), 0}},
    {10, {glm::mat4(0.0f), 0}},
    {11, {glm::mat4(0.0f), 0}},
    {12, {glm::mat4(0.0f), 0}},
    {13, {glm::mat4(0.0f), 0}},
    {14, {glm::mat4(0.0f), 0}},
    {15, {glm::mat4(0.0f), 0}},
    {16, {glm::mat4(0.0f), 0}},
    {17, {glm::mat4(0.0f), 0}},
    {18, {glm::mat4(0.0f), 0}},
    {19, {glm::mat4(0.0f), 0}},
    {20, {glm::mat4(0.0f), 0}},
    {21, {glm::mat4(0.0f), 0}},
    {22, {glm::mat4(0.0f), 0}},
    {23, {glm::mat4(0.0f), 0}},
    {24, {glm::mat4(0.0f), 0}},
    {25, {glm::mat4(0.0f), 0}},
    {26, {glm::mat4(0.0f), 0}},
    {27, {glm::mat4(0.0f), 0}},
    {28, {glm::mat4(0.0f), 0}},
    {29, {glm::mat4(0.0f), 0}},
    {30, {glm::mat4(0.0f), 0}},
    {31, {glm::mat4(0.0f), 0}},
    {32, {glm::mat4(0.0f), 0}},
    {33, {glm::mat4(0.0f), 0}},
    {34, {glm::mat4(0.0f), 0}},
    {35, {glm::mat4(0.0f), 0}},
    {36, {glm::mat4(0.0f), 0}},
    {37, {glm::mat4(0.0f), 0}},
    {38, {glm::mat4(0.0f), 0}},
    {39, {glm::mat4(0.0f), 0}},
    {40, {glm::mat4(0.0f), 0}},
    {41, {glm::mat4(0.0f), 0}},
    {42, {glm::mat4(0.0f), 0}},
    {43, {glm::mat4(0.0f), 0}},
    {44, {glm::mat4(0.0f), 0}},
    {45, {glm::mat4(0.0f), 0}},
    {46, {glm::mat4(0.0f), 0}},
    {47, {glm::mat4(0.0f), 0}},
    {48, {glm::mat4(0.0f), 0}},
    {49, {glm::mat4(0.0f), 0}},
    {50, {glm::mat4(0.0f), 0}},
    {51, {glm::mat4(0.0f), 0}},
    {52, {glm::mat4(0.0f), 0}},
    {53, {glm::mat4(0.0f), 0}},
    {54, {glm::mat4(0.0f), 0}},
    {55, {glm::mat4(0.0f), 0}},
    {56, {glm::mat4(0.0f), 0}},
    {57, {glm::mat4(0.0f), 0}},
    {58, {glm::mat4(0.0f), 0}},
    {59, {glm::mat4(0.0f), 0}},
    {60, {glm::mat4(0.0f), 0}},
    {61, {glm::mat4(0.0f), 0}},
    {62, {glm::mat4(0.0f), 0}},
    {63, {glm::mat4(0.0f), 0}},
    {64, {glm::mat4(0.0f), 0}},
    {65, {glm::mat4(0.0f), 0}},
    {66, {glm::mat4(0.0f), 0}},
    {67, {glm::mat4(0.0f), 0}},
    {68, {glm::mat4(0.0f), 0}},
    {69, {glm::mat4(0.0f), 0}},
    {70, {glm::mat4(0.0f), 0}},
    {71, {glm::mat4(0.0f), 0}},
    {72, {glm::mat4(0.0f), 0}},
    {73, {glm::mat4(0.0f), 0}},
    {74, {glm::mat4(0.0f), 0}},
    {75, {glm::mat4(0.0f), 0}},
    {76, {glm::mat4(0.0f), 0}},
    {77, {glm::mat4(0.0f), 0}},
    {78, {glm::mat4(0.0f), 0}},
    {79, {glm::mat4(0.0f), 0}},
    {80, {glm::mat4(0.0f), 0}},
    {81, {glm::mat4(0.0f), 0}},
    {82, {glm::mat4(0.0f), 0}},
    {83, {glm::mat4(0.0f), 0}},
    {84, {glm::mat4(0.0f), 0}},
    {85, {glm::mat4(0.0f), 0}},
    {86, {glm::mat4(0.0f), 0}},
    {87, {glm::mat4(0.0f), 0}},
    {88, {glm::mat4(0.0f), 0}},
    {89, {glm::mat4(0.0f), 0}},
    {90, {glm::mat4(0.0f), 0}},
    {91, {glm::mat4(0.0f), 0}},
    {92, {glm::mat4(0.0f), 0}},
    {93, {glm::mat4(0.0f), 0}},
    {94, {glm::mat4(0.0f), 0}},
    {95, {glm::mat4(0.0f), 0}},
    {96, {glm::mat4(0.0f), 0}},
    {97, {glm::mat4(0.0f), 0}},
    {98, {glm::mat4(0.0f), 0}},
    {99, {glm::mat4(0.0f), 0}},
    {100, {glm::mat4(0.0f), 0}},
    {101, {glm::mat4(0.0f), 0}},
    {102, {glm::mat4(0.0f), 0}},
    {103, {glm::mat4(0.0f), 0}},
    {104, {glm::mat4(0.0f), 0}},
    {105, {glm::mat4(0.0f), 0}},
    {106, {glm::mat4(0.0f), 0}},
    {107, {glm::mat4(0.0f), 0}},
    {108, {glm::mat4(0.0f), 0}},
    {109, {glm::mat4(0.0f), 0}},
    {110, {glm::mat4(0.0f), 0}},
    {111, {glm::mat4(0.0f), 0}},
    {112, {glm::mat4(0.0f), 0}},
    {113, {glm::mat4(0.0f), 0}},
    {114, {glm::mat4(0.0f), 0}},
    {115, {glm::mat4(0.0f), 0}},
    {116, {glm::mat4(0.0f), 0}},
    {117, {glm::mat4(0.0f), 0}},
    {118, {glm::mat4(0.0f), 0}},
    {119, {glm::mat4(0.0f), 0}},
    {120, {glm::mat4(0.0f), 0}},
    {121, {glm::mat4(0.0f), 0}},
    {122, {glm::mat4(0.0f), 0}},
    {123, {glm::mat4(0.0f), 0}},
    {124, {glm::mat4(0.0f), 0}},
    {125, {glm::mat4(0.0f), 0}},
    {126, {glm::mat4(0.0f), 0}},
    {127, {glm::mat4(0.0f), 0}},
    {128, {glm::mat4(0.0f), 0}},
    {129, {glm::mat4(0.0f), 0}},
    {130, {glm::mat4(0.0f), 0}},
    {131, {glm::mat4(0.0f), 0}},
    {132, {glm::mat4(0.0f), 0}},
    {133, {glm::mat4(0.0f), 0}},
    {134, {glm::mat4(0.0f), 0}},
    {135, {glm::mat4(0.0f), 0}},
    {136, {glm::mat4(0.0f), 0}},
    {137, {glm::mat4(0.0f), 0}},
    {138, {glm::mat4(0.0f), 0}},
    {139, {glm::mat4(0.0f), 0}},
    {140, {glm::mat4(0.0f), 0}},
    {141, {glm::mat4(0.0f), 0}},
    {142, {glm::mat4(0.0f), 0}},
    {143, {glm::mat4(0.0f), 0}},
    {144, {glm::mat4(0.0f), 0}},
    {145, {glm::mat4(0.0f), 0}},
    {146, {glm::mat4(0.0f), 0}},
    {147, {glm::mat4(0.0f), 0}},
    {148, {glm::mat4(0.0f), 0}},
    {149, {glm::mat4(0.0f), 0}},
    {150, {glm::mat4(0.0f), 0}},
    {151, {glm::mat4(0.0f), 0}},
    {152, {glm::mat4(0.0f), 0}},
    {153, {glm::mat4(0.0f), 0}},
    {154, {glm::mat4(0.0f), 0}},
    {155, {glm::mat4(0.0f), 0}},
    {156, {glm::mat4(0.0f), 0}},
    {157, {glm::mat4(0.0f), 0}},
    {158, {glm::mat4(0.0f), 0}},
    {159, {glm::mat4(0.0f), 0}},
    {160, {glm::mat4(0.0f), 0}},
    {161, {glm::mat4(0.0f), 0}},
    {162, {glm::mat4(0.0f), 0}},
    {163, {glm::mat4(0.0f), 0}},
    {164, {glm::mat4(0.0f), 0}},
    {165, {glm::mat4(0.0f), 0}},
    {166, {glm::mat4(0.0f), 0}},
    {167, {glm::mat4(0.0f), 0}},
    {168, {glm::mat4(0.0f), 0}},
    {169, {glm::mat4(0.0f), 0}},
    {170, {glm::mat4(0.0f), 0}},
    {171, {glm::mat4(0.0f), 0}},
    {172, {glm::mat4(0.0f), 0}},
    {173, {glm::mat4(0.0f), 0}},
    {174, {glm::mat4(0.0f), 0}},
    {175, {glm::mat4(0.0f), 0}},
    {176, {glm::mat4(0.0f), 0}},
    {177, {glm::mat4(0.0f), 0}},
    {178, {glm::mat4(0.0f), 0}},
    {179, {glm::mat4(0.0f), 0}},
    {180, {glm::mat4(0.0f), 0}},
    {181, {glm::mat4(0.0f), 0}},
    {182, {glm::mat4(0.0f), 0}},
    {183, {glm::mat4(0.0f), 0}},
    {184, {glm::mat4(0.0f), 0}},
    {185, {glm::mat4(0.0f), 0}},
    {186, {glm::mat4(0.0f), 0}},
    {187, {glm::mat4(0.0f), 0}},
    {188, {glm::mat4(0.0f), 0}},
    {189, {glm::mat4(0.0f), 0}},
    {190, {glm::mat4(0.0f), 0}},
    {191, {glm::mat4(0.0f), 0}},
    {192, {glm::mat4(0.0f), 0}},
    {193, {glm::mat4(0.0f), 0}},
    {194, {glm::mat4(0.0f), 0}},
    {195, {glm::mat4(0.0f), 0}},
    {196, {glm::mat4(0.0f), 0}},
    {197, {glm::mat4(0.0f), 0}},
    {198, {glm::mat4(0.0f), 0}},
    {199, {glm::mat4(0.0f), 0}},
    {200, {glm::mat4(0.0f), 0}},
    {201, {glm::mat4(0.0f), 0}},
    {202, {glm::mat4(0.0f), 0}},
    {203, {glm::mat4(0.0f), 0}},
    {204, {glm::mat4(0.0f), 0}},
    {205, {glm::mat4(0.0f), 0}},
    {206, {glm::mat4(0.0f), 0}},
    {207, {glm::mat4(0.0f), 0}},
    {208, {glm::mat4(0.0f), 0}},
    {209, {glm::mat4(0.0f), 0}},
    {210, {glm::mat4(0.0f), 0}},
    {211, {glm::mat4(0.0f), 0}},
    {212, {glm::mat4(0.0f), 0}},
    {213, {glm::mat4(0.0f), 0}},
    {214, {glm::mat4(0.0f), 0}},
    {215, {glm::mat4(0.0f), 0}},
    {216, {glm::mat4(0.0f), 0}},
    {217, {glm::mat4(0.0f), 0}},
    {218, {glm::mat4(0.0f), 0}},
    {219, {glm::mat4(0.0f), 0}},
    {220, {glm::mat4(0.0f), 0}},
    {221, {glm::mat4(0.0f), 0}},
    {222, {glm::mat4(0.0f), 0}},
    {223, {glm::mat4(0.0f), 0}},
    {224, {glm::mat4(0.0f), 0}},
    {225, {glm::mat4(0.0f), 0}},
    {226, {glm::mat4(0.0f), 0}},
    {227, {glm::mat4(0.0f), 0}},
    {228, {glm::mat4(0.0f), 0}},
    {229, {glm::mat4(0.0f), 0}},
    {230, {glm::mat4(0.0f), 0}},
    {231, {glm::mat4(0.0f), 0}},
    {232, {glm::mat4(0.0f), 0}},
    {233, {glm::mat4(0.0f), 0}},
    {234, {glm::mat4(0.0f), 0}},
    {235, {glm::mat4(0.0f), 0}},
    {236, {glm::mat4(0.0f), 0}},
    {237, {glm::mat4(0.0f), 0}},
    {238, {glm::mat4(0.0f), 0}},
    {239, {glm::mat4(0.0f), 0}},
    {240, {glm::mat4(0.0f), 0}},
    {241, {glm::mat4(0.0f), 0}},
    {242, {glm::mat4(0.0f), 0}},
    {243, {glm::mat4(0.0f), 0}},
    {244, {glm::mat4(0.0f), 0}},
    {245, {glm::mat4(0.0f), 0}},
    {246, {glm::mat4(0.0f), 0}},
    {247, {glm::mat4(0.0f), 0}},
    {248, {glm::mat4(0.0f), 0}},
    {249, {glm::mat4(0.0f), 0}},
    {250, {glm::mat4(0.0f), 0}},
    {251, {glm::mat4(0.0f), 0}},
    {252, {glm::mat4(0.0f), 0}},
    {253, {glm::mat4(0.0f), 0}},
    {254, {glm::mat4(0.0f), 0}},
    {255, {glm::mat4(0.0f), 0}}};
