//! #include "common/version.glsl"
//! #include "common/constants.glsl"
//! #include "common/math.glsl"
//! #include "common/uniform.glsl"

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

out GS_OUT 
{
    vec2 TextureCoords;
} gs_out; 

uniform vec2 u_Size;
uniform vec3 u_CameraXAxis;
uniform vec3 u_CameraYAxis;

void main()
{
    vec3 Center = gl_in[0].gl_Position.xyz;
    vec2 HalfSize = u_Size / 2.f;
    vec3 xAxis = u_CameraXAxis;
    vec3 yAxis = u_CameraYAxis;

    // Bottom-left
    {
        vec3 VertexPosition = Center - xAxis * HalfSize.x - yAxis * HalfSize.y;
        gl_Position = u_ViewProjection * vec4(VertexPosition, 1.f);

        vec2 TextureCoords = vec2(0.f, 1.f);
        gs_out.TextureCoords = TextureCoords;

        EmitVertex();
    }

    // Bottom-right
    {
        vec3 VertexPosition = Center + xAxis * HalfSize.x - yAxis * HalfSize.y;
        gl_Position = u_ViewProjection * vec4(VertexPosition, 1.f);

        vec2 TextureCoords = vec2(1.f, 1.f);
        gs_out.TextureCoords = TextureCoords;

        EmitVertex();
    }

    // Top-left
    {
        vec3 VertexPosition = Center - xAxis * HalfSize.x + yAxis * HalfSize.y;
        gl_Position = u_ViewProjection * vec4(VertexPosition, 1.f);

        vec2 TextureCoords = vec2(0.f, 0.f);
        gs_out.TextureCoords = TextureCoords;

        EmitVertex();
    }

    // Top-right
    {
        vec3 VertexPosition = Center + xAxis * HalfSize.x + yAxis * HalfSize.y;
        gl_Position = u_ViewProjection * vec4(VertexPosition, 1.f);

        vec2 TextureCoords = vec2(1.f, 0.f);
        gs_out.TextureCoords = TextureCoords;

        EmitVertex();
    }
}
