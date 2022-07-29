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

   // Real space triangle
   vec3 p1 = gl_in[0].gl_Position.xyz;
   vec3 p2 = gl_in[1].gl_Position.xyz;
   vec3 p3 = gl_in[2].gl_Position.xyz;

   // Normal texture space triangle
   vec2 uv1 = gtexCoord[0];
   vec2 uv2 = gtexCoord[1];
   vec2 uv3 = gtexCoord[2];

   // Calculate edge translation vectors duv stands for delta uv
   vec3 edge1 = p2 - p1;
   vec3 edge2 = p3 - p1;
   vec2 duv1 = uv2 - uv1;
   vec2 duv2 = uv3 - uv1;

   // Calculation of tangents and bi tangents
   // [ddTxBxTyByTzBz]=1ΔU1ΔV2−ΔU2ΔV1[ΔV2−ΔU2−ΔV1ΔU1][E1xE2xE1yE2yE1zE2z]
   // https://learnopengl.com/Advanced-Lighting/Normal-Mapping

   float invDet = 1.0 / (duv1.x * duv2.y - duv2.x * duv1.y);

   vec3 tangent = vec3 (invDet * (duv2.y * edge1 - duv1.y * edge2));
   vec3 bitangent = vec3 (invDet * (-duv2.x * edge1 - duv1.x * edge2));

   //Calculate TBN
   //mat3 normalMatrix = transpose(inverse(mat3(Model)));

   vec3 T = normalize(vec3(Model * vec4(tangent, 0.0f)));
   vec3 B = normalize(vec3(Model * vec4(bitangent, 0.0f)));
   vec3 N = normalize(vec3(Model * vec4(cross(edge2, edge1), 0.0f)));

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
