/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   uniformLight.h
 * Author: Morgenthaler S 
 *
 * Created on 22 décembre 2019, 20:03
 */

#ifndef UNIFORMLIGHT_H
#define UNIFORMLIGHT_H
#include "uniformBlock.h"

class UniformLight : public UniformBlock{
public:
    //--CONSTRUCTORS & DESTRUCTORS--//
    UniformLight    ();

    UniformLight    (
                      const glm::vec3& positionLight,
                      const glm::vec3& ambientLightIntensity,
                      const glm::vec3& diffuseLightIntensity,
                      const glm::vec3& specularLightIntensity
                    );
    ~UniformLight   ()                                       override = default;

    //----------METHODS------------//
    void            bind( const std::string& name,
                          const ShaderProgram& sp)                     override; 
    void            positionLight         (const glm::vec3& posLight);
    void            ambientLightIntensity (const glm::vec3& ambLightIntensity);
    void            diffuseLightIntensity (const glm::vec3& diffLightIntensity);
    void            specularLightIntensity(const glm::vec3& specLightIntensity);

private :

    //--------ATTRIBUTES-----------//
    glm::vec3       _positionLight;
    glm::vec3       _ambientLightIntensity;
    glm::vec3       _diffuseLightIntensity;
    glm::vec3       _specularLightIntensity;
};

#endif /* UNIFORMLIGHT_H */

