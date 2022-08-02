#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 Model;

in vec2 gtexCoord[];
in vec3 gnormCoord[];
in vec3 gWorldPos[];
uniform mat4 MVP;

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
   vec3 tangentNormPos;
} gs_out;

in DATA {
   vec3 normal;
   vec2 texCoord;
   mat4 camProj;
   mat4 modelProj;
   vec3 lightPos;
   vec3 camPos;
} data_in[];

void main(void)
{
   // Calculate Normal Map stuff
   // Edges of the triangle
   vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
   vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
   // Lengths of UV differences
   vec2 deltaUV0 = data_in[1].texCoord - data_in[0].texCoord;
   vec2 deltaUV1 = data_in[2].texCoord - data_in[0].texCoord;

   // one over the determinant
   float invDet = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

   vec3 tangent = vec3(invDet * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
   vec3 bitangent = vec3(invDet * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));

   vec3 T = normalize(vec3(data_in[0].modelProj * vec4(tangent, 0.0f)));
   vec3 B = normalize(vec3(data_in[0].modelProj * vec4(bitangent, 0.0f)));
   vec3 N = normalize(vec3(data_in[0].modelProj * vec4(cross(edge0, edge1), 0.0f)));

   mat3 TBN = mat3(T, B, N);
   // TBN is an orthogonal matrix and so its inverse is equal to its transpose
   TBN = transpose(TBN);
   gs_out.TBN = TBN;

   // send data to Fragment Shader
   gl_Position = data_in[0].camProj * gl_in[0].gl_Position;
   gs_out.tangentNormPos = data_in[0].normal;
   texCoord = data_in[0].texCoord;
   gs_out.tangentFragPos = TBN * gl_in[0].gl_Position.xyz;
   gs_out.tangentViewPos = TBN * data_in[0].camPos;
   gs_out.tangentLightPos = TBN * data_in[0].lightPos;
   EmitVertex();

   gl_Position = data_in[1].camProj * gl_in[1].gl_Position;
   gs_out.tangentNormPos = data_in[1].normal;
   texCoord = data_in[1].texCoord;
   gs_out.tangentFragPos = TBN * gl_in[1].gl_Position.xyz;
   gs_out.tangentViewPos = TBN * data_in[1].camPos;
   gs_out.tangentLightPos = TBN * data_in[1].lightPos;
   EmitVertex();

   gl_Position = data_in[2].camProj * gl_in[2].gl_Position;
   gs_out.tangentNormPos = data_in[2].normal;
   texCoord = data_in[2].texCoord;
   gs_out.tangentFragPos = TBN * gl_in[2].gl_Position.xyz;
   gs_out.tangentViewPos = TBN * data_in[2].camPos;
   gs_out.tangentLightPos = TBN * data_in[2].lightPos;
   EmitVertex();
   EndPrimitive();
};
