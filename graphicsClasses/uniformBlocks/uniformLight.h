/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   uniformLight.h
 * Author: morgenthaler
 *
 * Created on 22 décembre 2019, 20:03
 */

#ifndef UNIFORMLIGHT_H
#define UNIFORMLIGHT_H
#include "uniformBlock.h"

class UniformLight : public UniformBlock{
public:
    UniformLight                    ( const ShaderProgram& sp, 
                                      const std::string name,
                                      const glm::vec3 positionLight,
                                      const glm::vec3 ambiantLightIntensity,
                                      const glm::vec3 diffuseLightIntensity,
                                      const glm::vec3 specularLightIntensity
                                    );
    ~UniformLight                   ()                       override = default;

};

#endif /* UNIFORMLIGHT_H */

