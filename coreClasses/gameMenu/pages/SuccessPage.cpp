//
// Created by S.Morgenthaler on 20/09/2022.
//

#include "SuccessPage.h"
#include "gameMenu/nodes/ScreenNode.h"
#include "gameMenu/nodes/ScaledNode.h"
#include "gameMenu/nodes/CenteredNode.h"
#include "gameMenu/nodes/UpNode.h"
#include "gameMenu/nodes/DownNode.h"

SuccessPage::SuccessPage(
    Player_sptr &&player,
    Node_sptr &&goodGameNode,
    Node_sptr &&continueNode,
    Node_sptr &&exitNode,
    Label_sptr &&backgroundLabel,
    const Page_sptr &parent
) : Page(std::move(player)),
    _parent(parent),
    _goodGameNode(std::move(goodGameNode)),
    _continueNode(std::move(continueNode)),
    _exitNode(std::move(exitNode)),
    _backgroundLabel(std::move(backgroundLabel)),
    _inGamePage(nullptr) {
}

SuccessPage_sptr SuccessPage::createInstance(
    Player_sptr player,
    const Page_sptr &parent,
    float ratio
) {
    auto nodes = createNodes(ratio);
    return std::make_shared<SuccessPage>(
        std::move(player),
        std::move(nodes.at(0)),
        std::move(nodes.at(1)),
        std::move(nodes.at(2)),
        createBackgroundLabel(std::move(nodes.at(3))),
        parent
    );
}

vecNode_sptr SuccessPage::createNodes(float ratio) {

    const auto screenNode = std::make_shared<ScreenNode>(ratio);
    const auto resizedScreenNode = std::make_shared<ScaledNode>(screenNode, 0.95f);
    const auto mainTitleNode = std::make_shared<CenteredNode>(
        resizedScreenNode,
        9.f / 16.f
    );

    const auto goodGameTitle = std::make_shared<UpNode>(
        mainTitleNode,
        4.f
    );

    const auto optionsParentNode = std::make_shared<CenteredNode>(
        mainTitleNode,
        1.5f
    );
    constexpr float optionsNodeRatio = 7.f;

    const auto continueNode = std::make_shared<UpNode>(
        optionsParentNode,
        optionsNodeRatio
    );

    const auto exitNode = std::make_shared<DownNode>(
        optionsParentNode,
        optionsNodeRatio
    );

    return {goodGameTitle, continueNode, exitNode, optionsParentNode};

}

void SuccessPage::resize(float ratio) {
    const auto &nodes = createNodes(ratio);
    _goodGameNode = nodes.at(0);
    _continueNode = nodes.at(1);
    _exitNode = nodes.at(2);
    _backgroundLabel = createBackgroundLabel(nodes.at(3));
}

Page_wptr SuccessPage::parent() {
    return _parent;
}

void SuccessPage::setInGamePage(Page_sptr inGamePage) {
    _inGamePage = std::move(inGamePage);
}

Page_sptr SuccessPage::click(float mouseX, float mouseY) {
    const auto intersectTest = [&mouseX, &mouseY](const Node_sptr &node) {
        return node->intersect(mouseX, mouseY);
    };
    if (intersectTest(_exitNode)) {
        return _parent.lock();
    }
    if (intersectTest(_continueNode)) {
        const auto nextLevel = _player->getCurrentLevel() + 1;
        if (nextLevel > Player::maxLevel) {
            return nullptr;
        }
        _player->setCurrentLevel(nextLevel);
        return _inGamePage;
    }
    return nullptr;
}

vecCstTextNode_uptr SuccessPage::genTextNodes() const {
    vecCstTextNode_uptr textNodes;
    const auto english = _player->isUsingEnglishLanguage();
    textNodes.emplace_back(new TextNode(_goodGameNode, english ? "You did it!" : "Bien jou;!", 0));
    textNodes.emplace_back(new TextNode(
        _continueNode,
        english ? "Next level" : "Niveau suivant",
        continueLabelId
    ));
    textNodes.emplace_back(new TextNode(_exitNode, english ? "Exit" : "Sortir", exitLabelId));
    return textNodes;
}

std::vector<std::string> SuccessPage::shaderDefines() const {
    return {"TRANSPARENT_BACKGROUND"};
}

std::string SuccessPage::getVertexShaderName() const {
    return "titlePageVs.vs";
}

void SuccessPage::update(const Mouse &mouse) {

    if (!mouse.isPressed()) {
        _currentSelectedLabel = 0;
        return;
    }

    // Positions have to be centered
    const auto mouseX = mouse.currentXCoord() - 0.5f;
    const auto mouseY = mouse.currentYCoord() - 0.5f;
    const auto intersectTest = [&mouseX, &mouseY](const Node_sptr &node) {
        return node->intersect(mouseX, mouseY);
    };
    if (intersectTest(_continueNode)) {
        _currentSelectedLabel = continueLabelId;
    } else if (intersectTest(_exitNode)) {
        _currentSelectedLabel = exitLabelId;
    } else {
        _currentSelectedLabel = 0;
    }
}

vecCstLabel_sptr SuccessPage::labels() const {
    return {_backgroundLabel};
}
