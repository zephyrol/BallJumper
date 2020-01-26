/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FireBlock.h
 * Author: seb
 *
 * Created on 5 octobre 2019, 12:50
 */

#ifndef FIREBLOCK_H
#define FIREBLOCK_H
#include "Block.h"

class FireBlock : public Block {
public:
    FireBlock();
    FireBlock(const FireBlock& orig);
    virtual ~FireBlock();

    Block::categoryOfBlocksInFile getType() const override;

private:
    bool _isBurning;
};

#endif /* FIREBLOCK_H */
