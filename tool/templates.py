component_c = """
#include "{{component_name}}.h"

static ComponentMask mask = 0;

ComponentMask {{component_name}}_mask()
{
    if (mask == 0) mask = ecs_register_component(sizeof({{Component_name}}));
    return mask;
}
{{Component_name}}* {{component_name}}_get(EntityID e) {
    {{Component_name}}* pool = ({{Component_name}}*)ecs_get_pool({{component_name}}_mask());
    return &pool[e];
}

void {{component_name}}_add(EntityID e) {
    ecs_add(e, {{component_name}}_mask());
}
"""

component_h = """
#pragma once
#include "ecs.h"

typedef struct {
    // Your component code here
} {{Component_name}};

ComponentMask {{component_name}}_mask();
{{Component_name}}* {{component_name}}_get(EntityID e);
void {{component_name}}_add(EntityID e);
"""

system_h = """
#pragma once
#include "ecs.h"

void {{system_name}}_system_register();
"""

system_c = """
#include "{{system_name}}.h"

static void {{system_name}}_update(EntityID e) {
    // Your system code here
    (void)e;
}

void {{system_name}}_system_register() {
    ecs_register_update({{system_name}}_update, 0);
}
"""
