/*
 * File: BallState.h
 * Author: Morgenthaler S
 *
 * Created on 19 septembre 2020, 07h50
 */
#include "BallState.h"

BallState::BallState(const Ball& ball):
    _ball(ball),
    _coveredRotation(ball.getCoveredRotation()),
    _position(ball.get3DPosition()),
    _burnCoefficient(ball.burnCoefficient()),
    _currentSideAsVector(ball.currentSideAsVector()),
    _state(ball.state()),
    _stateOfLifeStatus(getStateOfLifeStatus()),
    _radius(ball.getRadius()),
    _timeToGetDestination(ball.getMechanicsJumping().getTimeToGetDestination()),
    _lookTowardsAsVector(ball.lookTowardsAsVector()),
    _crushingCoeff(ball.getCrushingCoefficient()),
    _teleportationCoeff(ball.getTeleportationCoefficient()),
    _teleportationColor(ball.getTeleportationColor()),
    _timeSecondsSinceAction(ball.getTimeSecondsSinceAction()),
    _timeSecondsSinceStateOfLife(ball.getTimeSecondsSinceStateOfLife()),
    _nextLook(JBTypesMethods::directionAsVector(ball.getNextBlockInfo().nextLook)) {
}

State::GlobalState BallState::update() {
    _coveredRotation = _ball.getCoveredRotation();
    _position = _ball.get3DPosition();
    _burnCoefficient = _ball.burnCoefficient();
    _currentSideAsVector = _ball.currentSideAsVector();
    _state = _ball.state();
    _stateOfLifeStatus = getStateOfLifeStatus();
    _radius = _ball.getRadius();
    _timeToGetDestination = _ball.getMechanicsJumping().getTimeToGetDestination(),
    _lookTowardsAsVector = _ball.lookTowardsAsVector();
    _crushingCoeff = _ball.getCrushingCoefficient();
    _teleportationCoeff = _ball.getTeleportationCoefficient();
    _teleportationColor = _ball.getTeleportationColor();
    _timeSecondsSinceAction = _ball.getTimeSecondsSinceAction();
    _timeSecondsSinceStateOfLife = _ball.getTimeSecondsSinceStateOfLife();
    _nextLook = JBTypesMethods::directionAsVector(_ball.getNextBlockInfo().nextLook);

    const Ball::StateOfLife stateOfLife = _ball.stateOfLife();
    if (stateOfLife == Ball::StateOfLife::Bursting) {
        return State::GlobalState::Separate;
    }
    if (stateOfLife == Ball::StateOfLife::Dead) {
        return State::GlobalState::Dead;
    }
    return State::GlobalState::United;
}

const JBTypes::vec3f& BallState::get3DPosition() const noexcept{
    return _position;
}

float BallState::burnCoefficient() const {
    return _burnCoefficient;
}

const JBTypes::vec3f& BallState::currentSideAsVector() const {
    return _currentSideAsVector;
}

float BallState::getTimeSecondsSinceAction() const {
    return _timeSecondsSinceAction;
}

Ball::State BallState::state() const {
    return _state;
}

float BallState::getRadius() const {
    return _radius;
}

const JBTypes::vec3f& BallState::lookTowardsAsVector() const {
    return _lookTowardsAsVector;
}

float BallState::crushingCoeff() const noexcept{
    return _crushingCoeff;
}

float BallState::teleportationCoeff() const {
    return _teleportationCoeff;
}

float BallState::timeToGetDestination() const {
    return _timeToGetDestination;
}

const JBTypes::Color& BallState::teleportationColor() const {
    return _teleportationColor;
}

const JBTypes::vec3f& BallState::nextLook() const {
    return _nextLook;
}

std::map <std::string, float> BallState::getDynamicFloats() const {
    return {
        { "ballRadius", _radius },
        { "crushingCoeff", _crushingCoeff },
        { "status", _stateOfLifeStatus },
        { "timeStateOfLife", _timeSecondsSinceStateOfLife }
    };
}

std::map <std::string, JBTypes::vec3f> BallState::getDynamicVec3fs() const {
    return {
        { "sideDir", _currentSideAsVector },
        { "position", _position }
    };
}

std::map <std::string, JBTypes::Quaternion> BallState::getDynamicQuaternions() const {
    return {
        { "quaternion", _coveredRotation }
    };
}

float BallState::getStateOfLifeStatus() const {
    const auto& stateOfLife = _ball.stateOfLife();
    if (
        stateOfLife == Ball::StateOfLife::Normal ||
        stateOfLife == Ball::StateOfLife::Burning ||
        stateOfLife == Ball::StateOfLife::Sliding
        ) {
        return 0.f;
    }
    if (stateOfLife == Ball::StateOfLife::Bursting) {
        return 1.f;
    }
    return 2.f;
}
