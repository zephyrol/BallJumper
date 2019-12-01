/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.h
 * Author: seb
 *
 * Created on 5 octobre 2019, 13:12
 */

#ifndef CAMERA_H
#define CAMERA_H
#include "Types.h"
#include "Ball.h"
#include "Map.h"

class Camera {

public:

    //--CONSTRUCTORS & DESTRUCTORS--//
    Camera                        ();
    virtual                       ~Camera();


    //---------CONSTANTS------------//
    static constexpr float        _zNear                                = 0.1f;
    static constexpr float        _zFar                                 = 100.f;


    //-------CONST METHODS----------//
    std::array<float,3>           pos()                          const noexcept;
    std::array<float,3>           dir()                          const noexcept;
    std::array<float,3>           up()                           const noexcept;


    //----------METHODS-------------//
    void                          follow(const Ball& ball)             noexcept;


private:

    //--------ATTRIBUTES-----------//
    float                         _posX, _posY, _posZ;
    float                         _dirX, _dirY, _dirZ;
    float                         _upX, _upY, _upZ;

};
#endif /* CAMERA_H */

