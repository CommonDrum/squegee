#pragma once
#include "ecs.h"

typedef struct {
    int x;
    int y;
} Transform;

ComponentMask transform_mask();
Transform* transform_get(EntityID e);
void transform_add(EntityID e);