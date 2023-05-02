//
// Created by S.Morgenthaler on 20/09/2022.
//

#ifndef JUMPERBALLAPPLICATION_INGAMEPAGE_H
#define JUMPERBALLAPPLICATION_INGAMEPAGE_H


#include "Page.h"
#include "gameMenu/labels/ArrowLabel.h"
#include "scene/ItemsContainer.h"

class InGamePage;

using InGamePage_sptr = std::shared_ptr<InGamePage>;

class InGamePage : public Page {


public:
    explicit InGamePage(
        Player_sptr &&player,
        ArrowLabel_sptr arrowLabel,
        Node_sptr &&leftDigitNode,
        Node_sptr &&middleDigitNode,
        Node_sptr &&rightDigitNode,
        Node_sptr &&coinsTensDigit,
        Node_sptr &&coinsUnitsDigit,
        Label_sptr key1,
        Label_sptr key2,
        Label_sptr key3,
        Label_sptr key4,
        Label_sptr coinSymbol,
        const Page_sptr &parent,
        CstItemsContainer_sptr itemsContainer
    );

    static InGamePage_sptr createInstance(
        Player_sptr player,
        const Page_sptr &parent,
        float ratio,
        CstItemsContainer_sptr itemsContainer
    );


    static std::shared_ptr<ArrowLabel> createInGameArrowLabel(const Node_sptr &headerNode);

    Page_wptr parent() override;

    vecCstLabel_sptr labels() const override;

    Page_sptr click(float mouseX, float mouseY) override;

    vecCstTextNode_uptr genTextNodes() const override;

    void update(const Mouse &mouse) override;

    void resize(float ratio) override;

    void setItemsContainer(CstItemsContainer_sptr itemsContainer);

    std::vector<std::string> shaderDefines() const override;

    DynamicNames getDynamicIntNames() const override;

    DynamicValues<int> getDynamicIntValues() const override;

    std::string getVertexShaderName() const override;

private:

    Page_wptr _parent;
    ArrowLabel_sptr _arrowLabel;
    Node_sptr _leftDigitNode;
    Node_sptr _middleDigitNode;
    Node_sptr _rightDigitNode;
    Node_sptr _coinsTensDigit;
    Node_sptr _coinsUnitsDigit;
    Label_sptr _key1;
    Label_sptr _key2;
    Label_sptr _key3;
    Label_sptr _key4;
    Label_sptr _coinSymbol;

    CstItemsContainer_sptr _itemsContainer;

    static const int arrowLabelId;
    static const int key1LabelId;
    static const int key2LabelId;
    static const int key3LabelId;
    static const int key4LabelId;
    static const int coinSymbolLabelId;

    static vecNode_sptr createNodes(float ratio);
};


#endif //JUMPERBALLAPPLICATION_INGAMEPAGE_H
