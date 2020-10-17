//
//  ThornBall.cpp
//  JumperBallCore
//
//  Created by S Morgenthaler on 08/10/2020.
//

#include "ThornBall.h"

ThornBall::ThornBall(const Block& tieBlock, 
             const std::array<unsigned int,3>& initialPosition,
             const JBTypes::Dir& dir,
             const JBTypes::Dir& movementDirection,
             size_t movementLength):
Enemy(tieBlock,initialPosition,dir, thornBallRadius,
      { static_cast<float>(initialPosition.at(0)),
        static_cast<float>(initialPosition.at(1)),
        static_cast<float>(initialPosition.at(2)),
        0.f,
        0.f,
        0.f,
        1.f,
        1.f,
        1.f }
),
_movementDirection(movementDirection),
_movementLenght(movementLength)
{
}

void ThornBall::touchingTest(const JBTypes::vec3f& entityPosition,
                         float radiusEntity) 
{
    if (JBTypesMethods::distance(entityPosition, _position) <
        (radiusEntity + thornBallRadius)) {
        _intersectionTime = JBTypesMethods::getTimePointMSNow();
        _hasHit = true;
    }
}
