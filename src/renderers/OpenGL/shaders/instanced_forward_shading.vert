//! #include "common/version.glsl"
//! #include "common/math.glsl"
//! #include "common/uniform.glsl"
//! #include "common/shadows.glsl"

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec3 in_Tangent;
layout(location = 3) in vec3 in_Bitangent;
layout(location = 4) in vec2 in_TextureCoords;
// -- ?
layout(location = 5) in ivec4 in_JointIndices;
layout(location = 6) in vec4 in_Weights;
// --
layout(location = 7) in mat4 in_InstanceModel;
layout(location = 11) in unsigned int in_Highlight;

out VS_OUT {
    vec3 VertexPosition;
    vec3 Normal;
    vec3 CascadeBlend;
    vec2 TextureCoords;
    mat3 TBN;
    unsigned int Highlight;
} vs_out; 

void main()
{
    mat4 InstanceModel = transpose(in_InstanceModel);

    vec3 T = normalize(vec3(InstanceModel * vec4(in_Tangent, 0.f)));
    vec3 B = normalize(vec3(InstanceModel * vec4(in_Bitangent, 0.f)));
    vec3 N = normalize(vec3(InstanceModel * vec4(in_Normal, 0.f)));
    
    vs_out.VertexPosition = (InstanceModel * vec4(in_Position, 1.f)).xyz;
    vs_out.Normal = mat3(transpose(inverse(InstanceModel))) * in_Normal;
    vs_out.TextureCoords = in_TextureCoords;
    vs_out.Highlight = in_Highlight;
    vs_out.TBN = mat3(T, B, N);

    vec4 p = InstanceModel * vec4(in_Position, 1.f);

    vec3 n = u_CameraDirection;
    vec3 c = u_CameraPosition;

    vec4 f1;
    f1.xyz = n;
    f1.w = -dot(n, c) - u_CascadeBounds[1].x;
    f1 *= (1.f / (u_CascadeBounds[0].y - u_CascadeBounds[1].x));

    vec4 f2;
    f2.xyz = n;
    f2.w = -dot(n, c) - u_CascadeBounds[2].x;
    f2 *= (1.f / (u_CascadeBounds[1].y - u_CascadeBounds[2].x));

    vec4 f3;
    f3.xyz = n;
    f3.w = -dot(n, c) - u_CascadeBounds[3].x;
    f3 *= (1.f / (u_CascadeBounds[2].y - u_CascadeBounds[3].x));

    vec3 u;
    u.x = dot(f1, p);
    u.y = dot(f2, p);
    u.z = dot(f3, p);

    vs_out.CascadeBlend = u;

    gl_Position = u_Projection * u_View * p;
}