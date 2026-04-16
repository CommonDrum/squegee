#pragma once
#include "ecs.h"

typedef struct {
    int x;
    int y;
} Transformm;

ComponentMask transform_mask();
Transformm* transform_get(EntityID e);
void transform_add(EntityID e);