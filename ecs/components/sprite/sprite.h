#pragma once
#include "ecs.h"

typedef struct {
    EntityID entity;
} Sprite;

ComponentMask sprite_mask();
Sprite* sprite_get(EntityID e);
void sprite_add(EntityID e);
