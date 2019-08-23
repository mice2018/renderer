#ifndef SCENE_H
#define SCENE_H

#include "geometry.h"
#include "graphics.h"
#include "mesh.h"
#include "skeleton.h"
#include "texture.h"

typedef struct {
    float frame_time;
    float delta_time;
    vec3_t light_dir;
    vec3_t camera_pos;
    mat4_t light_view_matrix;
    mat4_t light_proj_matrix;
    mat4_t camera_view_matrix;
    mat4_t camera_proj_matrix;
    float ambient_intensity;
    float punctual_intensity;
    texture_t *shadow_map;
    int layer_view;
} framedata_t;

typedef struct model {
    mesh_t *mesh;
    program_t *program;
    mat4_t transform;
    /* animation */
    skeleton_t *skeleton;
    int attached;
    /* sorting */
    int opaque;
    float distance;
    /* polymorphism */
    void (*update)(struct model *model, framedata_t *framedata);
    void (*draw)(struct model *model, framebuffer_t *framebuffer,
                 int shadow_pass);
    void (*release)(struct model *model);
} model_t;

typedef struct {
    vec4_t background;
    model_t *skybox;
    model_t **models;
    /* light intensity */
    float ambient_intensity;
    float punctual_intensity;
    /* shadow mapping */
    framebuffer_t *shadow_buffer;
    texture_t *shadow_map;
} scene_t;

scene_t *scene_create(vec3_t background, model_t *skybox, model_t **models,
                      float ambient_intensity, float punctual_intensity,
                      int with_shadow);
void scene_release(scene_t *scene);
void scene_draw(scene_t *scene, framebuffer_t *framebuffer,
                framedata_t *framedata);

#endif
