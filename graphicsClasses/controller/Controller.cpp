//
// Controller.cpp
// JumperBallApplication
//
// Created by S.Morgenthaler on 25/05/2020.
//

#include "Controller.h"

Controller::Controller(
    const size_t &screenWidth,
    const size_t &screenHeight,
    const JBTypes::FileContent &filesContent,
    const unsigned char *fontData,
    size_t fontDataSize,
    bool isUsingTouchScreen
) :
    _doubleChronometer(std::make_shared<DoubleChronometer>(
        // The chronometer tracking creation time needs to be started directly
        true,
        // The chronometer tracking in game time needs to be started later
        false)
    ),
    _player(Player::createInstance(_doubleChronometer, filesContent.at("save.txt"))),
    _filesContent(filesContent),
    _requestToLeave(false),
    _scene(std::make_shared<Scene>(
        filesContent.at("map" + std::to_string(_player->levelProgression()) + ".txt"),
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        _player,
        isUsingTouchScreen
    )),
    _menu(Menu::getJumperBallMenu(
        _player,
        _scene->getMap(),
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight)
    )),
    _viewer(std::make_shared<Viewer>(
        static_cast<GLsizei>(screenWidth),
        static_cast<GLsizei>(screenHeight),
        _scene,
        _menu->currentPage(),
        _filesContent,
        fontData,
        fontDataSize
    )),
    _keyboardKey({
                     [this]() { _scene->setUp(); },
                     [this]() { _scene->setDown(); },
                     [this]() { _scene->setLeft(); },
                     [this]() { _scene->setRight(); },
                     [this]() { escapeAction(); },
                     [this]() { _scene->setValidate(); },
                 }),
    _mouse(
        [this]() { _scene->setUp(); },
        [this]() { _scene->setDown(); },
        [this]() { _scene->setRight(); },
        [this]() { _scene->setLeft(); },
        [this](float mouseX, float mouseY) { setValidateMouse(mouseX, mouseY); },
        [this]() { _scene->mouseSetUp(); }
    ),
    _outputs{}{
}

void Controller::interactionButtons(const KeyboardKey::Button &button, const KeyboardKey::Status &status) {
    status == KeyboardKey::Status::Pressed
    ? _keyboardKey.press(button)
    : _keyboardKey.release(button);
}

void Controller::pressMouse(float posX, float posY) {
    _mouse.press(posX, posY);
}

void Controller::releaseMouse() {
    _mouse.release();
}

void Controller::runGame(size_t level) {
    _doubleChronometer->reset();
    _scene = std::make_shared<Scene>(
        _filesContent.at("map" + std::to_string(level) + ".txt"),
        _scene->getRatio(),
        _player,
        _scene->isUsingTouchScreen()
    );
    _menu->setItemsContainers(_scene->getMap());
    _viewer->setScene(_scene);
}

void Controller::setValidateMouse(float mouseX, float mouseY) {
    const auto currentStatus = _player->status();
    _scene->setValidateMouse();

    const auto &currentPage = _menu->currentPage();
    const auto &currentLanguage = _player->isUsingEnglishLanguage();
    const auto &currentMusicsStatus = _player->areMusicsActivated();
    const auto &currentSoundsStatus = _player->areSoundsActivated();
    _menu->mouseClick(mouseX, mouseY);

    // Reset the viewer if the language has changed.
    const auto &newPage = _menu->currentPage();
    const auto newLanguage = _player->isUsingEnglishLanguage();
    const auto newMusicsStatus = _player->areMusicsActivated();
    const auto newSoundsStatus = _player->areSoundsActivated();

    if (
        newPage != currentPage
        || newLanguage != currentLanguage
        || newMusicsStatus != currentMusicsStatus
        || newSoundsStatus != currentSoundsStatus
        ) {
        _viewer->setPage(newPage);
        _scene->setNoAction();
    }

    if (_player->wantsToQuit()) {
        _requestToLeave = true;
        return;
    }
    const auto newStatus = _player->status();
    if (newStatus != currentStatus && newStatus == Player::Status::InTransition) {
        runGame(_player->getCurrentLevel());
        return;
    }
}

void Controller::escapeAction() {

    const auto &currentPage = _menu->currentPage();
    if (_menu->escapeAction()) {
        _requestToLeave = true;
        return;
    }
    const auto &newPage = _menu->currentPage();

    if (newPage != currentPage) {
        _viewer->setPage(newPage);
    }
}

bool Controller::isRequestingLeaving() const {
    return _requestToLeave;
}

void Controller::resize(int screenWidth, int screenHeight) {
    float ratio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    _scene->updateScreenRatio(ratio);
    _menu->resize(ratio);
    _viewer->resize(screenWidth, screenHeight);
}

void Controller::render() const {
    _viewer->render();
}

std::string Controller::update() {

    // 1. Update chronometers
    const auto updatingTime = Chronometer::getTimePointMSNow();
    _doubleChronometer->update(updatingTime);
    _player->updateAdvertisementChronometer(updatingTime);

    // 2. Update controls
    _keyboardKey.update();
    _mouse.update();

    // 3. Update scene and menu
    const auto &currentPage = _menu->currentPage();

    const auto sceneUpdateOutput = _scene->update();
    _menu->update(_mouse);

    const auto &newPage = _menu->currentPage();
    if (newPage != currentPage) {
        _viewer->setPage(newPage);
        if(newPage->isCompatibleWithAdvertisements()) {
            _player->checkAdvertisement();
        }
    }

    // 4. Update viewer
    _viewer->update();

    return sceneUpdateOutput + _player->genOutputs();
}

bool Controller::areMusicsActivated() const {
    return _player->areMusicsActivated();
}

bool Controller::areSoundsActivated() const {
    return _player->areSoundsActivated();
}

void Controller::stop() {
    _doubleChronometer->stopBoth();
    _player->stopChronometer();
}

void Controller::resume() {
    _player->resumeChronometer();
    if (_player->status() != Player::Status::InGame) {
        _doubleChronometer->resumeFirst();
        return;
    }
    _doubleChronometer->resumeBoth();
}
