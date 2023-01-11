/*
 * File: Sphere.cpp
 * Author: Morgenthaler S
 *
 * Created on 29 mars 2020, 14:43
 */

#include "Sphere.h"

Sphere::Sphere(const glm::mat4 &modelTransform,
               const glm::mat4 &normalsTransform) :
    GeometricShape(modelTransform, normalsTransform, {}, {}) {
}

Sphere::Sphere(const glm::vec3 &customColor,
               const glm::mat4 &modelTransform,
               const glm::mat4 &normalsTransform) :
    GeometricShape(modelTransform, normalsTransform, {customColor}, {}) {

}

Sphere::Sphere(const glm::vec3 &customColor,
               const glm::vec3 &customColor2,
               const glm::mat4 &modelTransform,
               const glm::mat4 &normalsTransform) :
    GeometricShape(modelTransform, normalsTransform, {customColor, customColor2}, {}) {

}

Sphere::Sphere(const JBTypes::Color &color,
               const glm::mat4 &modelTransform,
               const glm::mat4 &normalsTransform) :
    Sphere(getSphereColor(color), modelTransform, normalsTransform) {
}

std::vector<glm::vec3> Sphere::genColors(const std::vector<glm::vec3> &colors) const {
    if (colors.size() == 1) {
        constexpr size_t numberOfColors = 2400;
        return GeometricShape::createCustomColorBuffer(
            colors.at(0), // customColor
            numberOfColors
        );
    }

    bool useCustomColors;
    glm::vec3 firstColor;
    glm::vec3 secondColor;
    if (colors.size() == 2) {
        useCustomColors = true;
        firstColor = colors.at(0);
        secondColor = colors.at(1);
    } else {
        useCustomColors = false;
        firstColor = glm::vec3(0.f);
        secondColor = glm::vec3(0.f);
    }
    std::vector<glm::vec3> outputColors{};

    constexpr unsigned int iParaCount = 40;
    constexpr unsigned int iMeriCount = 60;

    // Parallels
    for (unsigned int i = 0; i < iParaCount; ++i) {
        const auto iFloat = static_cast<float>(i);

        for (unsigned int j = 0; j < iMeriCount; ++j) {
            if (!useCustomColors) {
                outputColors.emplace_back(
                    iFloat / iParaCount,
                    (j < iMeriCount / 2) ? 1.f : 0.f,
                    0.5f
                );
            } else {
                outputColors.emplace_back((j < iMeriCount / 2) ? firstColor : secondColor);
            }
        }
    }
    return outputColors;
}

std::vector<GLushort> Sphere::genIndices() const {

    std::vector<GLushort> indices{};
    constexpr unsigned int iParaCount = 40;
    constexpr unsigned int iMeriCount = 60;

    // For quads split in 2
    for (unsigned int i = 0; i < (iParaCount - 1); ++i) {
        for (unsigned int j = 0; j < (iMeriCount - 1); ++j) {
            indices.push_back(iMeriCount * i + j);
            indices.push_back(iMeriCount * i + (j + 1));
            indices.push_back(iMeriCount * (i + 1) + (j + 1));
            indices.push_back(iMeriCount * (i + 1) + (j + 1));
            indices.push_back(iMeriCount * (i + 1) + j);
            indices.push_back(iMeriCount * i + j);
        }
    }
    return indices;
}

std::vector<glm::vec3> Sphere::genNormals() const {
    std::vector<glm::vec3> normals{};
    constexpr unsigned int iParaCount = 40;
    constexpr unsigned int iMeriCount = 60;

    // Create a sphere
    constexpr GLuint iVertexCount = iParaCount * iMeriCount;

    // Compute normals
    // on a 0 centered sphere : you just need to normalise the position!
    normals.reserve(iVertexCount);

    const std::vector<glm::vec3> positions = genPositions();
    for (unsigned int i = 0; i < iVertexCount; ++i) {
        normals.emplace_back(glm::normalize(positions[i]));
    }
    return normals;
}

std::vector<glm::vec3> Sphere::genPositions() const {
    std::vector<glm::vec3> positions{};
    constexpr unsigned int iParaCount = 40;
    constexpr unsigned int iMeriCount = 60;
    constexpr float r = 1.f;

    constexpr float a1 = (180.0f / static_cast <float>(iParaCount - 1)) * static_cast <float>(M_PI) / 180.0f;
    constexpr float a2 = (360.0f / (iMeriCount - 1)) * static_cast <float>(M_PI) / 180.0f;

    // Parallels
    for (unsigned int i = 0; i < iParaCount; ++i) {
        const auto iFloat = static_cast<float>(i);
        const float fAngle = -static_cast <float>(M_PI) / 2.0f + a1 * iFloat;
        const float z = r * sinf(fAngle);
        const float fRadius = r * cosf(fAngle);

        for (unsigned int j = 0; j < iMeriCount; ++j) {
            const auto jFloat = static_cast<float>(j);
            positions.emplace_back(
                fRadius * cosf(a2 * jFloat),
                fRadius * sinf(a2 * jFloat),
                z
            );
        }
    }
    return positions;
}

glm::vec3 Sphere::getSphereColor(const JBTypes::Color &color) {
    if (color == JBTypes::Color::Yellow) {
        return {1.f, 215.f / 255.f, 0.f};
    }
    if (color == JBTypes::Color::Red) {
        return {114.f / 255.f, 47.f / 255.f, 55.f / 255.f};
    }
    if (color == JBTypes::Color::Blue) {
        return {0.f, 0.f, 0.5f};
    }
    return {0.f, 0.f, 0.f};
}

