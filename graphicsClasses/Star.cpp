/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Star.cpp
 * Author: morgenthaler
 * 
 * Created on 20 décembre 2019, 13:46
 */

#include "Star.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> 

Star::Star( const glm::vec3& colorInside, const glm::vec3& colorOutside, 
            const GLfloat radiusInside,   const GLfloat radiusOutside, 
            const float distance,         const float radius):
        _idVertexArray(),
        _idVertexBuffer(),
        _colorInside(colorInside),
        _colorOutside(colorOutside),
        _radiusInside(radiusInside),
        _radiusOutside(radiusOutside),
        _transform( glm::translate(glm::vec3(0.f,0.f,-distance))
                    * glm::scale(glm::vec3(radius,radius,radius))),
        _timeCreation(Ball::getTimePointMSNow())
{
    glGenVertexArrays(1, &_idVertexArray);
    glBindVertexArray(_idVertexArray);

    glGenBuffers(1, &_idVertexBuffer);
    bindVertexData();
}

void Star::bindVertexData() const {

    std::vector<GLfloat> positionsQuad {
     0.f,0.f,0.f, 1.f,0.f,0.f, 0.f,1.f,0.f,  
     1.f,0.f,0.f, 1.f,1.f,0.f, 0.f,1.f,0.f
    };

    glBindBuffer(GL_ARRAY_BUFFER, _idVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, positionsQuad.size() * sizeof(GLfloat), 
            positionsQuad.data(), GL_STATIC_DRAW);

}

void Star::draw() const {

    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _idVertexBuffer);
    
    glVertexAttribPointer ( 
            0,
            3, // 3 GL_FLOAT per vertex
            GL_FLOAT,
            GL_FALSE,
            0,
            nullptr
            );
    
    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(0);
}

glm::vec3 Star::colorInside() const {
    return _colorInside;
}

glm::vec3 Star::colorOutside() const {
    return _colorOutside;
}

GLfloat Star::radiusInside() const {
    return _radiusInside;
}

GLfloat Star::radiusOutside() const {
    return _radiusOutside;
}

glm::mat4 Star::transform() const {
    const float timeSinceCreation  = 
                              Ball::getTimeSecondsSinceTimePoint(_timeCreation);
    const float timePerRound       = 10.f;
    const glm::mat4 rotationMatrix = glm::rotate( timeSinceCreation * 2.f
                                        *static_cast<float>(M_PI)/timePerRound,
                                        glm::vec3(0.5f,1.f,0.f)
                                                );

    return rotationMatrix * _transform;

}

glm::vec3 Star::centralPosition() const {
    return glm::vec3( transform() * glm::vec4(0.5f,0.5f,0.f,1.f) );
}

