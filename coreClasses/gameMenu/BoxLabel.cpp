/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BoxLabel.h
 * Author: Morgenthaler S
 *
 * Created on 13 juin 2020
 */

#include "BoxLabel.h"

BoxLabel::BoxLabel(
    const Label::WidthUnit& widthUnit,
    float width,
    float height,
    const JBTypes::vec2f& position):
    Label(widthUnit, width, height, position)
{}
