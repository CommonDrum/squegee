#include "movement.h"
#include "transform.h"
#include "stdio.h"

static void movement_update(EntityID e) {
    Transform *t = transform_get(e);
    t->x += 1;
    printf("%d \n", t->x);
}

void movement_system_register() {
    ecs_register_update(movement_update, transform_mask());
}