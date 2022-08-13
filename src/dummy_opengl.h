#pragma once

#define WIN32_RELOADABLE_SHADERS 1

#define OPENGL_MAX_MESH_BUFFER_COUNT 256
#define OPENGL_MAX_SKINNED_MESH_BUFFER_COUNT 32
#define OPENGL_MAX_TEXTURE_COUNT 64
#define OPENGL_MAX_SHADER_COUNT 64

#define OPENGL_SIMPLE_SHADER_ID 0x1
#define OPENGL_PHONG_SHADING_SHADER_ID 0x2
#define OPENGL_SKINNED_PHONG_SHADING_SHADER_ID 0x3
#define OPENGL_FRAMEBUFFER_SHADER_ID 0x4
#define OPENGL_GROUND_SHADER_ID 0x5
#define OPENGL_INSTANCED_PHONG_SHADING_SHADER_ID 0x6

#define OPENGL_MAX_POINT_LIGHT_COUNT 8

struct opengl_mesh_buffer
{
    u32 Id;
    u32 VertexCount;
    u32 IndexCount;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    u32 BufferSize;
};

struct opengl_skinned_mesh_buffer
{
    opengl_mesh_buffer *Buffer;

    GLuint SkinningTBO;
    GLuint SkinningTBOTexture;
};

struct opengl_texture
{
    u32 Id;
    GLuint Handle;
};

#define MAX_SHADER_FILE_PATH 64

struct opengl_shader
{
    u32 Id;
    GLuint Program;

    char VertexShaderFileName[MAX_SHADER_FILE_PATH];
    char FragmentShaderFileName[MAX_SHADER_FILE_PATH];

#if WIN32_RELOADABLE_SHADERS
    FILETIME LastVertexShaderWriteTime;
    FILETIME LastFragmentShaderWriteTime;
#endif

    GLint ModelUniformLocation;
    GLint SkinningMatricesSamplerUniformLocation;

    GLint ColorUniformLocation;

    GLint MaterialSpecularShininessUniformLocation;
    GLint MaterialAmbientColorUniformLocation;
    GLint MaterialDiffuseColorUniformLocation;
    GLint MaterialSpecularColorUniformLocation;
    GLint MaterialDiffuseMapUniformLocation;
    GLint MaterialSpecularMapUniformLocation;
    GLint MaterialShininessMapUniformLocation;
    GLint MaterialNormalMapUniformLocation;

    GLint MaterialHasDiffuseMapUniformLocation;
    GLint MaterialHasSpecularMapUniformLocation;
    GLint MaterialHasShininessMapUniformLocation;
    GLint MaterialHasNormalMapUniformLocation;

    GLint DirectionalLightDirectionUniformLocation;
    GLint DirectionalLightColorUniformLocation;

    GLint PointLightCountUniformLocation;

    GLint ScreenTextureUniformLocation;
    GLint BlinkUniformLocation;
};

struct opengl_shader_state
{
    mat4 Projection;
    mat4 View;
    alignas(16) vec3 CameraPosition;
    alignas(16) vec3 CameraDirection;
    f32 Time;
    f32 RenderShadowMap;
};

struct opengl_render_options
{
    b32 RenderShadowMap;
    b32 ShowCascades;
    mat4 CascadeView;
    mat4 CascadeProjection;
    u32 CascadeIndex;
};

#define CASCADE_COUNT 4

struct cascaded_shadow_maps
{
    vec4 ShadowOffset[2];
    vec3 CascadeScale[3];
    vec3 CascadeOffset[3];
    vec2 CascadeBounds[4];
    mat4 CascadeViewProjection[4];
    mat4 CascadeViewTexture0;
};

struct opengl_state
{
    char *Vendor;
    char *Renderer;
    char *Version;
    char *ShadingLanguageVersion;

    u32 WindowWidth;
    u32 WindowHeight;

    memory_arena Arena;
    platform_api *Platform;

    GLuint MultiSampledFBO;
    GLuint MultiSampledColorTexture;
    GLuint MultiSampledDepthTexture;

    GLuint SingleSampledFBO;
    GLuint SingleSampledColorTexture;
    GLuint SingleSampledDepthTexture;

    GLuint ShadowMapFBO;
    GLuint ShadowMapTextures[4];

    GLuint LineVAO;
    GLuint RectangleVAO;

    GLuint ShaderStateUBO;

    u32 CurrentMeshBufferCount;
    opengl_mesh_buffer MeshBuffers[OPENGL_MAX_MESH_BUFFER_COUNT];

    u32 CurrentSkinnedMeshBufferCount;
    opengl_skinned_mesh_buffer SkinnedMeshBuffers[OPENGL_MAX_SKINNED_MESH_BUFFER_COUNT];

    u32 CurrentTextureCount;
    opengl_texture Textures[OPENGL_MAX_TEXTURE_COUNT];

    u32 CurrentShaderCount;
    opengl_shader Shaders[OPENGL_MAX_SHADER_COUNT];

    u32 ShadowMapSize;
    cascaded_shadow_maps Csm;
};
