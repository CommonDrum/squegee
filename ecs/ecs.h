#pragma once 

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint32_t EntityID;
typedef uint64_t ComponentMask;
typedef void (*SystemFn)(EntityID);

typedef struct{
    void* data;
    size_t size;
} ComponentPool; 

typedef struct {
    SystemFn fn;
    ComponentMask mask;
} System;//TODO: Local enitites? 


EntityID ecs_entity_create();
void     ecs_entity_destroy(EntityID e); //TODO: add list of free ents

ComponentMask ecs_register_component(size_t size);
void*         ecs_get_pool(ComponentMask mask);
int           ecs_has(EntityID e, ComponentMask mask);
void          ecs_add(EntityID e, ComponentMask mask);
void          ecs_remove(EntityID e, ComponentMask mask);

void ecs_register_update(SystemFn fn, ComponentMask mask);
void ecs_run_update();

