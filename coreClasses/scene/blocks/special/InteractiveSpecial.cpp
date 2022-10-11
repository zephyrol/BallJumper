//
// Created by seb on 23/10/2021.
//

#include "InteractiveSpecial.h"

InteractiveSpecial::InteractiveSpecial(
    const JBTypes::Color &color,
    const JBTypes::vec3ui &position,
    const JBTypes::Dir &direction,
    const Ball_sptr &ball,
    bool isActivated
    ): Special(ball->getChronometer(), color, direction, position, isActivated),
    _ball(ball){

}
