/*
 * file: genStar.cpp
 * author: morgenthaler s
 *
 * created on 22 aout 2020, 18h15
 */

#include "MeshGenerator.h"

vecMesh_sptr MeshGenerator::genStar (const Star& star) {
    CstGeometricShape_sptr shape = std::make_shared <Quad>();
    vecCstGeometricShape_sptr geometricShapes { shape };
    State_uptr state_ptr(new StarState(star));
    Mesh_sptr meshSptr = std::make_shared <Mesh>(std::move(state_ptr), std::move(geometricShapes));
    return { meshSptr };
}
