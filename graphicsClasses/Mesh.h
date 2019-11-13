/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesh.h
 * Author: seb
 *
 * Created on 13 novembre 2019, 21:05
 */

#ifndef MESH_H
#define MESH_H
#include "Shader.h"
#include <Ball.h>
#include <Map.h>
#include <glm/glm.hpp>

class Mesh {
public:
    Mesh();
    Mesh(const Ball& ball);
    Mesh(const Map& map);
    virtual ~Mesh();
private:
    std::vector<glm::vec3> _positions;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec2> _uvCoords;

    glm::mat4 _local;
};

#endif /* MESH_H */

