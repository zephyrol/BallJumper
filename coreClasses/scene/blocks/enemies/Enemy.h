//
// Enemy.h
// JumperBallCore
//
// Created by S Morgenthaler on 08/10/2020.
//
#ifndef Enemy_hpp
#define Enemy_hpp

#include <scene/Shape.h>
#include "scene/SceneElement.h"

class Enemy;
using Enemy_sptr = std::shared_ptr <Enemy>;
using CstEnemy_sptr = std::shared_ptr <const Enemy>;
using vecCstEnemy_sptr = std::vector <CstEnemy_sptr>;
using vecEnemy_sptr = std::vector <Enemy_sptr>;
using Enemy_uptr = std::unique_ptr <Enemy>;

class Enemy : public SceneElement{
public:
    enum class Effect { Nothing, Burst };

Enemy(const JBTypes::vec3ui& initialPosition,
      const JBTypes::Dir& direction,
      float size,
      size_t length
      );

virtual void update();
virtual JBTypes::Color getColor() const;
const JBTypes::timePointMs& creationTime() const;
const JBTypes::vec3f& position() const;
const JBTypes::Dir& direction() const;
float size() const;
size_t length() const;

SceneElement::DynamicValues <JBTypes::vec3f> getDynamicVec3fs() const override;

SceneElement::GlobalState getGlobalState() const override;

virtual vecCstShape_sptr getShapes() const = 0;

virtual void switchOnOff();
virtual ~Enemy() = default;

private:
const JBTypes::timePointMs _creationTime;
const JBTypes::Dir _direction;
const float _size;
const size_t _length;

protected:
const JBTypes::vec3f _initialPosition;
JBTypes::vec3f _position;

private:
JBTypes::vec3f init3DPosition(const JBTypes::vec3ui& initialPosition) const;

};

#endif /* Enemy_hpp */
