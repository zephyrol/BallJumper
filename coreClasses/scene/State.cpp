/*
 * File: Mesh.h
 * Author: Morgenthaler S
 *
 * Created on 31 janvier 2021, 18:45
 */
#include "State.h"

State::State() {
}

std::vector <float> State::getStaticFloatValues() const {
    return {};
}

std::vector <JBTypes::vec2f> State::getStaticVec2fValues() const {
    return {};
}

std::vector <JBTypes::vec3f> State::getStaticVec3fValues() const {
    return {};
}

std::map <std::string, float> State::getDynamicFloats() const {
    return {};
}

std::map <std::string, JBTypes::vec2f> State::getDynamicVec2fs() const {
    return {};
}

std::map <std::string, JBTypes::vec3f> State::getDynamicVec3fs() const {
    return {};
}

std::map <std::string, JBTypes::Quaternion> State::getDynamicQuaternions() const {
    return {};
}
