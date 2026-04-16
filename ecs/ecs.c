#include "ecs.h"
#include <stdlib.h>


#define MAX_ENTITIES 10000
#define MAX_COMPONENTS 64
#define MAX_SYSTEMS 64


static ComponentMask entity_masks[MAX_ENTITIES];

static int next_entity = 0;
static int next_bit = 0;


static System update_systems[MAX_SYSTEMS];
static int update_count = 0;

ComponentPool pools[MAX_COMPONENTS];


EntityID ecs_entity_create(){
    return next_entity++;
}

void ecs_entity_destroy(EntityID e) {
    if (e >= MAX_ENTITIES) return;
    entity_masks[e] = 0;
}

int ecs_has(EntityID e, ComponentMask mask) {
    return (entity_masks[e] & mask) == mask;
}

void ecs_add(EntityID e, ComponentMask mask) {
    entity_masks[e] |= mask; 
}

void ecs_remove(EntityID e, ComponentMask mask) {
    entity_masks[e] &= ~mask; 
}

ComponentMask ecs_register_component(size_t size) {
    if (next_bit >= MAX_COMPONENTS) return 0;
    void* data = malloc(size * MAX_ENTITIES);
    if (!data) return 0;
    pools[next_bit] = (ComponentPool){data, size};
    return 1ULL << next_bit++;
}

void* ecs_get_pool(ComponentMask mask) {
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (mask & (1ULL << i)) return pools[i].data;
    }
    return NULL;
}

void ecs_register_update(SystemFn fn, ComponentMask mask) {
    if (update_count >= MAX_SYSTEMS) return;
    update_systems[update_count++] = (System){fn, mask};
}

void ecs_run_update() {
    for (int s = 0; s < update_count; s++) {
        System* sys = &update_systems[s];
        for (EntityID e = 0; e < (EntityID)next_entity; e++) {
            if (ecs_has(e, sys->mask)) {
                sys->fn(e);
            }
        }
    }
}

