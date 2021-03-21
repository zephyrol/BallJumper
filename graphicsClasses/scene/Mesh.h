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
#include <geometry/GeometricShape.h>
#include <scene/State.h>

class Mesh;
using Mesh_sptr = std::shared_ptr <Mesh>;
using CstMesh_sptr = std::shared_ptr <const Mesh>;
using vecCstMesh_sptr = std::vector <CstMesh_sptr>;
using vecMesh_sptr = std::vector <Mesh_sptr>;

class Mesh {
public:
Mesh(std::unique_ptr <State>&& state, vecCstGeometricShape_sptr&& shapes);

struct StateVertexAttributes {
    std::vector <std::vector <GLfloat> > staticFloats = {};
    std::vector <std::vector <glm::vec3> > staticVec3s = {};
    std::vector <std::vector <glm::vec2> > staticVec2s = {};
};

struct MeshVerticesInfo {
    GeometricShape::ShapeVerticesInfo shapeVerticesInfo;
    Mesh::StateVertexAttributes stateVertexAttributes;
};

template<typename T> using UniformVariable = std::map <std::string, T>;
struct Uniforms {
    UniformVariable <GLfloat> uniformFloats = {};
    UniformVariable <glm::vec2> uniformVec2s = {};
    UniformVariable <glm::vec3> uniformVec3s = {};
    UniformVariable <glm::vec4> uniformVec4s = {};
    UniformVariable <glm::mat4> uniformMat4s = {};
    UniformVariable <GLuint> uniformTextures = {};
};

State::GlobalState update();

size_t numberOfVertices() const;
Uniforms genUniformsValues() const;

MeshVerticesInfo genMeshVerticesInfo() const;

static void concatMeshVerticesInfo(MeshVerticesInfo& current, const MeshVerticesInfo& other);

private:

size_t computeNumberOfVertices() const;
template<typename T> void duplicateStateVertexAttribute(std::vector <std::vector <T> >& attributes,
                                                        const std::vector <T>& values) const;

template<typename RawType, typename OpenGLType> static void convertAttributesToOpenGLFormat(
    const std::vector <RawType>& rawValues, std::vector <OpenGLType>& openGLValues);

template<typename RawType, typename OpenGLType> static void convertUniformsToOpenGLFormat(
    const std::map <std::string, RawType>& rawValues, Mesh::UniformVariable <OpenGLType>& openGLValues);

template<typename T> static void concatStateVertexAttribute(
    std::vector <std::vector <T> >& current,
    const std::vector <std::vector <T> >& other
    );
static void concatStateVertexAttributes(StateVertexAttributes& current, const StateVertexAttributes& other);

const std::unique_ptr <State> _state;
const vecCstGeometricShape_sptr _shapes;
const size_t _numberOfVertices;
};

#endif // MESH_H
