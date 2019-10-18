/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gravity.h
 * Author: seb
 *
 * Created on 17 octobre 2019, 22:14
 */

#ifndef GRAVITY_H
#define GRAVITY_H

class Gravity {
public:
    Gravity();
    virtual ~Gravity();

    static constexpr float gravitationalAcceleration = 9.81f;

private:
    float _currentAcceleration;
};

#endif /* GRAVITY_H */

