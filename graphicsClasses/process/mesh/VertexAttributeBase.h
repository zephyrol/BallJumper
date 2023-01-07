//
// Created by Sebastien Morgenthaler on 04/01/2023.
//

#ifndef JUMPERBALLAPPLICATION_VERTEXATTRIBUTEBASE_H
#define JUMPERBALLAPPLICATION_VERTEXATTRIBUTEBASE_H

#include "Utility.h"

class VertexAttributeBase;

using VertexAttributeBase_sptr = std::shared_ptr<VertexAttributeBase>;
using CstVertexAttributeBase_sptr = std::shared_ptr<const VertexAttributeBase>;
using vecCstVertexAttributeBase_sptr = std::vector<CstVertexAttributeBase_sptr>;
using vecVertexAttributeBase_sptr = std::vector<VertexAttributeBase_sptr>;

using VertexAttributeBase_uptr = std::unique_ptr<VertexAttributeBase>;
using CstVertexAttributeBase_uptr = std::unique_ptr<const VertexAttributeBase>;
using vecCstVertexAttributeBase_uptr = std::vector<CstVertexAttributeBase_uptr>;
using vecVertexAttributeBase_uptr = std::vector<VertexAttributeBase_uptr>;

class VertexAttributeBase {

public:
    explicit VertexAttributeBase(GLenum dataType);

    GLenum getDataType() const;

    /**
     * Merge a vertex attribute geometry into the current one moving it.
     * @param other The other that will be moved into the current one.
     */
    virtual void merge(VertexAttributeBase_uptr &&other);

    virtual size_t dataLength() const = 0;

    virtual ~VertexAttributeBase() = default;

    /**
     * Use vertex attribute generation functions to gen them and filter the unused ones
     */
    static vecVertexAttributeBase_uptr genAndFilterVertexAttributes(
        const std::vector<std::function<VertexAttributeBase_uptr()> > &vertexAttributeGenerationFunction
    );

private:

    const GLenum _dataType;

    /**
     * Binary operation function usually used in reduce function to filter the unused vertex attributes
     */
    static vecVertexAttributeBase_uptr filterUnusedAttributes(
        vecVertexAttributeBase_uptr &current,
        const std::function<VertexAttributeBase_uptr()> &vertexAttributeGenerationFunction
    );

};


#endif //JUMPERBALLAPPLICATION_VERTEXATTRIBUTEBASE_H
