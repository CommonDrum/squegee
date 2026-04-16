#include "ecs.h"
#include "movement.h"
#include "transform.h"

int main(void) {

    movement_system_register();
    EntityID e = ecs_entity_create();

    transform_add(e);
    Transform *t = transform_get(e);
    *t = (Transform){0,0};

    
    while (true)
    {
        ecs_run_physics(1.f);
    }
    
    return 0;
}
