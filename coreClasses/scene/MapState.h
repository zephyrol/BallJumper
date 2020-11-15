/*
 * File:   StarState.h
 * Author: Morgenthaler S
 *
 * Created on 19 septembre 2020, 07h50
 */
#ifndef MAPSTATE_H
#define MAPSTATE_H
#include "scene/Map.h"
#include "scene/blocks/BlockState.h"
#include "scene/enemies/EnemyState.h"
#include "scene/special/SpecialState.h"

class MapState
{
public:
    MapState (const Map& map);
    void update();

    unsigned int width() const;
    unsigned int height() const;
    unsigned int deep() const;
    Map::BlockTypes getType( const std::array<unsigned int, 3>& position
                            ) const;
    const std::vector<Map::BlockInfo>& blocksInfo() const;
    std::array<unsigned int, 3> getBlockCoords(size_t index) const;
    const std::vector<std::shared_ptr<BlockState> > &blockStates() const;
    const std::vector<std::shared_ptr<EnemyState> > &enemiesStates() const;

private:
    const Map&                            _map;
    const unsigned int                    _width;
    const unsigned int                    _height;
    const unsigned int                    _deep;
    const std::vector<std::shared_ptr<BlockState> >
                                          _blockStates;
    const std::vector<std::shared_ptr<EnemyState> >
                                          _enemiesStates;
    const std::vector<std::shared_ptr<SpecialState> >
                                          _specialsStates;

    std::vector<std::shared_ptr<BlockState> >   genBlockStates() const;
    std::vector<std::shared_ptr<EnemyState> >   genEnemiesStates() const;
    std::vector<std::shared_ptr<SpecialState> > genSpecialsStates() const;
};

#endif // MAPSTATE
