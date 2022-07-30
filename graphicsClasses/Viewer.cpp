/*
 * File: Viewer.cpp
 * Author: Morgenthaler S
 */

#include "Viewer.h"

Viewer::Viewer(
    unsigned int resolutionX,
    unsigned int resolutionY,
    const CstScene_sptr &scene,
    const CstPage_sptr &page,
    const JBTypes::FileContent &fileContent,
    const unsigned char *fontData,
    size_t fontDataSize
) :
    _scene(scene),
    _page(page),
    _ftContent(FontTexturesGenerator::initFreeTypeAndFont(fontData, fontDataSize)),
    _fileContent(fileContent),
    _defaultFrameBuffer([]() {
        GLint defaultFrameBuffer;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFrameBuffer);
        return defaultFrameBuffer;
    }()),
    _resolutionX(static_cast<GLsizei>(resolutionX)),
    _resolutionY(static_cast<GLsizei>(resolutionY)),
    _sceneRendering(std::unique_ptr<SceneRendering>(new SceneRendering(
        *scene,
        _resolutionX,
        _resolutionY,
        _defaultFrameBuffer,
        fileContent
    ))),
    _pageRendering(std::unique_ptr<PageRendering>(new PageRendering(
        _page,
        _ftContent,
        _resolutionX,
        _resolutionY,
        fileContent
    ))) {
}

void Viewer::update() {
    _sceneRendering->update();
    _pageRendering->update();
}

void Viewer::render() const {
    _sceneRendering->render();
    _pageRendering->render();
}

void Viewer::freeGPUMemory() {
    _sceneRendering->freeGPUMemory();
    _pageRendering->freeGPUMemory();
}

void Viewer::resize(unsigned int resolutionX, unsigned int resolutionY) {
    _resolutionX = static_cast<GLsizei>(resolutionX);
    _resolutionY = static_cast<GLsizei>(resolutionY);
    freeGPUMemory();
    setSceneRendering(nullptr);
    setPageRendering(nullptr);
}

void Viewer::setSceneRendering(const CstScene_sptr& scene) {
    if(scene != nullptr) {
        _scene = scene;
    }
    _sceneRendering = std::unique_ptr<SceneRendering>(new SceneRendering(
        *_scene,
        _resolutionX,
        _resolutionY,
        _defaultFrameBuffer,
        _fileContent
    ));
}

void Viewer::setPageRendering(const CstPage_sptr& page) {
    if(page != nullptr) {
        _page = page;
    }
    _pageRendering = std::unique_ptr<PageRendering>(new PageRendering(
        _page,
        _ftContent,
        _resolutionX,
        _resolutionY,
        _fileContent
    ));
}

Viewer::~Viewer() {
    FontTexturesGenerator::clearFreeTypeRessources(_ftContent);
}
