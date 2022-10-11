//
// Created by S.Morgenthaler on 08/10/22.
//
#include "Mouse.h"

#include <utility>

Mouse::Mouse(
    const std::function<void()> &northActionFunc,
    const std::function<void()> &southActionFunc,
    const std::function<void()> &eastActionFunc,
    const std::function<void()> &westActionFunc,
    std::function<void(float mouseX, float mouseY)> validateActionFunc,
    std::function<void()> longPressActionFunc
) :
    _directionActionFunctions{
        {ScreenDirection::North, northActionFunc},
        {ScreenDirection::South, southActionFunc},
        {ScreenDirection::East,  eastActionFunc},
        {ScreenDirection::West,  westActionFunc},
    },
    _validateActionFunction(std::move(validateActionFunc)),
    _longPressActionFunction(std::move(longPressActionFunc)),
    _mouseCoords(nullptr),
    _currentState(),
    _pressingState(),
    _directionDetectionState(),
    _previousState(),
    _currentMovementDir(nullptr) {
}

void Mouse::press(float posX, float posY) {
    _mouseCoords = std::make_shared<Mouse::MouseCoords>();
    _mouseCoords->xCoord = posX;
    _mouseCoords->yCoord = posY;
}

void Mouse::release() {
    _mouseCoords = nullptr;
}

void Mouse::update() {
    _previousState = _currentState;
    _currentState.mouseCoords = _mouseCoords;
    !_mouseCoords ? releasedMouseUpdate() : pressedMouseUpdate();
}

void Mouse::pressedMouseUpdate() {
    if (!_previousState.mouseCoords) {
        _pressingState = _currentState;
    }

    const auto &updatingTime = _currentState.updatingTime;

    constexpr float updatingDirectionDetectionThreshold = 0.3f; // 0.3 seconds
    if (!_previousState.mouseCoords
        || (updatingTime - _directionDetectionState.updatingTime) > updatingDirectionDetectionThreshold) {
        _directionDetectionState = _currentState;
    }

    const auto computeCardinalDistance = [this](
        const Mouse::CardinalPoint &cardinalPoint
    ) -> CardinalDistance {
        const auto &directionStateCoords = _directionDetectionState.mouseCoords;
        const auto &currentStateCoords = _currentState.mouseCoords;
        const auto &point = cardinalPoint.point;
        return {cardinalPoint.direction, computeDistance(
            directionStateCoords->xCoord + point.first,
            directionStateCoords->yCoord + point.second,
            currentStateCoords->xCoord,
            currentStateCoords->yCoord
        )};
    };

    std::vector<Mouse::CardinalDistance> cardinalDistances(cardinalsPoints.size());
    std::transform(
        cardinalsPoints.begin(),
        cardinalsPoints.end(),
        cardinalDistances.begin(),
        computeCardinalDistance
    );

    Mouse::CardinalDistance nearestCardinal = cardinalDistances.front();
    for (auto iter = cardinalDistances.begin() + 1; iter != cardinalDistances.end(); ++iter) {
        const auto &cardinal = *iter;
        if (cardinal.distance < nearestCardinal.distance) {
            nearestCardinal = cardinal;
        }
    }
    constexpr auto movingThreshold = 0.05f;
    if (computeDistance(
        _currentState.mouseCoords->xCoord,
        _currentState.mouseCoords->yCoord,
        _directionDetectionState.mouseCoords->xCoord,
        _directionDetectionState.mouseCoords->yCoord
    ) > movingThreshold) {
        _currentMovementDir = std::make_shared<ScreenDirection>(nearestCardinal.direction);
    }

    constexpr auto pressingDetectionThreshold = 0.1f; // 0.1 seconds
    if (!_currentMovementDir) {
        if ((updatingTime - _pressingState.updatingTime) > pressingDetectionThreshold) {
            _longPressActionFunction();
        }
        return;
    }
    _directionActionFunctions.at(*_currentMovementDir)();
}

void Mouse::releasedMouseUpdate() {

    _currentMovementDir = nullptr;
    const auto &previousStateCoords = _previousState.mouseCoords;
    if (!previousStateCoords) {
        return;
    }
    constexpr float thresholdMoving = 0.05f;
    const auto &pressingStateCoords = _pressingState.mouseCoords;

    const float distance = computeDistance(
        previousStateCoords->xCoord,
        previousStateCoords->yCoord,
        pressingStateCoords->xCoord,
        pressingStateCoords->yCoord
    );
    constexpr float pressTimeThreshold = 300.f; // 0.3 seconds
    if (
        distance < thresholdMoving
        && (_currentState.updatingTime - _pressingState.updatingTime) < pressTimeThreshold) {
        _validateActionFunction(pressingStateCoords->xCoord, previousStateCoords->yCoord);
    }
}

const std::vector<Mouse::CardinalPoint> Mouse::cardinalsPoints{
    {Mouse::ScreenDirection::North, {0.f,  1.f}},
    {Mouse::ScreenDirection::South, {0.f,  -1.f}},
    {Mouse::ScreenDirection::East,  {1.f,  0.f}},
    {Mouse::ScreenDirection::West,  {-1.f, 0.f}},
};

float Mouse::computeDistance(float x0, float y0, float x1, float y1) {
    const auto x1MinusX0 = x1 - x0;
    const auto y1MinusY0 = y1 - y0;
    return sqrtf(x1MinusX0 * x1MinusX0 + y1MinusY0 * y1MinusY0);
}

float Mouse::currentYCoord() const {
    return _currentState.mouseCoords->yCoord;
}

bool Mouse::isPressed() const {
    return _currentState.mouseCoords != nullptr;
}

float Mouse::previousYCoord() const {
    return _previousState.mouseCoords->yCoord;
}

bool Mouse::wasPressed() const {
    return _previousState.mouseCoords != nullptr;
}

