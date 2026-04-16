#include "sprite.h"

static ComponentMask mask = 0;

ComponentMask sprite_mask()
{
    if (mask == 0) mask = ecs_register_component(sizeof(Sprite));
    return mask;
}
Sprite* sprite_get(EntityID e) {
    Sprite* pool = (Sprite*)ecs_get_pool(sprite_mask());
    return &pool[e];
}

void sprite_add(EntityID e) {
    ecs_add(e, sprite_mask());
}
