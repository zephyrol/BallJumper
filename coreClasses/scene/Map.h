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

class Map;
using Map_sptr = std::shared_ptr <Map>;
using CstMap_sptr = std::shared_ptr <const Map>;
using vecCstMap_sptr = std::vector <CstMap_sptr>;
using vecMap_sptr = std::vector <Map_sptr>;
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

unsigned int width() const;
unsigned int height() const;
unsigned int depth() const;

JBTypes::vec3f getCenterMap() const;
float getLargestSize() const;

float getTimeSinceCreation() const;

// TODO: move to special
std::map <JBTypes::Color, bool> createSpecialStates() const;

void update(const JBTypes::timePointMs& updatingTime, const Ball::ActionRequest& action);

    CstBall_sptr getBall() const;

void switchColor(const JBTypes::Color& color);
CstBlock_sptr getBlock(const JBTypes::vec3ui& pos) const;

static JBTypes::vec3ui getBlockCoords(size_t index, unsigned int width, unsigned int depth);

    JBTypes::vec3f getNextLook() const;

private:

static std::string positionToString(const JBTypes::vec3ui& position);
static JBTypes::vec3ui stringToPosition(const std::string& stringPosition);

bool ballIsOut() const;

std::map<std::string, Block_sptr> createBlockPositions() const;
std::vector<Block_sptr> getBlocksToUpdate() const;

const vecBlock_sptr _blocks;
const std::map<std::string,Block_sptr> _blocksPositions;
const vecBlock_sptr _blocksToUpdate;

const Ball_sptr _ball;

const unsigned int _width;
const unsigned int _height;
const unsigned int _depth;
std::unique_ptr<JBTypes::vec3ui> _currentBallPosition;

const JBTypes::timePointMs _creationTime;

ParallelTask <void> _blocksUpdating;
JBTypes::timePointMs _updatingTime;

const NextBlock _nextBlockGetter;
const TurnBack _turnBackMovement;


Ball::MovementDestination getNextBlockInfo() const;
std::shared_ptr<const std::vector<unsigned int>> intersectBlock(float x, float y, float z) const;


public :
    vecCstBlock_sptr getBlocks() const;
};

#endif /* MAP_H */
