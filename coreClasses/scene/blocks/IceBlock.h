/*
 * File: IceBlock.h
 * Author: Morgenthaler S
 *
 * Created on 5 octobre 2019, 12:49
 */

#ifndef ICEBLOCK_H
#define ICEBLOCK_H
#include "Block.h"

class IceBlock:public Block {
public:
    IceBlock(
        const JBTypes::vec3ui& position,
        const vecItem_sptr& items,
        const vecEnemy_sptr& enemies,
        const vecSpecial_sptr& specials,
        const Ball_sptr& ball
    );

    Effect detectionEvent(
        const JBTypes::Dir& direction,
        const JBTypes::timePointMs& currentTime
    ) override;

    JBTypes::Color getColor() const override;
};

#endif /* ICEBLOCK_H */
