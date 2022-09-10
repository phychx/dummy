#pragma once

#define GAME_PROCESS_ON_UPDATE(Name) void Name(struct game_state *State, struct game_process *Process, f32 Delta)
typedef GAME_PROCESS_ON_UPDATE(game_process_on_update);

enum game_mode
{
    GameMode_None,
    GameMode_World,
    GameMode_Menu,
    GameMode_Edit
};

struct game_entity
{
    transform Transform;

    model *Model;
    rigid_body *Body;
    animation_graph *Animation;

    b32 Controllable;   // todo: come up with smth better
    b32 FutureControllable;   // todo: come up with smth better
    b32 DebugView;
};

struct entity_render_batch
{
    char Name[256];
    u32 EntityCount;
    u32 MaxEntityCount;
    game_entity **Entities;
    render_instance *Instances;
    model *Model;
};

struct game_process
{
    char Name[256];
    game_process_on_update *OnUpdatePerFrame;
    game_process *Child;

    game_process *Prev;
    game_process *Next;
};

struct game_asset
{
    char Name[32];
    char Path[32];
    // todo:
    u32 MaxInstanceCount;
};


struct game_assets
{
    hash_table<model> Models;
};

struct game_options
{
    b32 ShowCascades;
    b32 ShowRigidBodies;
};

struct game_menu_quad
{
    vec4 Color;
    u32 Corner;
    f32 Move;
};

struct game_state
{
    memory_arena PermanentArena;
    memory_arena TransientArena;

    job_queue *JobQueue;

    game_mode Mode;
    game_input Input;

    vec2 ViewFrustrumSize;

    game_camera FreeCamera;
    game_camera PlayerCamera;

    polyhedron Frustrum;

    plane Ground;

    game_assets Assets;
    animator Animator;

    u32 EntityCount;
    u32 MaxEntityCount;
    game_entity *Entities;

    hash_table<entity_render_batch> EntityBatches;

    u32 PointLightCount;
    point_light *PointLights;

    directional_light DirectionalLight;

    hash_table<game_process> Processes;
    // linked-list (for efficient adding/removal and traversing)
    game_process ProcessSentinel;

    game_entity *Player;
    game_entity *Pelegrini;
    game_entity *MarkerMan;
    game_entity *xBot;
    game_entity *yBot;
    game_entity *Skulls[2];
    game_entity *Dummy;
    game_entity *Cubes[16];

    vec2 CurrentMove;
    vec2 TargetMove;

    random_sequence Entropy;

    vec3 BackgroundColor;

    b32 IsBackgroundHighlighted;

    // for testing purpuses
    f32 DelayTime;
    f32 DelayDuration;

    game_options Options;
    game_menu_quad MenuQuads[4];
};
