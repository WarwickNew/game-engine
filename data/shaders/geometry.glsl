#version 330 core
layout (triangles) in;
layout (triangle_strip) out;

in vec2 gtexCoord[];
in vec3 gnormCoord[];
in vec3 gWorldPos[];

out vec2 texCoord;
out vec3 normCoord;
out vec3 WorldPos;

void main()
{
   gl_Position = gl_in[0].gl_Position;
   texCoord = gtexCoord[0];
   normCoord = gnormCoord[0];
   WorldPos = gWorldPos[0];
   EmitVertex();

   gl_Position = gl_in[1].gl_Position;
   texCoord = gtexCoord[1];
   normCoord = gnormCoord[1];
   WorldPos = gWorldPos[1];
   EmitVertex();

   gl_Position = gl_in[2].gl_Position;
   texCoord = gtexCoord[2];
   normCoord = gnormCoord[2];
   WorldPos = gWorldPos[2];
   EmitVertex();
   EndPrimitive();
};
