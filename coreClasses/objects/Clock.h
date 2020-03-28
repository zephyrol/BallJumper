/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clock.h
 * Author: seb
 *
 * Created on 27 mars 2020, 20:48
 */

#ifndef CLOCK_H
#define CLOCK_H
#include "Object.h"

class Clock : public Object{
public:
    Clock(const std::shared_ptr<const Block>& block,
          JumperBallTypes::Direction side);
    Object::CategoryOfObjects getCategory() override;

    
private:

};

#endif /* CLOCK_H */

