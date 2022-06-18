#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#pragma once

#include "../Engine/Sprite.hpp"

class PlayerSprite : public Sprite {
public:
    void move(uint8_t direction);

private:
    uint8_t mvx, mvy, mvz;
};

#endif