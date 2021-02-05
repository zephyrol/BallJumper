/*
 * File: Mesh.h
 * Author: Morgenthaler S
 *
 * Created on 31 janvier 2021, 18:45
 */

#ifndef MESH_H
#define MESH_H
#include "Shader.h"
#include "ShaderProgram.h"
#include <system/ParallelTask.h>
#include <scene/Ball.h>
#include <scene/Map.h>
#include "Star.h"
#include "mesh/MeshGenerator.h"

class Mesh;
using Mesh_sptr = std::shared_ptr <Mesh>;
using CstMesh_sptr = std::shared_ptr <const Mesh>;
using vecCstMesh_sptr = std::vector <Mesh_sptr>;
using vecMesh_sptr = std::vector <Mesh_sptr>;

class Mesh {
public:
Mesh(const State& state, const vecCstGeometricShape_sptr& shapes);
struct StaticAttributes {
    std::vector <glm::vec3> positions;
    std::vector <glm::vec3> normals;
    std::vector <glm::vec3> colors;
    std::vector <glm::vec2> uvCoords;
    std::vector <GLushort> indices;
};

struct DynamicAttributes {
    std::vector<GLubyte> dynamicUbytes;
    std::vector<GLfloat> dynamicFloats;
    std::vector <glm::vec3> dynamicsVec3s;
    std::vector <glm::vec2> dynamicsVec2s;
};

struct UniformValues {
    std::map<std::string, GLuint> uniformUints;
    std::map<std::string, GLfloat> uniformFloats;
    std::map<std::string, glm::vec3> uniformVec3s;
    std::map<std::string, glm::vec2> uniformVec2s;
};

void update();

StaticAttributes genStaticAttributes() const;
DynamicAttributes genDynamicAttributes() const;
static Mesh::StaticAttributes concatStaticAttributes(const Mesh::StaticAttributes& current,
                                                     const Mesh::StaticAttributes& staticAttributes);

private:

template<typename T> static void concatShapeData(std::vector <T>& current, const std::vector <T>& dataShape);

template<typename Raw, typename OpenGL > 
static void convertVectorToOpenGLFormat (const std::vector<Raw>& rawValues, std::vector<OpenGL>& openGLValues);

const State& _state;
const vecCstGeometricShape_sptr _shapes;

};

#endif // MESH_H
