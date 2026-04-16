#include "transform.h"

static ComponentMask mask = 0;

ComponentMask transform_mask()
{
    if (mask == 0) mask = ecs_register_component(sizeof(Transform));
    return mask;
}
Transform* transform_get(EntityID e) {
    Transform* pool = (Transform*)ecs_get_pool(transform_mask());
    return &pool[e];
}

void transform_add(EntityID e) {
    ecs_add(e, transform_mask());
}