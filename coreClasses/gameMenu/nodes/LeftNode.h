//
// Created by S.Morgenthaler on 13/07/22.
//

#ifndef JUMPERBALLAPPLICATION_LEFTNODE_H
#define JUMPERBALLAPPLICATION_LEFTNODE_H

#include "FillingNode.h"

class LeftNode : public FillingNode {
public:
    explicit LeftNode(const CstNode_sptr &parent, float ratio);
};


#endif //JUMPERBALLAPPLICATION_LEFTNODE_H
