//
// Created by seb on 13/08/2021.
//

#include "Shape.h"

#include <utility>

Shape::Shape(const Shape::Aspect &aspect, const JBTypes::Color &color,
             std::list<Transformation>&& transformations):
             _aspect(aspect),
             _color(color),
             _transformations(std::move(transformations))
{

}

const Shape::Aspect& Shape::aspect() const {
    return _aspect;
}

const JBTypes::Color &Shape::color() const {
    return _color;
}

const std::list<Transformation> &Shape::transformations() const {
    return _transformations;
}

