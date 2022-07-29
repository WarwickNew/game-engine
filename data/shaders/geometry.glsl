#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 Model;

in vec2 gtexCoord[];
in vec3 gnormCoord[];
in vec3 gWorldPos[];

out vec2 texCoord;
out vec3 normCoord;
out vec3 WorldPos;

vec3 lightPosition = vec3(1, 1, 2);

uniform vec3 CameraPos;

out GS_OUT {
   mat3 TBN;
   vec3 tangentLightPos;
   vec3 tangentViewPos;
   vec3 tangentFragPos;
} gs_out;

void main(void)
{
   // Calculate Normal Map stuff

   // Edges of the triangle
   vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
   vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
   // Lengths of UV differences
   vec2 deltaUV0 = gtexCoord[1] - gtexCoord[0];
   vec2 deltaUV1 = gtexCoord[2] - gtexCoord[0];

   // one over the determinant
   float invDet = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

   vec3 tangent = vec3(invDet * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
   vec3 bitangent = vec3(invDet * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));

   //Calculate TBN
   //mat3 normalMatrix = transpose(inverse(mat3(Model)));

   vec3 T = normalize(vec3(Model * vec4(tangent, 0.0f)));
   vec3 B = normalize(vec3(Model * vec4(bitangent, 0.0f)));
   vec3 N = normalize(vec3(Model * vec4(cross(edge1, edge0), 0.0f)));

   mat3 TBN = transpose(mat3(T, B, N));
   gs_out.TBN = TBN;

   gs_out.tangentLightPos = TBN * lightPosition;
   gs_out.tangentViewPos = TBN * CameraPos;
   gs_out.tangentFragPos = TBN * gWorldPos[0];

   // send data to Fragment Shader
   gl_Position = gl_in[0].gl_Position;
   texCoord = gtexCoord[0];
   normCoord = gnormCoord[0];
   WorldPos = gWorldPos[0];
   EmitVertex();

   gl_Position = gl_in[1].gl_Position;
   texCoord = gtexCoord[1];
   normCoord = gnormCoord[1];
   WorldPos = gWorldPos[1];

   gs_out.tangentFragPos = TBN * gWorldPos[1];
   EmitVertex();

   gl_Position = gl_in[2].gl_Position;
   texCoord = gtexCoord[2];
   normCoord = gnormCoord[2];
   WorldPos = gWorldPos[2];

   gs_out.tangentFragPos = TBN * gWorldPos[2];
   EmitVertex();
   EndPrimitive();
};
