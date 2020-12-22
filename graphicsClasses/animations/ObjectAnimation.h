/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjectAnimation.h
 * Author: Morgenthaler S
 *
 * Created on 3 avril 2020, 11:36
 */

#ifndef OBJECTANIMATION_H
#define OBJECTANIMATION_H
#include <scene/objects/ObjectState.h>
#include "Animation.h"
#include "../Utility.h"

class ObjectAnimation : public Animation {
public:

    //--CONSTRUCTORS & DESTRUCTORS--//
    ObjectAnimation                 ( const ObjectState& object,
                                      const glm::vec3& blockPosition,
                                      const JBTypes::Dir& dir);
    virtual ~ObjectAnimation        ()                                = default;


    //----------METHODS------------//
    void                                updateTrans()                  override;
    void                                transBeforeObtaining();
    void                                transAfterObtaining();
private:

    const ObjectState&                  object()                          const;
    //--------ATTRIBUTES-----------//
    const ObjectState&                  _object;
    const JBTypes::Dir                  _direction;
    const glm::mat4                     _translationToBlock;
    const glm::mat4                     _initialRotation;
    const glm::mat4                     _tToBlockTCenterInitRotTOnBlock;
    const glm::mat4                     _tToBlockTOnBlock;

    glm::mat4                           _movingRotation;
    glm::mat4                           _movingScale;
    glm::mat4                           _movingTranslation;

    static const glm::mat4              translationOnBlock;
    static const glm::mat4              translationCenter;
    static const glm::mat4              inversedTranslationCenter;
    static const glm::vec3              rotationAxis;
};

#endif /* OBJECTANIMATION_H */

