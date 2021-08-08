/*
 * File: Map.h
 * Author: Morgenthaler S
 *
 * Created on 1 octobre 2019, 21:18
 */

#ifndef MAP_H
#define MAP_H
#include "blocks/Block.h"
#include "system/ParallelTask.h"
#include "Ball.h"
#include <fstream>

class Map {
public:

struct MapInfo { 
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    Ball_sptr ball;
    vecBlock_sptr blocks;
};

explicit Map(MapInfo&& mapInfo);
CstBlock_sptr getBlock(int x, int y, int z) const;

unsigned int width() const;
unsigned int height() const;
unsigned int depth() const;

JBTypes::vec3f getCenterMap() const;
float getLargestSize() const;

float getTimeSinceCreation() const;

// TODO: move to special
std::map <JBTypes::Color, bool> createSpecialStates() const;

void interaction();

void switchColor(const JBTypes::Color& color);
Block_sptr getBlock(int x, int y, int z);

static JBTypes::vec3ui getBlockCoords(size_t index, unsigned int width, unsigned int depth);

private:

enum class NextBlockLocal { Above, InFrontOf, Same, None };
struct nextBlockInformation {
    JBTypes::Dir nextSide;
    JBTypes::Dir nextLook;
    NextBlockLocal nextLocal;
    JBTypes::vec3ui pos;
};

static std::string positionToString(const JBTypes::vec3ui& position);
static JBTypes::vec3ui stringToPosition(const std::string& stringPosition);
CstBlock_sptr getBlock(const JBTypes::vec3ui& pos) const;

bool ballIsOut() const;

std::map<std::string,Block_sptr> createBlockPositions() const;
std::vector<Block_sptr> getBlocksToUpdate() const;

const vecBlock_sptr _blocks;
const std::map<std::string,Block_sptr> _blocksPositions;
const vecBlock_sptr _blocksToUpdate;
const Ball_sptr _ball;

const unsigned int _width;
const unsigned int _height;
const unsigned int _depth;
const JBTypes::timePointMs _creationTime;

ParallelTask <void> _blocksUpdating;
JBTypes::timePointMs _timeInteractions;

const NextBlock _nextBlockGetter;
const TurnBack _turnBackMovement;

nextBlockInformation getNextBlockInfo() const;
std::shared_ptr<const std::vector<int>> intersectBlock(float x, float y, float z) const;
};

#endif /* MAP_H */
