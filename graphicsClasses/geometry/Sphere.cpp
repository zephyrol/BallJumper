/*
 * File: Sphere.cpp
 * Author: Morgenthaler S
 *
 * Created on 29 mars 2020, 14:43
 */

#include "Sphere.h"

Sphere::Sphere(const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):
    GeometricShape(modelTransform, normalsTransform, {}) {
}

Sphere::Sphere(const glm::vec3& customColor,
               const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):
    GeometricShape(modelTransform, normalsTransform, { customColor }) {

}

Sphere::Sphere(const glm::vec3& customColor,
               const glm::vec3& customColor2,
               const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):
    GeometricShape(modelTransform, normalsTransform, { customColor, customColor2 }) {

}

/*Sphere::Sphere(const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):GeometricShape(
        Sphere::basicInfoSphere.positions,
        Sphere::basicInfoSphere.normals,
        Sphere::basicInfoSphere.colors,
        Sphere::basicInfoSphere.uvCoords,
        modelTransform,
        normalsTransform,
        Sphere::basicInfoSphere.indices) {
   }

   Sphere::Sphere(const glm::vec3& customColor,
               const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):GeometricShape(
        Sphere::basicInfoSphere.positions,
        Sphere::basicInfoSphere.normals,
        GeometricShape::createCustomColorBuffer(
            customColor,
            Sphere::basicInfoSphere.colors.size()),
        Sphere::basicInfoSphere.uvCoords,
        modelTransform,
        normalsTransform,
        Sphere::basicInfoSphere.indices) {
   }

   Sphere::Sphere(const glm::vec3& customColor,
               const glm::vec3& customColor2,
               const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):GeometricShape(
        Sphere::basicInfoSphere.positions,
        Sphere::basicInfoSphere.normals,
        computeBasicInfoSphere(true,
                               customColor,
                               customColor2
                               ).colors,
        Sphere::basicInfoSphere.uvCoords,
        modelTransform,
        normalsTransform,
        Sphere::basicInfoSphere.indices) {
   }

   Sphere::Sphere(const GeometricShape& sphere,
               const glm::mat4& modelTransform,
               const glm::mat4& normalsTransform):
    GeometricShape(sphere, modelTransform, normalsTransform) {
   }*/

GeometricShape::ShapeVertexAttributes Sphere::computeBasicInfoSphere (
    bool useCustomColors,
    const glm::vec3& firstColor,
    const glm::vec3& secondColor
    ) {

    GeometricShape::ShapeVertexAttributes infoSphere;

    constexpr unsigned int iParaCount = 40;
    constexpr unsigned int iMeriCount = 60;
    constexpr float r = 1.f;

    // Create a sphere ---------------------------------------------------------
    constexpr GLuint iVertexCount = iParaCount * iMeriCount;

    constexpr float a1 = (180.0f / static_cast <float>(iParaCount - 1)) *
                         static_cast <float>(M_PI) / 180.0f;
    constexpr float a2 = (360.0f / (iMeriCount - 1)) *
                         static_cast <float>(M_PI) / 180.0f;

    // parallels ---------------------------------------------------------------
    for (unsigned int i = 0; i < iParaCount; ++i) {
        const float fAngle = -static_cast <float>(M_PI) / 2.0f + a1 * (i);
        const float z = r * static_cast <float>(sin(fAngle));
        const float fRadius = r * static_cast <float>(cos(fAngle));

        for (unsigned int j = 0; j < iMeriCount; ++j) {
            infoSphere.positions.push_back(glm::vec3(
                                               fRadius * static_cast <float>(cos(a2 * j)),
                                               fRadius * static_cast <float>(sin(a2 * j)),
                                               z));
            infoSphere.uvCoords.push_back(
                glm::vec2(static_cast <float>(j) / iMeriCount,
                          static_cast <float>(iParaCount - i) / iParaCount));
            if (!useCustomColors) {
                infoSphere.colors.push_back(
                    glm::vec3(static_cast <float>(i) / iParaCount,
                              (j < iMeriCount / 2) ? 1.f : 0.f,
                              0.5f));
            } else {
                infoSphere.colors.push_back(
                    (j < iMeriCount / 2) ? firstColor : secondColor
                    );
            }
        }
    }
    // compute normals ---------------------------------------------------------
    // on a 0 centered sphere : you just need to normalise the position!
    infoSphere.normals.reserve(iVertexCount);

    for (unsigned int i = 0; i < iVertexCount; ++i) {
        infoSphere.normals.push_back(glm::normalize(
                                         infoSphere.positions[i]));
    }

    // for quads split in 2

    for (unsigned int i = 0; i < (iParaCount - 1); ++i) {
        for (unsigned int j = 0; j < (iMeriCount - 1); ++j) {
            infoSphere.indices.push_back(iMeriCount * i + j);
            infoSphere.indices.push_back(iMeriCount * i + (j + 1));
            infoSphere.indices.push_back(iMeriCount * (i + 1) + (j + 1));
            infoSphere.indices.push_back(iMeriCount * (i + 1) + (j + 1));
            infoSphere.indices.push_back(iMeriCount * (i + 1) + j);
            infoSphere.indices.push_back(iMeriCount * i + j);
        }
    }

    return infoSphere;
}



std::vector <glm::vec3> Sphere::genColors (const std::vector <glm::vec3>& colors) const {
    if (colors.size() == 2) {
        return computeBasicInfoSphere(true, colors.at(0), colors.at(1)).colors;
    }
    if (colors.size() == 1) {
        return GeometricShape::createCustomColorBuffer(colors.at(0), // customColor
                                                       basicInfoSphere.colors.size());
    }
    return basicInfoSphere.colors;
}

std::vector <glm::vec2> Sphere::genUvCoords() const {
    return basicInfoSphere.uvCoords;
}

std::vector <GLushort> Sphere::genIndices() const {
    return Sphere::basicInfoSphere.indices;
}

std::vector <glm::vec3> Sphere::genNormals() const {
    return basicInfoSphere.normals;
}

std::vector <glm::vec3> Sphere::genPositions() const {
    return basicInfoSphere.positions;
}


const GeometricShape::ShapeVertexAttributes Sphere::basicInfoSphere = computeBasicInfoSphere();
