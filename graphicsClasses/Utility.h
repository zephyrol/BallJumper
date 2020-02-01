#ifndef UTILITY_H
#define UTILITY_H
#include <Types.h>
#include "Shader.h"
#include <glm/glm.hpp>
#define RESOLUTION_X 1024 
#define RESOLUTION_Y 768

namespace Utility {

    std::string                       readFileSrc(const std::string& filePath);
    void                              printMatrix(const glm::mat4& m);
    std::vector<GLfloat>              computeNormals(const std::vector<GLfloat>&
                                                      positions);
    glm::mat4                         rotationUpToDir(
                                        JumperBallTypes::Direction dir);

    float                             evalGauss1D(float x, float sigma);
    std::vector<GLfloat>              genGaussBuffer( size_t patchSize,
                                                      float sigma);

    
    extern const std::vector<GLfloat> positionsCube;
    extern const std::vector<GLfloat> colorsCube;
    extern const std::vector<GLfloat> normalsCube;
    extern const std::vector<GLfloat> uvCoordsCube;

    extern const std::vector<GLfloat> positionsPike;
    extern const std::vector<GLfloat> colorsPike;
    extern const std::vector<GLfloat> normalsPike;
    extern const std::vector<GLfloat> uvCoordsPike;

    extern const std::vector<GLfloat> positionsQuadScreen;
    extern const std::vector<GLfloat> colorsQuadScreen;
    extern const std::vector<GLfloat> normalsQuadScreen;
    extern const std::vector<GLfloat> uvCoordsQuadScreen;
    
}

#endif /* UTILITY_H */

