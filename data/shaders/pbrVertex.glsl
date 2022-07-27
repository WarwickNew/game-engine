#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;
uniform mat4 Model;

out vec2 gtexCoord;
out vec3 gnormCoord;

//Pbr
out vec3 gWorldPos;

void main()
{
   gl_Position = MVP * Model * vec4(aPos, 1.0);
   gnormCoord = aNormal;
   gtexCoord = aTexCoord;

   // Calculate position of fragment
   gWorldPos = vec3(Model * vec4(aPos, 1.0));
};
