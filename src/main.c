#include "ecs.h"
#include "movement.h"
#include "transform.h"
#include <raylib.h>

int main(void) {

    movement_system_register();
    EntityID e = ecs_entity_create();

    transform_add(e);
    Transformm *t = transform_get(e);
    *t = (Transformm){0,0};

    
    while (true)
    {
        ecs_run_update();
    }
    
    return 0;
}
