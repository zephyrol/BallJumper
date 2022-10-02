//
// Created by S.Morgenthaler on 24/09/2022.
//

#include "ScrollablePage.h"

ScrollablePage::ScrollablePage(Player_sptr &&player, float height) :
    Page(std::move(player)),
    _height(height),
    _localPosY(0.f),
    _localPressedPosY(0.f),
    _localReleasedPosY(0.f),
    _isPressed(false),
    _pressedScreenPosY(0.f),
    _lastUpdate{},
    _lastSwipeUpdates{},
    _releaseVelocity(0.f) {
}

void ScrollablePage::update(bool isPressed, float screenPosY) {

    const auto now = JBTypesMethods::getTimePointMSNow();
    _lastUpdate = now;

    // Press cases
    if (isPressed && !_isPressed) {
        _pressedScreenPosY = screenPosY;
        _localPressedPosY = _localPosY;
        _isPressed = true;
        _lastSwipeUpdates.clear();
    }

    if (_isPressed) {
        constexpr float thresholdDeltaT = 0.1f; // 100 ms
        std::list<slideState>::iterator it;
        for (
            it = _lastSwipeUpdates.begin();
            it != _lastSwipeUpdates.end() &&
            JBTypesMethods::getFloatFromDurationMS(now - it->first) < thresholdDeltaT;
            ++it
            ) {
        }

        _lastSwipeUpdates.erase(it, _lastSwipeUpdates.end());
        _lastSwipeUpdates.push_front({now, screenPosY});
        _localPosY = _localPressedPosY + (screenPosY - _pressedScreenPosY);
    }

    // Release cases
    if (!isPressed && _isPressed && !_lastSwipeUpdates.empty()) {
        const slideState &lastSlideState = _lastSwipeUpdates.front();
        const slideState &olderSlideState = _lastSwipeUpdates.back();
        float deltaT = JBTypesMethods::getFloatFromDurationMS(
            lastSlideState.first - olderSlideState.first);

        // the velocity is the position derivative (pourcentagePage / ms)
        _releaseVelocity = (lastSlideState.second - olderSlideState.second) / deltaT;

        _localReleasedPosY = _localPosY;
        _isPressed = false;
    }
    if (!_isPressed && !_lastSwipeUpdates.empty()) {
        const slideState &lastSlideState = _lastSwipeUpdates.front();
        const float t = JBTypesMethods::getFloatFromDurationMS(now - lastSlideState.first);
        const float deceleration = decelerationCoefficient * powf(t, 2.f) / 2.f;

        if (_releaseVelocity > 0.f && t < -(_releaseVelocity) / (2.f * -decelerationCoefficient / 2.f)) {
            _localPosY = -deceleration + _releaseVelocity * t + _localReleasedPosY;
        } else if (
            _releaseVelocity < 0.f &&
            t < -(_releaseVelocity) / (decelerationCoefficient)
            ) {
            _localPosY = deceleration + _releaseVelocity * t + _localReleasedPosY;
        }

        if (_localPosY < 0.f) _localPosY = 0.f;
        else if (_localPosY > _height - 1.f) _localPosY = _height - 1.f;
    }

}

std::string ScrollablePage::shaderDefine() const {
    return "SCROLLABLE";
}

std::vector<std::string> ScrollablePage::getUniformNames() const {
    return {"positionY", "levelProgression"};
}

std::vector<float> ScrollablePage::getUniformValues() const {
    return {
        _localPosY * 2.f , // Convert to OpenGL format
        static_cast<float>(_player->levelProgression())
    };
}

float ScrollablePage::getOffsetY() const {
    return _localPosY;
}
