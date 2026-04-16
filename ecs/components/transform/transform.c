#include "transform.h"

static ComponentMask mask = 0;

ComponentMask transform_mask()
{
    if (mask == 0) mask = ecs_register_component(sizeof(Transformm));
    return mask;
}
Transformm* transform_get(EntityID e) {
    Transformm* pool = (Transformm*)ecs_get_pool(transform_mask());
    return &pool[e];
}

void transform_add(EntityID e) {
    ecs_add(e, transform_mask());
}