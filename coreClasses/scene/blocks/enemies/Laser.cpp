//
// Laser.cpp
// JumperBallCore
//
// Created by S Morgenthaler on 08/10/2020.
//

#include "Laser.h"

Laser::Laser(const JBTypes::Color& color,
    const JBTypes::vec3ui& initialPosition,
    const JBTypes::Dir& dir,
    size_t length,
    const Ball_sptr &ball
):
    InteractiveEnemy(initialPosition,
          dir,
          laserRadius,
          length,
          { 0.f,
            0.f,
            0.f,
            0.f,
            0.f,
            0.f,
            1.f,
            1.f,
            1.f },
          ball),
    _color(color),
    _isActivated(true) {
}

Enemy::Effect Laser::update () {
    touchingTest();
    if (_isActivated) {
        _transform.at(6) = 1.f;
        _transform.at(7) = 1.f;
        _transform.at(8) = 1.f;
    } else {
        _transform.at(6) = 0.f;
        _transform.at(7) = 0.f;
        _transform.at(8) = 0.f;
    }
    return _hasHit
           ? Enemy::Effect::Burst
           : Enemy::Effect::Nothing;
}

JBTypes::Color Laser::getColor() const {
    return _color;
}

void Laser::switchOnOff() {
    _isActivated = !_isActivated;
}

void Laser::touchingTest () {
    if (!_isActivated) {
        return;
    }

    const auto ball = _ball.lock();
    const auto& boundingSpherePosition = ball->get3DPosition();
    const auto& boundingSphereRadius = ball->getRadius();

    constexpr float offsetLaser = 0.5f;

    const float entityMinX = boundingSpherePosition.x - boundingSphereRadius;
    const float entityMaxX = boundingSpherePosition.x + boundingSphereRadius;
    const float entityMinY = boundingSpherePosition.y - boundingSphereRadius;
    const float entityMaxY = boundingSpherePosition.y + boundingSphereRadius;
    const float entityMinZ = boundingSpherePosition.z - boundingSphereRadius;
    const float entityMaxZ = boundingSpherePosition.z + boundingSphereRadius;

    const auto fLength = static_cast <float>(length());
    const float laserMinX = direction() == JBTypes::Dir::West
                            ? _position.x - offsetLaser - fLength
                            : _position.x - offsetLaser;
    const float laserMaxX = direction() == JBTypes::Dir::East
                            ? _position.x + offsetLaser + fLength
                            : _position.x + offsetLaser;
    const float laserMinY = direction() == JBTypes::Dir::Down
                            ? _position.y - offsetLaser - fLength
                            : _position.y - offsetLaser;
    const float laserMaxY = direction() == JBTypes::Dir::Up
                            ? _position.y + offsetLaser + fLength
                            : _position.y + offsetLaser;
    const float laserMinZ = direction() == JBTypes::Dir::South
                            ? _position.z - offsetLaser - fLength
                            : _position.z - offsetLaser;
    const float laserMaxZ = direction() == JBTypes::Dir::North
                            ? _position.z + offsetLaser + fLength
                            : _position.z + offsetLaser;

    if (
        (entityMinX < laserMaxX && entityMaxX > laserMinX) &&
        (entityMinY < laserMaxY && entityMaxY > laserMinY) &&
        (entityMinZ < laserMaxZ && entityMaxZ > laserMinZ)
        ) {
        _intersectionTime = JBTypesMethods::getTimePointMSNow();
        _hasHit = true;
    }
}

vecCstShape_sptr Laser::getShapes() const {
    return {};
}
