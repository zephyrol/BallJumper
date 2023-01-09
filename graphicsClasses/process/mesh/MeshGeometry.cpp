//
// Created by Sebastien Morgenthaler on 03/01/2023.
//

#include "MeshGeometry.h"


MeshGeometry::MeshGeometry(
    VertexAttributes vertexAttributes,
    GeometricShape::IndicesBuffer indices
) :
    _vertexAttributes(std::move(vertexAttributes)),
    _indices(std::move(indices)) {
}

void MeshGeometry::merge(MeshGeometry &&other) {

    // Number of positions corresponds to the number of vertices.
    const auto indicesOffset = static_cast<GeometricShape::IndexType>(
        _vertexAttributes.getNumberOfVertices()
    );

    // Merge vertex attributes.
    _vertexAttributes*=(other.moveVertexAttributes());

    // Concat indices.
    GeometricShape::IndicesBuffer indicesOther(other.moveIndices());
    for (auto &index: indicesOther) {
        index += indicesOffset;
    }
}

VertexAttributes &&MeshGeometry::moveVertexAttributes() {
    return std::move(_vertexAttributes);
}

GeometricShape::IndicesBuffer &&MeshGeometry::moveIndices() {
    return std::move(_indices);
}

const GeometricShape::IndicesBuffer &MeshGeometry::indices() const {
    return _indices;
}

MeshGeometry MeshGeometry::createInstance(
    const CstDisplayable_sptr &displayable,
    const vecCstGeometricShape_sptr &shapes
) {

    const auto &headShape = shapes.front();

    auto vertexAttributes = headShape->genVertexAttributes();

    GeometricShape::IndicesBuffer indices = headShape->genIndices();
    GeometricShape::IndexType indicesOffset = vertexAttributes.getNumberOfVertices();

    // 1. Merging the shapes vertex attributes and the concat indices together.
    for (auto it = shapes.begin() + 1; it < shapes.end(); ++it) {
        const auto &shape = *it;

        // Concat indices
        auto shapeIndices = shape->genIndices();
        for (auto &index: shapeIndices) {
            index += indicesOffset;
        }

        // Look the number of vertices on the current shape and increase the offset for the next loop turn.
        auto shapeVertexAttributes = shape->genVertexAttributes();
        indicesOffset += shapeVertexAttributes.getNumberOfVertices();

        // Merge vertex attributes.
        vertexAttributes*=(std::move(shapeVertexAttributes));
    }


    const auto numberOfVertices = vertexAttributes.getNumberOfVertices();

    // 2. Generate states vertex attributes.
    const auto staticVec3AttributesGeneration = createStaticVertexAttributeGenerationFunctions<
        VertexAttributeVec3
    >(numberOfVertices, displayable->getStaticVec3fValues());

    const auto staticVec2AttributesGeneration = createStaticVertexAttributeGenerationFunctions<
        VertexAttributeVec2
    >(numberOfVertices, displayable->getStaticVec2fValues());

    const auto staticFloatAttributesGeneration = createStaticVertexAttributeGenerationFunctions<
        VertexAttributeFloat
    >(numberOfVertices, displayable->getStaticFloatValues());

    const auto staticIntAttributesGeneration = createStaticVertexAttributeGenerationFunctions<
        VertexAttributeInt
    >(numberOfVertices, displayable->getStaticIntValues());

    vertexAttributes += VertexAttributes {
        VertexAttributeBase::genAndFilter(staticVec3AttributesGeneration),
        VertexAttributeBase::genAndFilter(staticVec2AttributesGeneration),
        VertexAttributeBase::genAndFilter(staticFloatAttributesGeneration),
        VertexAttributeBase::genAndFilter(staticIntAttributesGeneration)
    };


    // TODO: Il y a deux choses differentes comme merging. Merge de geometric shape n'a rien a voir avec
    // une fusion des shapes et states attributes !
    return MeshGeometry(std::move(vertexAttributes), std::move(indices));
}

vecVertexAttributeBase_uptr MeshGeometry::extractVertexAttributes() {
    return _vertexAttributes.extractVertexAttributes();
}

template<typename VertexAttribute, typename StaticValues>
std::vector<std::function<std::unique_ptr<VertexAttribute>()> >
MeshGeometry::createStaticVertexAttributeGenerationFunctions(
    size_t numberOfVertices,
    const StaticValues &staticValues
) {
    std::vector<std::function<std::unique_ptr<VertexAttribute>()> > staticVertexAttributeGenerationFunctions;
    for (const auto &staticValue: staticValues) {

        // Values are passed by copy, because the function will be called after the end of this current
        // function execution
        staticVertexAttributeGenerationFunctions.emplace_back([numberOfVertices, staticValue]() {
            std::vector<decltype(Utility::convertToOpenGLFormat(staticValue))> openGlVec3(
                numberOfVertices,
                Utility::convertToOpenGLFormat(staticValue)
            );
            return VertexAttributes::genVertexAttribute(std::move(openGlVec3));
        });
    }
    return staticVertexAttributeGenerationFunctions;
}
