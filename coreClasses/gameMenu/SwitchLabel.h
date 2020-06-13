/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SwitchLabel.h
 * Author: Morgenthaler S
 *
 * Created on 28 avril 2020, 19:43
 */

#ifndef SWITCHLABEL_H
#define SWITCHLABEL_H
#include "Label.h"

class SwitchLabel: public Label
{
public:
    SwitchLabel(float width,float height,
        const JumperBallTypes::vec2f& position,
        bool switchButton = false);

    virtual Label::TypeOfLabel typeOfLabel() const override;
    void turnOn();
    void turnOff();

private:
    bool _switch;
};

#endif // SWITCHLABEL_H
